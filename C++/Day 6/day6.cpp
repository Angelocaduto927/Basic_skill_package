/*
STL
    2.1 STL的诞生
    软件界一直希望建立一种可重复利用的东西，C++面向对象和泛型编程思想都是为了提高复用性；大多数情况下，数据结构和算法都未能有一套标准，导致被迫从事大量重复工作；为了建立数据结构和算法的一套标准，诞生了STL

    2.2 STL概念
    standard template library 标准模板库
    从广义上分：容器(container),算法（algorithm)，迭代器(iterator)
    容器和算法之间通过迭代器进行无缝连接
    STL几乎所有的代码都采用了模板类或者模板函数

    2.3 STL六大组件
    容器，算法，迭代器，仿函数，适配器（配接器），空间配置器
        1.容器 各种数据类型 vector,list,deque,set,map
        2.算法 常用的算法 sort,find,copy,for_each等
        3.迭代器 扮演容器和算法之间的胶合剂
        4.仿函数 行为类似函数，可作为算法的某种策略
        5.适配器 一般用来修饰容器或者仿函数或迭代器接口的东西
        6.空间配置器 负责空间的配置与管理

    2.4 STL中的容器，算法，迭代器
    容器
        将运用最广泛的一些数据结构实现出来
        常用的：数组，链表，树，栈，队列，集合，映射表等
        分为序列是容器和关联式容器
            序列是容器：强调值的排序，序列式容器中的每个元素均有固定的位置
            关联式容器：二叉树结构，各元素之间没有严格的物理上的顺序关系

    算法
        质变算法和非质变算法
        质变算法：指运算过程中会更改区间内的元素的内容，例如拷贝，替换，删除等
        非质变算法：是指运算过程中不会改变区间内的元素内容，例如查找，计数，遍历，寻找极值等

    迭代器 (算法要迭代器才能访问容器)
        提供一种方法，使之依序寻访某个容器所含的各个元素，又无需暴露该容器的内部表示方法
        每个容器都有自己专属的迭代器，很类似指针
        输入迭代器   对数据只读   只读，支持++，==，！=
        输出迭代器   对数据只写   只写，支持++
        前向迭代器   读写操作且能向前推进迭代器   读写，支持++，==，！=
        双向迭代器   读写操作且能向前向后操作     读写，支持++，--
        随机访问迭代器   读写操作，可以跳跃的访问任意数据，功能最强   读写，支持++，--，[n],-n,<,<=,>,>=

        常用双向和随即访问

    2.5容器算法迭代器初识
        2.5.1 容器：vector 算法：for_each 迭代器vector<int>::iterator
        vector存放内置数据类型，可以理解为数组
            #include<vector>
            vector<int> v; //创建一个vector
            v.push_back(10);
            v.push_back(20);  //插入数据

           //遍历方式  v.begin()和v.end()返回的都是迭代器，位置不一样，然后赋值给一个自命名的迭代器（拿到这种容器的迭代器类型）
            1.
            vector<int>::iterator itBegin = v.begin();  //迭代器访问元素，起始迭代器，指向容器的第一个元素
            vector<int>::iterator itEnd = v.end(); //结束迭代器，指向容器中的最后一个元素的下一个位置
            while(itBegin != itEnd)
            {
                cout << *itBegin << endl;
                itBegin++;
            }

            2.
            for(vector<int>::iterator it = v.begin(); it != v.end(); it++)
            {
                cout << *it << endl;
            }

            3.利用STL的遍历算法
            #include<algorithm> 标准算法的头文件
            void myprint(int val)
            {
                cout << val << endl;
            }
            for_each(v.begin(), v.end(), myprint);  //从起始叠加器位置开始，调用最后的那个func，传入迭代器解引用的值，直到碰到结束叠加器

        2.5.2 vector存放自定义数据类型
            vector<Person> v;
            Person a('aaa',18);
            v.push_back(a);
            for(vector<Person>::iterator it = v.begin(); it != v.end(); it++)
            {
                cout << (*it).m_name << it->m_age << endl;  //it就是一个指针
            }

        2.5.3 vector容器嵌套容器 类似二维数组
            vector< vector<int> > v; //大容器
            vector<int> v1;  //小容器
            vector<int> v2;  //小容器
            v1.push_back(1);
            v1.push_back(2);
            v2.push_back(3);
            v2.push_back(4);
            v.push_back(v1);
            v.push_back(v2);
            for(vector< vector<int> >::iterator it = v.begin(); it != v.end(); it++)
            {
                for(vector<int>::iterator vit = (*it).begin(); vit != (*it).end(); vit++)   //*it解出来就是括号里的vector<int>
                {
                    cout << (*vit) << endl;  //it就是一个指针
                }
            }
*/

