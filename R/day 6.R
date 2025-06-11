# Lecture 6: Scientific Computations in R
# 6.1 basic math
# 有时候一个n x p的矩阵不会把所有元素写出来，而是直接写X=(xij)表示这是一个二维矩阵，里面用xij表示第i行第j列的元素
# the norm of y定义位sqrt(y'y), sometimes donated as ||y||2, 注意norm等于0当且仅当y完全=0
# inner product: x'y = x1y1 + x2y2 + ... + xnyn, sometimes donated as <x,y>
# outer product: xy'是一个pxp的矩阵，第(i,j)个元素是xiyj, sometimes donated as x ⊗ y
# R语言有built-in function t()来计算矩阵的转置，"%*%"来计算矩阵乘法和向量内积，"%o%"来计算向量外积
# 如果两个矩阵之间用了*， 则表示逐元素相乘，两个矩阵的维度必须相同，得到的矩阵对应位置等于对应位置两个数相乘
x <- c(1, 2, 3)
x %*% x
# 14
# 我们可以用向量构造一个对角矩阵，或者从一个矩阵中把对角元素取出来变成一个向量
diag(x)
# x如果是向量，返回矩阵；如果是矩阵返回向量；如果是一个数字n，返回一个n x n的单位矩阵
# diag()即使x不是方形矩阵也可以用，从(0,0)开始按对角去取
# a matrix is called a singular matrix if its inverse does not exist, det=0
det()
# 返回传入的方形矩阵的行列式值
# 解方程组可以用矩阵形式
A <- matrix(c(1, 2, 3, 4), nrow = 2)
b <- c(5, 6)
x <- solve(A, b)
# x是一个向量，表示解方程组Ax=b的结果,用solve()函数来解方程组
# 因此计算逆矩阵的方法也可以用I和solve搞定
iden <- diag(c(1, 1))
solve(A, iden)
# 返回逆矩阵
# 或者直接输入solve(A)就可以得到逆矩阵
# R还有内置的计算covariance,correlation矩阵的函数，这种矩阵每个位置都是对应的两个变量的协方差或相关系数，一共有p(p-1)/2个位置，X1到Xp个随机变量
d <- read.csv("iris.csv")
colnames(d) <- NULL
sigma <- var(d[, 1:4])
# 计算协方差矩阵
cor(d[, 1:4])
# 计算相关系数矩阵

# 6.2 Markov chain
# Markov chain with transition matrix P
# P[i,j]表示从状态i转移到状态j的概率
# P是一个方形矩阵，行和列的数量相同，表示状态的数量, 每一行概率相加等于1
# pi(t)如果用来代表Xt的概率分布，那么pi(t+1) = pi(t)P, pi(t)是一个行向量，表示每个状态的概率
P <- matrix(c(0.3, 0.2, 0.5, 0.4, 0.3, 0.3, 0.3, 0.4, 0.3), nrow = 3, byrow = TRUE)
p <- c(1, 0, 0)
(p <- p %*% P)
# 重复计算后会发现收敛，收敛的分布叫做invariant distribution of P，满足pi=piP,也就是说后面乘再多次也还是这个pi，根据特征值特征向量 Ax = λx的定义，pi是P的特征向量，特征值是1
# 注意pi的转置是P的转置的特征向量，对于特征值1且归一化之后的情况
eig <- eigen(t(P))
# eigen()求特征值，返回一个列表，$values是特征值，$vectors是特征向量
eig$vectors[, 1] / sum(eig$vectors[, 1])
# vectors 是一个矩阵，每一列是一个特征向量，取第一列除以它的和得到归一化的特征向量,一列对应一个特征值

# 6.3 finding roots of nonlinear equations
# uniroot()可以找到一维非线性方程的根，一维非线性函数比如f(x) = x^2 - 2
fx <- function(x) {
    3 * exp(-0.5 * x) + 3 * exp(-1 * x) + 3 * exp(-1.5 * x) + 103 * exp(-2 * x) - 98.39
}
uniroot(fx, c(0.0001, 1))
# uniroot()的第一个参数是函数，第二个参数是一个区间，表示在这个区间内寻找根
# 注意这个区间必须包含一个根，否则会报错
# uniroot()返回一个列表，$root是找到的根，$iter是迭代次数，$f.root是函数在根处的值,$estim.prec是估计的精度
# 首先我们需要定义我们的函数f(x)取求解f(x)=0, 然后给一个包含根的区间
# 这个区间的两端必须在f(x)上衡量时符号相反，否则报错
plot(fx, xlim = c(0, 0.1))
# plot的第一个参数可以接受很多类型，比如函数，向量，矩阵等
# 或者用curve()函数来画函数图像, 函数，自变量开始点，自变量结束点
# bisection algorithm可以用来求解一维非线性方程的根，要求函数在区间两端符号相反
# 每次取区域中点，如果精度不够且最大循环次数没到，就用中点替换掉同符号的边界缩小一半的区间，这样去逼近根

