#pragma once
#undef REFLECT_BODY_8
#define REFLECT_BODY_8()\
typedef GPlayer ThisClass;\
public:\
Reflect_API static ::mirror::TypeId GetTypeId();\
private:
