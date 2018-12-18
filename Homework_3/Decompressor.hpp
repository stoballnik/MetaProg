struct NoneType {};
struct NoDecompressor {};

template<typename Type, typename ConpressedType, typename DecompressorType>
struct Decompressor;

template<typename Type, typename ConpressedType>
struct Decompressor<Type, ConpressedType, NoDecompressor> {
    Type decompress( const std::string& elem )
    {
        return ConpressedType(elem).decompress();
    }
};

template<typename Type, typename DecompressorType>
struct Decompressor<Type, NoneType, DecompressorType> {
    Type decompress( const std::string& elem )
    {
        return DecompressorType().decompress(elem);
    }
};
