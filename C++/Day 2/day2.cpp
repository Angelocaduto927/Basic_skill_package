// 数组，指针，函数   如何把数组传给函数
/*
#include <iostream>
using namespace std;

void bubblesort(int *arr, int len)
{
    for (int i = len - 1; i >= 0; i--)
    {
        for (int j = 0; j < i; j++)
        {
            if (arr[j] > arr[j + 1]) // 这里arr虽然是一个指针，但是在函数里arr[i]会等价于*(arr + i)，因此可以访问元素
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp; // 因为是传递地址，所以外面的arr也会被修改
            }
        }
    }
}
int main()
{
    int arr[5] = {5, 4, 3, 2, 1};
    int len = sizeof(arr) / sizeof(arr[0]); // C++没有len函数，对于string和vector可以用size()函数
    bubblesort(arr, len);
    for (int i = 0; i < len; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
    return 0;
}
*/

/*
结构体：用户自定义的数据类型，允许用户储存不同的数据类型   //和python的Class很像
定义 写在main函数外面
    struct 结构体名{
        //结构体成员列表
        数据类型 成员1;  //比如年龄，姓名，性别等等elements
        数据类型 成员2;
    };
通过结构体创建变量  都在main函数里
    结构体创建变量的时候struct可以省略，但定义的时候struct不可以省略
    1. struct 结构体名 变量名;
        struct Student s1;
        s1.age = 18; // 用点访问结构体成员
        s1.name = "Tom";
        s1.sex = 'M';
    2. struct 结构体名 变量名 = {成员1, 成员2, ...};
        struct Student s2 = {18, "Tom", 'M'};
    3. 定义结构体时顺便创建变量
        struct Student{
            int age;
            string name;
            char sex;
        }s3; //这样就定义了一个变量
        s3.age = 18;
        s3.name = "Tom";
        s3.sex = 'M';

结构体数组 将自定义的结构体放入到数组中方便维护
    struct 结构体名 数组名[数组大小] = { {}，{}，{} };
    e.g. struct Student s[3] = { {18, "Tom", 'M'}, {19, "Jerry", 'M'}, {20, "Mary", 'F'} };  定义的时候已经赋值
    访问结构体数组的成员
        s[0].age = 20;
        s[0].name = "To"; 修改结构体数组

结构体指针
通过指针访问结构体中的成员
    利用操作符 -> 可以通过结构体指针访问结构体属性
    struct Student * p = &s1; // 取地址符号&，指针变量，取s1地址时返回的是student的数据类型，当然struct可以省略
    p->age; // 通过指针访问结构体成员，语法“指针->成员”就可以获取了

结构体嵌套结构体   结构体的成员可以是另一个结构体   比如老师的机构体成员里有一个成员是学生的结构体，学生的结构体也需要单独定义
    struct student{
        int age;
        string name;
    };
    struct teacher{
        struct student stu[5]; // 定义老师的学生的结构体数组
    };
    //学生定义要先于老师，struct student ~ int/float也是一个数据结构
    t.stu[0].age = 18; // 定义老师的学生的年龄

结构体做函数参数，将结构体作为参数向函数中传递
    1. 值传递
        void func(struct Student s) // 传递结构体
        {
            s.age = 20; // 修改传入的结构体的值
        }
        int main()
        {
            struct Student s1;
            s1.age = 18;
            func(s1); // 传递结构体
            cout << s1.age << endl; // 输出18，值传递，函数内修改不会影响函数外的值
        }
    2. 地址传递
        void func(struct Student * s) // 传递结构体指针
        {
            s->age = 20; // 修改传入的结构体的值
        }
        int main()
        {
            struct Student s1;
            s1.age = 18;
            func(&s1); // 传递结构体指针
            cout << s1.age << endl; // 输出20，地址传递，函数内修改会影响函数外的值
        }

结构体中const的使用操作，防止误操作
    值传递虽然可行，但是因为要复制一份，很浪费空间，更推荐用地址传递减少内存空间，也因此需要防止误操作
    void func(const struct Student * s) // 传递结构体指针,并且这个指针在函数内不能被修改
    {
        // s->age = 20; // 错误，不能修改const指针指向的值
        cout << s->age << endl; // 可以读取const指针指向的值
    }

清屏操作
    system("cls");
*/

