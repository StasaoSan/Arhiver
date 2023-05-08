#include <iostream>
#include "HaffmanTree.h"
#include "HaffmanTable.h"
#include "cICoder.hpp"
#include "FilesWork.hpp"
#include "haffman_coder.h"

//@todo for debug (delete)
cHaffmapTree::symbolArray_t createCharArray(const std::string& input) {
    cHaffmapTree::symbolArray_t output;
    for (char ch : input) {
        output.push_back(ch);
    }
    return output;
}
//@todo for debug (delete)


int main( [[ maybe_unused ]] int argc, [[ maybe_unused ]] char **argv )
{
////    //@todo for debug (delete)
//    std::string input;
//    std::cout << "Введите строку: ";
//    std::cin >> input;
//    cHaffmapTree::symbolArray_t charArray = createCharArray(input);
////    //@todo for debug (delete)
//
//    cHaffmapTree::symbolArray_t data {'T', 'v', 'o', 'r', 'e', 'c', ' ', 'x', 'o', 't', 'e', 'l', ' ', 'd', 'o', 'b', 'r', 'a', ' ', 'l', 'u', 'd', 'i', 'm'};
//
//
   cHaffmanCoder coder;
////   auto res = coder.code( data );
//    auto res = coder.code( charArray );
//// @todo for debug (delete)
//
//   std::cout << "Result: ";
//   for( const auto &it : res )
//   {
//       std::cout << std::hex << "0x" << (int)it << " ";
//   } std::cout << std::endl;
//
//    cHaffmapTree::mapSym2Code_t tree2 = cHaffmanTable::Bytes2Tree(res);
//    for (const auto &it: tree2) {
//        std::cout<<it.first << "   ";
//        for (const auto &it2 : it.second) {
//            std::cout<<it2;
//        }
//        std::cout<<"\n";
//    }
//    std::cout<<"\n";std::cout<<"\n";std::cout<<"\n";std::cout<<"\n";
//    for (const auto &it : coder.decode(res)) {
//        std::cout<<it<<" ";
//    }

    cArhWork Arch("shk.txt", coder);
    Arch.AddFile("wvh.txt");
    Arch.ExtractFile("Extracted.txt");
    return 0;
}


//@bug при попытке кодирования набора, состоящего только из одинаковых символов,
// баг происходит еще на уровне построения дерева (не присваиваются коды)
//**********Пример**********
//Введите строку: ff
//Init msg: ff
//f
//Header: 0x1 0x66 0x0 0x0
//Result: 0x1 0x66 0x0 0x0 0x0 0x0
//f

//При кодировании более, чем 7 различных символов нельзя в строке декодировщике
// найти подстроку, содержащую изначальную
// qwertyu  => q w e r t y u t t
// qwertyui => w y u r t


//При кодировани  более чем 8 символом, 2 из которых одинаковы - нельзя в строке декодировщике
// найти подстроку, содержащую изначальную
// qwertyuq  => q w e r t y u q q
// qwertyuqq => u e y r w w r e e t q
