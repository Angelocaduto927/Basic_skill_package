# Lecture 3: Basic Data Visualization
# simple used options: pie, histogram, Quantile-Quantile, Box, Scatter, Matrix scatter, Time series, Mathematical function plot
# the functions to draw these plots are called "high level"
# because we don't worry about the details of where the ink goes
# only describe the plot we want and R does the drawing
# all graphics in R are produced in separate graphics windows
# the windows and the graphic can be resized, copy, paste in the usual way
# by copy and paste, we can include R's output to our reports

# 3.1 histogram
# 在很多文章里，为了美观会需要把许多图片生成在一个单独的绘图区域内
# R可以把很多图片生成在一个框内用函数par()里面的mfrow参数
# par代表graphical parameters, mfrow代表multi-frame filled in row-wise
# 也有mfcol代表按照列优先排列，可以用help(par)来看看里面的选择
d <- read.csv("popden1.csv", stringAsFactor = T)
names(d)
# display the names in d (the first row)
par(mfrow = c(2, 2))
# set up a 2x2 multi-frame for graphics and fill by row first
hist(d$year86)
hist(d$lnpd86)
hist(d$year90)
hist(d$lnpd90)
# 原本的变量高度skewed to the right, 经过对数转换后减少了skewness
# skewed to the right意味着右侧尾巴较长，有少量数据在右侧拉长了右端
# 可以用xlab, ylab, main来命名坐标和图像
# 很多统计技术都假设数据是正态分布的，可以加一个normal density作为参考线
par(mfrow = c(1, 2))
hist(d$lnpd86, freq = F)
# freq = F 表示直方图绘制的是密度直方图而不是频数直方图
x <- seq(5, 12, 0.1)
# 因为提前知道两个直方图的分布是从5-12，所以用这个办法构造正态分布线的横坐标
lines(x, dnorm(x, mean(d$lnpd86), sd(d$lnpd86)), lty = 2)
# dnorm能获得在x位置，在这个均值和方差的条件下的正态分布的概率，所以能把图画出来
hist(d$lnpd90, freq = F)
lines(x, dnorm(x, mean(d$lnpd90), sd(d$lnpd90)), lty = 2)
# lines和abline都可以在现有的图像上添加线，但是abline专门用于直线
# lines可以是直线或者曲线，取决于接收进来的点的分布
# 线型
# 6: twodash
# 5: longdash
# 4: dotdash
# 3: dotted
# 2: dashed
# 1: solid
# 0: blank

# 3.2 Pie chart
# pie chart通过把一个圆盘分成面积成比例的块，展示一个向量的数字
pie(d$lnpd90, labels = d$district, cex = 0.8, main = "log(density)")
# cex是character expansion factor, 0.8表示字体大小是默认的80%
# 当各个部分大小相近时，pie chart就不好明显的比较出各个部分的大小

# 3.3 Bar chart
# 当各个类别的比例相近时，用bar chart展示更高效
# 下面生成两个bar charts，一个有color and legend
# 另一个是黑白，legend text在bar的里面然后数字在bar的末端
# legend是图例的意思，解释图表中的颜色形状的区域
barplot(d$lnpd90,
    horiz = T, col = rainbow(20),
    xlim = c(0, 25), legend.text = d$district,
    args.legend = list(x = 25, y = 23, cex = 0.8),
    main = "log(density of population in 1990"
)
# horiz = T生成一个横向的bar chart
# col = rainbow(20)用彩虹颜色组合出20种颜色
# xlim = c(0, 25)设置x轴的范围从0到25
# legend.text = d$district 表示图例的文字是d$district，每个颜色是哪个district的
# args.legend是一个legend的列表,右上角位置放在x = 25, y = 23
y <- barplot(d$lnpd90,
    horiz = T, col = "white", xlim = c(0, 15),
    main = "log(density of population in 1990"
)
# barplot会返回一个向量代表每个条形的中心位置，
x <- round(d$lnpd90, 1)
# bar chart会返回一个向量，对于横的bar chart记录的是中心点的y位置
# x的位置有传入数据直接控制，不需要额外记录，只需要记录y确保不会重叠
# bar的宽度是系统默认的，如果使用了width调整，返回的位置可能不准确后续用不上了
# round里面的digit用来控制小数点后位数
# options(digits = n) 用来控制整体的有效位数，系统会灵活使用科学计数法，四舍五入等来保证只出现4个数字
text(0.5 * x, y, d$district, cex = 0.8)
text(x + 0.8, y, labels = x, cex = 0.8)

