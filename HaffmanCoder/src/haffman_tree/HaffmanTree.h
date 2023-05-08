//
// Created by Тихонов Александр on 30.01.2023.
//
#ifndef UNTITLED1_HAFFMANTREE_H
#define UNTITLED1_HAFFMANTREE_H

#include <cstdint>
#include <vector>
#include <unordered_map>



class cHaffmapTree
{
public:
    using symbol_t = uint8_t;
    using symbolArray_t = std::vector< symbol_t >;
    using dynamicBitset_t = std::vector< bool >;
    using mapSym2Code_t = std::unordered_map< symbol_t , dynamicBitset_t >;

    /// @todo Весь функционал делать из конструктора
    /// @todo Конструктор по умолчанию
    cHaffmapTree( const symbolArray_t &rawData = symbolArray_t() );

    cHaffmapTree(cHaffmapTree &) = delete;
    cHaffmapTree(cHaffmapTree &&) = delete;

    cHaffmapTree &operator= (cHaffmapTree &) = delete;
    cHaffmapTree &operator= (cHaffmapTree &&) = delete;

    void clear();

    mapSym2Code_t getSym2Code() const;

    mapSym2Code_t getSym2Code(const symbolArray_t &rawData);

    ~cHaffmapTree();


private:
    struct sNode
    {
    public:
        /// @brief Конструктор
        /// \param [in] sym Символ
        /// \param [in] freq Частота символа в исходном тексте
        /// \param [in] left Левый лист
        /// \param [in] right Правый лист
        sNode( char sym,
               size_t freq,
               sNode *left = nullptr,
               sNode *right = nullptr ) :
                mSym( sym ),
                mFreq( freq ),
                mpLeft( left ),
                mpRight( right ) {}

        /// @brief Символ
        char mSym = '0';
        /// @brief Частота символа в исходном тексте
        size_t mFreq = 0;
        /// @brief Левый лист
        sNode *mpLeft = nullptr;
        /// @brief Правый лист
        sNode *mpRight = nullptr;
    };

    sNode *mpTree = nullptr;
    mapSym2Code_t mSym2Code;

    std::unordered_map< symbol_t, size_t > countSymFreq( const symbolArray_t &rawData );

    void buildTree( const symbolArray_t &rawData );
    void deleteTree(sNode *parent);

    mapSym2Code_t createSymCode(sNode *node, const dynamicBitset_t &code = dynamicBitset_t() );

};


#endif //UNTITLED1_HAFFMANTREE_H
