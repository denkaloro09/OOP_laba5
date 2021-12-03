#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <memory>

using namespace std;

class Basic //базовый класс
{
protected:
	int number;
public:
	Basic() //конструктор
	{
		printf("Basic Created\n");
		number = 0;
	}
	Basic(int _number)
	{
		printf("Basic Created\n");
		number = _number;
	}
	void method1() //метод, который переопределяется в классе-наследнике
	{
		printf("Basic:\n %d + 1 = ", number);
		number = number + 1;
		printf(" %d\n", number);
	}
	void method2() //метод, который наследуется классом-наследником
	{
		printf("Basic:\n %d - 1 = ", number);
		number = number - 1;
		printf(" %d\n", number);
	}
	virtual void method3() //виртуальный метод
	{
		printf("Basic:\n %d * 3 = ", number);
		number = number * 3;
		printf(" %d\n", number);
	}
	virtual string classname() //
	{
		return "Basic";
	}
	virtual bool isA(string who) //возвращает true, если вызван у объекта класса Basic (переопределен в потомке)
	{
		return (who == "Basic");
	}
	virtual~Basic()
	{
		printf("Basic Deleted\n");
	}
};
class BasicExtends : public Basic //класс наследник
{
public:
	BasicExtends()
	{
		printf("BasicExtends Created\n");
		number = 0;
	}
	BasicExtends(int _number)
	{
		printf("BasicExtends Created\n");
		number = _number;
	}
	void method1()
	{
		printf("BasicExtends:\n %d + 1 = ", number);
		number = number + 1;
		printf(" %d\n", number);
	}
	void method3() override
	{
		printf("BasicExtends:\n %d * 3 = ", number);
		number = number * 3;
		printf(" %d\n", number);
	}
	string classname()
	{
		return "BasicExtends";
	}
	~BasicExtends()
	{
		printf("BasicExtends Deleted\n");
	}
	void method4() //метод, который есть только в классе-наследнике
	{
		printf("BasicExtends:\n %d * %d = " , number,number);
		number = number * number;
		printf(" %d\n", number);
	}
	bool isA(string who)
	{
		return(who == "BasicExtends" || Basic::isA(who));
	}
};
class Base //классы с отладочными выводами для функций
{
public:
	int number;
	Base()
	{
		printf("Base\n");
		number = 1;
	}
	Base(Base* obj)
	{
		printf("Base(Base* obj\n");

		number = obj->number;
	};

	Base(Base& obj)
	{
		printf("Base(Base& obj\n");
		number = obj.number;
	};
	void PlusNumber()
	{
		printf("PlusNumber\n");
		this->number += 1;
	}

	~Base()
	{
		printf("~Base\n");
	};
};



class Desc : public Base
{
public:
	Desc()
	{
		printf("Desc\n");
		number = 1;
	}
	Desc(Desc* obj)
	{
		printf("Desc(Desc* obj\n");
		number = obj->number;
	};

	Desc(Desc& obj)
	{
		printf("Desc(Desc& obj\n");
		number = obj.number;
	};

	~Desc()
	{
		printf("~Desc\n");
	}
};





void func1(Base obj)
{
	obj.PlusNumber();
	printf("func1(Base obj)\n");
};

void func2(Base* obj)
{
	obj->PlusNumber();
	printf("func2(Base* obj)\n");
};

void func3(Base& obj)
{
	obj.PlusNumber();
	printf("func3(Base& obj)\n");
};

Base func12() 
{
	//Base* bas = new Base();
	printf("func12 - Base\n");
	return new Base();
};

Base* func22()
{
	//Base* bas = new Base();
	printf("func22 - Base*\n");
	return new Base();
};

Base& func32() 
{
	Base bas = new Base();
	printf("func32 - Base&\n");
	return bas;
};

