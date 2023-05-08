#ifndef UNTITLED1_HAFFMAN_CODER_H
#define UNTITLED1_HAFFMAN_CODER_H

#include "cICoder.hpp"
#include "cIBirPacker.hpp"


class cHaffmanCoder : public cICoder
{
public:
    symbolArray_t code( const symbolArray_t &data ) override;
    symbolArray_t decode( const symbolArray_t &data ) override;

private:
    class cDataPacker : public cIBitPacker
    {
    public:
        cDataPacker(const mapSym2Code_t &mappa, const symbolArray_t &data, symbolArray_t &storage ) :
            cIBitPacker( mappa, storage ),
            mrData( data ) { pack(); };

        virtual void pack() override;

    private:
        const symbolArray_t & mrData;
    };

    class cDataUnpacker : public cIBitUnpack{
    public:
        cDataUnpacker(const cHaffmapTree::symbolArray_t &bytes,
                      cHaffmapTree::mapSym2Code_t &mappa, int LenHead, symbolArray_t &ExitData) :
                cIBitUnpack(bytes,mappa, LenHead), mrExitData(ExitData) { unpack(); };

        void unpack() override;


    private:
        symbolArray_t &mrExitData;
    };

};



#endif // UNTITLED1_HAFFMAN_CODER_H