/*
C++核心编程 面向对象编程技术
1. 内存分区模型  C++程序在执行时，将内存大方向划分为4个区域
    1.代码区 存放函数体的二进制代码，有操作系统进行管理
    2.全局区 存放全局变量和静态变量，以及常量
    3.栈区 由编译器自动分配释放，存放函数的参数值，局部变量和临时变量等
    4.堆区 由程序员分配和释放，若程序员不释放，程序结束时由操作系统回收
    不同区域存放的数据，赋予不同的生命周期，更灵活的编程

    1.1 程序运行前 (程序被编译编程一个二进制的exe文件后，但是还没有双击运行之前)
        已经有两个区域：代码区和全局区
        代码区：
            存放CPU执行的机器指令 (二进制代码)
            代码区是共享的，让频繁被执行的程序只需要有一份代码就可以
            代码区是只读的，防止有程序意外的修改了他的指令
        全局区：
            全局变量和静态变量存放于此 （写在函数内的变量是局部变量，写在外面的是全局变量）
            还包括常量区，字符串常量(双引号括起来的字符串)和其他常量（const修饰的全局变量）存放于此
            该区域的数据在程序结束后由操作系统释放

            静态变量，在普通变量前面加static关键字
                static int count = 0; // 静态变量只会被初始化一次

            const修饰的局部变量不放在全局区
                int main(){
                    const int count = 0; //局部常量
                }

            总结：
                1.全局变量在        写在函数外且没有const
                2.静态变量在        写在函数里或外且有static
                3.字符串常量在      写在函数里或外且有双引号
                4.全局常量在        写在函数外且有const
    1.2 程序运行后 (双击exe文件后)
        栈区 由编译器自动分配释放，存放函数的参数值，局部变量等
            注意：不要返回局部变量的地址，栈区开辟的数据由编译器自动释放
                int* func(){
                    int a = 10;
                    return &a; // 错误，返回局部变量的地址,而a是局部变量存放在栈区，当函数执行完之后会自动释放
                }
                int main(){
                    int* p = func();
                    cout << *p << endl; // 有的编译器第一次运行会输出10，因为编译器做了保留，但是vscode gcc会直接警告并且不可运行
                    cout << p << endl; // 错误，第二次运行会输出随机值，因为p指向的地址已经被释放
                }
        堆区 由程序员分配和释放，若程序员不释放，程序结束时由操作系统回收
            在C++中，主要利用new在堆区开辟内存
            int * func(){
                //利用new将数据开辟到堆区
                int * p = new int(10); // 开辟方法，new 加 数据类型(初始值)， 然后他会返回该数据对应的类型的指针
                //指针* p 仍然是局部变量，放在栈区，指针保存的数据在堆区
                return p; // 返回指向堆区的指针
            }
            int main(){
                int * p = func(); // p指向堆区的地址
                cout << *p << endl; // 输出10
                delete p; // 释放堆区的内存，delete加指针变量名
                p = NULL; // 将指针置空，防止野指针
                return 0;
            }

            在堆区开辟数组
            int * arr = new int[5]; // 开辟一个int类型的数组，长度为5
            赋值与正常数组一样
            arr[i] = 值; // arr[i] 等价于 * (arr + i)
            delete[] arr; // 释放堆区的数组，delete加中括号
*/