int main()
{
	setlocale(LC_ALL, "RU");
	Basic* b = new Basic(5); //объект базового класса
	BasicExtends* be = new BasicExtends(3); //объекта класса-наследника
	Basic* bb = new BasicExtends(8); //объект класса-наследника, помещенного в переменную базового класса
	printf("Метод базового класса у объекта базового класса:\n");
	b->method2();
	printf("Наследуемый метод базового класса у объекта класса-наследника:\n");
	be->method2();

	printf("Метод базового класса у объекта базового класса:\n");
	b->method1();
	printf("Вызов метода базового класса, перекрытого в классе-наследнике, у объекта класса-наследника:\n");
	be->method1();

	printf("Виртуальный метод у объекта базового класса:\n");
	b->method3();
	printf("Переопределенный метод у объекта класса-наследника:\n");
	be->method3();

	printf("Перекрываемый метод у объекта класса-наследника, помещенного в переменную базового класса:\n");
	bb->method1();

	printf("Метод базового класса у объекта класса-наследника, помещенного в переменную базового класса:\n");
	bb->method2();

	printf("Переопределенный метод у объекта производного класса, помещенного в переменную базового класса:\n");
	bb->method3();

	printf("Удаление объекта базового класса:\n");
	delete b;
	printf("Удаление объекта производного класса:\n");
	delete be;
	printf("Удаление объекта производного класса, помещенного в переменную базового класса:\n");
	delete bb;
	printf("\n\n\n\n\n\n\n");

	//проверка на принадлежность классу
	printf("Создание трех объектов:\nBasic - basic\nBasicExtends - basicEx\nBasicExtends - ExInBasic, помещенного в переменную базового типа\n");
	Basic* basic = new Basic();
	BasicExtends* basicEx = new BasicExtends();
	Basic* ExInBasic = new BasicExtends();
	//C* c = new C();
	printf("\nДалее идут проверки на принадлежность к классу с помощью метода classname:\n");
	cout << "\nbasic это объект какого класса? - " << basic->classname() << endl;
	cout << "\nBasicEx это объект какого класса? - " << basicEx->classname() << endl;
	cout << "\nExInBasic это объект какого класса? - " << ExInBasic->classname() << endl;
	printf("\nДалее идут проверки на принадлежность к классу с помощью метода isA:\n");
	cout << "\nbasic это объект класса Basic? - " << basic->isA("Basic") << endl;
	cout << "\nbasic это объект класса BasicExtends? - " << basic->isA("BasicExtends") << endl;
	cout << "\nbasicEx это объект класса Basic? - " << basicEx->isA("Basic") << endl;
	cout << "\nbasicEx это объект класса BasicExtends? - " << basicEx->isA("BasicExtends") << endl;
	cout << "\nExInBasic это объект класса Basic? - " << ExInBasic->isA("Basic") << endl;
	cout << "\nExInBasic это объект класса BasicExtends? - " << ExInBasic->isA("BasicExtends") << endl;
	printf("\n\n\n\n\n\n\n");

	//безопасное приведение типов (dynamic_cast)
	printf("Создание объекта BasicExtends и помещение его в переменную типа Basic:\n");
	Basic* b2 = new BasicExtends(5);
	printf("Производится динамическое приведение типов (dynamic_cast) и у объекта вызывается метод, которого нет в базовом классе:\n");
	if (dynamic_cast<BasicExtends*>(b2))
	{
		dynamic_cast<BasicExtends*>(b2)->method4();
	}
	printf("\n\n\n\n\n\n\n");

	//безопасное приведение типов (вручную)
	printf("Создание объекта BasicExtends и помещение его в переменную типа Basic:\n");
	Basic* b3 = new BasicExtends(9);
	printf("Производится ручное приведение типов и у объекта вызывается метод, которого нет в базовом классе:\n");
	if (b3->isA("BasicExtends"))
	{
		((BasicExtends*)b3)->method4();
	}
	printf("\n\n\n\n\n\n\n");


	printf("Создание объектов Base и Desc\n");
	Base* base = new Base();
	printf("\n");
	Desc* desc = new Desc();
	printf("\nВызов функций с параметром Base:\n");
	func1(*base);
	printf("\n");
	func2(base);
	printf("\n");
	func3(*base);
	printf("\nВызов функций с параметром Desc:\n");
	func1(*desc);
	printf("\n");
	func2(desc);
	printf("\n");
	func3(*desc);
	printf("\n");
	printf("\nВызов функций, которые возвращают Base:\n");
	func12();
	printf("\n");
	func22();
	printf("\n");
	func32();
	printf("\n");
	delete base;
	delete desc;
	printf("\n\n\n\n\n\n\n");

	printf("Создание объекта\n");
	Basic* bas = new Basic(8);
	//printf("Создание первого shared_ptr\n");
	shared_ptr<Basic> ptr1(bas);
	{
		//printf("Создание второго shared_ptr\n");
		shared_ptr<Basic> ptr2(ptr1);
		printf("Удаление ptr2\n");
	}
	
	printf("\n\n\n\n\n\n\n");

	{
		printf("Создание объекта\n");
		unique_ptr<Basic> bas2(new Basic(9));
		bas2->method1();
		printf("Выход из области видимости\n");
	}
	printf("\n\n\n\n\n\n\n");
	//_getch();
	printf("Удаление ptr1 - завершение работы программы\n");
	
}