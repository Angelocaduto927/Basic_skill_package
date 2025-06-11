# this symbol can be use to write comment

# Lecture 1
# 1.1 basic functions
3 + 7
# 10
3 * 21
# 63
1 / 0
# Inf, reserve word
0 / 0
# NaN, reserve word, stand for not a number
1:7
# generate sequence: 1 2 3 4 5 6 7
c(3, 4, 1, 6)
# c is a function of combining numbers into a verctor: 3 4 1 6
newvec <- c(3, 4, 1, 6)
newvec
# assignment, assign the vector to a variable called newvec: 3 4 1 6

# 1.2
# R is case sensitive, newvec is not the same as Newvec
demo(graphics)
# show demos
# whenever quitting R, will be asked if you want to save the workspace image.
# If yes, all the variables or objects created will be saved
# and will be restored next time when R is invoked.
ls()
# display all the objects exist in this R session
rm(list = ls())
# remove all the objects in the R session

# 1.3 the assignment operator
x = 3
x <- 3
# both are the same, but the latter is more common, = sign has another purpose
# associating function arguments with values. E.g. f(x=3)
# one is assigning 3 to x,
# the other is calling function f and set the argument x to 3
# technically, <- is a global assignment, = is local
sin(x = 1)
# x
# error: object 'x' not found
sin(x <- 1)
# x
# 1

# 1.4 Rules for R variable names
# must start with a letter, can't start with number or (_)
# can be combination of letters, digits, period(.), and underscore(_)
# if it starts with a period, it can't be followed by a digit
# case sensitive, not a reserved word

# 1.5 saving R commands and output
# presss Save History and Save to File in the file menu

# 1.6 Data objects
# data are stored as object in R. abstract term that can be assigned to variable
# e.g. vector, matrix, data frame, list, function

# 1.6.1 Vectors
# vector is an one-dimensional array, systematic arrangement of similar objects
# a scalar is considered as a vector with single element
# vector is the simplest data type in R
x <- 5:1
# numeric vector; x ; 5 4 3 2 1
mode(x)
# display the mode of x; numeric
length(x)
# display the length of x; 5
x < 2
# return a logical vector; FALSE FALSE FALSE FALSE TRUE
y <- x < 2
# save the result to y; y ; FALSE FALSE FALSE FALSE TRUE
mode(y)
# display the mode of y; logical
z <- c("a", "b", "c")
mode(z)
# display the mode of z; character
length(z)
# display the length of z; 3
c(x, y)
# combine vectors of different types
# combining numeric with logical vectors becomes numeric
# 5 4 3 2 1 0 0 0 0 1; TRUE 1 FALSE 0
c(x, y, z)
# combining numeric, logical and character vectors
# "5", "4", "3", "2", "1", "FALSE" ... "a", "b","c"

# 1.6.2 simple patterned vectors
# ":" can produce simple sequences of integers
# seq() and rep() functions can produce patterned vectors
seq(1, 21, by = 2)
# start from 1, smaller or equal to 21, gap is 2
# rep() can generate repeated patterns
rep(3, 12)
# repeat the value 3, 12 times
rep(seq(2, 20, by = 2), 2)
# repeat the pattern 2,...,20, 2 times
rep(c(1, 4), c(3, 2))
# repeat 1, 3 times and 4, 2 times; 1 1 1 4 4
rep(c(1, 4), each = 3)
# repeat each values 3 times
rep(1:10, rep(2, 10))
# repeat each value twice

# 1.6.3 extracting elements from vectors
# [] are used to index and extract vector elements
x[3]
x[3:5]
x[c(1, 3, 5)]
# 5 3 1
x[x > 3]
# 2 1
# R language's index start from 1

