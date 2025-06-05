/*
STL函数对象
    4.1 函数对象
        4.1.1 函数对象的概念
            概念
                重载函数调用操作符，也就是小括号的类，其对象常称为函数对象
                函数对象使用重载的()时，行为类似函数调用，也叫仿函数
            本质
                函数对象（仿函数）是一个类，不是一个函数

        4.1.2 函数对象使用
            特点
                函数对象在使用时，可以像普通函数那样调用，可以有参数，可以有返回值    int operator()(int a, int b) 有参数有返回值
                函数调用超出普通函数的概念，函数对象可以有自己的状态，因为他本质上是一个类，可以有自己的成员来记录状态
                函数对象可以作为参数传递，因为是一个类对象

            e.g. 在类里面加一个成员属性count，就可以记录调用次数，不用借助全局的变量

    4.2 谓词
        4.2.1 谓词的概念
            返回bool类型的仿函数称为谓词
            如果operator()接受一个参数，那么叫一元谓词
            如果operator()接受两个参数，那么叫二元谓词

        4.2.2 一元谓词
            新算法 find_if(First, Last, Pred);   Pred就是谓词，First,Last是区间
            Class GreaterFive
            {
            public:
                bool operator()(int val)
                {
                    return val > 5;
                }
            };
            find_if(v.begin(), v.end(), GreaterFive());     他是在这个区间内逐个把值取出来然后放到最后的类对象里面（最后一位要求是类对象，并且有返回bool的仿函数），如果遇到了判断为真的就停止，然后返回那个位置的迭代器

        4.2.3 二元谓词
            例子：vector的自定义排序
            算法 sort(first, last, pred)

            sort(v.begin(), v.end(), mycompare());  pred也是放入函数对象

    4.3 内建函数对象  STL内建了一些函数对象（仿函数），使用时引入头文件#include<functional>
        4.3.1 内建函数对象意义
            分类
                算术仿函数  逻辑运算
                关系仿函数  对比大小
                逻辑仿函数  与或非
            用法
                这些仿函数所产生的对象，用法和一般的函数完全相同

        4.3.2 算数仿函数
            功能：实现四则运算
            其中negate（取反）是一元运算，其他都是二元运算
            仿函数原型
                template<class T> T plus<T>   加法仿函数
                template<class T> T minus<T>  减法仿函数
                template<class T> T multiplies<T>  乘法仿函数
                template<class T> T divides<T>  除法仿函数
                template<class T> T modules<T>  取模仿函数
                template<class T> T negate<T>   取反仿函数

            使用
                #include<functional>
                negate<int> n;  //这样就创建了一个取反的函数对象
                n(50);  返回-50

                plus<int>p;
                p(10,20); 返回30

        4.3.3 关系仿函数
            功能：实现关系对比
            仿函数原型
                template<class T> bool equal_to<T>
                template<class T> bool not_equal_to<T>
                template<class T> bool greater<T>
                template<class T> bool greater_equal<T>
                template<class T> bool less<T>
                template<class T> bool less_equal<T>

            sort函数默认不需要传入pred的版本，其实是把仿函数指定成了less<>也就是小于的这个内建函数
            所以如果要实现降序排序，我们也可以直接用内建的greater函数，而不用自己再去写
            比如 sort(v.begin(), v.end(), greater<int>()); 指明数据类型，加个小括号创建函数对象

        4.3.4 逻辑仿函数
            功能：实现逻辑运算
            仿函数原型
                template<class T> bool logical_and<T>
                template<class T> bool logical_or<T>
                template<class T> bool logical_not<T>

            新算法
                transform(vorigin.beg,vorigin.end,vnew.beg, pred); 搬运算法，原容器起点，原容器终点，新容器起点，搬运过程中的操作
                注意：使用搬运算法，新容器必须要在使用之前把空间开辟好，比如v2.resize(v.size());

            e.g.
                transform(v.begin(), v.end(), v2.begin(), logical_not<bool>())
*/

