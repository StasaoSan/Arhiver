//
// Created by Тихонов Александр on 02.02.2023.
//
#include <list>
#include <iostream>
#include <cmath>
#include <cassert>

#include "HaffmanTable.h"


using bitsSize_t = uint8_t;


cHaffmapTree::symbolArray_t cHaffmanTable::Tree2Bytes(const cHaffmapTree::mapSym2Code_t &mapsym){
    cHaffmapTree::symbolArray_t resData{};

    resData.reserve( mapsym.size() * 2 );
    resData.emplace_back( mapsym.size() );

    for (const auto &it : mapsym)
    {
        resData.emplace_back( it.first );
        resData.emplace_back( it.second.size() );
    }

    cHeaderPacker p(mapsym, resData);
    return resData;
}

//@todo проверка корректности
 cHaffmapTree::mapSym2Code_t cHaffmanTable::Bytes2Tree(const cHaffmapTree::symbolArray_t &symarr){
    cHaffmapTree::mapSym2Code_t resData;
    resData.reserve(symarr[0]*2);
    int LenHead = symarr[0]*2+1;
    int tempLenBits = 0;
     for (int i = 1; i < LenHead; ++i) {
         if (i % 2 == 0){
             tempLenBits +=symarr[i];
         }
     }
     int tempLenBytes = std::ceil(tempLenBits / 8.0);
     LenHead+=tempLenBytes;
//     std::cout<<"\n"<<std::dec<<LenHead<<"\n";
    cHeaderUnpacker(symarr, resData, LenHead);
     return resData;
}

/// @todo проверка корректности
 void cHaffmanTable::cHeaderPacker::pack() {
     for (const auto &it : mMapSym )
     {
         const auto crntByteList = getBytes( it.second );

         auto sz = it.second.size();
         for( const auto &crntByte : crntByteList )
         {
             sz > 8 ? addByte( crntByte, 8 )
                    : addByte( crntByte, sz );
             sz -= 8;
         }
     }

     mResult.emplace_back( crntByte );
     crntShift = crntByte = 0;
 }





////@todo проверить)
void cHaffmanTable::cHeaderUnpacker::unpack() {
    //идем до symarr[0] * 2
    //добавляем в map символ и через какую то функцию (обращаемся к информации байта в конце) вытащить значение
    //      этого символа
    //цикл по всем символам => добавлять в mapsym + 2й эл-т от GetNextCode
    for (int i = 1; i <= data[0] * 2; i+=2) {
        MapSym.insert(std::make_pair(data[i], GetNextCode(data[i+1])));
    }
}

//unsigned crntShift = 0; /// 0...7
//cHaffmapTree::symbol_t crntByte = 0;
////
//const cHaffmapTree::symbolArray_t &data;
