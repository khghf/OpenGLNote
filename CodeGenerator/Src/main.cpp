#include"Generator/CodeParser.h"
#include"Generator/CodeGrenerator.h"
#include<iostream>
#include <filesystem> 
#include<memory>
int main(int args, char* argment[])
{
	reflect::CodeParser parse;
	if (args > 1)
	{
		parse.m_ScanPaths.push_back(argment[1]);
	}
	else
	{
		parse.m_ScanPaths.push_back("../DM/Src/FrameWork");
	}

	//parse.m_ExcludePaths.emplace("../DM/Core");
	parse.m_ProjectRoot = "D:/Projects/DM";
	parse.m_IncludeDir = "DM/Src";
	parse.Parse();
	for (int i = 0; i < args; ++i)
	{
		std::cout <<"Argument:"<<argment[i] << std::endl;
	}
	reflect::CodeGrenerator::FileStorageFloder =parse.m_ProjectRoot + "/" + "Intermediate/GeneratedCode";
	reflect::CodeGrenerator::GenerateCode();
	return 0;
}