/*
STL常用算法
概述
    算法主要是由头文件<algorithm>,<functional>,<numeric>组成
    <algorithm>是所有STL头文件中最大的一个，范围涉及比较，交换，查找，遍历操作，复制，修改等
    <numeric>体积很小，只包括几个在序列上面进行简单数学运算的模板函数
    <functional>定义了一些模板类，用以声明函数对象

    5.1 常用遍历算法
        5.1.1 for_each  //遍历容器
            原型
                for_each(iterator beg, iterator end, _func);    _func是函数（普通函数放函数名）或者函数对象（放对象），他会遍历每一个元素然后丢进这个函数或者函数对象里面去调用

        5.1.2 transform //搬运容器到另一个容器，容器要提前开辟空间
            原型
                transform(iterator beg1, iterator end1, iterator beg2, _func);  _func是函数或者函数对象，搬运的过程中把元素丢进函数里面进行一些逻辑运算或者算数运算
                如果不用操作的话，也需要写_func()
                比如
                int operator()(int val)
                {
                    return val; 这样就保持数据不变的搬运了
                }

    5.2 常用查找算法
        5.2.1 find     查找元素
            查找指定元素，找到返回指定元素的迭代器，找不到返回结束迭代器end()
            原型
                find(iterator beg, iterator end, value);   value可以是内置或者自定义的
                注意：因为find的底层代码是用==来比较两个对象是否相等，自定义的数据类型他不知道怎么比
                所以要找自定义的数据类型就必须在class里面先重载==返回bool值；

        5.2.2 find_if  按条件查找元素
            原型
                find_if(iterator beg, iterator end, _pred);  一样返回迭代器位置
                一直找，直到_pred会返回true的数据，返回

                1.查找内置数据类型
                2.查找自定义数据类型

        5.2.3 adjacent_find  查找相邻重复元素
            原型
                adjacent_find(iterator beg, iterator end); 返回相邻重复元素的第一个元素的迭代器地址

        5.2.4 binary_search  二分查找法
            原型
                bool binary_search(iterator beg, iterator end, value);
                查找指定元素是否存在，查到返回true,查不到返回false
                注意：在无序序列中不可用，如果是无序的就未知了

        5.2.5 count  统计元素个数
            原型
                count(iterator beg, iterator end, value);  返回int
                1.统计内置数据类型
                2.统计自定义数据类型（底层仍然使用的==来判断是否和目标元素相等，但是编译器并不知道自定义的类型怎么比较）
                    ->根据需求重载==号，返回Bool值
                    bool operator==(const Person &p) 这个const还是很重要的，不加有可能会报错，要求数据不能更改

        5.2.6 count_if  按条件统计元素个数
            原型
                count_if(iterator beg, iterator end, _pred)
                统计_pred能返回true的元素个数，_pred写在一个class里面，然后重载()

    5.3 常用排序算法
        5.3.1 sort  对容器内元素进行排序
            原型
                sort(iterator beg, iterator end, _pred)
                _pred返回bool类型的谓词，排序方式将按照传入一前一后两个数据能返回true的方式排序，默认升序
                降序的最快方式，使用greater<int>()

        5.3.2 random_shuffle   洗牌，指定范围内的元素随机调整次序
            原型
                random_shuffle(iterator beg, iterator end);
                要每次打乱都不一样的话需要随机数种子
                #include<ctime>
                srand((unsigned int)time(NULL));   C风格
                或者srand((unsigned int)time(nullptr));   C++风格

        5.3.3 merge  容器元素合并，并储存到另一个容器中
            原型
                merge(iterator beg1, iterator end1, iterator beg2, iterator end2, iterator dest);
                注意：两个容器必须是有序的且排序方式一致， dest是目标容器的开始迭代器，合并之后依然有序
                合并容器前需要给新内存分配内存 v.resize(v1.size()+v2.size());

        5.3.4 reverse  反转指定范围的元素
            原型
                reverse(iterator beg, iterator end);

    5.4 常用拷贝和替换算法
        5.4.1 copy  容器内指定范围的元素拷贝到另一个容器
            原型
                copy(iterator beg, iterator end, iterator dest);
                仍然，需要提前开辟数据，所有拷贝容器元素都需要，但不如直接等号赋值（类的重载=函数）

        5.4.2 replace  容器内指定范围的旧元素修改为新元素
            原型
                replace(iterator beg, iterator end, oldvalue, newvalue);  会替换所有old value

        5.4.3 replace_if  容器内指定范围满足条件的旧元素替换为新元素
            原型
                replace_if(iterator beg, iterator end, _pred, newvalue);
                所有满足_pred为true的就替换,利用仿函数可以灵活改变替换要求

        5.4.4 swap  互换两个容器的元素
            原型
                swap(container1, container2);
                要求两个容器是同种类型的

                例如swap(v1,v2);

    5.5 常用算术生成算法
        属于小型算法，使用时包含的头文件为#include<numeric>
        5.5.1 accumulate   计算区间内容器元素累计总和(累加)
            原型
                accumulate(iterator beg, iterator end, value)
                这个value是起始累加值，一般设置为0，然后会返回一个int值

        5.5.2 fill   向容器区间填充为指定的元素  （其实应该是属于algorithm库下的！！）
            原型
                fill(iterator beg, iterator end, value);  可以用于后期填充
                如果原本有值会被覆盖掉，和insert的插入不一样，有点像赋值操作

    5.6 常用算法集合  #include<algorithm>
        5.6.1 set_intersection  交集
            原型
                set_intersection(iterator beg1, iterator end1, iterator beg2, iterator end2, iterator dest);
                注意：两个集合必须是有序序列，dest是目标容器的迭代器
                且因为是放到另一个容器中，所以新容器要提前开辟空间  v.resize(min(v1.size(), v2.size()))   //但是min也是一个算法，要包括algorithm头文件

                返回的是交集中最后一个元素的迭代器位置，然后最好用一个迭代器End接收下来，在遍历输出的时候就从begin()，迭代到End即可； 如果选择从容器自身的begin()，迭代到end()的话，会把后面当时多扩充的空间也给输出出来然后就一堆的0；

        5.6.2 set_union  并集
            原型
                set_union(iterator beg1, iterator end1, iterator beg2, iterator end2, iterator dest);
                注意：两个集合必须是有序序列，dest是目标容器的迭代器
                且因为是放到另一个容器中，所以新容器要提前开辟空间  v.resize(v1.size()+v2.size())

                返回的是并集中最后一个元素的迭代器位置，然后最好用一个迭代器End接收下来，在遍历输出的时候就从begin()，迭代到End即可； 如果选择从容器自身的begin()，迭代到end()的话，会把后面当时多扩充的空间也给输出出来然后就一堆的0；

        5.6.3 set_difference  差集
            原型
                set_union(iterator beg1, iterator end1, iterator beg2, iterator end2, iterator dest);
                注意：两个集合必须是有序序列，dest是目标容器的迭代器
                且因为是放到另一个容器中，所以新容器要提前开辟空间  v.resize(max(v1.size(), v2.size()))  //max也是算法，包含<algorithm>头文件

                返回的是差集中最后一个元素的迭代器位置，然后最好用一个迭代器End接收下来，在遍历输出的时候就从begin()，迭代到End即可； 如果选择从容器自身的begin()，迭代到end()的话，会把后面当时多扩充的空间也给输出出来然后就一堆的0；

                因为差集的定义问题，所以里面的容器1和容器2的顺序有关系，谁放前就是谁的差集，也就是他有别人没有的
*/