# 3.4 grouped bar chart
yr86 <- by(d$lnpd86, d$Region, sum)
# by函数可以对数据进行分组计算，按region分组，计算各组内的lnpd86的和
yr90 <- by(d$lnpd90, d$Region, sum)
# 返回的是一个类列表，但是因为是sum,mean,sd等函数，返回的结果是每个组一个标量数据而不是复杂的数据结构
# 所以当cbind遇到这种类型的by对象时，会自动调用unclass去除类属性当作普通向量处理，然后就可以bind了
# 而bind的输出结构是竖着的，所以用cbind
rs <- cbind(yr86, yr90)
# rs现在是一个矩阵
barplot(t(rs), beside = T, horiz = F, legend.text = c("yr86", "yr90"))
# t(rs)是转置矩阵，变成横向的
# beside = T 表示每个组的条形是分开的而不是叠加在一起
barplot(rs,
    beside = T, horiz = T, xlim = c(0, 100), ylim = c(0, 10),
    legend.text = c("HK", "KL", "NT"), args.legend = list(horiz = T, bty = "n")
)
# 这是横着的grouped bar chart
# horiz = T 表示legend是横向的，bty="n" 表示legend没有边框
# barplot画矩阵的时候默认是按照列分大组，行分小组，根据自己的大小组安排看是否需要转置
# args.legend等价于调用底层函数legend(),不指定位置的话会自动放在右上角
prop.table(t(rs), margin = 1)
# margin = 1 means row, prop.table会计算个部分的比例按照margin来算
barplot(prop.table(t(rs), 1), horiz = F, legend.text = c("yr86", "yr90"))
barplot(prop.table(rs, 2),
    horiz = F, xlim = c(0, 3),
    legend.text = c("HK", "KL", "NT")
)

# 3.5 Normal quantile-quantile plot(QQ plot)
# normal probability plot is a method for checking the normality assumption
# 很多测试要求数据是来自一个正太分布population的随机样本
# 也就是数据是independently and identically distributed as normal
# 实际操作中，不可能知道数据的真实分布，只能期望不是跟normal distribution差太多
# normal probability plot是画sample quantiles versus the theoretical quantiles from a standard normal distribution
# 如果图像很接近45度的直线，说明样本百分位数和标准正态分布的百分位数线性相关，因此正态分布假设成立
# R有built-in function qqnorm()来画图，以及qqline()来添加参考线
# 相当于qqnorm是标点，qqline是画出一条线
par(mfrow = c(2, 2))
qqnorm(d$year86, main = "1")
qqline(d$year86, col = "red")
qqnorm(d$year90, main = "2")
qqline(d$year90, col = "red")
qqnorm(d$lnpd86, main = "3")
qqline(d$lnpd86, col = "red")
qqnorm(d$lnpd90, main = "4")
qqline(d$lnpd90, col = "red")
# qqline理论上是通过连接一四分位的点和三四分位的点

# 3.6 general QQ plot
r <- runif(1000, -10, 10)
# sample uniform distribution
qqnorm(r)
qqline(r, col = "red")
# qqnorm画出来验证不是正态分布
hist(r)
# 直方图画出来像Uniform
n <- length(r)
r2 <- sort(r)
i <- ((1:n) - 0.5) / n
# 减0.5是为了五篇修正的调整，统计学上有助于更准去的反映数据点在整个分布中的位置
# 避免了极端值过于靠近0或者1的概率边界
q <- qunif(i)
# qunif 默认0-1
plot(q, r2, main = "QQ plot")
abline(lsfit(q, r2), col = "red")
# remarks, QQ plot是一个图形工具用来辅助判断data是不是normal distributed，结论可能很主观
# 因此还有其他客观的方法判断一个dataset是不是正态分布的
# Shapiro-Wilk test: reliable test of normality, 适用于小样本(n<50),因为有更强的能力去拒绝零假设当样本小的时候
# Kolmogorov-Smirnov test: 更general的test,把样本的经验分布函数(也就是样本的cdf)和参考函数的cdf比较，但是他比Shapiro-Wilk test在小样本时的拒绝正态分布的零假设的能力弱
# Anderson-Darling test: Kolmogorov-Smirnov test的改版，在尾部增加更多的权重，在小样本时powerful
# Jarque-Bera test: 基于分布的skewness and kurtosis，对于大样本能力更强

