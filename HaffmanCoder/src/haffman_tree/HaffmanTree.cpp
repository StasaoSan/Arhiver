//
// Created by Тихонов Александр on 30.01.2023.
//

#include <queue>
#include "HaffmanTree.h"

cHaffmapTree::cHaffmapTree(const cHaffmapTree::symbolArray_t &rawData) {
    if (rawData.size()) {
        buildTree(rawData);
        mSym2Code = createSymCode(mpTree);
    }
}

void cHaffmapTree::clear() {
    deleteTree(cHaffmapTree::mpTree);
    mSym2Code.clear();
}

cHaffmapTree::mapSym2Code_t cHaffmapTree::getSym2Code() const {
    return mSym2Code;
}

cHaffmapTree::mapSym2Code_t cHaffmapTree::getSym2Code(const cHaffmapTree::symbolArray_t &rawData) {
    buildTree(rawData);
    mSym2Code = createSymCode(mpTree);
    return mSym2Code;
}

cHaffmapTree::~cHaffmapTree() {
    deleteTree(cHaffmapTree::mpTree);
}

////**** PRIVATE METHODS ****////

std::unordered_map <cHaffmapTree::symbol_t, size_t>
        cHaffmapTree::countSymFreq(const cHaffmapTree::symbolArray_t &rawData) {

    std::unordered_map< symbol_t, size_t > symFreq;

    for( const auto & sym : rawData )
    {
        symFreq[ sym ]++;
    }

    return symFreq;
}

void cHaffmapTree::buildTree(const cHaffmapTree::symbolArray_t &rawData) {
    auto comparer = []( sNode* l, sNode* r ) { return l->mFreq > r->mFreq; };
    deleteTree(cHaffmapTree::mpTree);

    std::priority_queue< sNode *,
            std::deque< sNode * >,
            decltype ( comparer ) > prQu( comparer );

    for( const auto &pair : countSymFreq(rawData) )
    {
        prQu.push( new sNode( pair.first, pair.second ) );
    }

    while( prQu.size() > 1 )
    {
        /// Получение 2х узлов с наивысшим приоритетом
        auto left = prQu.top(); prQu.pop();
        auto right = prQu.top(); prQu.pop();

        /// Создание нового узла, частота которого равна сумме частот двух
        /// листьев
        const size_t sumFreq = left->mFreq + right->mFreq;
        prQu.push( new sNode( '\0', sumFreq, left, right ) );
    }

    mpTree = prQu.top();
}

//void cHaffmapTree::deleteTree(cHaffmapTree::sNode *parent) {
//    if (parent == nullptr){
//        return;
//    }
//    deleteTree( parent->mpLeft );
//    deleteTree( parent->mpRight );
//    if ( !parent->mpLeft && !parent->mpRight ) {
//        delete parent;
//        parent = nullptr;
//    }
//}

void cHaffmapTree::deleteTree(cHaffmapTree::sNode *parent) {
    if (parent == nullptr){
        return;
    }
    if (parent && parent->mpLeft) {
        sNode *child = parent->mpLeft;
        deleteTree(child);
        parent->mpLeft = nullptr;
        delete child;

        child = parent->mpRight;
        deleteTree(child);
        parent->mpRight = nullptr;
        delete child;
    }
    parent->mFreq = 0;
}

cHaffmapTree::mapSym2Code_t cHaffmapTree::createSymCode(sNode *node, const dynamicBitset_t &code) {
    if( !node )
    {
        return mapSym2Code_t();
    }

    static mapSym2Code_t sym2HfmnCode;

    if( code.empty() )
    {
        sym2HfmnCode.clear();
    }

    // Если лист - записываем код
    if ( !node->mpLeft && !node->mpRight )
    {
        if (!code.empty()){
            sym2HfmnCode[node->mSym] = code;
        }
        else {
            dynamicBitset_t NewCode(code); NewCode.emplace_back(0);
            sym2HfmnCode[ node->mSym ] = NewCode;
        }
    }
    else
    {
        dynamicBitset_t leftCode( code ); leftCode.emplace_back( 0 );
        dynamicBitset_t rightCode( code ); rightCode.emplace_back( 1 );

        createSymCode( node->mpLeft, leftCode );
        createSymCode( node->mpRight, rightCode );
    }

    return sym2HfmnCode;
}

