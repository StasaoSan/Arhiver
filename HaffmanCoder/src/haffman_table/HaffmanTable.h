//
// Created by Тихонов Александр on 02.02.2023.
//
#ifndef UNTITLED1_HAFFMANTABLE_H
#define UNTITLED1_HAFFMANTABLE_H

#include "HaffmanTree.h"
#include "cIBirPacker.hpp"

#include <list>


class cHaffmanTable{
public:
    static cHaffmapTree::symbolArray_t Tree2Bytes(const cHaffmapTree::mapSym2Code_t &mapsym);

    static cHaffmapTree::mapSym2Code_t Bytes2Tree(const cHaffmapTree::symbolArray_t &symarr);

private:
    using bitsize_t = std::size_t;


    class cHeaderPacker : public cIBitPacker
    {
    public:
        cHeaderPacker(const mapSym2Code_t &mappa, symbolArray_t &storage ) :
            cIBitPacker( mappa, storage ) { pack(); };
    private:
        virtual void pack() override;
    };

    /// @todo
    class cHeaderUnpacker : public cIBitUnpack {
    public:
        cHeaderUnpacker(const cHaffmapTree::symbolArray_t &bytes,
                 cHaffmapTree::mapSym2Code_t &mappa, int LenHead) : cIBitUnpack(bytes, mappa, LenHead) {unpack();};
    private:
        void unpack() override;
    };
};


#endif //UNTITLED1_HAFFMANTABLE_H
