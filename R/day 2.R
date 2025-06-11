# Lecture 2 Simulation and Exploratory Data Analysis
# simulation is a major application of computer in statistic
# it can be used in testing and assessing out statistical methodologies
# it can test our procedures under different distributional assumption
# in R, we can generate pseudorandom numbers from statisical distributions

# 2.1 Pseudorandom numbers
# algorithm is used to generate a sequence of pseudorandom numbers
# whose properties approximate the properties of sequence of random numbers
# they exhibit independebce and follow prescribed probability distributions
# it's important for their speed in generation and reproducibility
# a way to generate pseudorandom numbers: linear congruential
# a multiplier a; modulus m; seed x0
# x(n) = (x(n-1) * a) (mod m)
# function sample() generates random samples or permutations of data
sample(10)
# random permutation of integers from 1 to 10, 10 numbers
sample(10, replace = T)
# 10 random numbers of integer from 1 to 10, with replacement
sample(c(-1, 0, 1), size = 20, prob = c(0.25, 0.5, 0.25), replace = T)
# generate 20 numbers of -1,0,1, and they follow the prob
d <- sample(c(-1, 0, 1), size = 20, prob = c(0.25, 0.5, 0.25), replace = T)
# d is now a vector, sample also return a vector
sum(d == 0)
# d == 0 will return TRUE FALSE vector, and TRUE is 1, FALSE is 0, so sum up
# can get the number of "0" in vector d
# the proportion is close to the prob, difference is due to sampling error
# we will get different sequence when use sample() at different time
# because it is using a random initial seed
# to get the same sequence, set the initial seed by set.seed()
set.seed(1)
sample(10) # (1)
sample(10) # (2)
set.seed(1)
sample(10) # (3)
sample(10) # (4)
# 1和3一样，2和4一样，1和2不一样，3和4不一样
# a throw coin test
set.seed(13579)
r <- sample(c(-1, 1), prob = c(0.5, 0.5), replace = T, size = 100)
(r <- c(10, r))
# append the initial value 10
(w <- cumsum(r))
w <- as.ts(w)
# transform w into a time series object
plot(w, main = "random walk")
# plot w with a main title
abline(h = 10)
# add a horizontal line y = 10, other parameters: col = "red", lty,lwd
# lty: line type, 1 -> solid line, 2 -> dash line, 3 -> dot line
#                 4 -> dot-dash, 5 -> long dash short dash, 6 -> two dash dot
# lwd: line width: the larger the wider
# if want to draw a vertical line: abline(v = 10)
(sum(w < 0) > 0)
# find whether there is a number smaller than 0

# 2.2 Monte Carlo Simulation
# a general computer-based method to approximate properties of random variables
# to approximate the mean, we generate m independent and identically distributed copies of X
# namely X1,X2 ··· Xm and use the sample mean as an estimate of E(X)
# further, when m is large, the distribution of the sample mean can be approximated by a normal distribution with mean miu and variance (sigma^2)/m, where the (sigma)^2 is the variance Var(X)
# this allows us to construct approximate confidence intervals for miu.

# 2.3 random number between a and b
runif(n, min = a, max = b)
# produce n pseudorandom uniform number in this interval, by default a=0, b=1