# 3.7 Box plot
# 除直方图外另一个常用的展示数据分布的方法
# 还可以用于识别outliers和比较两个样本的分布
par(mfrow = c(1, 2))
yr <- c(rep(86, 19), rep(90, 19))
pd <- c(d$year86, d$year90)
lnpd <- c(d$lnpd86, d$lnpd90)
boxplot(pd ~ yr, main = "1")
boxplot(lnpd ~ yr, main = "2")
par(mfrow = c(2, 1))
boxplot(pd ~ yr, horizontal = T, main = "3")
boxplot(lnpd ~ yr, horizontal = T, main = "4")
# Boxplot的几条线，中间粗的是中位数，箱子上下是25和75百分位数，延长出去的叫whiskers(或者fence)，会向外延伸1.5倍箱体，在两个whiskers中间的数据都是合理区域内的数据，超出范围的就是Outliers,如果没有outliers,那么whiskers只延长到最大值和最小值
# pd~yr 表示pd是因变量，yr是自变量，~表示因变量和自变量之间的关系，也就是按照yr分组画pd
# pd~yr相当于把两个向量组合起来，形成一个个点，然后yr是自变量，根据yr来划分pd
# there are other ways to compare and present these data
s86 <- split(d$lnpd86, d$Region)
# split返回一个list
s90 <- split(d$lnpd90, d$Region)
par(mfrow = c(1, 3))
boxplot(c(s86$HK, s90$HK) ~ rep(c(86, 90), each = length(s86$HK)), main = "HK", xlab = "", ylab = "")
boxplot(c(s86$KL, s90$KL) ~ rep(c(86, 90), each = length(s86$KL)), main = "KL", xlab = "", ylab = "")
boxplot(c(s86$NT, s90$NT) ~ rep(c(86, 90), each = length(s86$NT)), main = "NT", xlab = "", ylab = "")
par(mfrow = c(1, 1))
# 重新par会使窗口恢复到单图形模式，然后后续画图的话会覆盖，如果是添加标题什么的就是在当前图形上添加
title(sub = "ln by region")
par(mfrow = c(1, 2))
boxplot(lnpd86 ~ Region, data = d, main = "lnpd86 by region")
boxplot(lnpd90 ~ Region, data = d, main = "lnpd90 by region")
# 注意，如果R会自动把~后的变量弄成factor处理，然后分组，如果完全没有重复的那就每个数据一个组

# 3.8 Scatter plot
# it's a natural and useful way to find out relationship between two variables
# linearly or nonlinearly related; high or low, positive or negative correlation
par(mfrow = c(1, 1))
plot(d$lnpd86, d$lnpd90)
text(d$lnpd86 - 0.1, d$lnpd90 + 0.1, cex = 0.8)
# 默认text添加的内容是case number in the plot with x- and y-coordinates, 如果要指定内容要加第三个参数
# 第三个参数默认是从1开始的序号，所以可以不写
plot(d$lnpd86, d$lnpd90, pch = 21, bg = c("red", "blue", "green")[d$Region])
# pch是点的形状，21是可填充颜色的圆圈，bg是填充背景色，后面的[d$Region]是根据Region来填充颜色
d[d$year86 < d$year90]
# 创建一个Logical向量，表示year86小于year90的行，然后用[]选出为True的行，这是逻辑索引的规则
id <- (d$year86 < d$year90) + 1
par(mfrow = c(1, 2))
plot(d$lnpd86, d$lnpd90, pch = c(19, 21)[id])
# 依据id的向量的不同画出两种点
plot(d$lnpd86, d$lnpd90, pch = 21, col = c("red", "blue")[id])
# 依据id的向量的不同画出两种颜色的点
# 如何用abline把蓝点和红点分开 --> 回归模型
model <- glm(I(id == 1) ~ lnpd86 + lnpd90, data = d, family = binomial)
# I表示整个括号内的都是因变量整体，加号表示两个数据都被用于自变量计算方程
# family = binomial表示这是一个二项分布的回归模型，适用于分类问题
# glm是generalized linear model的缩写，适用于各种类型的回归分析
# 提取系数
coef <- coef(model)
intercept <- coef[1]
slope_x <- coef[2]
slope_y <- coef[3]
# 决策边界方程：intercept + slope_x * x + slope_y * y = 0
# 转换为 y = a*x + b 的形式：
a <- -slope_x / slope_y
b <- -intercept / slope_y
# 第三步：画出分界线
abline(a = b, b = a, col = "green", lwd = 2)

