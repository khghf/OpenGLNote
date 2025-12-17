#pragma once
#include<DMPCH.h>
template<
    typename Key,
    typename Val,
    typename Hash = std::hash<Key>,        // 默认哈希函数（和 std::unordered_map 一致）
    typename Com = std::equal_to<Key>      // 默认键比较函数（和 std::unordered_map 一致）
>
using UnOrderedMap = std::unordered_map<Key, Val, Hash, Com>;