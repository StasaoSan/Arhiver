#ifndef UNTITLED1_C_I_CODER_HPP
#define UNTITLED1_C_I_CODER_HPP

#include <cstdint>
#include <vector>
#include <unordered_map>

class cICoder
{
public:
    using symbol_t = uint8_t;
    using symbolArray_t = std::vector< symbol_t >;
    using dynamicBitset_t = std::vector< bool >;
    using mapSym2Code_t = std::unordered_map< symbol_t , dynamicBitset_t >;

    virtual ~cICoder() {}

    virtual symbolArray_t code( const symbolArray_t &data ) = 0;
    virtual symbolArray_t decode( const symbolArray_t &data ) = 0;
};





#endif // UNTITLED1_C_I_CODER_HPP
