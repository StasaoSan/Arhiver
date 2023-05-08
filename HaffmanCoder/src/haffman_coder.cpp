#include "haffman_coder.h"

#include "HaffmanTree.h"
#include "HaffmanTable.h"

#include <iostream>

cICoder::symbolArray_t cHaffmanCoder::code( const cICoder::symbolArray_t &data )
{
    std::cout << "Init msg: ";
    for( const auto &it : data )
    {
        std::cout << it;
    } std::cout << std::endl;

    /// @todo логика, исключения, проверки, использование внутреннего tree?
    cHaffmapTree tree( data );
    auto mapSym2Code( tree.getSym2Code() );

    for (const auto &it: mapSym2Code )
    {
        std::cout<<it.first << "   ";
        for (const auto &it2 : it.second) {
            std::cout<<it2;
        }
        std::cout<<"\n";
    }

    auto header = cHaffmanTable::Tree2Bytes( mapSym2Code );

    std::cout<<"Header: ";
    for (const auto &it : header) {
        std::cout<<std::hex<<"0x"<<(int)it<<" ";
    } std::cout<<"\n";

    cDataPacker p(mapSym2Code, data, header);
    return header;
}

cICoder::symbolArray_t cHaffmanCoder::decode(const cICoder::symbolArray_t &data)
{
    cHaffmapTree::mapSym2Code_t mapCode = cHaffmanTable::Bytes2Tree( data );
    symbolArray_t Data;
    cDataUnpacker(data, mapCode, 0, Data);
    return Data;
}

/* --- cDataPacker implementation ------------------------------------------- */

void cHaffmanCoder::cDataPacker::pack()
{
    symbol_t CountByte = 0x00;
    mResult.emplace_back(CountByte);
    auto ItMatterBit = mResult.end()-1;
    for (const auto &symbol : mrData )
    {
        const auto crntByteList = getBytes( mMapSym.at( symbol ) );

        auto sz = mMapSym.at( symbol ).size();
        for( const auto &crntByte : crntByteList )
        {
            sz > 8 ? addByte( crntByte, 8 )
                   : addByte( crntByte, sz );
            sz -= 8;
        }
    }

    *ItMatterBit = crntShift;
    mResult.emplace_back( crntByte );

    crntShift = crntByte = 0;
}

void cHaffmanCoder::cDataUnpacker::unpack()
{
    std::unordered_map<dynamicBitset_t , symbol_t> MapSymReverse;
    for (auto const &[key, val] : MapSym) {
        MapSymReverse[val] = key;
    }

    int BitCodeStartInd = 0;////@todo чет поплыло
    for (int i = 2; i <= data[0]*2; i += 2) {
        BitCodeStartInd += data[i];
    }

    int StartByte = (BitCodeStartInd / 8);
    if (BitCodeStartInd % 8){
        StartByte += 1;
    }

    StartByte += (data[0]*2)+1;
    int rem = 8 - crntShift;

    cHaffmapTree::dynamicBitset_t ResBit;

    for (int byte = StartByte + 1; byte < data.size(); ++byte) {
        int MostBit = byte != (data.size() - 1) ? 8 : data[StartByte];
        for (int bit = 0; bit < MostBit; ++bit) {
            ResBit.emplace_back( 1 & ( data[ byte ] >> bit ) );
            if (auto it = MapSymReverse.find(ResBit);  it != MapSymReverse.end()){
                mrExitData.emplace_back(it->second);
                ResBit.clear();
            }
        }
    }

//Разобрать на биты текущий байт
//Идя по биту, сохраняя в symArray-t (для случая когда код больше 8 бит) 
// проверяя наличие его в mapsym (где ключ - тот самый symArray-t)
//Если нашли - изменяем остаток, текущий бит (не всегда) и добавляем его в mrExitData


}
