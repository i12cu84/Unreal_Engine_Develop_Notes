#include <iostream>
#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
 
int main()
{
	//生成UUID:
	{
		//字符串生成器，字符串格式要求：
		//1、没有连接符的全16进制数字.
		//2、使用连接符，但连接符只能出现在第5、7、9、11字节前面.
 
		//构造字符串生成器变量
		boost::uuids::string_generator sgen;
		boost::uuids::uuid u1 = sgen("{0123456789abcdef0123456789abcdef}");
		//std::cout << u1 << std::endl;
		boost::uuids::uuid u2 = sgen("01234567-89ab-cdef-0123-456789abcdef");
		//std::cout << u2 << std::endl;
 
		std::cout << "======================================" << std::endl;
 
		//名字生成器：
		//需要先指定一个基准的UUID，然后使用字符串名字派生出基于
		//这个UUID的一系列UUID.
		//我们以上面u1为基准UUID：
 
		//构造名字生成器变量
		boost::uuids::name_generator ngen(u1);
		boost::uuids::uuid u3 = ngen("zzc");
		std::cout << u3 << std::endl;
		boost::uuids::uuid u4 = ngen("dyb");
		//std::cout << u4 << std::endl;
		boost::uuids::uuid u5 = ngen("hh");
		//std::cout << u5 << std::endl;
 
		std::cout << "======================================" << std::endl;
 
		//随机生成器：内部根据随机数生成UUID
		boost::uuids::random_generator rgen;
		boost::uuids::uuid u6 = rgen();
		//std::cout << u6 << std::endl;
 
		boost::uuids::uuid u7 = rgen();
		//std::cout << u7 << std::endl;
 
	}
 
	std::cout << "======================================" << std::endl;
 
	//操纵访问得到的UUID：
	{
		boost::uuids::random_generator rgen;
		boost::uuids::uuid u6 = rgen();
 
		//UUID转回字符串1：
		std::string str1 = boost::uuids::to_string(u6);
		std::cout << str1 << std::endl;
 
		//UUID转字符串2：
		std::string str3 = boost::lexical_cast<std::string>(u6);
		std::cout << str3 << std::endl;
	}
	
	return 1;
}