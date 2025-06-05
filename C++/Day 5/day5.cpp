/*
C++提高编程   针对C++泛型编程（主要通过模板实现）和STL技术   |  另一个思想是前面学过的面向对象编程思想

1.模板
    1.1模板的概念
        模板就是建立通用的模具，大大提高复用性
        模板不可以直接使用，只是框架，且不是万能的
        C++提供两种模板机制 函数模板|类模板

    1.2函数模板语法
        1.2.1作用：建立一个通用函数，其函数返回值类型和形参类型可以不具体指定，用一个虚拟的类型来代表
        1.2.2语法：
            template<typename T>
            函数声明或定义
        1.2.3解释：
            template -- 声明创建模板
            typename -- 表明他后面的符号是一种通用数据类型，让编译器在后面的代码不要报错（typename可以用class代替）
            T -- 通用的数据类型，名字可以替换，通常为大写字母

        1.2.4例子：
            template<typename T>
            void myswap(T &a, T &b)  //将类型参数化
            {
                T temp = a;
                a = b;
                b = temp;
            }
            //使用（两种方式）
            1.自动类型推导
                myswap(a,b);  编译器自己推导出来传进去的参数是什么类型
            2.显示指定类型
                myswap<int>(a,b);   多一个尖括号，里面放T对应的数据类型，让编译器不用猜了

        1.2.5注意事项：
            1.使用自动类型推导式，必须推导出来一致的数据类型T，才可以使用
                比如传入的一个是int,传入的一个是char，不一致用不了
            2.模板必须要确定出T的数据类型，才可以使用
                例子
                    template<typename T>
                    void func()
                    {
                        cout << "11" << endl;
                    }
                    //调用
                    //func();  会报错，因为编译器没有办法推导出来这个T应该是什么数据类型，函数体并没有传参，但是模板必须要让T是某一种数据类型，所以只能用显示指定类型
                    func<int>();  这个指定成什么数据类型都没有关系，因为反正函数体里也用不到这个T，但是必须要让它是一个东西

        1.2.6普通函数和函数类型的区别
            普通函数调用时可以发生自动类型转换（隐式类型转换）
            函数模板调用时，如果利用自动类型推导，不会发生隐式类型转换
            如果利用显示指定类型的方式，可以发生隐式类型转换

            普通函数例子
                int add(int a, int b)
                {
                    return (a+b)
                }
                int a = 10;
                char c = 'c';
                cout << add(a,c) << endl;   //会把c隐式转换成ASCII码，然后相加

            自动类型推导
                会报错，两个变量的类型不一致，无法调用（原因T既可以是整型也可以是字符型，他不知道应该要哪个，不会出现像普通函数一样的强制转成整型）

            显示指定类型
                add<int>(a,c); 可以，他现在知道要变成Int类型而不是char型

        1.2.7普通函数和函数模板的调用规则（普通函数可以和函数模板发生重载）
            1.如果普通函数和函数模板都可以实现，优先调用普通函数
            2.可以通过空模板参数列表来强调调用函数模板
            3.函数模板也可以发生重载
            4.如果函数模板可以产生更好的匹配，优先调用函数模板

            例子
            void mprint(int a, int b)
            {
                cout << "调用普通函数" << endl;
            }
            template<typename T>
            void mprint(T a,T b)   //跟上面的函数重载了
            {
                cout << "调用模板" << endl;
            }

            //test 1
            int a = 1; int b = 1;
            mprint(a,b);   //现在两个函数都可以实现，且都是int类型可以说是一模一样，所以按照规定1，优先调用普通函数，输出“调用普通函数”

            //test 2
            如果普通函数只有声明没有实现   void mprint(int a, int b);
            那么调用的时候仍然是两个都可以调用优先找普通函数，结果发现普通函数没有实现，报错

            //test 3
            空模板参数列表，强制调用函数模板
            mprint<>(a,b);  现在就强制使用了模板，输出“调用模板”

            //test 4
            模板也可以重载
            再加一个
            template<class T>
            void mprint(int a, int b, int c)
            {
                cout << "重载" << endl;
            }

            //test 5
            如果函数模板匹配的更好优先调用函数模板
            char c1 = 'a';
            char c2 = 'b';
            mprint(c1,c2);  //这个调用仍然是两个函数都可以调用，因为普通函数可以强制转换类型变成int，但是因为用模板的匹配更好不需要强制转换，直接让T是char类型就可以了，所以会优先调用函数模板


        1.2.8模板的局限性（并非万能）
            比如
                template<class T>
                void func(T a, T b)
                {
                    a = b;
                }
                如果传入的是数组，而C++不支持对数组进行和其他数据类型类似的直接全部赋值的操作，所以不行
                另：在函数传递中 void func(int arr[]) 效果和 void func(int * arr)是一样的，因为前者也会把数组简化为首地址指针，在函数内部使用arr[i]其实是在解首地址偏移后的地址，所以就是一个指针，在这个条件下T也会被自动检测为指针类型

                再例如
                如果传入的是自定义的Person类型，也无法正常运行

                因此C++提供模板的重载，可以为这些特定的类型提供具体化的模板 （另一个方法：运算符重载）
                    template<> bool mycompare(Person &p1, Person &p2)  //前面加template<>和指定类型就是具体化的模板，当编译器遇到Person类型的调用时，就会用下面这个而不是通用的那个
                    {
                        if (p1.m == p2.m && p1.a == p2.a)
                        {
                            return true;
                        }
                        else
                        {
                            return false;
                        }
                    }

    1.3类模板
        1.3.1语法
            建立一个通用的类，类中的成员数据类型可以不具体制定，用一个虚拟的类型来代表
            template<typename T， typename Y>  可以有多个类型，因为成员不会全部都是一种类型的
            Class Person
            {
            Public:
                Person(T a, Y b)
                {
                    this->name = a;
                    this.age = b;
                }
                T name;
                Y age;
            };
            Person<string,int> p1("Tom",18);

        1.3.2类模板和函数模板的区别
            1.类模板没有自动化类型推导的使用方式，必须显示指定
            2.类模板在模板参数列表中可以有默认参数   如 template<class T = int> 这样下面就可以不显示指定类型

        1.3.3类模板中成员函数的创建时机
            普通类中的成员函数一开始就创建了
            类模板中的成员函数在调用的时候才创建
            无法提前确定数据类型，所以不会创建，只有确定了数据类型才会看能不能调出来有没有语法错误。所以如果模板中的函数有错误，在没有调用它的情况下程序也不会报错

        1.3.4类模板对象做函数参数
            1.指定传入的类型      直接显示对象的数据类型
            2.参数模板化          将对象中的参数变为模板进行传递
            3.整个类模板化        将这个对象类型 模板化进行传递

            template<class T1>
            class Person
            {
            public:
                Person(T a)
                {
                    this->m_a = a;
                }
                void showperson()
                {
                    cout << "show" <<endl;
                }
                T m_a;
            };

            //method1
            void method1(Person<int>&p)  //把整个Person<int>p传进来且用引用的方式,指定类型的意思是所有数据类型都写清楚了
            {
                p.showperson();
            }

            Person<int>p(10);   //如何把这个类模板对象p传到method1里面作为参数调用showperson()？
            method1(p);

            //method2
            template<class T>                 //参数模板化，意思是告诉编译器是哪个类的，但是我创建对象的参数具体是什么数据类型就让编译器推，这样同一个类的不同数据都能用
            void method2(Person<T>&p)
            {
                p.showperson();
                cout << typeid(T).name() << endl; //可以看数据类型的名字
            }

            Person<int>p(10);
            method2(p);

            //method3
            template<class T>
            void method3( T &p)  //整个类模板化，就是让编译器直接去推这是哪一个类，里面的参数数据类型是什么，这样不同类的也能用
            {
                p.showperson();
            }

            Person<int>p(10);
            method3(p);

        1.3.5类模板和继承
            当子类继承的父类是一个类模板时，子类在声明的时候，要指定出父类中T的类型
            如果不指定，编译器无法给子类分配内存
            如果想灵活指定出父亲T的类型，子类也许变为类模板

            e.g.
            class son : public base<int>

            template<class T, class T1>
            class son : public base<T1>
            {
                T1 obj;
            };
            创建对象 son<int,char> s;

        1.3.6类模板成员函数类外实现
            普通函数模板的类外实现
            template<class T>
            Person::Person(T a)
            {
                this->m_a = a;
            }

            类模板构造函数的类外实现
            template<class T>
            Person<T>::Person(T a)
            {
                this->m_a = a;
            }
            类内声明
            template<class T>
            class Person
            {
            public:
                Person(T a);
                T m_a;
            };

            类模板成员函数的类外实现（即使函数没有形参，也必须写成一个template的格式，因为这样才知道时类模板的成员函数）
            template<class T>
            void Person<T>::showperson()
            {
                cout << "111" << endl;
            }

        1.3.7类模板分文件编写
            问题：类模板的成员函数是在调用的时候才创建的，导致分文件编写时链接不到

            解决办法1：直接包含.cpp源文件
                一般而言是在.h头文件里面写类的框架，然后在.cpp源文件里面写类里面函数的具体实现
                然后在main的主文件里面包含#include .h的头文件即可，但是这个写法对于类模板是会报错的
                解决办法是把包含的.h文件变成.cpp文件，就不会报错了

                C++头文件和链接的规则
                    1.首先把主文件中包含的头文件变成单独的头文件中实际的代码
                    2.所有.cpp编译成.o的文件，同时会生成一个机器码，如果有包含.h，那么他就能通过.h的机器码找到对应的.cpp的实现文件，这样就链接了起来
                    3.翻译成机器语言
                    4.根据机器码去所有的.o文件中链接找需要的补充文件

                    普通类的情况:
                    首先头文件里会把类的声明代码加入main.cpp，然后编译。因为类的实现源文件是可以编译运行的函数，所以在编译阶段他们的.cpp文件可以正常的变成.o编译文件
                    在main.cpp运行的时候，会通过.h的机器码找到这个对应的.o编译文件然后调用里面的函数
                    因此链接成功，可以正常使用

                    模板类的情况（有问题的写法）
                    首先头文件里会把类的声明代码加入main.cpp，然后编译。因为类的实现源文件是不可以直接编译运行的函数，参考规定“不能直接使用模板”，因此他无法变成一个.o的编译文件
                    在main.cpp运行的时候，通过.h的机器码找不到这个对应的.o编译文件，无法调用里面的函数
                    因此链接失败，不可以正常使用

                    模板类的情况（解决办法1）  //少用
                    首先头文件里会把类的实现代码（.cpp）加入main.cpp，然后编译。这样main.cpp里面已经可以看到实现的函数了，并且因为实现文件里面包含了.h的头文件，所以声明也能看到，其实已经是一个完整的代码了
                    在main.cpp运行的时候，直接编译运行整个完整的代码
                    因此链接成功，可以正常使用

            解决办法2：将声明和实现写到同一个文件中，并更改后缀名为.hpp（hpp是约定的名字，并非强制）

                    模板类的情况（解决办法2）  //常用
                    把声明和实现写在一起，这样头文件include<.hpp>替换的时候，也是直接得到完整的代码了，然后main.cpp就编译运行
                    因此链接成功，可以正常使用

        1.3.8类模板与友元 （一个全局函数作为友元访问类模板里的private成员）
            1.全局函数类内实现 - 直接在类内声明友元即可
                template<class T>
                class Person
                {
                    friend void func(Person<T> p)
                    {
                        cout << "11" << endl;
                    }
                public:
                    //构造函数
                private:
                    int m_a;
                };
                Person<int> p(10);
                func(p);
                这个是全局函数类内实现友元，函数func并不是Person的成员函数，他是全局的，因此类的对象无法调用他，然后他顺便在类内把实现写了

            2.全局函数类外实现 - 提前让编译器知道全局函数的存在

                template<class T>  //因为下面的函数模板里面提到了Person，又要让编译器先知道这个类模板的存在，所以要写声明
                class Person;

                template<class T>
                void func(Person<T> p)  //全局函数，无需作用域，但是要提前让编译器知道这个函数模板的存在，所以要放在类模板的实现前面
                {
                    cout << "11" << endl;
                }

                template<class T>
                class Person
                {
                    //friend void func(Person<T> p);   //普通函数声明，但是下面的实现是函数模板的实现，不匹配
                    friend void func<>(Person<T> p);   //加个空的模板参数列表让编译器知道这是一个函数模板的声明
                public:
                    //构造函数
                private:
                    int m_a;
                };
                Person<int> p(10);
                func(p);

                这是全局函数类内声明，类外实现，类模板的声明、全局函数模板的实现都要提前
*/

