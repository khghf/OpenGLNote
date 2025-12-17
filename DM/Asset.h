#pragma once
#include<string>
#include<DataType.h>
class Asset
{
public:
	Asset()=default;
	virtual ~Asset() = default;
protected:
	std::string Name;
	std::string Path;
	EAssetsType AssetsType = EAssetsType::None;
protected:
	
public:
	std::string GetName()const;
};