#Task #1
data <- read.csv(file.choose())
print(data)

#Task #2
one <- data$HHt
one <- one[one != 0]
print(one)

#a)
max <- max(one)
print(max)

#b)
min <- min(one)
print(min)

#c)
sr <- mean(one)
print(sr)

#d)
med <- median(one)
print(med)

#i)
moda <- function(v) {
  uniqv <- unique(v)
  uniqv[which.max(tabulate(match(v, uniqv)))]
}

result <- moda(one)
print(result)

#y)
dis <- var(one)
print(dis)

#r)
sq <- sqrt(dis)
print(sq)

#b)
q <- quantile(one, c(0.25, 0.75))
print(q)


#Task #3
boxplot(one)


#Task #4
two <- data$LHt
two <- two[two != 0]
print(two)

boxplot(one, two)


#Task #5
plot.ecdf(one)

#Task #6
hist(one, col="orange", border="black", prob = TRUE, main = "HHt")
lines(density(one), lwd = 2, col = "red")


#Task #7
qqnorm((one - mean(one)) / sd(one), ylim = c(-3, 3), col = "blue")
lines(c(-3, 3), c(-3, 3),lwd = 3, col = "red")