/*
string
    3.1.1 string的基本概念
        本质：string是C++风格的字符串，本质上是一个类
        string和char *的区别：
            char* 是一个指针【形成字符数组】
            string是一个类，类内部封装了char*，管理这个字符串，是一个char*型的容器

            C语言风格字符串 const char * str = "hello world";
        特点
            string内部封装了很多成员方法，如find,copy,delete,replace,insert
            string内部管理char*所分配的内存，不用担心复制越界或取值越界的问题，由类内部进行负责

    3.1.2 string构造函数
        string();  创建一个空的字符串
        string(const char* s);  使用字符串s初始化
        string(const string& str);   使用一个string对象初始化另一个string对象
        string(int n, char c);  使用n个字符c初始化

    3.1.3 string赋值操作
        函数原型
            string& operator=(const char * s);
            string& operator=(const string &s);
            string& operator=(char c);
            string& assign(const char *s);
            string& assign(const char *s, int n);  //把字符串s的前n个字符赋给当前的字符串
            string& assign(const string &s);
            string& assign(int n, char c);  //用n个字符c赋给当前的字符串
        可以用=号或者assign方法去赋值
        "hello world"这种直接写出来的字符串本质上是一个字符数组，然后简化成首地址指针，所以也就是char *类型

    3.1.4 string拼接
        在字符串末尾增加字符串
        原型
            string& operator+=(const char * str);
            string& operator+=(const char c);
            string& operator+=(const string& str);
            string& append(const char * s);
            string& append(const char * s, int n);   //字符串s的前n个字符连接到当地字符串结尾
            string& append(const string &s);
            string& append(const string &s, int pos, int n);   //字符串s从pos开始的n个字符连接在字符串的结尾

    3.1.5 string查找和替换
        查找find 看指定的字符串是否存在于该字符串中
        替换replace 指定位置替换字符串

        原型  返回的是index位置
            int find(const string &str, int pos = 0) const;
            int find(const char * s, int pos = 0) const;
            int find(const char * s, int pos, int n) const;  //从pos位置查找s的前n个字符第一次出现的位置
            int find(const char c, int pos = 0) const;
            int rfind(const string &str, int pos = npos) const;  //rfind是查找最后一次出现的位置，从pos开始找
            int rfind(const char * s, int pos = npos) const;
            int rfind(const char * s, int pos, int n) const;  //从pos查找s的前n个字符最后一次出现的位置
            int rfind(const char c, int pos = 0) const;
            string& replace(int pos, int n, const string& str);  //替换从pos开始把n个字符替换为str
            string& replace(int pos, int n, const char * s);   //替换从pos开始的n个字符为字符串s

    3.1.6 string字符串比较
        按ASCII码比较， = 返回0， > 返回1， <返回-1
        原型
            int compare(const string &s) const;
            int compare(const char *s) const;

    3.1.7 string字符存取
        string中单个字符存取方式有两种
            char& operator[](int n); 通过重载[]加上index获取字符
            char& at(int n)；通过at加上index的方式获取字符
        用这两个方法也可以修改字符串内的字符

    3.1.8 string长度获取
        str.size()；

    3.1.9 string插入和删除
        原型
            string& insert(int pos, const char* s);
            string& insert(int pos, const string& str);
            string& insert(int pos, int n, char c);   //在指定位置插入n个字符c
            string& erase(int pos, int n = npos); //删除从pos开始的n个字符

    3.1.10 string子串
        从字符串中获取想要的子串
        原型
            string substr(int pos = 0, int n = npos) const;  //返回由pos开始的n个字符组成的字符串
*/