# 3.9 Matrix scatter plot
# iris.csv包括了150个样本和5个变量，前四个变量是iris花的测量数据，最后一个指示了鸢尾花的种类
d <- read.csv("iris.csv")
pairs(d[, 1:4], pch = 21, bg = c("red", "blue", "green")[d$Species])
# matrix plot的意思是每个变量之间两两画一个关系图，最后形成一个4x4的矩阵图
# pairs()函数会自动生成一个矩阵图,和plot()不同的是，pairs()会自动生成所有变量之间的关系图

# 3.10 Time series plot
# 它就是一个x轴是时间，y轴是数据的图
# stock.dat包含了修正过的每天股市收仓价位，从1999到2002
d <- read.table("stock.dat", header = T)
# read.table是最通用的读取方式，根据文本内的数据分割情况指定sep = ''来读取，按行读取变成data frame结构形式
names(d)
t1 <- as.ts(d$HSBC)
# as.ts用于把一个向量或者矩阵变成时间序列对象
# change to time series object, time series object是一个对象，表示一组按时间顺序排列的数据
# 需要有时间戳，或者是一个时间序列的索引
t2 <- as.ts(d$CLP)
t3 <- as.ts(d$CK)
par(mfrow = c(3, 1))
plot(t1)
plot(t2)
plot(t3)
# 对于as.ts(d$HSBC),后面什么参数都没有，所以他被认为是一个没有周期结构的普通时间序列，然后时间索引从start = 1开始一直累加
# 这样一个向量就变成了一系列的点向量，然后就可以用Plot来画出散点图
# 如果是要让R直到这是按周期算的，需要指定开始时间和frequency
# 比如start = c(1999,1) 第一个数字表示是从1999年开始的，第二个数字代表的含义取决于后面的频率，代表这一年的第几个观测周期
# 如果frequency = 1 代表是一年一年，所以每个数据就是一年的数据
# 如果frequency = 4 代表是季度，= 12代表是月份，=5，=7会被理解为按周计算，5是不算周末
# 如果=365就是直接按日计算，所以理解的方式都能够自动跳转到下一年如果超过了那一年的天数
t <- cbind(t1, t2, t3)
# 把ts类的向量拼接
par(mfrow = c(1, 1))
plot(t)
# 这样就把三张图合在一个图片区域里了，虽然不是在同一个y-axis上
matplot(t, type = "l")
grid()
# matplot是一个矩阵或多列数据框绘图函数，会自动把每一列当作一条线统一画在相同的坐标系下
# type = "l"表示画折线而不是点
par(mfrow = c(3, 1))
u1 <- log(lag(t1) / t1)
u2 <- log(lag(t2) / t2)
u3 <- log(lag(t3) / t3)
plot(u1, main = "HSBC")
grid()
plot(u2, main = "CLP")
grid()
plot(u3, main = "CK")
grid()
# lag()只能用于时间序列Object，会返回传入值的下一个时间点的值

# 3.11 Mathematical function plot
x1 <- seq(-0.4, -0.001, by = 0.001)
x2 <- seq(0.001, 0.4, by = 0.001)
x <- c(x1, 0, x2)
y <- c(x1 * sin(pi / x1), 0, x2 * sin(pi / x2))
# 因为0不能作除数，所以y必须分成三部分，对应的x也只能分成三部分
plot(x, y, type = "l", ylim = c(-0.4), 0.4)
abline(0, 1, lty = 2)
abline(0, -1, lty = 2)
# 对于简单的数学函数，curve()已经够用了
curve(x * sin(x), -4 * pi, 4 * pi)
# 第一个参数是函数，后面是自变量取值范围，会自动计算曲线并画出

