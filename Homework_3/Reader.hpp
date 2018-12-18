template<typename TList, typename CompressedTList, typename DecompressorTList>
class Reader;

template<>
struct Reader<EmptyTypeList, EmptyTypeList, EmptyTypeList> {
    explicit Reader( const std::string& filename )
    {
        file.open( filename, std::ifstream::in);
        memSize = 0;
    }
    
    virtual ~Reader()
    {
        file.close();
    }
    virtual void readNextElement( void* memPtr ){ return; }
    
    std::ifstream file;
    size_t memSize;
};

template<typename Type, typename ... TList, typename CompressedType, typename ... CompressedTList, typename DecompressorType, typename ... DecompressorTList>
struct Reader<TypeList<Type, TList ...>, TypeList<CompressedType, CompressedTList ...>, TypeList<DecompressorType, DecompressorTList ...>> :
public Reader<TypeList<TList ...>, TypeList<CompressedTList ...>, TypeList<DecompressorTList ...>>
{
    using Base = Reader<TypeList<TList ...>, TypeList<CompressedTList ...>, TypeList<DecompressorTList ...>>;
    
    explicit Reader( const std::string& filename ) :
    Base::Reader( filename )
    {
        memSize = Base::memSize + sizeof( Type );
    }
    
    virtual ~Reader() {}
    
    void* readNextLine()
    {
        if (Base::file.eof()) return nullptr;
        void* mem = std::malloc( memSize );
        readNextElement( mem );
        return mem;
    }

    void readNextElement( void* memPtr )
    {
        std::string elem;
        char c = 0;
        while(true) {
            Base::file.get( c );
            if ( Base::file.eof() ) break;
            if ( c != '\t' && c != '\n')
                elem += c;
            else
                break;
        }
        if ( elem.size() == 0 ) return;
        Type element = decompressor.decompress( elem );
        std::memcpy( memPtr, &element, sizeof( Type ) );
        Base::readNextElement( (char*)memPtr + sizeof( Type ) );
    }
    
    Decompressor<Type, CompressedType, DecompressorType> decompressor;
    size_t memSize;
};