/*
vector
    3.2.1 vector概念
        数据结构和数组非常相似，也成为单端数组

        与普通数组的区别
            数组是静态空间，而vector可以动态扩展

        动态扩展
            并不是在原空间之后续接新空间，而是找更大的内存空间，然后将原数据拷贝新空间，释放原空间

        结构：
        和栈类似，前端是封闭的，插数和删数都是从vector的结尾操作
        front()     第一个
        back()      最后一个
        push_back() 末端减少
        pop_back()  末端增加
        insert()    插入
        v.rend()    左端的前一个位置
        v.begin()   左端
        v.rbegin()  右端
        v.end()     右端的后一个位置
        迭代器是支持随机访问的迭代器

    3.2.2 vector构造函数
        原型
            vector<T> v; 模板实现类实现，默认构造函数
            vector(v.begin(), v.end())  将v[begin(),end())区间中的元素拷贝给本身,v要先存在
            vector(n, elem);  构造函数将n个elem拷贝给本身
            vector(const vector &vec)  拷贝构造函数

    3.2.3 vector赋值
        原型
            vector& operator=(const vector& vec);  重载等号
            assign(v.beg, v.end);  将[beg, end)区间中的数据拷贝赋值给本身,v要先存在
            assign(n, elem);  n个elem拷贝赋值

    3.2.4 vector容量和大小
        原型
            empty();  判断是否为空
            capacity();   返回容器的容量，最大储存多少个数
            size();  返回容器中元素的个数，目前存放的数量
            resize(int num);  重新指定容器的长度为num，若容器边长则以默认值“0”填充新位置，如果变短，则末尾超出容器长度的元素被删除
            resize(int num, elem);  重新指定容器的长度为num，若容器边长则以elem填充新位置，如果变短，则末尾超出容器长度的元素被删除

    3.2.5 vector插入和删除
        原型
            push_back(ele); 尾部插入
            pop_back();
            insert(const_iterator pos, ele); 迭代器指向位置pos处插入ele
            insert(const_iterator pos, int count, ele); 迭代器指向位置pos处插入count个ele
            erase(const_iterator pos);
            erase(const_iterator start, const_iterator end); 删除迭代器从start到end之间的元素，可以只删除一部分区间
            clear(); 删除所有元素

    3.2.6 vector数据存取
        原型
            at(int index);
            operator[];  返回索引所指的元素   v[1];
            front();  返回第一个数据
            back();   返回最后一个数据

    3.2.7 vector互换容器
    实现两个容器内元素的互换
        原型
            swap(vec);

    实际用途
        1.用swap可以收缩内存空间
            vector<int>(v).swap(v);
            原本v的容量是10000，大小是9000，然后我resize了他变成只有1个元素，那么会造成很严重的空间浪费9999；
            这个时候用上面的代码，通过拷贝构造（按照v目前所用的size)初始化一个临时对象，然后跟v进行互换，那个临时对象马上就释放掉然后v还用了新的小空间，节省内存

    3.2.8 vector预留空间
        减少vector在动态扩展容量时的扩展次数
        原型
            reserve(int len); 容器预留len个元素长度，预留位置不初始化，元素不可访问

        判断开辟次数
            只需要找一个指针指向vector的首地址，如果他新开辟了一次，这个指针和这个新的vector的首地址肯定不一样，所以就知道他变了一次
*/

