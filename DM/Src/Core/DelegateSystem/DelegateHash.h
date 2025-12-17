#pragma once
#include<DMPCH.h>
namespace DM
{
    template<typename T>
    struct FTypeHash
    {
        size_t operator()()const
        {
            return typeid(T).hash_code();
        }
    };
    template<typename T>
    struct  FFunHash
    {
        size_t operator()(T CallObj)const
        {
            return std::hash<void*>()(reinterpret_cast<void*>(CallObj));
        }
    };
    template<typename T>
    struct FLambdaHash
    {
        size_t operator()(const T& lambda)const
        {
            size_t TypeHash = std::hash<std::string_view>()(typeid(T).name());
            size_t Obj_Hash = std::hash<std::uintptr_t>()(reinterpret_cast<std::uintptr_t>(&lambda));
            return hash_combine(TypeHash, Obj_Hash);
        }
    };
    template <typename T>
    size_t hash_combine(const size_t& seed, const T& val) {
        std::hash<T> hasher;
        return hasher(val) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    }

    template<typename Class, typename Ret, typename ...Args>
    struct FMebFunHash
    {
        size_t operator()(Ret(Class::* MebFun)(Args...))const
        {
            size_t seed = FTypeHash<Class>()();
            // 哈希成员函数指针的每个字节地址
            using MebFunType = Ret(Class::*)(Args...);
            static_assert(std::is_trivially_copyable_v<MebFunType>,
                "Member function pointer must be trivially copyable");
            const unsigned char* ptr = reinterpret_cast<const unsigned char*>(&MebFun);
            for (size_t i = 0; i < sizeof(MebFunType); ++i) {
                hash_combine(seed, ptr[i]);
            }
            return seed;
        }
        // 重载：支持const成员函数
        size_t operator()(Ret(Class::* MebFun)(Args...) const) const {
            size_t seed = FTypeHash<Class>()();

            using MebFunType = Ret(Class::*)(Args...) const;
            static_assert(std::is_trivially_copyable_v<MebFunType>,
                "Const member function pointer must be trivially copyable");
            const unsigned char* ptr = reinterpret_cast<const unsigned char*>(&MebFun);
            for (size_t i = 0; i < sizeof(MebFunType); ++i) {
                hash_combine(seed, ptr[i]);
            }
            return seed;
        }
    };
}