// 类模板案例
#include <iostream>
using namespace std;

template <class arrtype>
class Array
{
public:
    // 构造函数
    Array(arrtype array[], int len)
    {
        this->m_arr = new arrtype[len];
        for (int i = 0; i < len; i++)
        {
            m_arr[i] = array[i];
        }
        this->m_len = len;
        this->m_size = sizeof(arrtype) * this->m_len;
    }
    // 拷贝构造函数
    Array(const Array &arr) // 加const
    {
        this->m_len = arr.m_len;
        this->m_arr = new arrtype[this->m_len];
        for (int i = 0; i < this->m_len; i++)
        {
            this->m_arr[i] = arr.m_arr[i]; // 注意这里是arr.m_arr[i],不是arr[i],因为arr这里是一个对象，他不知道arr[i]是什么意思
        }
        this->m_size = arr.m_size;
    }

    ~Array()
    {
        if (this->m_arr != NULL)
        {
            delete[] m_arr;
            this->m_arr = NULL;
        }
    }

    // 重载运算符
    Array &operator=(const Array &arr) // 1.加上const；2.传入的应该是Array的对象，而不是arrtype(Array对象中的宇哥元素),返回的也应该是一个对象而不是其中的arrtype元素
    {
        if (this->m_arr != NULL)
        {
            delete[] m_arr;
            this->m_arr = NULL;
        }
        this->m_len = arr.m_len;
        this->m_arr = new arrtype[this->m_len];
        for (int i = 0; i < this->m_len; i++)
        {
            this->m_arr[i] = arr.m_arr[i];
        }
        this->m_size = arr.m_size;
        return *this;
    }