/*
引用  给变量起别名
    语法： 数据类型 &别名 = 原名;  （别名可以和原名一样）
    两个变量指向同一块内存，一个修改另一个也修改
引用的注意事项
    1.引用必须初始化
        int &b = a; // 右边必须要有等于一个变量，不可以不写        int& b = a;也可以，空格不重要
    2.引用初始化之后不可改变
        确定之后，b不可以再更改成其他变量的别名
        b = c; //正确，不是指向别的地方，而是赋值操作
引用做函数参数（引用传递）,效果和指针传递一样但是更简洁
    函数传参时，可以利用引用的技术让形参修饰实参; 可以优化指针修改实参的方法
    void func(int &a, int &b) // 传递引用, 其实就是&a = 传入参数
    {
        a = 10; // 修改传入的实参的值
        b = 20;
    }
引用做函数返回值  作用：引用可以作为函数的返回值存在
    注意：不要返回局部变量引用
    用法：函数调用可以作为左值
    int& func(){     //int&就是返回引用类型数据
        int a = 10;
        return a; // 错误，返回局部变量的引用
    }
    int main(){
        int &b = func(); // 错误，b是引用类型，func()返回的是局部变量的引用
        cout << b << endl; //  报错
        return 0;
    }

    int& func(){     //int&就是返回引用类型数据
        static int a = 10;  //静态变量，存放在全局区，全局区上的数据在程序结束后系统释放
        return a; // 正确，返回静态变量的引用
    }
    int main(){
        int &b = func(); // 正确，b是引用类型，func()返回的是静态变量的引用
        cout << b << endl; //  输出10

        func() = 20; //  func()返回了a的引用，相当于把a返回了，然后就是a = 20
        return 0;
    }

引用的本质： 内部实现是指针常量（指向不可改，指向的值可以改）  int * const p = &a;
    所有的定义和赋值解引用都是通过编译器自动做的

常量引用  常量引用主要用来修饰形参，防止误操作
    void func(const int &a) // 传递常量引用
    {
        // a = 10; // 错误，不能修改常量引用的值
        cout << a << endl; // 可以读取常量引用的值
    }
    int & ref = 10; // 错误，不能将常量引用赋值给常量
    const int & ref = 10; // 正确，常量引用可以指向常量;  编译器把代码修改成了 int temp = 10; const int & ref = temp; 找不到原名
    ref = 20; // 错误，不能修改常量引用的值

*/

/*
函数提高
1.函数默认参数
    形参可以有默认值， 返回值类型 函数名 （参数=默认值）{}
        1.如果某个位置有默认值，那么他的右边全部都要有默认值
        2.如果函数声明有默认值，函数实现的时候就不能有默认参数  ||  如果实现的时候已经有了默认参数，声明的时候就不能有默认参数

    函数声明要写在main的前面，但是有了函数声明后，函数的具体定义可以放在后面
    函数声明
        void func(int a, int b = 10); // b有默认值
        int main(){
            func(1); // 1 10
            func(1, 2); // 1 2
        }
        void func(int a, int b = 10) // 报错，即使函数声明的默认参数和实现参数是一样的也不可以在实现部分再次定义默认参数，会冲突
        {
            cout << a << " " << b << endl;
        }
2.函数占位参数
    形参可以有占位参数，用来做占位，调用时必须填补该位置
    语法： 返回值类型 函数名（数据类型）{}
    甚至可以和默认参数结合
        void func(int a, int = 10); // b有默认值

3.函数重载  函数名可以相同，提高复用性
    1.重载的条件（三个都满足才行）：
        ·同一个作用域下（比如都是全局的//都在main的外面）
        ·函数名相同
        ·函数参数类型不同或者个数不同或者顺序不同 （注意函数的返回值不同不可以作为重载的条件）

    e.g.
        void func(int a, int b) // 函数1
        {
            cout << a << " " << b << endl;
        }
        void func(double a, double b) // 函数2
        {
            cout << a << " " << b << endl;
        }
        //这样就可以根据调用时候传入的参数的数量，顺序，和数据类型判断用的是哪个函数

        int func(int a, int b) // 函数1
        {
            cout << a << " " << b << endl;
            return 0;
        } //这个就不可以，因为返回值类型不可以作为重载的条件，调用的时候无法判断用的哪个函数

        //如果作用域不同，比如一个是局部的，一个是全局的，也会不知道要用哪个

    注意事项：
        1.引用作为重载的条件
            void func(int& a){
                cout << a << endl;
            }
            void func(const int& a){
                cout << a << endl;
            }
            // 这个是可以的，因为引用的类型不同,const int& 和 int& 不一样
            int a = 10;
            func(a); // 调用第一个函数  原因：a是一个变量，可读可写，所以优先走第一个函数，也是可读可写
            func(10); // 调用第二个函数  原因： int &a = 10不合法，但是const int &a = 10合法,所以只会走第二个

        2.函数重载碰到函数的默认参数
            void func(int a, int b = 10){
                cout << a << " " << b << endl;
            }
            void func(int a){
                cout << a << endl;
            }
            func(10); // 这个就会报错，因为有默认参数，两个都可以调用，编译器无法判断用的是哪个函数；
            func(10, 20); // 这个就不会报错，因为第二个函数没有默认参数，编译器可以判断用的是哪个函数
            函数重载尽量不要写默认参数

*/

