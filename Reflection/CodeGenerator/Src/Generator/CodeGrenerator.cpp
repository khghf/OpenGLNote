#include "CodeGrenerator.h"
#include"../Meta/MetaInfo.h"
#include<string>
#include<string_view>
#include"../Util.h"
#include<iostream>
#include<fstream>
#include<sstream>
#include<regex>
#include<filesystem>
namespace reflect
{
	namespace fs = std::filesystem;
	std::string CodeGrenerator::FileStorageFloder = "";
	std::string_view GeneratedCppIncludes = "Reflect/GeneratedCppIncludes.h";
	std::string_view GeneratedHppIncludes = "Reflect/GeneratedHppIncludes.h";
	MetaFile* Info = nullptr;
	void CodeGrenerator::GenerateCode()
	{
		Util::CretaFloderIfNotExist(FileStorageFloder);
		for (auto& it : MetaInfo::GetMetaRegistry())
		{
			Info = &it.second;
			if (!Info->bHasReflectMark)
			{
				const std::string fileName = Util::GetFileName(Info->Path, false) + ".gen.h";
				std::string includePath = include_angled(fileName);//include_angled会在末尾加上\n
				ClearInclude(Util::ModifySuffix(Info->Path, "h"), includePath.substr(0, includePath.size() - 1));
				continue;
			}
			Generate_h();
			Generate_cpp();
		}
	}
	void CodeGrenerator::Generate_h()
	{
		const std::string fileName = Util::GetFileName(Info->Path, false)+".gen.h";

		std::string savePath = FileStorageFloder.data();
		savePath = savePath + "/"+ fileName;
		std::string includePath = include_angled(fileName);//include_angled会在末尾加上\n
		InsertIncludeToFile(Util::ModifySuffix(Info->Path, "h"), includePath.substr(0, includePath.size()-1));
		std::ofstream out(savePath, std::ios_base::trunc);
		std::stringstream content;
		content << "#pragma once\n";
		content << include_angled(GeneratedHppIncludes.data());
		for (const auto& metaClass : Info->Classes)
		{
			int nameSpaceCount = metaClass.NameSpaces.size();
			std::string nameSpace = "";
			if (nameSpaceCount > 0)
			{
				for (int i = nameSpaceCount - 1; i >= 0; --i)
				{
					if (i != 0)
					{
						nameSpace += metaClass.NameSpaces[i] + "::";
					}
					else
					{
						nameSpace += metaClass.NameSpaces[i];
					}
				}
			}
			const std::string& className = metaClass.Name;
			const std::string opertaorName = "AAA_" + className + "_Operator";
			if (metaClass.ReflectBodyLine == 0)
			{
				std::string estr = "ERROR:Marco REFLECT_BODY must be used in reflection class " + className;
				std::cerr << estr << std::endl;
				throw std::runtime_error(estr.c_str());
			}
			else
			{
				content << "class " + opertaorName + ";\n";
				std::string indent = "";
				if(nameSpace.size()>0)
				{
					content << "namespace " + nameSpace + "\n";
					content << "{\n";
					indent += "\t";
				}
				content << indent + "class " + className +";\n";
				content << indent + "DEC_TO_JSON(" + className + ")\n";
				content << indent + "DEC_FROM_JSON(" + className + ")\n";
				if (nameSpace.size() > 0)content << "}\n";
				//REFLECT_BODY()----------
				content << "#undef REFLECT_BODY_" + std::to_string(metaClass.ReflectBodyLine) + "\n";
				content << "#define REFLECT_BODY_" + std::to_string(metaClass.ReflectBodyLine) + "()\\\n";
				content << "friend class " + opertaorName + ";\\\n";
				content << "typedef " + className + " ThisClass;\\\n";
				if(metaClass.SuperClassesNames.size()>0)content << "typedef " + metaClass.SuperClassesNames[0].second + " Super;\\\n";
				content << "public:\\\n";
				content << "Reflect_API static ::reflect::RClass*RClassInst();\\\n";//返回类自身的RClass*
				//content << "Reflect_API virtual void to_json(::nlohmann::json&j)const";//序列化函数
				//if (metaClass.SuperClassesNames.size() > 0)content << " override";
				//content << ";\\\n";
				//content << "Reflect_API virtual void from_json(const ::nlohmann::json&j)";//反序列化函数
				//if (metaClass.SuperClassesNames.size() > 0)content << " override";
				//content << ";\\\n";
				content << "virtual std::string GetTypeName ()const";
				if (metaClass.SuperClassesNames.size() > 0)content << " override";
				content << "{return TypeName;}\\\n";
				content << "static constexpr  char* TypeName =TOSTR(" + className + ");\\\n";
				content << "private:\\\n";
				//REFLECT_BODY()----------
			}
		}
		out << content.str();
	}

