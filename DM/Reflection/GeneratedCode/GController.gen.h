#pragma once
#undef REFLECT_BODY_8
#define REFLECT_BODY_8()\
typedef GController ThisClass;\
public:\
Reflect_API static ::mirror::TypeId GetTypeId();\
private:
