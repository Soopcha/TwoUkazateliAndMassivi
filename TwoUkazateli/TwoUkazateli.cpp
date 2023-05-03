﻿#include <iostream>
#include <math.h>
using namespace std;
//ctrl + k + d => выравнивание кода

int main()
{
	setlocale(LC_ALL, "Russian");
	//УКАЗАТЕЛИ; операции & и *

	//переменная-указатель хранит адрес по оторому размещаются данные (и они типпизированны те в них + инфа о типе данных, 
	//для которых они поределены)
	int i = 1; float f = 10;
	int* pi;	//указатель на объект целого типа (умеет харнить только адресс целого типа данных)
	float* pf;	// указатель действительного типа

	pi = &i;	//& - адрессная операция  (возвращает адрес операнда (переменной i в данном случае))
	pf = &f;

	// * - операция разыменования (обращение по адресу в указателе (достаётся то, на что указан адрес))
	cout << "i= " << *pi << "; f= " << *pf << endl;

	// те pi = pf; pi = &f; pf = &i - ОШИБОЧНЫ (тк типизация другая)

	//ЛИШЬ указатель на пустой тип - это просто адрес, бех спецификации типа данных
	void* pv = pf;


	//обманка: заставим *pi указывать на весчественный тип .... что же будет?
	void* pv2 = pf;
	pi = (int*)pv2;
	cout << "?= " << *pi << "; f= " << *pf << endl;
	//показывает как это число float расположено в памяти 


	//можно определить указатель на указатель
	int i2 = 1;
	int* pi2 = &i2;			//int* - описание типа
	int** ppi2 = &pi2;		//int** - описание типа, хранит адрес на указатель на целый объект (хранит адрес на адрес на тип int)

	//обращение к i путём косвенной адресации:
	cout << "i= " << **ppi2 << endl;

	//приоритеты   <-----  ассоциативность (порядок выполнения операций с одинаковым приоритетом)
	//-  !  ~  ++i  --i  (type)  *  &  sizeof
	//**ppi = *(*ppi)     ***ppi = *(*(*ppi))  и тд


	cout << "									    " << endl;
	cout << "  ---------------------------------    " << endl;
	cout << "									    " << endl;



	//Указатели; Динамическая память
	//вся память разделена на статическую и динамическую
	// статическая - размещаются все переменные на этапе компиляции  (управляет компилятор)
	// (все переменные автомотически уничтожаются, когда выходят за пределы области видимости)
	// динамическая - (управляет программа)

	// new и delete - операции для динамического распределения памяти (введены в язык с++)
	// new - резервирование динамической памяти
	// delete - удаление динамической памяти 

	//А прога на Си использует функции библиотеки stdlib.h:     ( в С++ можно заменить на new и delete(даже НУЖНО))
	int* pi4 = (int*)malloc(sizeof(int)); // размещение
	free(pi4); // освобождение (удаление переменной)


	int* pi3 = new int; // размещение новой переменной типа int в динамической памяти и сохранение её адреса в указателе pi
	// new зарезервировал для хранения место в динамической памяти
	// а указатель pi в динамической памяти 

	//   статическая память      |       динамическая память   
	//							 |
	//      pi: [*]----------------------->[      ]			
	//							 |

	*pi3 = 1; //по указателю теперь обращение к динамичекой переменной 

	float* pf3 = new float(10); // размещение переменной с инициализацией
	cout << "*pi3= " << *pi3 << "; *pf3 = " << *pf3 << endl;

	//   статическая память      |       динамическая память   
	//							 |
	//      pi3: [*]----------------------->[   1   ]			
	//							 |
	//      pf3: [*]----------------------->[  10.0 ]	
	//							 |
	//							 |

	// кста  к динамическим переменным можно образаться только указателями
	// так что надо чистить память

	delete pi3; delete pf3; // удаление динамических переменных в которых отпала необходимость   (в Си free)
	// а то сами же указатели лежат в  статической а потом мб область видимости их закончится, они потеряются а в динамической памяти
	//мусор продолжит лежать, так что надо его чистить. И теперь:

	//   статическая память      |       динамическая память   
	//							 |
	//      pi3: [*]-------X-------------->			
	//							 |
	//      pf3: [*]-------X-------------->	
	//							 |
	//							 |
	//те delete - удаляет динамическую память  (но адресс сохраняется даже)
	// !!!!!!!!!!!!!! кажой new ---- свой delete !!!!!!!!!!!  (статическое само удалится, как ненужно будет, а динамическое нет)
	// а то будет утечка памяти




	//					УКАЗАТЕЛИ И МАССИВЫ

	//указатели можно уменьшать и увеличивать на целое число (+ - ++ -- -= +=)
	//эти операции введены для эфективной работы с массивами. 
	//(увеличение указателя на 1 вызывает его перемещение на следующий эл массива)


	//приоритеты									 ассоциативность (порядок выполнения операций с одинаковым приоритетом)
	// ()  []  .   ->  i++  i--						 ----->
	//  -   !  ~  ++i  --i  (type)  *  &  sizeof     <-----


	//(но для начала....)    описание массивов:
	int a[10];				//определение массива из 10 целых эл
	//определение и инициализация массива:
	float b[] = { 1,2,3,4,5 };	// размер можно опустить


	// Индексная операция [] - для обращения к эл массива (это НЕ синтаксическая конструкция)
	for (i = 0; i < 10; i++) a[i] = i; // a[i] = i это выражение


	//операция sizeof(a) - возвращает размер массива в байтах
	for (i = 0; i < sizeof(a) / sizeof(int); i++) a[i] = i;
	// или
	for (i = 0; i < sizeof(a) / sizeof(a[0]); i++) a[i] = i;
	//              \						   /   sizeof(a) - те 10 * sizeof(int) ( sizeof(int) тоже в байтах)
	//				 ----------V--------------
	//                     кол-во эл


	//Имя массива - обозначает указатель на начало массива.
	if (a == &a[0])				//a==&a[0]   те можно удобно это юзать
		cout << "Индификатор массива можно использовать как указаель на его начало (адрес 0-го эл)" << endl;


	//Операции сравнения применимы к указателям. ПРАВИЛО сложения указателя с целым числом: 
	//изменение указателя на 1 вызывает изменение адреса в указателе на sizeof(типа данных)
	for (i = 0; i < sizeof(b) / sizeof(float); i++)
		cout << " " << *(b + i) << endl;	//это эквивалентно b[i] (индексная операция делается компилятором именно таким образом)
	//те    указатель += n
	//          <=>
	//      адрес += n*sizeof(тип)
	// это работает тк все эл стоят друг за другом в памяти



	//Строковые константы - в памяти как массивы символов, с 0-вым байтом в конце
	char s[] = "0123456789";
	// s: [0][1][2][3][4][5][6][7][8][9]0      0 - это конец стр значит и этим можно пользоваться

	char* ps = s;	//	указатель на начало строки
	cout << *ps << endl;
	++ps;			//	переместили указатель на следующий эл
	cout << *ps << endl;
	ps += 4;		//сместили указатель на 4 эл
	cout << *ps << endl;

	cout << "                              " << endl;


	char* ps2 = s;
	// тк == 0 => false       а !=0 => true
	while (*ps2)			//те пока *ps!=0 (пока наш указатель не укажет на 0)
		cout << *ps2++;		//те  ==	*(ps++)  согласно приоритетам

	cout << "                              " << endl;

	while (ps2 > s)			//тк после прошло цикла наш ps2 в конце уже
		cout << *--ps2;		//те ==     *(--ps)  согласно ассоциативности

	cout << "                              " << endl;
	cout << "                              " << endl;




	//указатели можно вычитать и получать целочисленное смещение эл массива
	//указатель1 - указатель2 = (адрес1 - адрес2)/sizeof(тип)

	char s1[] = "0123456789", * ps3 = s; //  <==> char* ps3 = s;    тк char написан левее
	while (*ps3) 
		ps3++;
	while (ps3 > s)		 //		сравнение указателей
		cout << *--ps3;

	cout << "                              " << endl;


	char* ps4 = s, * ps5 = s + 5;			//тк не забываем s == &s[0]
	cout << ps4 - ps5 << " " << ps5 - ps4;	//	-5 5



	cin.ignore();
	return -1;

}
