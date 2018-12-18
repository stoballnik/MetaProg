#include <iostream>
#include <fstream>
#include <string>

#include "TypeList.hpp"
#include "Decompressor.hpp"
#include "Reader.hpp"
#include "CompressedTypes.hpp"
#include "DecompressorsTypes.h"

int main()
{
    Reader<TypeList<int, int, double, double, char, char>,
    TypeList<CompressedInt, NoneType, CompressedDouble, NoneType, CompressedChar, NoneType>,
    TypeList<NoDecompressor, IntDecompressor, NoDecompressor, DoubleDecompressor, NoDecompressor, CharDecompressor>> reader( "input.txt" );
    
    void* line = nullptr;
    while( line = reader.readNextLine() ) {
        void* pl = line;
        std::cout << *(int*)line << " ";
        line = (char*)line + sizeof(int);
        std::cout << *(int*)line << " ";
        line = (char*)line + sizeof(int);
        std::cout << *(double*)line << " ";
        line = (char*)line + sizeof(double);
        std::cout << *(double*)line << " ";
        line = (char*)line + sizeof(double);
        std::cout << *(char*)line << " ";
        line = (char*)line + sizeof(char);
        std::cout << *(char*)line << std::endl;
        std::free(pl);
    }
    
    return 0;
}

