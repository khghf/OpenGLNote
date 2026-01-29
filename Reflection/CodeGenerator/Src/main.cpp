#include"Generator/CodeParser.h"
#include"Generator/CodeGrenerator.h"
#include<iostream>
#include <filesystem> 
#include<json/json.hpp>
#include<memory>
#include<tuple>
using Json = nlohmann::json;
class Person
{
	friend class A;
private:
public:
	Person() {};
	~Person() = default;
	std::string name = "person";
	int age = 100;
};
class Person1:public Person
{
	friend class A;
private:
public:
	Person1() {
		name = "person1";
	};
	~Person1() = default;
};
class A
{
	using type = int;
public:
	A() = default;
	std::shared_ptr<Person>p=std::make_shared<Person>();
	virtual type get();
};
class B:public A
{
public:
	B() = default;
	std::shared_ptr<Person>p = std::make_shared<Person>();
};
void to_json(Json& j, const Person& p)
{
	j = Json{ {"name", p.name}, {"age", p.age} };
}
void to_json(Json& j, const Person* p)
{
	j = Json{ {"name", p->name}, {"age", p->age} };
}
void to_json(Json& j, const std::shared_ptr<Person> p)
{
	j = Json{ {"name", p->name}, {"age", p->age} };
}
void from_json(const Json& j, Person& p) {
	j.at("name").get_to(p.name);
	j.at("age").get_to(p.age);
}
void from_json(const Json& j, std::shared_ptr<Person>& p) {
	p = std::shared_ptr<Person>(new Person());
	j.at("name").get_to(p->name);
	j.at("age").get_to(p->age);
}
int main(int args, char* argment[])
{
	//Json js;
	//A a;
	//Person* p = new Person1();
	//std::vector<int>vec = { 1,2,3,4,5 };
	//js["person1"] = p;
	//js["vec"] = vec;
	//std::cout << js.dump() << std::endl;
	//Person p2(js);
	//delete p;
	//return 0;


	//ParserConfig config=ParseArguments(args, argment);
	reflect::CodeParser parse;
	if (args > 1)
	{
		parse.m_ScanPaths.push_back(argment[1]);
	}
	else
	{
		parse.m_ScanPaths.push_back("../../DM/Src");
		//parse.m_ScanPaths.push_back("../../DM/Src/FrameWork/Entity.h");
	}
	parse.Parse();
	for (int i = 0; i < args; ++i)
	{
		std::cout <<"Argument:"<<argment[i] << std::endl;
	}
	reflect::CodeGrenerator::FileStorageFloder = "../Reflect/GeneratedCode";
	reflect::CodeGrenerator::GenerateCode();
	return 0;
}