/*
deque
    3.3.1 deque基本概念
        双端数组，可以对头段进行插入删除操作

        与vector的区别
        vector对于头部的插入删除效率低，数据量越大，效果越低
        deque相对而言，对头部的插入删除速度比vector快
        vector访问元素是的速度会比deque快，这和两者内部实现有关

        push_front()
        pop_front()
        push_back()
        pop_back()
        begin()  迭代器
        end()  //最后一个元素的下一个位置  迭代器
        insert()
        front()
        back()

        内部工作原理
            deque内部有个中控器，维护每段缓冲区中的内容，缓冲区中存放真实数据
            中控器维护的是每个缓冲区的地址，使得使用deque时像一片连续的内存空间，但实际上时一段一段的，尾插尾删就是在最后一个缓冲区加减，头插头删就是在第一个缓冲区开辟新的区域或者删掉元素
            但是因此访问没有那么的快，要找新的缓冲区地址链接过去

        deque迭代器也支持随机访问
        头文件 #include<deque>
        for(deque<int>::iterator it = deq.begin(); it != deq.end(); it++)
        {
            cout << *it
        }

        iterator 和 const_iterator是两个东西
        如果一个函数传进来的是const deq &d也就是希望只对d进行读的操作，那么在for循环输出的时候要使用const_iterator来迭代，然后函数内是不允许对*it修改复制的
        如果使用的是普通的iterator则会报错
        如果传入的是可写的，那么只能用普通的iterator迭代

    3.3.2 deque构造函数
        原型
            deque<T> deqT;
            deque<T> deq1(deqT.begin(), deqT.end())  拷贝一个deq的[begin,end)之间的元素
            deque(n, elem); 将n个elem拷贝构造
            deque（const deque &deq)  拷贝构造

    3.3.3 deque赋值操作
        原型
            deque& operator=(const deque &deq);
            assign(deq.begin, deq.end);
            assign(n,elem);

    3.3.4 deque大小操作
        原型
            deque.emtpy();
            deque.size();  返回容器中元素的个数
            deque.resize(num);         重新指定容器的长度为num，若容器边长则以默认值“0”填充新位置，如果变短，则末尾超出容器长度的元素被删除
            deque.resize(num, elem);   重新指定容器的长度为num，若容器边长则以elem填充新位置，如果变短，则末尾超出容器长度的元素被删除
            没有获取容量的操作，因为没有容量的概念，随便增加无上限

    3.3.5 deque插入和删除
        原型
            两端的插入操作
            push_back(elem);
            push_front(elem);
            pop_back();
            pop_front();

            指定位置操作
            insert(pos, elem);  在pos位置插入一个elem元素的拷贝，返回新数据的位置
            insert(pos, n, elem);  在pos位置插入n个elem数据，无返回值
            insert(pos, deq.beg, deq.end);  在Pos位置插入一个区间的数据，无返回值
            clear(); 清空
            erase(deq.beg, deq.end);  删除区间的数据，返回下一个数据的地址
            erase(pos);   删除pos位置的数据，返回下一个数据的地址
            提供pos位置的都是迭代器

    3.3.6 deque数据存取
        原型
            at(int index);
            operator[];   deq[i]只能读不能写，写的话要用push方法
            front();
            back();
            *(deq.begin() + 1)  通过迭代器的方法获取数据

    3.3.7 deque排序
        原型
            #include<algorithm>
            sort(iterator beg, iterator end);  //对beg，end区间内的元素进行排序

            使用直接
            sort(deq.begin(), deq.end())  默认升序， 不是deq.sort的调用方式

            对于支持随机访问的迭代器的容器，都可以利用sort算法直接对其进行升序排序，比如vector
*/

/*
stack
    3.5.1 stack基本概念
        先进后出的数据结构，只有一个出口
        push()
        pop()
        top()

        因为只有顶端的元素才能被访问，所以不允许遍历（因为如果要看第二个元素必须要把顶部的元素拿出去，然而这样栈的数据内容就变了，遍历是非质变算法不允许数据内容改变，所以栈不能遍历）
        栈可以判断容器是否为空
        栈可以返回元素个数 额外记录

    3.5.2 stack常用接口
        构造函数
            原型
                stack<T> stk;  默认构造
                stack(const stack &stk); 拷贝构造

        赋值操作
            原型
                stack& operator=(const stack& stk); 重载等号

        数据存取
            原型
                push(elem);
                pop();
                top();

        大小操作
            empty();
            size();
*/

/*
queue
    3.6.1 queue基本概念
        先进先出，两个出口
        push()
        back()
        pop()
        front()
        只有队头和队尾元素能被外界访问，因此不能遍历
        可判断是否为空
        可返回元素数量

    3.6.2 queue常用接口
        构造函数
            queue<T> que;
            queue(const queue &que);
        赋值操作
            queue& operator=(const queue &que);
        数据存取
            push(elem);
            pop();
            front();
            back();
        大小操作
            empty();
            size();
*/

