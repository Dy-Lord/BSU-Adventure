#Task №1
#a)
v1 <- seq(6,6.5,length.out = 9)
print(v1)

#b)
i <- 6

b1 <- (abs(13 - i) + 2)

q <- (100 / b1)^(1 / (i - 1))
v2 <- b1*q^(1 : 6 - 1)

print(v2)

#c)
if((v1[1] + v2[1]) %% 2 == 0){
  if(i %% 2 == 0)
  m <- matrix(c(v1, v2), nrow = 2, byrow = TRUE)
  else
    m <- matrix(c(v1, v2), nrow = 2,  byrow = FALSE)
}else{
  if(i %% 2 == 0)
    m <- matrix(c(v2, v1), nrow = 2, byrow = TRUE)
  else
    m <- matrix(c(v2, v1), nrow = 2, byrow = FALSE)
}

print(m)


#Task №2
mood <- c('angry','happy','boring')
mood <- factor(mood)

tablel <- data.frame(numbers = -2:3,logical = c(TRUE, FALSE),moodfactors = mood)
print(tablel)

str(tablel)

strtb <- (tablel[tablel$logical == TRUE,])
print(strtb)


#Task №3
df <- read.csv(file.choose())
print(df)

df1 <- subset(df, Species == "setosa")
df2 <- subset(df, Species == "versicolor")
df3 <- subset(df, Species == "virginica")

#a)
acf1 <- (nrow(df1[df1 $ Sepal.Width <= 3,]))
print(acf1)

acf2 <- (nrow(df2[df2 $ Sepal.Width <= 3,]))
print(acf2)

acf3 <- (nrow(df3[df3 $ Sepal.Width <= 3,]))
print(acf3)


#b)
tcf1 <- (nrow(df1[df1$Petal.Length > 4.5,]))
print(tcf1)

tcf2 <- (nrow(df2[df2$Petal.Length > 4.5,]))
print(tcf2)

tcf3 <- (nrow(df3[df3$Petal.Length > 4.5,]))
print(tcf3)


#c)
thcf1 <- (nrow(df1[df1$Sepal.Width <=3 & df1$Petal.Length > 4.5,]))
print(thcf1)

thcf2 <- (nrow(df2[df2$Sepal.Width <=3 & df2$Petal.Length > 4.5,]))
print(thcf2)

thcf3 <- (nrow(df3[df3$Sepal.Width <=3 & df3$Petal.Length > 4.5,]))
print(thcf3)


#d)
avr1 <- (mean(df1$Petal.Width))
print(avr1)

avr2 <- (mean(df2$Petal.Width))
print(avr2)

avr3 <- (mean(df3$Petal.Width))
print(avr3)

  
