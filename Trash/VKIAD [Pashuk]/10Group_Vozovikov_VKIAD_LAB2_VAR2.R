MyFunction <- function(x){
  result <- log(sin(x ^ 2))
  
  return(result)
}


MyIntegrate <- function(fun, left, right, e){
  
  n <- 1
  s1 <- 0
  s2 <- fun(right) * (right - left)
  
  while(abs(s2 - s1) >= e) {
    
    n <- n * 2
    h <- (right - left) / n;
    s1 <- s2
    s2 <- 0
    
    for (i in 0:(n-1)){
      s2 <- s2 + fun(left + h * i)
    }
    s2 <- s2 * h
  }
  
  return(s2)
  
}


MyResult <- MyIntegrate(MyFunction, 0.1, 1, 0.000001)    
print(MyResult)

LibResult <- integrate(MyFunction, 0.1, 1)
print(LibResult)