# 2.4 built-in probability distribution functions
# 4 fundamental items can be computed for statistical distribution
# pdf or pmf (e.g. dnorm)
# cdf (e.g. pnorm)
# quantiles (e.g. qnorm)
# pseudorandom numbers (e.g. rnorm)
# concepts in statistics
# p(x) for discrete random variable X is the pmf
# f(x) for continuous random variable X is the pdf
# cdf F(x) gives the prob of X less than or equal to x
# quantile function is the inverse of cdf, q-th quantile of X is the smallest value of x donated as xq such that Pr{X <= xq} >= q
x <- seq(-4, 4, 0.1)
plot(x, dnorm(x), type = "l", main = "N(0,1) density")
# dnorm(x, mean = a, sd = b) return pdf of position x follow the normal distri
# type = "l" causes the plot using lines instead of points
pnorm(1.96)
# count the pdf of X <= 1.96 in mean=0, sd = 1's normal distribution
q <- c(0.05, 0.5, 0.95)
qnorm(q)
# return the value of this quantiles in normal distri, e.g. for 0.5 is 0
rnorm(100)
# generate 100 random numbers from N(0,1)
# now try binomial distribution
x <- 0:20
p <- dbinom(x, size = 20, prob = 1 / 4)
# p is a prob vector, p=Pr(X=x)
round(p, digits = 4)
# display with four digits approximation
plot(x, p, type = "h")
# h causes it to plot the pmf using vertical lines
# to get Pr{X > 8}, we can use
1 - pbinom(8, size = 20, prob = 1 / 4)
1 - sum(p[1:9])
# to find the 0th, 10th ··· 100th quantiles of X
(q <- seq(0, 1, 0.1))
qbinom(q, size = 20, prob = 1 / 4)
# we can confirm by doing
round(cumsum(p), digits = 4)

# 2.5 table of built in distribution (add d,p,q,r before the function name)
# Distribution      R name      Additional arguments
# Beta              beta        shape1, shape2, ncp
# Binomial          binom       size, prob
# Cauchy            cauchy      location, scale
# Chi-square        chisq       df, ncp
# Exponential       exp         rate
# F                 f           df1, df2, ncp
# Gamma             gamma       shape, scale
# Geometric         geom        prob
# Hypergeometric    hyper       m, n, k
# Log-normal        lnorm       meanlog, sdlog
# Logistic          logis       location, scale
# Negative binomial nbinom      size, prob
# Normal            norm        mean, sd
# Poisson           pois        lambda
# Student's t       t           df, ncp
# Uniform           unif        min, max
# Weibull           weibull     shape, scale
# Wilcoxon          wilcox      m, n

# 2.6 Exploratory data analysis
# first step is to read in data, row is observation, col is variables
# most common format is ASCII with file extention .dat or .txt
getwd()
# see the current working directory
setwd("C:/Folder")
# change the working directory, we can press File -> Change dir from menu
# or use the above command
edit(file = "ch2-apply.r")
# commands can be executed from an ASCII file using the source command
# first enter commands using a text editor and save it as text(ASCII) file or simply using the above command
# it invokes the built-in text editor and open an ASCII file "ch2-apply.r"
# the file is .txt and if there is no such file, it will create a new one
x <- runif(500, 0, 20)
y <- matrix(x, ncol = 10)
m <- apply(y, 2, mean)
# apply() is a function that applies a function to the margins of an array or matrix
# margins are the dimensions of the array or matrix, 1 for rows, 2 for columns
# this command means counting the mean of each column of matrix y
s <- apply(y, 2, sd)
source("ch2-apply.r", echo = T)
# execute the commands in the file "ch2-apply.r" and echo the commands
# echo = T will echo these commands to the screen, equal to write them on screen

