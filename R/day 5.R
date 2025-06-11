# Lecture 5: Input, Output and other programming issues
# 5.1 Error handling
stop("This is an error message")
# 可以用if判断加stop()函数来手动触发一个错误并终止程序
# stop()属于error

# 5.2 warning
warning("This is a warning message")
# warning比error弱一些，他指示有些东西出错了但是这个代码可以回复并且继续运行
# 与stop不一样的地方是，调用一个函数可能会返回很多个warning，但是stop的信息最多只有一个

# 5.3 user defined operator
"%+-%" <- function(x, s) {
    c(x - s, x + s)
}
# 自定义运算符必须要用括号括起来然后左右两个%符号
3 %+—% 2

# 5.4 replacement functions
# 作用有点像直接在原对象上对某部分进行修改
# 比如我们可以用names()来修改一个列表的name attribute
x <- list(a = 1, b = 2, c = 3)
names(x) <- c("A", "B", "C")
# 我们可以写自己的替换函数
"replacement_function_name" <- function(x, position, value) {
    x[position] <- value
    return(x)
}
x <- 1:10
replacement_function_name(x, 3) <- 100
# 第三个参数看起来像是赋值，这是R的语法设计，展示replace的目的
# 但实际上还是函数调用，因此形参列表顺序很重要，要传的是最后一个形参

# 5.5 flexible number of arguments
maxlen <- function(...) {
    arg <- list(...)
    mx <- 0
    for (x in arg) mx <- max(mx, length(x))
    return(mx)
}
# ···代表允许传入任意数量的参数，然后处理的时候也是用···来指代传入参数，后续可以通过list等来获取数据

# 5.6 saving multiple outputs from functions
# 返回的时候return(c())里面包括多个值
# c(a,b,c)直接放值的话输出出来就一行，没有name；如果要有name，c(a = a, b = b, c = c)就可以了,这样输出是两行
# 第二个方法： 用list(a,b,c,d,e)储存起来，然后names(list)<-c("a", "b", "c", "d", "e")取名,返回list
# list返回的话是按照类一列下来，后续可以用$来取值

# 5.7 formatted input and output
outer(y, x, func)
# outer的作用是对两个向量所有的元素两两进行function操作，返回一个矩阵，前一个参数是行，后一个参数是列
sprintf("Pi is %f", pi)
# sprintf的作用是格式化输出，%f代表浮点数，%d代表整数，%s代表字符串,浮点数实数输出默认6位小数
sprintf("Pi is %.3f", pi)
# %.3f代表保留三位小数
sprintf("%5.1f", pi)
# %5.1f代表保留一位小数，且总长度为5位，不够的前面补空格
sprintf("%-10f", pi)
# -表示左对齐，10表示总宽度为10，没有.说明按照默认6位小数输出
# "3.141592  ", 宽度和保留小数没有关系，不够的就补空格
# 如果不加-，默认是右对齐，"  3.141592"
sprintf("%e", pi)
# %e代表科学计数法输出, 但也还是6位小数
# 第一个参数带%的叫formatting string，f代表fixed point.

# 5.8 the cat function
# 非常适用于打印string, numbers,variable在自定义的函数里
n1 <- dim(x)[1]
# dim返回x的维度比如（2，3）两行三列
for (i in 1:n1) {
    for (j in 1:i) {
        cat(sprintf("%2.0f", x[i, j]), " ")
    }
    cat("\n")
}
# cat是连续输出的，每个都接着上一个cat往输出台输出内容，直到程序结束

# 5.9 readline function
# readline的作用是从控制台读取输入,默认是character类型，需要做类型转换如as.numeric()
# 对于plot，如果传入的是一个数值矩阵，默认第一列当作x坐标，第二列当作y坐标，后续多的列舍弃
# 在调试阶段可以用readline()来暂停程序，等待用户输入

# 5.10 recursive functions
# 自己调用自己没什么好说的，和其他的语言一致

# 5.11 efficient programming
# 为了写出高效的代码，需要了解正在写代码的平台
# R设计出来就是用以处理向量的，作用在整个向量上的操作通常快于一个个元素去操作，这就是为什么vector-based programming好于用loop
proc.time()
# 这个built-in函数让我们可以计算实际的代码运行时间，用法如下：
t0 <- proc.time()
# 代码
t1 <- proc.time()
process_time <- t1 - t0
# 得到的是一个向量，包含了user time, system time, elapsed time，总之能对向量对象进行操作就比对单个元素操作快
is_positive <- function(x) {
    if (x > 0) 1 else 0
}
# 注意，这个函数里面因为有if所以是不允许传入一个向量x的，就算传入了一个向量他也只会用第一个值，所以这个函数是没有办法向量化的
# 但是有两个办法可以使他向量化，1：对函数进行修改，if变成ifelse；ifelse是一个向量化的函数，第一个参数是一个逻辑向量，然后根据这个逻辑向量的值的每个具体的元素的值来返回第二个或第三个参数，最终返回一个向量，这种情况下x就可以传入一个向量了
# 第二个方法是不修改函数，用vapply()方法，这个函数第一个参数是传入的向量，第二个参数是非向量化函数，第三个参数是函数返回格式
vapply(x, is_positive, numeric(1))
# 他的原理是对x的每一个元素调用一次is_positive函数，然后返回，numeric(1)代表是浮点的格式
# logical(1)代表是逻辑格式，integer(1)代表整数格式，character(1)代表字符串格式
# 另外我们前面还见到过outer函数，就是把两个向量每个元素互相组合的函数，返回一个矩阵，这使得矩阵操作可以执行加速代码
A <- matrix(1:16, nrow = 4)
outer(1:nrow(A), 1:nrow(A), ">=") * A
# 这就直接得到了下三角矩阵，根本不需要两个循环
# 除了1：nrow(A)，还可以用函数seq_len(nrow(A))来代替，这个函数的作用是生成一个从1到nrow(A)的整数向量

# 5.12 general guidance
# 交换两个数，除了用一个新的临时变量，还能用下面的方法
x[i] = x[i] + x[j]
x[j] = x[i] - x[j]
x[i] = x[i] - x[j]
# 在R里可以使用traceback()函数来获取有关一个error的更多信息，当一个error发生时，R会记录下函数调用的堆栈信息，traceback()会打印这个列表
