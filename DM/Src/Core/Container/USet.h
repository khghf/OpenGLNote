#pragma once
#pragma once
#include<DMPCH.h>
template<
    typename Val,
    typename Hash = std::hash<Val>,   
    typename Com = std::equal_to<Val>   
>
using USet = std::unordered_set<Val, Hash, Com>;
