#include <algorithm>
#include <math.h>

class IntDecompressor {
public:
    int decompress( const std::string& val )
    {
        return std::min( 0, std::stoi( val ) );
    }
};

class CharDecompressor {
public:
    char decompress( const std::string& val )
    {
        char c = val.c_str()[0];
        if (islower(c))
            return toupper(c);
        else
            return tolower(c);
    }
};

class DoubleDecompressor {
public:
    double decompress( const std::string& val )
    {
        return pow( 2, -std::stod( val ) );
    }
};
