/*
初始化列表   C++提供了初始化列表语法，用来初始化属性   ，   除了构造函数初始化之外的方法
    语法： 构造函数（参数）：属性1(值1), 属性2(值2), ... {  }
    Class Person{
    public:
        //传统方法
        Person(int a, int b)
        {
            m_a = a;
            m_b = b;
        }
        int m_a;
        int m_b;

        //初始化列表初始化属性
        Person(int a, int b):m_a(a), m_b(b) // 初始化列表
        {
        }
    }
    Person p(1, 2); // 创建对象，调用构造函数
*/

/*
类对象作为类成员  C++类中的成员可以是另一个类的对象，我们称该对象为 对象成员
    Class A{
        A(int a):A_a(a)
        {
        }
        int A_a; // A类的属性
    }
    Class B{
        B(int b, int a):m_b(b),a(a)
        {
        }
        int b;
        A a; // A类的对象成员
    }
    问题：A,B的构建析构顺序
    1. 构造顺序：先构造成员，再构造自己
       - 创建B对象时，先构造A对象，再构造B对象
    2. 析构顺序：先析构自己，再析构成员
       - 销毁B对象时，先析构B对象，再析构A对象
*/

/*
静态成员   就是在成员变量和成员函数前面加上关键字static,称为静态成员
    1.静态成员变量
        所有对象共享同一份数据   所有对象他们的这个成员变量值都一样，改了一个全部都会变
        在编译阶段分配内存       放在全局区
        类内声明，类外初始化     必须要有初始值

        Class Person
        {
        public:
            static int m_A;
        }
        //加上这一句就不会报错
        //int Person::m_A = 0;  //Person作用域下的m_A初始值为0
        int main(){
            Person p;
            cout<<p.m_A<<endl; //会报错，因为没有初始化m_A,编译器觉得m_A的值已经有了，但是去找的时候找不到，于是报错
        }

        因为静态成员变量不属于某个对象，所有对象都共享同一份数据，因此静态成员变量有两种访问方式
        1.通过对象访问   p.m_A
        2.通过类名进行访问   Person::m_A

        //静态成员变量也有访问权限，如果放在private下，类外也访问不到


    2.静态成员函数
        所有对象共享同一个函数
        静态成员函数只能访问静态成员变量

        访问静态成员函数也是两种方法
            1.通过对象访问   p.func()
            2.通过类名进行访问   Person::func()
        静态成员函数内不能访问和改写非静态的成员变量， 因为静态函数是共享的，非静态成员变量不是共享的，会出现不知道访问的是哪个对象的成员变量的问题

        //静态成员函数也有访问权限


    C++对象模型和this指针
        1.成员变量和成员函数分开储存
            类内的成员变量和成员函数分开储存
            只有非静态成员变量才属于类的对象上

            Class Person{
            }
            Person p;
            空对象的占用内存空间为1
            cout << sizeof(p) << endl; //输出1,原因是即使是空的对象，也需要互相区分且保存一个独一无二的地址，所以占一个字节空间

            Class Person{
                int m_A;
            }
            Person p;
            cout << sizeof(p) << endl; //输出4,因为m_A占用4个字节空间,不是空的就按照实际成员变量的大小来计算

            Class Person{
                int m_A;   //属于类的对象
                static int m_B;   //不属于类的对象
            }
            int Person::m_B = 0; //静态成员变量需要在类外初始化
            Person p;
            cout << sizeof(p) << endl;  //输出4,因为m_A占用4个字节空间，静态成员变量不属于类的对象，所以不计算在内

            Class Person{
                int m_A;   //属于类的对象
                static int m_B;   //不属于类的对象
                void func(){} //非静态成员函数
            }
            int Person::m_B = 0; //静态成员变量需要在类外初始化
            Person p;
            cout << sizeof(p) << endl;  //输出4，成员变量和成员函数分开储存，成员函数的内存空间也不计算在内，非静态成员函数也不属于类的对象，但他有办法区分谁在调用它
            非静态成员变量也不属于类的对象

            //总而言之，只有非静态成员变量属于一个对象，且计入计算

        2.this指针概念
            每一个非静态成员函数只会诞生一份函数实例，也就是说多个同类型的对象会共用一块代码
            C++通过提供特殊的对象指针，this指针，解决上述问题： this指针指向被调用的成员函数所属的对象

            this指针是隐含在每一个非静态成员函数内的一种指针，不需要被定义可直接使用

            用途：
                1.当形参和成员变量同名是，可用This区分
                2.在类的非静态成员函数中返回对象本身，可用return *this;

            Class Person{
            public:
                Person(int a) //构造函数
                {
                    this->a = a;   //如果写a = a，非静态成员函数a并不会被初始化
                    //this指针指向 被调用的成员函数 所属的对象     被调用函数是Person，所属的对象（调用它的对象是 p）,所以this指针指向p，this->a就是p.a
                }
                int a;
            };
            int main(){
                Person p(1); //创建对象p，调用构造函数
                cout << p.a << endl; //输出1
                return 0;
            }



            Class Person{
            public:
                Person(int a) //构造函数
                {
                    this->a = a;   //如果写a = a，非静态成员函数a并不会被初始化
                }

                Person& add(Person &p)
                {
                    this->a += p.a; //this指针指向 被调用的成员函数 所属的对象
                    return *this; //返回对象本身
                }
                int a;
            };
            int main(){
                Person p(1); //创建对象p，调用构造函数
                Person q(2); //创建对象q，调用构造函数
                q.add(p).add(p).add(p); //调用add函数，返回q对象本身，链式编程思想（如果函数返回的是void就不可以）
                cout << p.a << endl; //输出1
                return 0;
            }


            //注意：所有的按值传递，在函数创建时都会拷贝副本（传入对象则是调用拷贝构造函数）；所有按值返回， 在函数结束时也会拷贝副本返回（调用拷贝函数），所以按值永远都是新东西，不会互相影响

            Person func(Person &p) //按值传递，p是一个副本
            {
                this->a += p.a //修改副本的值
                return p; //返回副本
            }
            Person p(1);
            Person p1(1); //创建对象p1，调用构造函数
            p1.func(p).func(p).func(p); //调用func函数，但是按值返回每次都是新东西不是p1了，所以P1只加了第一次，结果是2；



*/