/*
list
    3.7.1 list基本概念（链表）
    将数据进行链式存储
        链表（list）是一种物理存储单元上非连续的存储结构，数据元素的逻辑顺序是通过链表中的指针链接实现的

        链表的组成：链表由一系列结点组成

        结点的组成：一个是存储数据元素的数据域，另一个是存储下一个结点地址的指针域

        STL中的链表是一个双向循环链表

        优点：可以对任意位置快速插入或删除元素；动态分配内存，不会浪费内存
        缺点：容器遍历速度没有数组快；占用空间比数组大

        data 数据
        prev 上结点指针
        next 下结点指针
        begin()
        insert()
        end() 最后一个节点的下一个位置
        pop_back()
        pop_front()
        push_front()
        push_back()
        front()
        back()

        由于链表的存储方式不是连续的内存空间，因此链表中的迭代器只支持前移和后移，属于双向迭代器

        重要性质：list的插入和删除操作都不会让迭代器失效（除非删了迭代器所在的结点），而vector不是这样（因为vector创建新的时候会改变地址）

        总结：STL中list和vector是最常用的容器
        #include<list>

    3.7.2 list构造函数
        原型
            list<T> lst;
            list(beg,end);
            list(n,elem);
            list(const list &lst);

    3.7.3 list赋值和交换
        原型
            assign(beg, end);
            assign(n, elem);
            list& operator=(const list &lst);
            swap(lst);

    3.7.4 list大小操作
        原型
            size()
            empty()
            resize(num);
            resize(num, elem);

    3.7.5 list插入和删除
        原型
            push_back(elem);
            pop_back()
            push_front(elem);
            pop_front();
            insert(pos, elem);   返回新数据位置
            insert(pos, n, elem);    无返回值
            insert(pos, beg, end);    无返回值
            clear();
            erase(beg, end);    返回下一个数据位置
            erase(pos);     返回下一个数据位置
            remove(elem);   删除容器中所有与elem值匹配的元素

    3.7.6 list数据存取 //不能直接利用[]或at随机访问中间的元素，所以接口只有第一个和最后一个
        原型
            front();
            back();

        it+1是不允许的操作，因为如果可以，那也可以it+2,it+3这样就可以跳着随机访问了不适用于list的迭代器
        但是it++是允许的，这是前移操作

    3.7.7 list反转和排序
        原型
            reverse(); 反转
            sort();    排序

            只有支持随机访问的迭代器，才可以使用标准sort算法，也就是把sort当作全局函数
            直接 sort(beg, end); 就会自动升序

            对于不支持随机访问的迭代器的容器，内部会提供一些对应的算法
            但这些是成员函数所以要
            L1.sort();使用  升序

            如何降序排序？ 要使用仿函数
            bool myCompare(int v1, int v2)
            {
                return v1 > v2;
            }
            L1.sort(myCompare);  //括号里面加一个仿函数指定比较方式，这个函数返回Bool值里面是排序的比较方式

            e.g.
            bool compare(Person& p1, Person& p2)
            {
                if (p1.age == p2.age)
                {
                    return p1.height > p2.height;
                }
                else
                {
                    return p1.age < p2.age;
                }
            }   //按年龄升序，如果相同按身高降序
            L1.sort(compare);
*/

/*
set/ multiset容器
    3.8.1 set基本概念
        所有元素都会在插入时被自动排序
        本质
        set/multiset属于关联式容器，底层结构是用二叉树实现

        set/multiset区别
            set中不允许由重复的元素
            multiset中允许有重复的元素

        两个只需要包含一个头文件
        #include<set>

        插入数据没有什么Push方法，只有insert(n)的方法

    3.8.2 set构造和赋值
        原型
            set<T> st;
            set(const set &st);

            set& operator=(const set &st);

    3.8.3 set大小和交换
        原型
            size();
            empty();
            swap(st);
            没有resize的操作，因为resize会填入很多个一样的默认值，重复了所以不允许

    3.8.4 set插入和删除
        原型
            insert(elem);
            clear();
            erase(pos);  删除pos位置元素，返回下一个元素的迭代器，pos跟插入的顺序无关，是排序之后的顺序
            erase(beg, end); 删除区间，返回下一个元素的迭代器
            erase(elem);    删除所有值为elem的元素

    3.8.5 set查找和统计
        原型
            find(key);  查找key是否存在，若存在返回该键的元素的迭代器，不在则返回set.end() 也是迭代器但是是最后的位置;
                set<int>::iterator pos = s1.find(10);
                if pos != s1.end()
                {
                    cout << *pos << endl;
                }

            count(key); 统计key的元素个数

    3.8.6 set和multiset的区别
        ·set不可以插入重复数据，而multiset可以
        ·set插入数据的同时会返回插入结果，表示插入是否成功
        ·multiset不会监测数据，因此可以插入重复数据

        如何接收插入是否成功
        pair<set<int>::iterator, bool> ret = s.insert(10);    set的插入返回的是一个对组，前面是迭代器表示插入的位置，后面是一个bool值表示插入是否成功
        if(ret.second)
        {
            cout << 插入成功；
        }
        如果ret.second为真，也就是ret对组的第二个位置的bool值为真，那么说明插入成功，反之如果为假，说明插入失败。

        multiset的insert只返回迭代器表示插入的位置，不会判断和返回Bool值是否插成功

    3.8.7 pair对组创建
        成对出现的数据，利用对组可以返回两个数据
        两种创建方式
            pair<type, type> p ( value1, value2);
            pair<type, type> p = make_pair( value1, value2 );

    3.8.8 set容器排序
        默认排序方式是从小到大，如何改变
            利用仿函数可以改变排序规则

            set存放内置数据类型
                必须在创建set的时候就规定排序方式

                class compare   //仿函数是一个类，跟int一个性质
                {
                public:
                    bool operator()(int v1, int v2){  //重载()
                        return v1 > v2;
                    }
                };
                set<int, compare> s;   //指定规则
                for(set<int, compare>::iterator it = s.begin(); it != s.end(); it++)
                {
                    cout << *it << endl;
                }

            set存放自定义数据类型   因为set不知道自定义的数据类型应该按什么方式去进行排序，所以一定需要手写仿函数规定排序的方法
            class Person
            {
            public:
                Person(string name, int age)
                {
                    this->mname = name;
                    this->mage = age;
                }
                string mname;
                int mage;
            };
            class compare
            {
            public:
                bool operator()(Person& p1, Person& p2)
                {
                    return (p1.mage > p2.mage);
                }
            };
            set<Person, compare> s;
            set<Person, compare>::iterator it = s.begin();
*/