# 3.12 low level graphics functions
# 下面将讨论一些低级的函数可以使用户自定义画图
# 1.R如何看他正在画的纸 2.如何给已有图画加点线 3.一些常见的画图设置如何自定义
# 基础的绘画时，R会把展示界面划分成数个区域

# 3.12.1 The plotting region and margins
# 首先中间是plot region用来画data,在plot region里面R会根据data维护一个坐标系系统
# 在plot region外面的就是margins,从底部开始顺时针编号为Margin 1到4,通常text和label会画在margins
# 同时R会根据几条线，把objects放在plot region外面，从region每个边开始向外延申Line 0到Line 4,作为放置的位置参照

# 3.12.2 adding to plots
# 存在很多函数来添加组件到plot region of existing graphs
points(x, y, options)
lines(x, y, options)
# x,y都是向量，然后两两连线画出折线图
text(x, y, labels, options)
abline()
polygon(x, y, options)
# add a closed and possibly filled polygon，画一个多边形，xy是多边形的各个顶点坐标
segments(x0, y0, x1, y1, options)
# x0,y0,x1,y1都是向量，然后画的是(x01,y01)到(x11,y11)的线段,(x02,y02)到(x12,y12)的线段,各个线段直接断开的
# lines()不一样的地方是，这个函数首尾相连，单segment不是首尾相连
arrows(x0, y0, x1, y1, options)
# 有一个参数length,表示箭头的长度，默认是0.1，表示箭头的长度是线段长度的10%
# 一样首尾断开，但是有个箭头有指向
symbols(x, y, options)
# 用来画一些特殊的符号图形，比如原型、矩形、线段等, 每次只能画一种图形
# e.g. symbols(x, y, circles = r, add = T, inch = F)
# 中心位置在x,y，半径为r，在现有图形上添加，不按英寸计算（因此尺寸不会按照英寸单位缩放）
# e.g. symbols(x, y = NULL, circles, squares, rectangles, stars, thermometers, boxplots, inches = TRUE, add = FALSE, fg = par("col"), bg = NA, xlab = NULL, ylab = NULL, main = NULL, ...)
legend(x, y, legend, options)
# orange里面有age, circumference, Tree三个变量，代表不同种类橙子树在不同年龄的树干周长
unique(as.character((Orange$Tree)))
# as.character()把Orange$Tree转换成字符向量, Orange$Tree是一个factor类型的向量,里面都是1，2，3，4，5
# unique()返回一个向量，选取出向量中唯一的值

# 3.13 labelling
title(main, sub, xlab, ylab, options)
# 加主标题、副标题、x轴标签、y轴标签
mtext(text, side, line, options)
# 在margins上添加文本，text是要添加的文本，side是边界编号，line是行数
axis(side, at, labels, options)
# 加一个坐标轴，side是边界编号，at是指定在哪些位置画刻度线和标签，labels是刻度线对应的标签
# 相当于自己设定坐标系，因此plot的时候可以设置axes = FALSE不要自动画的坐标系
box()
# 在plot region周围加一个box
text(x, y, labels, options)
# 在plot region里面添加文本，x,y是位置，labels是要添加的文本
# bty = 'n'表示没有边框，bty = 'o'表示有边框, 只有两条轴而且还不是连起来的
plot(circumference ~ age, pch = as.numeric(as.character(Tree)), data = Orange)
# 把点按照Tree的值来画点，as.numeric(as.character(Tree))把Tree从factor转换成数字
# 如果直接使用as.numeric返回的是索引值，不是实际的数字
abline(lm(circumference ~ age, data = Orange, subset = Tree == "1"), lty = 1)
# lm()是最fit的线对于某一棵树，根据subset参数只取Tree为1的行
legend("topleft", legend = paste("Tree", 1:5), pch = 1:5, lty = 1:5, lwd = c(1, 1, 2, 1, 1))
# legend()添加图例，位置在左上角，legend是图例的文字，pch是点的形状，lty是线型，lwd是线宽
# paste()函数可以把多个字符串连接起来，形成一个新的字符串,这种写法就是构造Tree 1, Tree 2, Tree 3, Tree 4, Tree 5,默认有空格