/*
空指针访问成员函数   C++中空指针也是可以调用成员函数，但是要注意有没有用到this指针
    Class Person
    {
    public:
        void showClassname()
        {
            cout<<1<<endl;
        }
        void showPersonAge()
        {
            cout<<m_Age<<endl;
        }
        int m_Age;
    }
    int main()
    {
        Person * p = NULL;
        //复习，对于指针，利用操作符->就可以访问函数成员，实际语法结构等价于(*p).showClassname();
        p->showClassname(); //不报错
        p->showPersonAge();  //报错，原因：在成员函数里访问成员对象，实际结构是this->m_Age,但是(*p).showPersonAge()传进去后，this指向*p也就是NULL，自然没有对用m_Age，所以报错;
    }
    可以加入
    if (this == NULL)
    {
        return; //防止空指针问题
    }

Const 修饰成员函数
    常函数
        ·函数后面加上const就是常函数
        ·常函数内不可以修改成员属性
        ·成员属性声明时加关键字mutable后，在常函数中依然可以修改

        //原因： 修改成员属性时 m_a = 100 等价于 this->m_a = 100
        //而this指针是指针常量，他的指向是不可以改变的 Person * const this;
        //想让this指针连值都不能修改就需要把他变成 const Person * const this;那这个新的const加在函数声明的前面和中间都不合适，所以就设定为加在函数的后面了

        mutable int m_b;加了关键字之后在常函数里就可以修改了

    常对象
        ·声明对象前加const叫常对象
        const Person p;
        p.m_a = 100; //报错，因为常对象不允许修改成员属性
        p.m_b = 100；//可以修改，因为有mutable是特殊的
        ·常对象只能调用常函数
        //原因：普通函数内可以修改成员属性，如果允许了调用普通函数等于变相允许了修改成员属性，但是常对象不允许这种事情，所以直接连普通函数都不能调用

*/

