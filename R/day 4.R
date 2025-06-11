# Lecture 4 Programming in R
# write own user defined function
# 如果一个文件ch4.r里面包含了很多函数，我们可以直接加载这些函数通过R command: source("ch4.r")

# 4.1 writing functions in R
# syntax
myfunction <- function(arg1, arg2, ...) {
    statements
    return(object)
}
# 如果没有显式的返回，最后一个执行语句的返回值会被返回
se <- function(x) {
    n <- length(x)
    return(sd(x) / sqrt(n))
}
# 函数可以被输入或者修改通过fix(function_name)的方法
# fix(se)会打开一个记事本，如果是新的函数里面就只有框架，然后就可以自己填充语句保存关闭，这样就定义了一个函数
# 如果不想这么麻烦直接输入上面的几行代码也可以定义一个函数，不过要修改的话还是只能用fix函数
se
# 会返回fix(se)打开的记事本中看见的几行代码语句
se(1:20)
# 传入x，测试函数
# 注意：写函数最好使用缩进增加可读性

# 4.2 scope of variables
# the scope of variable tells us where the variable would be recognized
# 比如函数内定义的变量有Local scope，只能在函数内被识别
# 在不同函数内可以创建同样名字的变量并且没有问题
f <- function() {
    x <- 1
    g()
    return(x)
}
g <- function() {
    x <- 2
    return(x)
}
f()
# 返回1，因为g()函数内的x是局部变量，只能在g()函数内被识别，不会影响到f里面的x
# 和其他语言不同的点在于，以上都是函数的定义，只有f()是调用，只要在调用之前f和f里面的g都被定义了就不会报错
# 如果在定义g之前就调用了f就会报错；其他语言g必须写在f之前才能调用；R是动态解释性的，只有在调用时才会去查找是否存在
# 其他是在编译的阶段就检查
# super assignment可以用于全局变量赋值
f <- function() {
    if (!exists("f_count")) {
        f_count <<- 1
    } else {
        f_count <<- f_count + 1
    }
    return(f_count)
}
# <- 在当前环境赋值， <<- 从当前环境开始逐级向上级环境中查找变量并赋值，到全局都还没有的话就创建全局变量
# exists括号里面用双引号包括变量的名称，总之接收字符串形式的变量名

# 4.3 logical expressions
# 1,0可以用来表示TRUE和FALSE
# 逻辑表达式里面的与或非用的是& | !
# difference between & and &&, | and ||
# &是一个向量化操作符，返回一个向量； &&只检验从左到右每个向量的第一个元素,同时要求两个操作数都是长度为1的逻辑值；|同理
# &&唯一的优势就是他是短路的，第一个操作数为FALSE时，第二个操作数不会被计算，可以避免第二个操作符有问题时使用&报错

# 4.4 the for loop
for (x in v) {
    commands
}
# 设置变量x，他每次等于v中的一个元素，执行下面的命令， v通常是一个向量，但也可以是一个列表
# 花括号的作用是把命令集合在一起，R会把他们看作一个命令，因此如果只有一个命令这个括号不是必须的，if else也是，如果不用括号只有紧跟的第一个语句被当作命令
fi <- numeric(12)
# numeric是一个构造函数，创建一个指定长度的数值型向量，初始值为0
fi[1] <- fi[2] <- 1
# 合法的串联赋值
for (i in 1:length(v)) v[i] <- v[i] + 1
# 这样才可以修改v向量内的值，否则用x<-x+1只会修改x的不会修改v的
v <- c(1, 1)
for (i in v) v <- c(v, 1)
v
# 这并不是一个无限循环，因为for loop的循环次数以及里面的v在开始前就会确定并且无法修改，command里对v的修改不会影响Loop

# 4.5 the if statement
if (condition) {
    commands
} else if (condition) {
    commands
} else {
    commands
}

