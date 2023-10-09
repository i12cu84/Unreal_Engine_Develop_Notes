#include <iostream>
using namespace std;
class Base
{
public:
	virtual void f() { cout << "f()" << endl; }
	virtual void g() { cout << "g()" << endl; }
	virtual void h() { cout << "h()" << endl; }
};
class Devired : public Base
{
public:
	virtual void x() { cout << "x()" << endl; }
};

int main()
{
	Devired obj;
	void** vtabl=*reinterpret_cast<void***>(&obj);//获取对象的虚函数表指针
	//访问虚函数表中的第一个元素,并执行相应的函数
	{
		typedef void (*FuncPtr)();
		//using FuncPtr = void(*)();
		FuncPtr func1_prt=reinterpret_cast<FuncPtr>(vtabl[0]);
		func1_prt();
		// f()
		func1_prt=reinterpret_cast<FuncPtr>(vtabl[1]);
		func1_prt();
		// g()
	}
	{
		using FuncPtr = void(*)();
		FuncPtr func1_prt=reinterpret_cast<FuncPtr>(vtabl[0]);
		func1_prt();
		// f()
		func1_prt=reinterpret_cast<FuncPtr>(vtabl[1]);
		func1_prt();
		// g()
	}
	/*
	Devired t;
	(((void (*)()) * ((int *)(*((int *)&t)))))();
	(((void (*)()) * ((int *)(*((int *)&t)) + 1)))();
	(((void (*)()) * ((int *)(*((int *)&t)) + 2)))();
	(((void (*)()) * ((int *)(*((int *)&t)) + 3)))();
	*/
	return 0;
}