# 6.4 numerical integration
stdnorm <- function(x) {
    exp(-x^2 / 2) / sqrt(2 * pi)
}
integrate(stdnorm, -Inf, 0)
# 0.5 with absolute error < 4.7e-05, integrate()函数可以用来计算一维函数的积分，第一个参数是函数，第二个参数是积分区间
# 注意integrate()函数返回一个列表，$value是积分值，$abs.error是绝对误差,会直接输出结果和误差

# 6.5 differentiation
D(expr, "x")
# expr是一个表达式，"x"是变量名，D()函数可以用来计算简单表达式的导数，而且他是符号运算不是数值运算，也就是说不是迭代逼近的，保有精确度
# 二阶导就嵌套，D(D(expr, "x"), "x")， 偏微分就改掉后面的变量
fx <- expression(exp(x * y))
D(fx, "x")
D(fx, "y")
# 注意要用expression()函数来定义表达式，D()函数才能正确识别变量，不能用function()函数
# 可以说如果是数值计算的就要用function，因为他要算值，如果是符号计算的就用expression

# 6.6 univariate optimization
fx <- function(x) {
    3 * exp(-0.5 * x) + 3 * exp(-1 * x) + 3 * exp(-1.5 * x) + 103 * exp(-2 * x) - 98.39
}
gx <- function(x) {
    fx(x)^2
}
optimize(gx, c(0, 1))
# 第二个参数是一个区间，表示在这个区间内寻找最小值
# optimize()默认是最小值，如果要算最大值，里面加个option maximum=TRUE,传入的仍然是函数因为是数值计算
# 注意optimize()返回一个列表，$minimum是找到的最小值，$objective是函数在最小值处的值

# 6.7 multivariate optimization
fx <- function(x) {
    p <- sqrt((x[1] - 5)^2 + (x[2] - 5)^2)
    -sin(p) / p
}
# fx接收一个两个元素的向量
optim(c(2, 2), fx)
# optim()函数是一个通用目的的优化函数，可以用来做多元优化，第一个参数是初始点，第二个参数是目标函数
# 注意optim()返回一个列表，$par是找到的最优点，$value是函数在最优点处的值，$counts是迭代次数
# 注意optim()默认是最小化，如果要最大化，可以在目标函数前加个负号
# counts是一个列表，$function是函数调用次数，$gradient是梯度调用次数, $convergence是收敛标志，0表示收敛，1表示未收敛
# 因为函数是一个二维的函数
# R提供了内置函数persp()来画三维图像(stand for perspective plot透视图)
# persp需要三个参数x,y,z，x和y是网格点，z是对应的函数值，xy都是向量，z是一个矩阵
# 还有一个参数theta和phi，表示视角，theta是绕z轴旋转的角度，phi是绕x轴旋转的角度， col,ticktype是颜色和刻度类型
x <- seq(0, 10, length.out = 100) # length.out是生成的向量长度
y <- seq(0, 10, by = 0.1)
z <- outer(x, y, fx)
persp(x, y, z, theta = 30, phi = 30, col = "lightblue", ticktype = "detailed")
# detailed表示刻度线详细，还有其他选项比如"simple", "none"

# 6.8 Nonlinear least squares
# 需要先构造一个含参数学模型，一个error函数，然后去最优化参数
fx <- function(x, p) {
    (p[1] * x) * (p[2] + x) / (x^2 + p[3] * x + p[4])
}
# 这个就是数学模型,p是参数向量，目标是找到最好的p使得我的这个近似函数算出来的值和实际值的平方和最小
obj <- function(p, data) {
    x <- data[, 1]
    y <- data[, 2]
    sum((y - fx(x, p))^2)
    # 最小二乘法
}
d <- read.csv("nls.csv")
p <- c(1, 1, 1, 1) # 初始参数
out <- optim(p, obj, data = d)
# optim默认只会把第一个参数传进目标函数，如果目标函数还需要其他参数就必须用R语言的机制，在后面加上形参名和参数值
# 这实际上是R的···参数功能，前面有学到过，允许函数接受未知数量的参数，并且通过···把他们当作整体一起传给其他函数或者放入list等数据储存类型中
# e.g. optim(p, func, ···){
#   func(p, ···)
# }
# 这样子所有后面的未知数量个参数就都传给了func函数，如果有形参名就不需要按顺序，没有就必须按顺序
# 另外在有···机制的函数里，通常也是用arg <- list(···)； arg$name来访问参数，如果没有传入形参名，那就只能按index访问会很不方便
x <- seq(0, 10, length.out = 100)
fix <- fx(x, out$par)
plot(x, fix, type = "l", col = "blue", lwd = 2, ylim = c(0, 10), xlab = "x", ylab = "y")
points(d, col = "red", pch = 19)
# 画出拟合曲线和数据点

# 6.9 nonlinear multivariate functions' root
# 用multiroot()函数来求解多元非线性方程组的根
library(rootSolve)
fxy <- function(x) {
    c(x[1]^2 + x[2]^2 - 1, x[1] + x[2] - 0.5)
    # 多个方程需要用c形成一个向量
}
out <- multiroot(fxy, c(0.5, 0.5))
# multiroot()的第一个参数是函数，第二个参数是初始猜测点
# 注意multiroot()返回一个列表，$root是找到的根，$f.root是函数在根处的值，$iter是迭代次数，$estim.prec是估计的精度