/*
友元
在程序里，有些私有属性也想让类外特殊的一些函数或者类进行访问，需要用到友元技术
目的就是让一个函数或者类访问另一个类中的私有成员
关键字为friend

三种实现
    1.全局函数做友元
        Class A
        {
            friend void func(A &n); //在类的最上面加上friend和声明，这个函数就可以访问私有部分了；
        public:
            int a;
        private:
            int b;
        }
        void func(A &n)
        {
            n.a;
            n.b; //不报错，但如果没有那一行就会报错
        }
    2.类做友元
        Class A; //先声明后实现
        Class B
        {
        public:
            B(); //类内声明成员函数，类外实现
            void func();
            A * a;
        }
        Class A
        {
            friend Class B; //加上这一行就可以访问A中的私有部分c2，不加的话访问不了
            A();
        public:
            int c1;
        private:
            int c2;
        }

        A::A()
        {
            A.c1 = 1;                                                           第三步，调用A的构造函数,并附初值
        }
        B::B()
        {
            a = new A;   //在B内通过成员指针维护一个A类型的对象                    第二步，调用B的构造函数，在里面创建了一个A对象并且放在堆区
                                                                                第四步，用指针指向这个对象
        }
        void B::func()                                                               第六步，来到这个函数，并且通过指针访问c1
        {
            cout << a->c1 <<endl;  //通过这个指针访问A类型对象内的成员对象
            cout << a->c2 <<endl;
        }

        int main()
        {
            B bb;                                                                第一步，创建B对象
            bb.func();                                                           第五步，调用B的func（）
        }


    3.成员函数做友元
        Class A;
        Class B
        {
        public:
            B();
            void func1();  //只让func1作为特殊的成员函数可以访问A中的私有部分
            void func2();

            A * a;
        };
        Class A
        {
            friend void B::func1();  //告诉编译器，B类作用域下的func1()函数作为A类的友元可以访问私有部分；
        public:
            A();
            int c1;
        private:
            int c2;
        };
        A::A()
        {
            c1 = 1;
            c2 = 2;
        }
        B::B()
        {
            a = new A;
        }
        void B::func1()
        {
            cout << a.c1;
            cout << a.c2;  //可以访问
        }
        void B::func2()
        {
            cout << a.c1;
            cout << a.c2;  //不可访问
        }
*/

