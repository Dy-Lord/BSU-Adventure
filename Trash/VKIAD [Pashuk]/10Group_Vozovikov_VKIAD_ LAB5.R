library(cluster)
library(fpc)
library(party)

#Task 1

x <- c( rnorm(20, 3), rnorm(30, 7), rnorm(40, 3), rnorm(50, 4))
y <- c(rnorm(20, 1), rnorm(30, 5), rnorm(40,9), rnorm(50, 1))
plot(x, y)


temp <- c(x, y)
m <- matrix(temp, ncol = 2)
colnames(m) <- c("x", "y")
plot(m)

#Task 2

cl1 <- kmeans(m, 3)
plot(m, col = cl1$cluster, pch = 9 + cl1$cluster)

cl2 <- clara(m, 4)
plot(m, col = cl2$clustering, pch = 9 + cl2$clustering)

cl3 <- pam(m, 5)
plot(m, col = cl3$clustering, pch = 9 +cl3$clustering)

#Task 3

cl4 <- kmeansruns(m)
plot(m, col = cl4$cluster, pch = 9 + cl4$cluster)


cl5 <- pamk(m)
plot(m, col = cl5$pamobject$clustering, pch = 9 + cl5$pamobject$clustering)


#Task 4

k <- data.frame(x = x, y = y, cluster = cl1$cluster)
plot(ctree(cluster~., k))

