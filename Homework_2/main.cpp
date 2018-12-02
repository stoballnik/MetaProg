#include <type_traits>
#include <algorithm>
#include <iostream>

#pragma mark Declaration NullType
class NullType {
};

#pragma mark Declaration TypeList
template<typename T=NullType, typename ... U>
struct TypeList {
    using head = T;
    using tail = TypeList<U ...>;
};

template<typename T>
struct TypeList<T> {
    using head = T;
    using tail = NullType;
};

#pragma mark TypeList::Length
template <typename TypeList>
struct Length {
    enum { value = Length<typename TypeList::tail>::value + 1 };
};

template <>
struct Length<NullType> {
    enum { value = 0 };
};

template <>
struct Length<TypeList<>> {
    enum { value = 0 };
};

#pragma mark TypeList::PushFront
template <typename T, typename ... Types>
class PushFront;

template <typename T, typename ... Types>
struct PushFront<TypeList<Types ...>, T> {
    using result = TypeList<T, Types ...>;
};

template<typename T>
struct PushFront<NullType, T> {
    using result = TypeList<T>;
};

template<>
struct PushFront<NullType, NullType> {
    using result = NullType;
};

#pragma mark TypeList::PushBack
template <typename T, typename ... Types>
class PushBack;

template <typename T, typename ... Types>
struct PushBack<TypeList<Types ...>, T> {
    using result = TypeList<typename TypeList<Types ...>::head, typename PushBack<typename TypeList<Types ...>::tail, T>::result>;
};

template<typename T>
struct PushBack<NullType, T> {
    using result = TypeList<T>;
};

template<>
struct PushBack<NullType, NullType> {
    using result = NullType;
};

#pragma mark TypeList::Take
template <typename TList, int N>
struct Take {
    enum {size = N < Length<TList>::value ? N: Length<TList>::value};
    using result = typename PushFront<typename Take<typename TList::tail, size - 1>::result, typename TList::head>::result;
};

template <>
struct Take<NullType, -1> {
    using result = NullType;
};

template <typename TList>
struct Take<TList, 0> {
    using result = NullType;
};

#pragma mark TypeList::Remove
template <typename TList, int N>
struct Erase {
    enum { value = Length<TList>::value, size = N < value ? N: value};
    using result = typename Erase<typename TList::tail, size - 1>::result;
};

template <typename TList>
struct Erase<TList, 0> {
    using result = TList;
};

template <>
struct Erase<NullType, -1> {
    using result = TypeList<>;
};

#pragma mark Declaration Fibonacci
template <int index>
struct Fibonacci {
    enum { value = Fibonacci<index - 1>::value + Fibonacci<index - 2>::value };
};

template <>
struct Fibonacci<0> {
    enum { value = 1 };
};

template <>
struct Fibonacci<1> {
    enum { value = 1 };
};

#pragma mark GenTypeListOfFibonacciTypeLists
template <typename TList, int index>
struct GenTypeListOfFibonacciTypeLists {
    using chunk = typename Take<TList, Fibonacci<index>::value + 1>::result;
    using residue = typename Erase<TList, Fibonacci<index>::value + 1>::result;
    
    using result = typename PushFront<typename GenTypeListOfFibonacciTypeLists<residue, index + 1>::result, chunk>::result;
};

template <int index>
struct GenTypeListOfFibonacciTypeLists<NullType, index> {
    using result = TypeList<>;
};

#pragma mark GetScatterHierarchy
template <template<typename> class Unit, typename ... Types>
struct GenScatterHierarchy;

template <template<typename> class Unit, typename ... Types>
struct GenScatterHierarchy<Unit, TypeList<Types ...>> : public Unit<Types> ... {
};


#pragma mark GenLinearHierarchy
template <template<typename, typename> class Unit, typename TList, typename Root = NullType>
struct GenLinearHierarchy : public Unit<typename TList::head, GenLinearHierarchy<Unit, typename TList::tail, Root>> {
};

template <template<typename, typename> class Unit, typename Root>
struct GenLinearHierarchy<Unit, TypeList<>, Root> : public Root {
};

#pragma mark GenLinearChunks
template <template <typename, typename> class Unit, typename Root, typename ... TLists>
struct GenLinearChunks;