/*
类和对象
C++面向对象的三大特性： 封装，继承，多态； C++认为万事皆为对象，对象上有其属性和行为； 具有相同性质的对象可以抽象成一个类

1.封装
    1.1意义
        ·将属性和行为作为一个整体，表现生活中的事物
        ·将属性和行为加以权限控制
    1.2语法
        class 类名{
            访问权限： 属性(变量)/行为(函数)
        };

        e.g.
        class Circle
        {
        public: // 公有权限
            //类中的属性和行为统一称为成员
            //属性 成员属性 成员变量
            //行为 成员函数 成员方法
            //属性
            int r; // 半径
            //行为
        public:
            double area() // 面积
            {
                return 3.14 * r * r;
            }
            void show_r() // 显示半径
            {
                cout << r << endl;
            }
            void set_r(int r1) // 设置半径
            {
                r = r1; // this指针指向当前对象的地址
            }

        };
        //通过类创建具体的对象
        Circle c1; // 创建对象
        c1.r = 10; // 访问对象的属性
        cout << c1.area() << endl; // 访问对象的行为

    2.权限
        访问权限有三种：
        1. public 公有权限，类内外可以访问
        2. private 私有权限，类外不可以访问，类内可以访问，子不可以访问
        3. protected 保护权限，类外不可以访问，类内可以访问，子可以访问
        访问权限的顺序是： public -> protected -> private

        class test
        {
        public:
            int a;
        private:
            int b;
        protected:
            int c;
        public:
            void func()
            {
                a = 1; // 可以访问
                b = 2; // 可以访问
                c = 3; // 可以访问
            }
        };
        class p;
        p.a = 1; // 可以访问
        p.b = 2; // 错误，不能访问
        p.c = 3; // 错误，不能访问

    3.struct 和 class的区别
        唯一区别：默认的访问权限不同
        struct 默认是public，class 默认是private

    4.将成员属性设置为私有
        优点1：将所有成员属性设置为私有，可以自己控制读写权限
        优点2：对于写权限，我们可以检测数据的有效性 (在成员函数里面加入If语句+return，判断输入设置是否有效)

        主要思路：属性全部都设置为私有，然后在class里面提供公有的读写方法，这样就可以控制权限
        e.g.
        class P
        {
        private:
            int a; // 私有属性,可读可写
            int b; //只读
            int c; //只写
        public:
            void set_a(int a1) // 设置a
            {
                a = a1; // 赋值
            }
            int get_a() // 获取a
            {
                return a; // 返回a
            }
            int get_b() // 获取b
            {
                return b; // 返回b
            }
            void set_c(int c1) // 设置c
            {
                c = c1; // 赋值
            }
        };

    5.实际案例
        全局函数传入n个参数
        类函数只需要传入n-1个参数，因为自身不需要传入
        地址传递节省内存空间（指针或者引用都可以）
        在类中，可以让另一个类作为成员

    6.把类拆开放到不同的头文件，源文件调用
        1. 头文件 point.h
            #progma once // 防止头文件重复包含
            #include <iostream>
            using namespace std;
            class Point
            {
            public:
                void method1(int a);
                void method2();
            private:
                int x;
                int y;
            };   //头文件里只需要写出声明，不需要写出具体的实现，直接分号补全
        2. 源文件 point.cpp
            #include "point.h" // 引入头文件
            // void method1(int a)
            // {
            //     x = a; // 直接访问类的属性
            // }
            // void method2()
            // {
            //     y = b;
            // }
            // 其他什么iostream, class, private, public, 属性全部省略不需要写，因为已经声明过了，只需要写他的函数实现
            //！！！函数实现的时候因为这样写是全局函数，但是我们知道这些method1,method2其实是成员函数，不是全局的，所以需要告诉编译器他是哪个作用域下的成员函数
            如
            point::method1(int a)  // 这样就可以了
            {
                x = a; // 直接访问类的属性
            }
            point::method2()
            {
                y = b;
            }
    7.对象的初始化和清理
        C++中每个对象都会有初始设置以及对象销毁前的清理数据的设置
        构造函数
            对象或者变量没有初始状态，对其使用后果是未知的

            作用：创建对象时为对象的成员属性赋值，由编译器自动调用无须手动调用（就比如声明了一个int变量就会自动赋值为0）
        析构函数
            对象或变量使用之后没有及时清理，也会造成一定的安全问题

            作用：对象销毁前系统自动调用，执行一些清理工作

        这两个函数将会被编译器自动调用，完成对象初始化和清理工作，这也是编译器强制我们要做的事情，因此如果我们不提供构造和析构，编译器会提供且他提供的构造、析构函数是空实现


        构造函数语法：
            类名（）{}
            1.构造函数，没有返回值也不需要写void
            2.函数名称与类名相同
            3.函数可以有参数，因此可以发生重载
            4.程序在调用对象时会自动调用构造，无须手动调用且只会调用一次

        析构函数语法：
            ~类名（）{}
            1.析构函数，没有返回值也不需要写void
            2.函数名称与类名相同，前面加一个~符号
            3.函数不可以有参数，因此不可以发生重载
            4.程序在对象销毁前会自动调用析构，无须手动调用且只会调用一次

        e.g.
        Class Circle
        {
        public:
            Circle(){
            } //编译器自动创建的空构造函数
            Circle() // 构造函数
            {
                cout << "Circle constructor" << endl;
            }
            ~Circle() // 析构函数
            {
                cout << "Circle destructor" << endl;
            }
        }
        void func()
        {
            Circle c1; // 创建对象，自动调用构造函数
        } // 离开作用域，自动调用析构函数
        int main()
        {
            func();    // 创建对象，自动调用构造函数
        }
        //会输出
        // Circle constructor
        // Circle destructor     因为c1是局部变量，在栈区，func执行之后会释放销毁，所以两个都会输出

        构造函数的分类和调用
            按参数：
                有参构造
                    Circle(int r) // 构造函数
                    {
                        r1 = r; // 赋值
                    }
                无参构造（默认构造）
                    Circle() // 构造函数
                    {
                        r1 = 0; // 赋值
                    }
            按类型
                普通构造
                拷贝构造
                    Circle(const Circle &c) // 拷贝构造函数
                    {
                        r1 = c.r1; // 赋值
                    }

            三种调用方法
                括号法
                    Circle c1(10); // 创建对象，调用有参构造
                    Circle c2; // 创建对象，调用无参构造（默认构造）
                    Circle c3(c1); // 创建对象，调用拷贝构造
                    注意事项： 调用默认构造函数的时候不要加（），否则会被认为是函数声明（在一个函数里面写另一个函数的声明是允许的）
                        Circle c1(); 一个无参的返回Circle类型的函数声明

                显示法（创个匿名对象然后再给他个名字）
                    Circle c1;
                    Circle c1 = Circle(10); // 创建对象，调用有参构造
                    Circle c3 = Circle(c1); // 创建对象，调用拷贝构造

                    Circle(10) 是一个匿名对象，创建了一个对象但是没有名字，左边加一个变量等号就有名字了； 特点：当前行执行结束后会立即回收匿名对象
                    注意事项：不要利用拷贝构造函数，初始化匿名对象，因为编译器会认为 Circle(c3) === Circle c3;这样就重复定义了
                    e.g.
                    Circle(c1);   你以为是利用拷贝构造函数初始化了一个匿名对象
                    实际上会报错，编译器认为这等价于 Circle c1, 但是c1在前面早就初始化过了，所以重复定义

                隐式转换法
                    Circle c1 = 10; // 创建对象，调用有参构造，相当于Cicle c1 = Circle(10);
                    Circle c3 = c1; // 创建对象，调用拷贝构造  相当于Circle c3 = Circle(c1);
                    注意事项：隐式转换法只能用在有参构造函数上，不能用在无参构造函数上，因为无参构造函数没有参数

        拷贝构造函数的调用时机
            1.使用一个已经创建完毕的对象来初始化一个对象
            2.值传递的方式给函数参数传参
                void dowork(Circle c) // 值传递
                {
                }
                void test(){
                    Circle c4 = Circle(20);
                    dowork(c4); // 调用拷贝构造函数
                }
                //会调用一次有参构造和一次拷贝构造，因为值传递的本质就是拷贝一份数据然后传递过去，所以函数参数circle c会调用拷贝构造函数
            3.以值的方式返回局部对象
                Circle func()
                {
                    Circle c5; // 创建对象，调用无参构造, 这是个局部变量，函数调用结束之后就会被销毁
                    return c5; // 返回局部对象，调用拷贝构造函数，所以返回的时候是拷贝了一份的新的数据然后传出去
                }
                int main()
                {
                    Circle c6 = func(); // 创建对象，调用拷贝构造函数，这一句话和上面的return共同构成了一次拷贝构造函数的调用
                }
                顺序是调用无参构造 -> 调用拷贝构造 -> 调用析构函数  -> 调用析构函数  // c5和c6不一样

        构造函数的调用规则
            默认情况下，只要写了一个类编译器就会至少添加三个函数
            1.空的默认构造函数
            2.空的默认析构函数
            3.默认拷贝函数，对属性进行拷贝（值拷贝）

            规则：
            1.如果写了有参构造函数，编译器就不会提供无参构造函数，但会提供拷贝构造函数
                因此如果写了有参构造，然后又想用默认构造，必须要自己写
            2.如果写了拷贝构造函数，编译器就不会提供无参构造函数和拷贝构造函数
                因此如果写了拷贝构造函数，然后又想用默认构造、有参构造，必须要自己写

        深拷贝和浅拷贝（常见的坑）
            浅拷贝：编译器提供的简单的赋值拷贝操作
            深拷贝：在堆区重新申请空间，进行拷贝工作

            Class Person
            {
            public:
                Person(int age, int Hight)
                {
                    m_age = age;
                    m_Hight = new int(Hight); // 在堆区开辟空间,并且用指针接受
                }
                ~Person() //作用：通常将堆区开辟的数据释放操作
                {
                    if (m_Hight != NULL) // 防止野指针
                    {
                        delete m_Hight; // 释放堆区开辟的内存
                        m_Hight = NULL; // 将指针置空，防止野指针
                    }
                    cout << "析构函数" << endl;
                }
                int m_age;
                int *m_Hight; // 指针类型的成员变量
            }
            int main(){
                Person p1(18, 180); // 创建对象，调用构造函数
                Person p2(p1); // 调用拷贝构造函数，浅拷贝
                //会报错
            }

            解释：
                1.P1，P2是在栈区的变量，他们的构建和析构遵循先进后出原则，所以P2会先被析构释放，然后才是P1。
                2.这里没有写拷贝构建函数，座椅使用的是编译器自带的浅拷贝构建函数，也就是单纯的完全的复制粘贴
                3.对于指针*Height， P1里面存放的是一个指向堆区的地址，因此P2拷贝过去之后也是一个指向堆区的地址
                4.P2析构的时候按照代码会把堆区的内存释放掉，但是轮到P1的时候，他的指针也不为空所以会再次释放
                5.然而重复释放堆区内存会报错，所以代码有问题，非法操作

            解决方案：
                1.自定义拷贝构造函数，进行深拷贝
                    在拷贝的变量中，也重新申请一个堆区空间，然后将值拷贝过去，值是一样的，但是地址不一样，不会重复释放
                    Person(const Person &p) // 拷贝构造函数
                    {
                        m_age = p.m_age; // 拷贝年龄
                        m_Hight = new int(*p.m_Hight); // 在堆区重新开辟空间，拷贝高度,解引用->重新生成空间
                        //编译器默认 m_Hight = p.m_Hight;
                    }


*/