    // 下标访问
    arrtype &operator[](int index)
    {
        return this->m_arr[index];
    }

    // 尾插
    void tail_add(arrtype &p)
    {
        arrtype *temp = new arrtype[this->m_len + 1];
        for (int i = 0; i < this->m_len; i++)
        {
            temp[i] = this->m_arr[i];
        }
        temp[this->m_len] = p;
        this->m_len++;
        this->m_size = this->m_size + sizeof(arrtype);
        if (this->m_arr != NULL)
        {
            delete[] m_arr;
            this->m_arr = NULL;
        }
        this->m_arr = temp;
    }

    // 尾删
    void tail_del()
    {
        arrtype *temp = new arrtype[this->m_len - 1];
        for (int i = 0; i < this->m_len - 1; i++)
        {
            temp[i] = this->m_arr[i];
        }
        this->m_len--;
        this->m_size = this->m_size - sizeof(arrtype);
        if (this->m_arr != NULL)
        {
            delete[] m_arr;
            this->m_arr = NULL;
        }
        this->m_arr = temp;
    }

    // 获取数组容量
    int get_len()
    {
        return this->m_len;
    }

    // 获取数组大小
    int get_size()
    {
        return this->m_size;
    }

private:
    arrtype *m_arr;
    int m_len;
    int m_size;
};

int main()
{
    int array[] = {1, 2, 3, 4, 5};
    Array a(array, sizeof(array) / sizeof(int));
    cout << a.get_len() << endl;
    cout << a.get_size() << endl;
    cout << a[2] << endl;
    int b = 8;
    a.tail_add(b);
    cout << a.get_len() << endl;
    cout << a.get_size() << endl;
    int c = 9;
    a.tail_add(c);
    cout << a.get_len() << endl;
    cout << a.get_size() << endl;
    a.tail_del();
    cout << a.get_len() << endl;
    cout << a.get_size() << endl;
    Array d(a);
    cout << d.get_len() << endl;
    cout << d.get_size() << endl;
    int array2[] = {1, 3, 2};
    Array e(array2, sizeof(array2) / sizeof(float));
    e = a;
}