template <template <typename, typename> class Unit, typename Root, typename ... TLists>
struct GenLinearChunks<Unit, Root, TypeList<TLists ...>> {
    using result = TypeList<GenLinearHierarchy<Unit, TLists, Root> ...>;
};

#pragma mark GenFibonacciHierarchy
template <template <typename> class ScatterUnit, template <typename, typename> class LinearUnit, typename Root, typename TList>
using GenFibonacciHierarchy = GenScatterHierarchy<ScatterUnit, typename GenLinearChunks<LinearUnit, Root, typename GenTypeListOfFibonacciTypeLists<TList, 0>::result>::result>;





template <typename T>
struct ScatterUnit {
};

template <typename T, typename U>
struct LinearUnit : public U {
};

struct A1 {
};

struct A2 {
};

struct A3 {
};

struct A4 {
};

struct A5 {
};

struct A6 {
};

struct A7 {
};

struct A8 {
};

struct A9 {
};

struct A10 {
};

struct A11 {
};

struct A12 {
};

struct A13 {
};

int main() {
    using TList1 = TypeList<A1>;
    std::cout << Length<TList1>::value << std::endl;
    std::cout << Length<GenTypeListOfFibonacciTypeLists<TList1, 0>::result>::value << std::endl;
    using FibonacciHierarchy1 = GenFibonacciHierarchy<ScatterUnit, LinearUnit, NullType, TList1>;
    
    using TList2 = TypeList<A1, A2>;
    std::cout << Length<TList2>::value << std::endl;
    std::cout << Length<GenTypeListOfFibonacciTypeLists<TList2, 0>::result>::value << std::endl;
    using FibonacciHierarchy2 = GenFibonacciHierarchy<ScatterUnit, LinearUnit, NullType, TList2>;
    
    using TList3 = TypeList<A1, A2, A3>;
    std::cout << Length<TList3>::value << std::endl;
    std::cout << Length<GenTypeListOfFibonacciTypeLists<TList3, 0>::result>::value << std::endl;
    using FibonacciHierarchy3 = GenFibonacciHierarchy<ScatterUnit, LinearUnit, NullType, TList3>;
    
    using TList4 = TypeList<A1, A2, A3, A4>;
    std::cout << Length<TList4>::value << std::endl;
    std::cout << Length<GenTypeListOfFibonacciTypeLists<TList4, 0>::result>::value << std::endl;
    using FibonacciHierarchy4 = GenFibonacciHierarchy<ScatterUnit, LinearUnit, NullType, TList4>;
    
    using TList5 = TypeList<A1, A2, A3, A4, A5>;
    std::cout << Length<TList5>::value << std::endl;
    std::cout << Length<GenTypeListOfFibonacciTypeLists<TList5, 0>::result>::value << std::endl;
    using FibonacciHierarchy5 = GenFibonacciHierarchy<ScatterUnit, LinearUnit, NullType, TList5>;
    
    using TList7 = TypeList<A1, A2, A3, A4, A5, A6, A7>;
    std::cout << Length<TList7>::value << std::endl;
    std::cout << Length<GenTypeListOfFibonacciTypeLists<TList7, 0>::result>::value << std::endl;
    using FibonacciHierarchy7 = GenFibonacciHierarchy<ScatterUnit, LinearUnit, NullType, TList7>;
    
    using TList8 = TypeList<A1, A2, A3, A4, A5, A6, A7, A8>;
    std::cout << Length<TList8>::value << std::endl;
    std::cout << Length<GenTypeListOfFibonacciTypeLists<TList8, 0>::result>::value << std::endl;
    using FibonacciHierarchy8 = GenFibonacciHierarchy<ScatterUnit, LinearUnit, NullType, TList8>;
    
    using TList11 = TypeList<A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11>;
    std::cout << Length<TList11>::value << std::endl;
    std::cout << Length<GenTypeListOfFibonacciTypeLists<TList11, 0>::result>::value << std::endl;
    using FibonacciHierarchy11 = GenFibonacciHierarchy<ScatterUnit, LinearUnit, NullType, TList11>;
    
    using TList12 = TypeList<A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12>;
    std::cout << Length<TList12>::value << std::endl;
    std::cout << Length<GenTypeListOfFibonacciTypeLists<TList12, 0>::result>::value << std::endl;
    using FibonacciHierarchy12 = GenFibonacciHierarchy<ScatterUnit, LinearUnit, NullType, TList12>;
    
    return 0;
}