# 1.7 matrix
# matrix is a collection of numbers in a rectangular form
# matrix with dimension n by m means n rows and m columns
m <- matrix(1:12, nrow = 3, ncol = 4)
# 3 by 4 matrix filled in columnwise
m
# 1 4 7 10
# 2 5 8 11
# 3 6 9 12
dim(m)
# 3 4
nrow(m)
# 3
ncol(m)
# 4
matrix(1:12, nrow = 3, byrow = T)
# filled by row
# also can be writen as byrow = TRUE
# 1 2 3 4
# 5 6 7 8
# 9 10 11 12
m[2, ]
# select the 2nd row
m[, 3]
# select the 3rd column
m[2, 3]
# select an element
m[1:2, 2:4]
# select submatrix
# equivalent to m[c(1,2), c(2,3,4)]
# ":" include two sides
m[-2, ]
# exclude the second row
m[c(1, 2), c(3, 2, 4)]
# row follows 1,2; column follows 3,2,4
matrix(1:10, nrow = 3)
# the columns will be ceiling(10/3) = 4;
# data will be used repeately when it's not enough to fill it
# 1 4 7 10
# 2 5 8 1
# 3 6 9 2
m1 <- matrix(1:8, nrow = 2) # 2 x 4
m2 <- matrix(1:6, nrow = 3) # 3 x 2
rbind(m, m1) # m is 3 x 4
# combine m and m1 row-wise, pile up
cbind(m, m2)
# combine m and m2 column-wise, side by side

# 1.8 Multidimensional Arrays
x <- array(data = 1:24, dim = c(3, 4, 2))
# 3 rows, 4 colums, 2 widths, column first then row then width

# 1.9 List
# List is the most general object in R and is more powerful than vectors, matrix
# since it can hold multiple types of objects
x <- 1:3
y <- c("a", "b")
z <- matrix(1:6, nrow = 2)
w <- list(x, y, z)
w
# print 1st, 2nd, 3rd components of w
# note that list has two subscripts. 1st subscript denotes the component of list
# and the 2nd subscript denotes the elements within that component
# selecting elements from a list requires two separate subscripts
# 1st subscript tells which component, 2nd tells which elements
w[[1]]
w[[2]][2]
w[[3]][1:2, 2]
# list can be assigned a names attribute as follow
names(w) <- c("x", "y", "z")
# can assign names to the components of list and extract through name
# $x
# 1 2 3
# $y
# "a" "b"
# $z
# ···
w$x
# 1 2 3
u <- unlist(w)
# function unlist will change list object to a long vector
as.numeric(u)
# function as.numeric will change vector to numeric
# if the element can't be change to numeric, will become NA
# NA =  missing value

# 1.10 Data frame
# it is a special kind of list or structure
# most important distinction is that in data frame, the members must
# all be vectors of equal length
# women is an inside R data frame, contain 2 columns, weight and height
summary(women)
# a summary of the data frame women
women$height[women$weight > 140]
# $ operator can address columns in data frame using their names
# the above syntax means extract all heights for which the weights exceed 140
# [] use for logically selection
with(women, weight / height)
# with() function can access columns of data frame directly without $
# the above syntax means divide the weights by heights in women data frame
head(women)
# return first 6 rows
women[[1]]
# return a vector of first column, equivalent to women$height
women[1]
# return a new data frame containing only height
women["weight"]
# return a new data frame
women[["weight"]]
# return a vector
women["wei"]
# return error because wei is not a name of components
women$wei
# return vector, R does the unique partial match, equivalent to women$weight
member <- data.frame(
    name = c("Tom", "May"),
    age = c(22, 20)
)
member
# data frame can be created using the data.frame() function
#   name age
# 1 Tom  22
# 2 May  20

# single type: vector, matrix, array (contain single data type)
# multiple type: list, data frame (can have multi type)

# 1.11 Factor
# Factors offer an alternative way to store character vector.
grp <- c("control", "treatment", "control", "treatment")
# this is a character vector (elements are string)
grp
# control treatment control treatment
grp <- factor(grp)
grp
# control treatment control treatment
# levels: control treatment
# this is a factor with 4 elements and 2 levels
# level means how many possible value can one element takes
# element means how many value are there in this factor
# factor is efficient to store character data when there are repeated elements
# because levels of a factor are internally coded as integers
as.integer(grp)
# 1 2 1 2
# control is coded as 1, treatment is coded as 2
levels(grp)
# "control" "treatment"
levels(grp)[as.integer(grp)]
# use the indice in [] to extract the element of levels(grp)
# "control" "treatment" "control" "treatment"
# labels for the levels are stored just once each rather than repeated
# the codes are indices of the vector of levels
levels(grp) <- c("1", "2")
# redefine the labels of a factor object
grp
# 1 2 1 2
# levels: 1 2
grp == "1"
# TRUE FALSE TRUE FALSE
# note: levels of a factor are stored as character strings
# even the original data vector was numeric, it will be changed to string
# so logical expression should be expressed in character form