/*
运算符重载
    对已有的运算符重新进行定义，赋予另一种功能以适应不同的数据类型 （比如我们自定义的class数据类型的操作）；对于内置的数据类型编译器会做，但是对于非内置的数据类型编译器就不会做了

    1.加号运算符重载
        对于一个类
        Class Person
        {
        public:
            int m_a;
        };
        int main()
        {
            Person p1;
            Person p2;
            想实现
            Person p3 = p1 + p2 (实际上是p1.m_a+ p2.m_a的功能)
        }

        有三种实现方式
            1.通过成员函数实现
                Person Personaddm_a (Person & p)
                {
                    Person temp;
                    temp.m_a = this->m_a + p.m_a;
                    return temp;
                }
                Person p3 = p1.Personaddm_a(p2);  这样就实现了相加

            2.用编译器起的通用名称重载，并且用成员函数重载+号 (operator+)
                Person operator+ (Person & p)
                {
                    Person temp;
                    temp.m_a = this->m_a + p.m_a;
                    return temp;
                }
                Person p3 = p1.operator+(p2); 可以被简化为 Person p3 = p1 + p2;

            3.还是使用编译器的名字，但是用全局函数重载加号
                Person operator+ (Person &p1, Person &p2)
                {
                    Person temp;
                    temp.m_a = p1.m_a + p2.m_a;
                    return temp;
                }
                Person p3 = operator+(p1,p2)  可以被简化为 Person p3 = p1 + p2;

            4.运算符重载，也可以发生函数重载
                比如前面的加号是两个Person类型的相加，还可以写一个用于把Person类型和指数型相加的函数
                放在同一个作用域下，以全局函数为例
                Person operator+ (Person &p1, int a)
                {
                    Person temp;
                    temp.m_a = p1.m_a + a;
                    return temp;
                }
                Person p4 = P3 + 10;

            注意：
                1.对于内置的数据类型的表达式的运算符是不可以改变的
                2.不要滥用运算符重载



    2.左移运算符重载 << ，可以把他改成输出一些自定义的类型，比如cout << p，就知道输出什么
        Class Person
        {
        public:
            int m_a;
        };
        int main()
        {
            Person p1;
            想实现
            cout << p1; 的时候输出里面的m_a
        }
        两个方法：
            1.成员函数重载
                如果写成 void operator<< (cout)，调用的时候也就是 p.operator<<(cout)会被简化成p << cout 和我们想要的反了
                所以无法利用成员函数重载左移运算符，因为无法实现cout在左侧（成员函数一定要先有一个对象去调用，做不到）

            2.全局函数重载
                void operator<<(cout, p)   //本质 operator(cout, p) 被简化为 cout << p;
                //cout是属于标准输出流ostream的对象，且全局只能有一个所以传入必须用引用

                被修改为
                void operator<<(ostream &cout, Person &p)
                {
                    cout << p.m_a;
                }
                这个时候输出 cout<<p就不会报错了，但是输出cout<<p<<endl;仍然会报错，因为多个cout属于链式调用，根据前面的例子，如果要使用链式，那么函数应该返回它本身的类型

                被修改为
                ostream & operator<<(ostream &out, Person &p)
                {
                    out<<p.m_a;
                    return out;
                }
                现在输出cout<<p<<endl;就不报错了，然后out因为是一个引用相当于起别名，所以取什么名字都是可以的

                如果想把m_a设置为私有类，然后ostream函数还能访问，可以使用友元来操作


    3.递增运算符重载 ++    要实现前置和后置递增运算符
        Class InteNum
        {
            friend ostream & operator<<(ostream &out, Person &num);
        public:
            Person()
            {
                InteNum = 0;
            }
            //重载前置++运算符
            InteNum& operator++() //返回引用，使他可以进行链式操作
            {
                InteNum++;
                return *this;   //如果返回空值, <<operator的传参就不是InteNum了而是一个void类型，会报错，所以要传回它自身也就是*this
            }
            //重载后置++运算符
            InteNum operator++(int)   //通过一个int占位符，区分前置和后置，并且编译器只认这个Int;
            {
                //先记录结果
                InteNum temp = *this; //拷贝初始化，隐式转换法
                //再递增
                InteNum++;
                //最后将记录的结果做返回
                return temp;      //最后返回的是一个局部变量所以不可以用引用，必须返回值类型
            }

        private:
            int InteNum;
        }; //class后面记得加;

        ostream & operator<<(ostream &out, InteNum &num)
        {
            out<<num.InteNum;
            return out;
        }

        int main()
        {
            InteNum num;
            cout << num++ <<endl;
            cout << ++num <<endl;
        }


    4.赋值运算符重载
        C++编译器至少给一个类添加4个函数
            1.默认构造函数（无参，函数体为空）
            2.默认析构函数（无参，函数体为空）
            3.默认拷贝构造函数，对属性进行值拷贝
            4.赋值运算符 operator=，对属性进行值拷贝

            如果类中有属性指向堆区，做赋值操作回出现深浅拷贝问题（重复删同一个内存地址）

            Class Person
            {
            Public:
                Person(int num)
                {
                    m_a = new int(num);
                }
                ~Person()
                {
                    if m_a != NULL
                    {
                        delete m_a;
                        m_a = NULL;
                    }
                }
                Person& operator=(Person &p)
                {
                    //首先删除干净初始化时在堆区创建的空间
                    if (m_a != NULL)
                    {
                        delete m_a;
                        m_a = NULL;
                    }
                    //编译器提供的浅拷贝如下， 拷贝指向地址
                    //m_a = p.m_a
                    //深拷贝
                    m_a = new int(*p.m_a);
                    return *this; //为什么要返回自身，看下面的例子
                }
                int *m_a;
            };
            int main()
            {
                Person p1(10);
                Person p2(20);
                p1 = p2;
                cout << p1 <<endl;   //会有问题，原因是class里面在堆区新建了内存空间，如果直接使用编译器的等号，则是浅拷贝，会重复删除同一块地址报错；因此需要重载等号变成深拷贝
            }


            补充例子
            如果a=10,b=20,c=30;   ->  c=b=a会返回a,b,c都是10；
            如果上面的重载函数返回的是void则没办法做到这种链式传递，所以需要传回自身


    5.关系运算符重载  可以让两个自定义的类型对象进行比对操作
        Class Person
        {
        public:
            Person(int a, int b)
            {
                m_a = a;
                m_b = b;
            }

            bool operator==(Person &p)
            {
                if (this->m_a == p.m_a && this->m_b == p.m_b)
                {
                    return true;
                }
                return false;
            }

            bool operator!=(Person &p)
            {
                if (this->m_a == p.m_a && this->m_b == p.m_b)
                {
                    return false;
                }
                return true;
            }
            int m_a;
            int m_b;
        };
        int main()
        {
            Person p1(1,2);
            Person p2(1,2);
            if (p1 == p2)
            {
                cout << "相等" <<endl;
            }
        }


    6.函数调用运算符重载 符号：()
        由于重载后使用的方式非常像函数，因此称为仿函数，没有固定写法，非常灵活

        Class myprint
        {
        public:
            void operator()(string text)
            {
                cout << text <<endl;
            }
        }
        int main()
        {
            myprint mprint;
            mprint("hello world");  //这个看起来非常像函数的调用，但是实际上他是让对象使用了重载的小括号，前面的那个是对象名不是函数名
        }

        这个小括号重载可以实现很多的功能，取决于你怎么写
        甚至可以使用匿名的函数对象
        cout << myprint()("hello world") <<endl; 输出完下一行就释放，无参构造
*/