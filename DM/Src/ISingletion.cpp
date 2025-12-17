#include"DMPCH.h"
#include"ISingletion.h"
#include<Core/EventSystem/EventManager.h>
namespace DM
{
    template <typename T>
    T* ISingletion<T>::Instance = nullptr; 
    template EventManager* ISingletion<EventManager>::GetInst();//显示实例化防止链接错误
}