 #include "cIBirPacker.hpp"


std::list<cIBitPacker::symbol_t> cIBitPacker::getBytes( const dynamicBitset_t &data )
{
    std::list< symbol_t > resultList{};

    uint8_t vecByte = 0;

    for (unsigned pos = 0, count = 0; pos < data.size(); ++pos, ++count)
    {
        vecByte |= data[ pos ] << count;

        if ((count % 7) == 0 && count != 0) {
            resultList.emplace_back(vecByte);
            vecByte = 0;
            count = -1;
        }
    }

    resultList.emplace_back(vecByte);

    return resultList;
}

void cIBitPacker::addByte(symbol_t bt, bitsize_t sz)
{
    // Осталось свободных мест в байте
    auto rem = 8 - crntShift;

    if( sz > rem ) /// @todo при условии 8 максимум
    {
        crntByte |= bt << crntShift;
        mResult.emplace_back( crntByte );
        crntShift = crntByte = 0;
        bt >>= rem; /// @todo Можно удалить
        sz -= rem;
        rem = 8;
    }

    crntByte |= bt << crntShift;
    crntShift += sz;
}

 cHaffmapTree::dynamicBitset_t cIBitUnpack::GetNextCode(int BitSize) {
     /// @bug rem <= 0?

     static int BitCodeStartInd = data[0]*2 + 1;

     int rem = 8 - crntShift;

     int byte = BitCodeStartInd + crntByte;

     cHaffmapTree::dynamicBitset_t ResBit;

     auto push2ResBit = [ & ] ( unsigned count )
     {
         for (unsigned i = crntShift; i < crntShift + count; ++i)
         {
             ResBit.emplace_back( 1 & ( data[ byte ] >> i ) );
         }
         crntShift += count;
         rem -= count;
         BitSize -= count;

         if( 0 == rem )
         {
             crntShift = 0;
             rem = 8;
             byte += 1;
             crntByte += 1;
         }
     };

     while( BitSize )
     {
         unsigned bound = BitSize < rem ? BitSize : rem;
         push2ResBit( bound );
     }

     assert( ( rem >= 0 ) && "Something wrong with remainder logic...");

     return ResBit;
}
