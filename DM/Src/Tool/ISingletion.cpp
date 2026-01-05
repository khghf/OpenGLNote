#include"DMPCH.h"
#include"ISingletion.h"
#include<Core/EventSystem/EventManager.h>
#include<Resource/AssetManager.h>
namespace DM
{
    template <typename T>
    T* ISingletion<T>::Instance = nullptr; 
    template EventManager* ISingletion<EventManager>::GetInst();//显示实例化防止DLL导出时链接错误
    template AssetManager* ISingletion<AssetManager>::GetInst();//显示实例化防止DLL导出时链接错误
    //template TimeMeasurerLayer* ISingletion<TimeMeasurerLayer>::GetInst();//显示实例化防止DLL导出时链接错误
}