prime_list <- function(n) {
    if (n > 2) {
        comp <- seq(2, n)
        # comp维护还没有被移除的数字的向量
        prime <- c()
        for (i in seq(2, n)) {
            if (any(comp == i)) {
                prime <- c(prime, i)
                # 如果i在comp中，说明i是一个素数
                comp <- comp[comp %% i != 0]
                # 移除comp中所有能被i整除的数字
            }
        }
        return(prime)
    } else {
        stop("n must be greater than 2")
    }
}
# any()用于检查一个逻辑向量中是否至少有一个为TRUE
# stop()函数用于手动触发一个错误并终止程序，会输出内容

# 4.6 the while loop
while (condition) {
    statements
}
# 有些时候我们想重复某些语句，但是重复的方式无法提前知道
# 条件被评估，如果是FALSE，就不会再做
# 注意： vec[-1]不是去除最后一个元素，而是去掉第一个元素返回其他剩下的，要取最后一个应该用vec[length(vec)]
cat("loan will be paid off in", n, "months.\n")
# cat()函数用于连接多个字符串并输出，\n表示换行,和paste()类似，但cat()不会返回一个字符串，而是直接输出到控制台

# 4.7 the repeat loop
# 有时候我们不想固定循环次数，同时也不想把test放在循环的顶部像while那样
# 这时候可以用repeat, 这个循环会一直重复直到我们呢执行了一个break语句
repeat {
    statements
    if (condition) {
        break
    }
}
# break语句会立刻终止循环也可以用在for和while循环中
# next语句会跳过当前循环的剩余部分并开始下一次循环，立刻返回顶部，也可以用在各种循环中
sample(c(0, 1), size(20), replace = TRUE)
# sample()函数用于从指定的向量中随机抽样，size指定抽样的数量，replace = TRUE表示允许重复抽样,还有一个参数可以用于指定权重比例
# 三种循环一样好，但是用向量化的操作会比他们都要快，尤其在数据多的情况下，应该多用向量层面的操作处理问题，少用循环
ifelse(condition, expr1, expr2)
# ifelse()函数用于向量化的条件判断，condition是一个逻辑向量，如果为TRUE则返回expr1对应位置的值，否则返回expr2对应位置的值,允许对整个向量或数组进行条件判断并返回同样长度的结果向量
# ifelse()里面还可以嵌套，跟weka的ifelse结构一致，就是正确错误分别执行两个位置的语句
switch(expr,
    case1 = {
        statements
    },
    case2 = {
        statements
    },
    ...,
    default = {
        statements
    }
)
# switch()函数用于多分支选择，expr是一个表达式或变量，根据其值选择对应的case执行
# 可以省略default关键字，直接把默认情况放在最后
# 和C++一样，如果expr==case1，就执行case1对应的语句，case2同理，default是可选的，如果没有匹配到任何case就执行default对应的语句
if (dist == "norm") {
    rnorm(n)
} else if (dist == "unif") {
    runif(n)
} else {
    stop("Unknown distribution")
}
# 这是一个隐式if else的嵌套结构，第二行都是第一行的else部分，不加括号是else把后面的一整个if-else语句当作statement
# 函数的参数可以设置默认值，并且一旦定义好了就跟build-in函数一样可以直接调用
# ifelse()和向量的逻辑选取判断可以处理向量中有NA值的情况，对于前者，他是遇到NA直接返回NA不会执行yes or no
# 后者会忽略NA值，返回TRUE的元素对应的值，但是如果用循环来处理每个数，那就必须要考虑NA值的情况
# 对于一个表达式，如果里面任何一个地方出现了c返回的就会是一个向量，标量跟向量做运算是每个元素都计算
# 向量跟向量做运算，是对应index的元素做运算,如果长度不匹配会warning
# ifelse()还有用处是在避免一些warning的出现
sqrt(ifelse(x >= 0, x, NA))
# sqrt(NA)返回NA，避免负数开根
