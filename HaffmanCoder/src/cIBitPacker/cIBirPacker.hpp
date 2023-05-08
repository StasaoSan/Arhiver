#ifndef UNTITLED1_C_I_BIT_PACKER_HPP_
#define UNTITLED1_C_I_BIT_PACKER_HPP_

#include "HaffmanTree.h"

#include <list>

class cIBitPacker
{
public:
    using symbol_t = cHaffmapTree::symbol_t;
    using symbolArray_t = cHaffmapTree::symbolArray_t;
    using dynamicBitset_t = cHaffmapTree::dynamicBitset_t;
    using mapSym2Code_t = cHaffmapTree::mapSym2Code_t;
    using bitsize_t = std::size_t;

 cIBitPacker( const mapSym2Code_t &mappa, symbolArray_t &storage ) :
        mMapSym( mappa ),
        mResult( storage ){}

    virtual ~cIBitPacker() {};

protected:
    virtual void pack() = 0;

    virtual std::list< symbol_t > getBytes( const dynamicBitset_t &data );
    virtual void addByte( symbol_t bt, bitsize_t sz);

    const mapSym2Code_t &mMapSym;
    symbolArray_t &mResult;
    unsigned crntShift{ 0 };
    symbol_t crntByte{ 0 };
};


class cIBitUnpack{
public:
    using symbol_t = cHaffmapTree::symbol_t;
    using symbolArray_t = cHaffmapTree::symbolArray_t;
    using dynamicBitset_t = cHaffmapTree::dynamicBitset_t;
    using mapSym2Code_t = cHaffmapTree::mapSym2Code_t;
    using bitsize_t = std::size_t;
    cIBitUnpack(const cHaffmapTree::symbolArray_t &bytes,
                cHaffmapTree::mapSym2Code_t &mappa, int LenHead): mHeadLen(LenHead),
                                                                  data(bytes),
                                                                  MapSym(mappa){};
    virtual ~cIBitUnpack(){};
protected:
    virtual void unpack() = 0;
    cHaffmapTree::dynamicBitset_t GetNextCode(int BitSize);

    const int mHeadLen;
    unsigned crntShift = 0; /// 0...7
    cHaffmapTree::symbol_t crntByte = 0;
    const cHaffmapTree::symbolArray_t &data;
    cHaffmapTree::mapSym2Code_t &MapSym;
};
#endif // UNTITLED1_C_I_BIT_PACKER_HPP_
