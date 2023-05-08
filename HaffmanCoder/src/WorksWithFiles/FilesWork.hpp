//
// Created by Тихонов Александр on 16.04.2023.
//

#ifndef MAIN_CPP_FILESWORK_HPP
#define MAIN_CPP_FILESWORK_HPP
#include <string_view>
#include <iostream>
#include <list>
#include <string>
#include <optional>
#include <fstream>
#include <filesystem>
#include "cICoder.hpp"

class cArhWork{
public:
    cArhWork(const std::filesystem::path &ArhName, cICoder &Coder);
    ~cArhWork();
    cArhWork(const cArhWork &) = delete;
    cArhWork(cArhWork &&) = delete;
    cArhWork& operator= (cArhWork &&) = delete;
    cArhWork& operator= (const cArhWork &) = delete;

    struct ArhInfo{
                        //название файла
                                        //размер файла
        std::list<std::pair<std::string, int64_t>> FileInArc;
        int64_t ArhSize; //размер архива //?возможно не надо?//
    };

    std::optional<ArhInfo> GetInfo();
    cArhWork& AddFile(const std::filesystem::path &FileName);
    cArhWork& DeleteFile(const std::filesystem::path &FileName);
    cArhWork& ExtractFile(const std::filesystem::path &FileName);
    cArhWork& ArhRename(const std::filesystem::path &NewName);

private:
    cICoder &mCoder;
    const static std::string SIGN;
    std::filesystem::path mArhName;
    std::fstream mFile;
    [[ nodiscard ]] bool CheckSignature();
    void InsertSignature();
};

#endif //MAIN_CPP_FILESWORK_HPP