	void CodeGrenerator::Generate_cpp()
	{
		const std::string fileName = Util::GetFileName(Info->Path, false) + ".gen.cpp";
		std::string savePath = FileStorageFloder.data();
		savePath = savePath + "/" + fileName;

		std::ofstream out(savePath, std::ios_base::trunc);
		std::stringstream content;
		content << include_angled(GeneratedCppIncludes.data());
		content << include_quotes( Util::ModifySuffix(Info->Path,"h"));

		const std::string rclass = "reflect::RClass";
		const std::string rfunction = "reflect::RFunction";
		const std::string rproperty = "reflect::RProperty";

		for (const auto& metaClass : Info->Classes)
		{
			const std::string& className = metaClass.Name;
			int nameSpaceCount = metaClass.NameSpaces.size();
			std::string nameSpace = "";
			if (nameSpaceCount > 0)
			{
				for (int i = nameSpaceCount - 1; i >= 0; --i)
				{
					if (i != 0)
					{
						nameSpace += metaClass.NameSpaces[i] + "::";
					}
					else
					{
						nameSpace += metaClass.NameSpaces[i];
					}
				}
			}
			//***************************************************************AAA_XXX_Operator,用于访问类的私有成员
			const std::string opertaorName = "AAA_" + className + "_Operator";
			content << "class "+opertaorName + "\n";
			content << "{\n";
			content << "public:\n";
			content << "\tConstructRClass(" + className +","+nameSpace+ ")\n";
			for (const auto& metaFun : metaClass.Functions)
			{
				const std::string& funName = metaFun.Name;
				content << "\tConstructRFunction(" + funName + "," + className + "," + nameSpace + ")\n";
			}
			for (const auto& metaProperty : metaClass.Properties)
			{
				const std::string& proName = metaProperty.Name;
				content << "\tConstructRProperty(" + proName + "," + className + "," + nameSpace + ")\n";
			}
			//ToJson
			content << "\tstatic void ToJson(::nlohmann::json&j,const void*obj)\n";
			content << "\t{\n";
			content << "\t\tconst "+nameSpace+"::" + className + "*ptr=static_cast<const "+nameSpace + "::" + className + "*>(obj);\n";
			for (const auto& Pro : metaClass.Properties)
			{
				content << "\t\tj[TOSTR(" + Pro.Name + ")]=ptr->" + Pro.Name + ";\n";
			}
			content << "\t}\n";
			//FromJson
			content << "\tstatic void FromJson(const ::nlohmann::json&j,void*obj)\n";
			content << "\t{\n";
			content << "\t\t" +nameSpace + "::" + className + "*ptr=new " + nameSpace + "::" + className + "();\n";
			for (const auto& metaPro : metaClass.Properties)
			{
				content << "\t\tptr->" + metaPro.Name + "=j[TOSTR(" + metaPro.Name + ")].get<" + metaPro.TypeName + ">();\n";
			}
			content << "\t\tobj=ptr;\n";
			content << "\t}\n";

			content << "};\n";





			//***************************************************************为类生成的成员函数

			content << "::reflect::RClass*" + nameSpace + "::" + className + "::RClassInst()\n";//返回类自身的RClass*
			content << "{\n";
			content << "\treturn " + opertaorName + "::ConstructRClass_" + className + "(); \n";
			content << "}\n";
			std::string indent = "";
			if (nameSpace.size()>0)
			{
				content << "namespace " + nameSpace + "\n";
				content << "{\n";
				indent += "\t";
			}
			//json 序列化函数
			content << indent+"DEF_TO_JSON("+className+")\n";
			//json 反序列化函数
			content << indent + "DEF_FROM_JSON(" + className + ")\n";
			if (nameSpace.size() > 0)content << "}\n";
			//***************************************************************FunDec
			//声明父类构造函数
			for (const auto& superClass : metaClass.SuperClassesNames)
			{
				content <<"extern "+ rclass + "*AAA_Construct_RClass_" + superClass.second + "();\n";
			}
			//将AAA_XXX_Operator内部的函数包装成普通函数
			content << rclass+"*AAA_Construct_RClass_" + className + "()\n";
			content << "{\n";
			content << "\treturn "+opertaorName+"::ConstructRClass_"+className + "(); \n";
			content << "}\n";
			
			for (const auto& metaFun : metaClass.Functions)
			{
				const std::string& funName = metaFun.Name;
				content << rfunction+"*AAA_Construct_RFunction_" + funName + "()\n";
				content << "{\n";
				content << "\treturn " + opertaorName + "::ConstructRFunction_" + funName + "();\n";
				content << "}\n";

			}
			for (const auto& metaProperty : metaClass.Properties)
			{
				const std::string& proName = metaProperty.Name;
				content << rproperty+"*AAA_Construct_RProperty_" + proName + "()\n";
				content << "{\n";
				content << "\treturn " + opertaorName + "::ConstructRProperty_" + proName + "();\n";
				content << "}\n";
			}

			content << "\tvoid ToJson(::nlohmann::json&j,const void*obj)\n";
			content << "{\n";
			content << "\t" + opertaorName + "::ToJson(j,obj);\n";
			content << "}\n";
			content << "\tvoid*FromJson(const ::nlohmann::json&j,void*obj)\n";
			content << "{\n";
			content << "\t" + opertaorName + "::FromJson(j,obj);\n";
			content << "}\n";

			//***************************************************************收集信息
			//将信息收集到AAA_Construct_XXX_Statics中
			const std::string structStatics = "AAA_Construct_"+ className+"_Statics";
			content << "struct "+ structStatics+"\n";
			content << "{\n";
			if (metaClass.SuperClassesNames.size() > 0)content << "\tstatic RClassConstructor SuperClass_Constructor[];\n";
			content << "\tstatic RClassConstructor RClass_" + className + "_Constructor;\n";
			if(metaClass.Functions.size()>0)content << "\tstatic RFunctionConstructor RFunction_" + className + "_Constructor[];\n";
			if (metaClass.Properties.size() > 0)content << "\tstatic RPropertyConstructor RProperty_" + className + "_Constructor[];\n";
			
			content << "\tconst static uint32_t SuperClassNum;\n";
			content << "\tconst static uint32_t FunctionNum;\n";
			content << "\tconst static uint32_t PropertyNum;\n";
			content << "\tconst static _TO_JSON_ ToJson;\n";
			content << "\tconst static _FROM_JSON_ FromJson;\n";
			content << "};\n";


				//SuperClass
			if (metaClass.SuperClassesNames.size() > 0)
			{
				content << "RClassConstructor " + structStatics + "::SuperClass_Constructor[]=\n";
				content << "{\n";
				for (const auto& superClass : metaClass.SuperClassesNames)
				{
					content << "\tAAA_Construct_RClass_" + superClass.second + ",\n";
				}
				content << "};\n";
			}
				//RClass
			content << "RClassConstructor " + structStatics + "::RClass_" + className + "_Constructor = AAA_Construct_RClass_" + className + ";\n";
				//RFunctions
			if (metaClass.Functions.size() > 0)
			{
				content << "RFunctionConstructor " + structStatics + "::RFunction_" + className + "_Constructor[]=\n";
				content << "{\n";
				for (const auto& metaFun : metaClass.Functions)
				{
					const std::string& funName = metaFun.Name;
					content << "\tAAA_Construct_RFunction_" + funName + ",\n";

				}
				content << "};\n";
			}
				//RProperties
			if (metaClass.Properties.size() > 0)
			{
				content << "RPropertyConstructor " + structStatics + "::RProperty_" + className + "_Constructor[]=\n";
				content << "{\n";
				for (const auto& metaPro : metaClass.Properties)
				{
					const std::string& proName = metaPro.Name;
					content << "\tAAA_Construct_RProperty_" + proName + ",\n";

				}
				content << "};\n";
			}
				//SuperClassNum
			if (metaClass.SuperClassesNames.size() > 0)content << "const uint32_t "+ structStatics+"::SuperClassNum = ARRAY_COUNT("+ structStatics+"::SuperClass_Constructor);\n";
			else content << "const uint32_t "+ structStatics+"::SuperClassNum = 0;\n";
				//FunctionNum
			if (metaClass.Functions.size() > 0)content << "const uint32_t "+ structStatics+"::FunctionNum = ARRAY_COUNT("+ structStatics+"::RFunction_" + className + "_Constructor);\n";
			else content << "const uint32_t "+ structStatics+"::FunctionNum = 0;\n";
				//PropertyNum
			if (metaClass.Properties.size() > 0)content << "const uint32_t "+ structStatics+"::PropertyNum = ARRAY_COUNT("+ structStatics+"::RProperty_" + className + "_Constructor);\n";
			else content << "const uint32_t "+ structStatics+"::PropertyNum = 0;\n";
			//ToJson
			content << "const _TO_JSON_ " + structStatics + "::ToJson=ToJson;\n";
			//FromJson
			content << "const _FROM_JSON_ " + structStatics + "::FromJson=FromJson;\n";
			//***************************************************************转发注册
			//将收集的信息转发注册
			content << "static RegistrationInfo Collector_" + className + "=\n";
			content << "{\n";
			if (metaClass.SuperClassesNames.size() > 0)content << "\t" + structStatics + "::SuperClass_Constructor,\n";
			else content << "\tnullptr,\n";
			content << "\t"+structStatics+"::RClass_" + className + "_Constructor,\n";
			if (metaClass.Functions.size() > 0)content << "\t" + structStatics + "::RFunction_" + className + "_Constructor,\n";
			else content << "\tnullptr,\n";
			if (metaClass.Properties.size() > 0)content << "\t" + structStatics + "::RProperty_" + className + "_Constructor,\n";
			else content << "\tnullptr,\n";
			content << "\t" + structStatics + "::SuperClassNum,\n";
			content << "\t" + structStatics + "::FunctionNum,\n";
			content << "\t" + structStatics + "::PropertyNum\n";
			content << "};\n";
			content << "static CollectRegistrationInfo Register_"+className+"(Collector_" + className + "); \n";
		}
		out << content.str();
	}

