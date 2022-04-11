#Task #1
datat <- read.csv(file.choose())
print(data)

x = datat$x7
y = datat$y7
  
b1 = (mean(x * y) - mean(x) * mean(y)) / (mean(x ^ 2) - mean(x) ^ 2)
print(b1)

b0 = mean(y) - b1 * mean(x)
print(two)

qwe = lm(y ~ x, data = datat)
print(qwe)


plot(x, y, col = "orange")
abline(qwe, lwd = 3, col = "red")  