# 2.7 inputting ASCII data files
d <- read.table("popden.dat", header = T, stringsAsFactors = T)
# read in data file with header
# character variables are stored as factor
names(d)
# display the labels of d
# "district" "year86" "year"90 "Region"
# note that the first row in file is the header containing the label of variable
# therefor need to set header = T
head(d)
# display the first 6 rows of d with the variable names
tail(d)
# display the last 6 rows of d with the variable names
# in analysis, usually classify variables into categorical and continuous
# District and Region are categorical variables
# Year86 and Year90 are continuous variables
class(d$year86)
# "integer"
class(d$Region)
# "factor"
d$Region
# NT NT NT ··· KL
# Levels: HK KL NT
# d is a data.frame object, looks like a matrix but each column contain different type of data
# we can change a matrix into a data frame by data.frame()
class(d)
# "data.frame"
(t <- tapply(d$year90, d$Region, mean))
# tapply() applies a function to subsets of a vector
# find the mean of year90 for each region
# tapply() takes 3 arguments: the vector, the factor, and the function
# return array/list type
(s <- split(d$year90, d$Region))
# split() splits the data into a list with components according to the factor
# HK
# ····
# KL
# ····
# NT
# ····
# the name of the list is the levels of the factor
mean(s$HK)
# equal to t[1]
mean(s$KL)
# equal to t[2]
mean(s$NT)
# equal to t[3]
table(d$Region)
# table() counts the frequency(how many cases) in each level of the factor
by(d[, c(2, 3)], d$Region, colMeans)
# d[, c(2, 3)] means the second and third columns of d
# colMeans() calculates the mean of each column
# d$Region is the factor, so by() applies colMeans() to columns of levels
# return by type (kind of list)
dense <- as.numeric((d$year86 > 10000) & (d$year90 > 10000))
# we can define our own categorical variable as well
# this create a binary variable dense
(t <- table(dense, d$Region))
# return a contingency table of the counts of each level of dense and Region
dense
# display the vector
# also we can use with() to create extra variables for a data frame
d$dense <- with(d, as.numeric((year86 > 10000) & (year90 > 10000)))
# add the variable dense to d
# with() takes two arguments: the data frame and the expression
# it's like create a new column in Excel, and put the value of the expression of that row into the blank cell, the name of that column is behind the $

# 2.8 aggregate() function
# it's a more flexible way to split and apply transformation to data
aggregate(year86 ~ Region, d, mean)
# use data frame d, group by Region, take out only year86, and calculate the mean
# it return a new data frame with two columns
aggregate((cbind(year86, year90)) ~ Region + dense, d, mean)
# cbind() combines the two columns into a matrix
# and then aggregate() applies mean to each column
# return a new data frame with 4 columns, it's spliting by Region and dense
# Region dense year86 year90

# 2.9 simple scatter plot
# we can use scatter plot to study the relationship between two or more continuous variables
pd86 <- d$year86
pd90 <- d$year90
plot(pd86, pd90, main = "Population Density 1986 vs 1990")
# sometimes the range is large , we can use log transformation
lnpd86 <- log(pd86)
lnpd90 <- log(pd90)
plot(lnpd86, lnpd90, main = "Population Density 1986 vs 1990 (log scale)")
abline(lsfit(lnpd86, lnpd90))
# lsfit() fits a linear model to the data, and return the coefficients
# so it adds a least square line to the plot
# least square line is the line that closest to the data point (minimizing the error sum of squares)
# the built-in function lsfit() wil; return the intercept and slope of the line
# three use of abline()
# abline(a,b) -> linear line y=bx+a
# abline(v = x) -> vertical line at x
# abline(h = y) -> horizontal line at y

# 2.10 saving an R plot
# 1.copy the plot window and paste into a proper file type (e.g. word document)
# 2. use pdf() function to create a pdf file
# 3. use jped() function to create a jpeg file
pdf("Figure.pdf")
plot(lnpd86, lnpd90, main = "Population Density 1986 vs 1990 (log scale)")
abline(lsfit(lnpd86, lnpd90))
dev.off()
# the plot will not show on screen, but in the pdf file
# dev.off() closes the current device, so the plot is saved and can check

# 2.11 saving data file
# suppose we want to save original data with the transformed data
x <- cbind(d[, 1:4], lnpd86, lnpd90)
names(x)
# "district" "year86" "year90" "Region" "lnpd86" "lnpd90"
# the name of the vector will be the column names
write.table(x, file = "popden1.dat", row.names = F)
# write x to an ASCII file, row.names=F means not to write the row names(index)
# without row.names=F, R will automatically add in the row numbers
# next time read the file, we will have two more columns
# another common file format is csv (comma separated values)
# it can be imported and exported from Excel directly
write.csv(x, file = "popden1.csv", row.names = F)
# save the object x to a csv file
d1 <- read.csv("popden1.csv", header = T, stringsAsFactors = T)

# 2.12 R data editor
# R has a built-in data editor to help us enter the data like excel
x <- edit(d1)
# suppose we want to edit the data in d1
# then the editor window appears and we can edit the data
# close the window when finish and will have data stored in x