# 1.12 mode() vs class()
# they are ywo functions to describe a data object in R
# mode() describe the data type used for storage
# e.g. numeric, logical, character, etc.
# class() describe the object class of the input variable
# e.g. numeric, integer, list, matrix, factor, etc. (no vector)
mode(1L)
class(1L)
# "numeric"
# "integer"
mode(factor(c("a", "b")))
class(factor(c("a", "b")))
# numeric    because inside factor, it use numeric to store data
# factor
# 1. can use ";" to write several syntax in one line
# 2. by default, number will be recognized as double type which is numeric
# 3. to make it an integer type, add a "L" behind to show it as long type
# 4. science notation 1e3 is also double type
# 5. mode is more general: numeric(numbers), logical, character, function(list,)

# 1.13 approximate storage of numbers
# it is common to use approximate representation: usually floating point repre
# it's a binary version on scientific notation 1.011(2)x2^-11(4 digit precision)
# in base 2, 4/5 is 0.110011001100···
# R stores only 53 bits, rounding error will occur in storage
n <- 1:10
1.25 * (n * 0.8) - n
# should all be 0, but some of the answer are not
# operations that can easily prone rounding error:
# subtraction of two nearly equal numbers
# addition of two nearly same magnitude but opposite sign numbers

# 1.14 missing values and other special values
# missing value: NA
# it often arise in real data problem, but also because improper calculation
some.evens <- NULL
# create a vector with no elements
some.evens[seq(2, 20, 2)] <- seq(2, 20, 2)
# NA 2 NA 4 ··· NA 18 NA 20
is.na(some.evens)
# when there exist missing values, this function could be used to detect them
# TRUE FALSE TRUE FALSE ··· TRUE FALSE TRUE FALSE
!is.na(some.evens)
# ! means not, so reverse all results
some.evens[!is.na((some.evens))]
# display only not NA element

# 1.15 expression and operator
# expression and operators on scalers are easy to follow
# but they can also be performed on each component of vector or matrix
x <- 4:1
2 * (x - 1)
# 6 4 2 0 will not change the original value in x
x^2
# 16 9 4 1
# priority:
# bracket "()"
# component selection "$"
# subscripts, element "[], [[]]"
# exponentiation "^"
# unary minus and plus "- +"
# sequence operator ":"
# modulus, interger division, matrix multiplication "%% %/% %*%"
# multiplication, division "* /"
# addition subtraction "+ -"
# comparison "< > <= >= == !="
# not "!"
# vectorized and or, control and or "& | && ||"
# assignment "<- -> ="
2 - -1
# 3
1 + 5^3 * 4
# 501
x <- c(TRUE, FALSE, TRUE)
y <- c(FALSE, TRUE, TRUE)
# vectorized and or: use for comparing and get the new vector
x & y
# FALSE FALSE TRUE; compare every element one by one
# control and or: use for if, while control and so on
x && y
# FALSE: only compare the first element
# operator associativity
# most operators have associativity from left to right
# exponentiation ^ and leftward assignment (<-,=) are from right to left
5 %% 3 %% 2
# (5 %% 3) %% 2
2^3^4
# 2^(3^4)

# 1.16 built in functions
# mathematical functions: sqrt, abs, sin, cos, log, exp···
# ceiling (floor): smallest (largest) integer >= (<=) to the element
# trunc: ignore decimal part
# round: round up for positive, round down for negative
# sort: sort the vector in ascending or descending order
#       by default ascend, descend by setting decreasing = TRUE
# sum, prod: sum and product of a vector/matrix element
#           inside use na.rm = TRUE to remove NA value
# cumsum, cumprod: cumulative sum and product
# min, max: return the smallest or the largest values
# range: return a vector of length 2, containing the min and max
# mean: return the sample mean of a vector
# var: return the sample variance of a vector
# sd: return the sample standard deviation of a vector
# which: return the indices of TRUE elements of a logical object
# options(digit = n): control the number n of display
# these operation will not change the original object unless do assignment
(z <- 1:5)
# with a bracket, can achieve the short cut of create and display
cumsum(z)
# 1 3 6 10 15
sum(z)
# 15
cumprod(z)
# 1 2 6 24 120
prod(z)
# 120
y <- c(-sqrt(1:5), sqrt(1:5))
mean(sqrt(y))
# NaN, because there are negative number in y, can't do sqrt
y[which(y >= 0)]
# select elements that are >= 0
mean(sqrt(y[which(y >= 0)]))
# correct
