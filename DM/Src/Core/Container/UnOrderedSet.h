#pragma once
#pragma once
#include<DMPCH.h>
template<
    typename Val,
    typename Hash = std::hash<Val>,        // 默认哈希函数（和 std::unordered_map 一致）
    typename Com = std::equal_to<Val>      // 默认键比较函数（和 std::unordered_map 一致）
>
using UnOrderedSet = std::unordered_set<Val, Hash, Com>;