/*
map/multimap容器
    3.9.1 map基本概念 （有点像dict）
        简介
            使用率仅此list和vector，高性能，高效率
            ·map中所有元素都是pair
            ·第一个元素为key（键值），起到索引作用，第二个元素为value(实值)
            ·所有元素都会根据元素的键值自动排序

        本质
            map/multimap属于关联式容器，底层结构是二叉树实现

        优点
            可以通过Key快速找到value值 (高效)

        map和multimap的区别
            map不允许容器中有重复的key值，value可以重复
            multimap允许

        #include<map>
        插入和set一样使用insert，但是插入的是一个对组  mp.insert(pair<int, int>(1,10));
        迭代器 map<T1,T2>::iterator, 取出it后还要.first,.second才会得到pair中的值

    3.9.2 map构造和赋值
        原型
            map<T1, T2> mp;
            map(const map &mp);

            map& operator=(const map &mp);

    3.9.3 map大小和交换
        原型
            size();
            empty();
            swap(mp);

    3.9.4 map插入和删除
        原型
            insert(elem);   elem可以是pair<T1,T2>(a1,a2),  make_pair(a1,a2),  map<T1,T2>::value_type(a1,a2)
            或者不太建议的方法：用中括号来插入数据 m[4] = a;
            如果访问了一个没有的数据，比如cout << m[5] << endl;  之前的map里面没有key为5的对组，那么他会自动生成一个值为0，key为5的对值放进去然后输出0
            所以如果用中括号插值插错了，中间很可能会多很多个0.

            中阔号建议的用途是通过Key来访问value

            clear();
            erase(pos);  删除pos迭代器所指的元素，返回下一个元素的迭代器
            erase(beg, end);  删除区间元素，返回下一个元素的迭代器
            erase(key);    删除key值为传入数据的对组

    3.9.5 map查找和统计
        原型
            find(key);  存在则返回该键的元素的迭代器，如果不在返回map.end()
            map<T1,T2>::iterator pos = mp.find(3);
            if pos != s1.end()
                {
                    cout << (*pos).second << endl;
                }
            count(key);

    3.9.6 map容器排序
        默认按照key值从小到大排序
        利用仿函数，可以改变排序规则

        class compare
        {
        public:
            bool operator()(int v1, int v2)
            {
                return v1 > v2;
            }
        }
        map<T1,T2,compare> mp;
*/

// 如果for循环里面的遍历器在外部已经定义过了就可以省掉一部分，e.g.
/*
map<int,int>::iterator it = mp.find(0);
index = 0;
for( ; it < mp.end() && index < mp.count(0); it++, index++)
{
    ···
}
*/