	const std::string CodeGrenerator::include_angled(const std::string& path)
	{
		return "#include<" + path + ">\n";
	}

	const std::string CodeGrenerator::include_quotes(const std::string& path)
	{
		return "#include\"" + path + "\"\n";
	}

	void CodeGrenerator::InsertIncludeToFile(const std::string& filePath, const std::string& includestr)
	{
		if (!fs::is_regular_file(filePath))return ;
		std::ifstream file(filePath, std::ios::in);
		//先去掉可能存在的想要插入的头文件
		std::stringstream steam;
		steam << file.rdbuf();
		std::string content = steam.str();
		Util::RemoveUtf8Bom(content);
		const std::string includeStrModified = includestr + "(\n|\r)*";
		std::regex re(includeStrModified, std::regex::nosubs);
		uint32_t bExisit = 0;
		if (std::regex_search(content, re))
		{
			content = std::regex_replace(content, re, "");
			file.close();
			std::ofstream out(filePath, std::ios_base::trunc);
			out << content;
			out.close();
			file.open(filePath);
			bExisit = 1;
		}
		else
		{
			for (int i = 0; i < Info->Classes.size(); ++i)
			{
				++Info->Classes[i].ReflectBodyLine;
			}
		}
		Util::SkipUtf8Bom(file);
		std::vector<std::string> fileLines;
		std::string line;
		uint32_t CurLine = 0;
		bool bPushed = false;
		while (std::getline(file, line)) {
			++CurLine;
			if (CurLine > (Info->LastIncludeLine-bExisit)&&!bPushed)
			{
				bPushed = true;
				fileLines.emplace_back(includestr+"\n");
			}
			fileLines.emplace_back(std::move(line) + "\n");
		}
		file.close();
		std::ofstream out(filePath, std::ios_base::trunc);
		for (const auto& str : fileLines)
		{
			out << str;
		}
		out.close();
	}

	void CodeGrenerator::ClearInclude(const std::string& filePath, const std::string& includestr)
	{
		if (!fs::is_regular_file(filePath))return;
		std::ifstream in(filePath);
		std::string content;
		Util::SkipUtf8Bom(in);
		std::stringstream stream;
		stream << in.rdbuf();
		in.close();
		content =stream.str();
		const std::string includeStrModified = includestr + "(\n|\r)*";
		std::regex re(includeStrModified, std::regex::nosubs);
		content=std::regex_replace(content, re, "");
		std::ofstream out(filePath);
		out << content;
	}
}