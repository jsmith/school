# Lecture 1
We use algorithms and data structures to solve problems. Making the right choices is essential to solve problems efficiently (time & space).

## Swap(A, i, j) i != j
```
{
  t = A[i]
  A[i] = A[j]
  A[j] = t
}
```
or
```
{
  A[i] += A[j]
  A[j] = A[i] - A[j]
  A[i] -= A[j]
}
```

## A = 2^k + 1 for k > 0
```
{
  x = A - 1
  while ((x%2 == 0) && (x > 1)) {
    x = x/2
  }
  return x==1
}
```
or
```
{
  return ( ((A-2) & (A-1)) == 0)  
}
```

# Lecture 2

## MaxDistance(A) for n > 1
```
{
  max = A[1]
  min = A[2]
  for(i=2 to n) {
    if(A[i] < min) {
      min = A[i]
    }
    if(A[i] > max) {
      max = A[i]
    }
  }
  return max-min
}
```
or
```
{
  max = 0
  for(i=1 to n)
  {
    for(j=i+1 to n) {
      dis = abs(A[i] - A[j])
      if(dis > max) {
        max = dis
      }
    }
  }
  return max
}
```

## MinDistance(A) for n > 1
```
{
  min = 9999999999999999999
  for(i=1 to n)
  {
    for(j=i+1 to n) {
      dis = abs(A[i] - A[j])
      if(dis < min) {
        min = dis
      }
    }
  }
  return min
}
```
