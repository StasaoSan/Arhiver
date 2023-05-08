# 3.23
cmake_minimum_required(VERSION 3.17)
project( untitled1 )

# 14
set( CMAKE_CXX_STANDARD 17 )

add_compile_options(-lstdc++fs)
# @todo rename
add_executable( untitled1
                main.cpp
                HaffmanCoder/src/haffman_coder.cpp
                HaffmanCoder/src/haffman_tree/HaffmanTree.cpp
                HaffmanCoder/src/haffman_table/HaffmanTable.cpp
                HaffmanCoder/src/cIBitPacker/cIBitPacker.cpp HaffmanCoder/src/WorksWithFiles/FilesWork.cpp HaffmanCoder/src/WorksWithFiles/FilesWork.hpp)

# @todo direcctories
include_directories( ${CMAKE_CURRENT_SOURCE_DIR}
                     HaffmanCoder/h
                     HaffmanCoder/src/haffman_tree
                     HaffmanCoder/src/haffman_table
                     HaffmanCoder/src/cIBitPacker
                     HaffmanCoder/src/WorksWithFiles )

