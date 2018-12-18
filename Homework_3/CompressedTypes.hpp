#include <algorithm>
#include <math.h>

struct CompressedInt {
    explicit CompressedInt( const std::string& _val ) : val( _val ){}
    
    int decompress()
    {
        return std::max( 0, std::stoi( val ) );
    }

    const std::string& val;
};

struct CompressedChar {
    explicit CompressedChar( const std::string& _val ) : val( _val ){}

    char decompress()
    {
        return val.c_str()[0] + 1;
    }

    const std::string& val;
};

struct CompressedDouble {
    explicit CompressedDouble( const std::string& _val ) : val( _val ){}
    
    double decompress()
    {
        return pow( 2, std::stod( val ) );
    }
    
    const std::string& val;
};
