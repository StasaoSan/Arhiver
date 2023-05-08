#include "FilesWork.hpp"

const std::string cArhWork::SIGN = "ArchiverStasao ";

cArhWork::cArhWork(const std::filesystem::path &ArhName, cICoder &Coder):
    mArhName (ArhName),
    mCoder(Coder) {
    try {
        if (std::filesystem::exists(ArhName)){
            mFile.open(mArhName, std::fstream::in | std::fstream::out | std::fstream::binary);
            if (!CheckSignature()){
                throw std::runtime_error("Sign is not current");
            }

        }
        else{
            mFile.open(mArhName, std::ios::trunc | std::fstream::in | std::fstream::out | std::fstream::binary);
            if (!mFile.is_open()){
                std::cout<<"FIle doesn't open";
            }
            mFile<<SIGN;
        }
    }
    catch(...){
        std::cerr<<"Exception while conctruct file\n";
        throw;
    }
}
//H
//f1
//f2

cArhWork::~cArhWork() {
    mFile.close();
}

std::optional<cArhWork::ArhInfo> cArhWork::GetInfo() {
    if (!mFile.is_open() || false == CheckSignature()){
        std::cerr<<"In this archive files doesn't exist\n";
        return std::nullopt;
    }
    ArhInfo info;
    return info;
}

cArhWork &cArhWork::AddFile(const std::filesystem::path &FileName) {
    if (!std::filesystem::exists(FileName) || !mFile.is_open()){
        throw std::runtime_error("Error AddFile\n");
    }
    std::ifstream iNewFile(FileName, std::ios::binary);
    if (!iNewFile.is_open()){
        throw std::runtime_error("Error AddFile\n");
    }
    cICoder::symbolArray_t DataFile;
    while (!iNewFile.eof()){
        DataFile.emplace_back(iNewFile.get());
    }
    auto CodedData = mCoder.code(DataFile);
    mFile.seekp(SIGN.size(), std::fstream::beg);
    for (const auto &CodedByte : CodedData) {
        mFile.put(CodedByte);
    }
    iNewFile.close();
    return *this;
}

cArhWork &cArhWork::ExtractFile(const std::filesystem::path &FileName) {
    cICoder::symbolArray_t ExData;
    std::ofstream oExFile(FileName, std::ios::binary);
    if (!oExFile.is_open() || !mFile.is_open()){
        throw std::runtime_error("Error Extract\n");
    }
    mFile.clear();
    mFile.seekg(15, std::ios::beg);
    while (!mFile.eof()){
        cICoder::symbol_t ExSym;
        ExSym = mFile.get();
        ExData.emplace_back(ExSym);
    }
    auto DecData = mCoder.decode(ExData);
    for (const auto &it : DecData) {
        oExFile<<it;
    }
    oExFile.close();
    return *this;
}

bool cArhWork::CheckSignature() {
    if (!mFile.is_open()){
        return false;
    }
    mFile.seekg(0);
    std::string CurSign;
    mFile>>CurSign;
    CurSign += ' ';
    return SIGN == CurSign;
}
