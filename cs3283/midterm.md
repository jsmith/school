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

This algorithm can also check to see if there are two of the same value in an array. A faster way to do this would be to use the sort the array then following algorithm or to use a hash table or  pigeonhole principle.
```
{
  for(i=1 to n-1) {
    if(A[i] == A[i+1]) {
      return true
    }
  }
  return false
}
```

## SecondSmallest(A)
```
{
  fs = A[1]
  ss = A[2]
  if(fs < ss) {
    swap(A, 1, 2)
  }
  for(i=3 to n) {
    if(A[i] < fs) {
      ss = fs
      fs = A[i]
    }
    else if(A[i] > fs && A[i] < ss) {
      ss = A[i]
    }
  }
  return ss
}
```

## InsertionSort(A)
```
for(j=2 to n) {
  y = A[j]
  i = j-1
  while(y < A[i] && i > 0) {
    A[i+1] = A[i]
    i = i - 1
  }
  A[i+1] = y
}
```

## SelectionSort(A)
```
for(i=1 to n) {
  k = i
  for(j=i+1 to n) {
    if(A[j] < A[k]) {
      k = j
    }
  }
  min = A[k]
  A[k] = A[i]
  A[i] = min
}
```

# Lecture 3
How do we analyze algorithms?

Data structures and algorithms affect performance

## Algorithm Evaluation
There are several measures such as time and instruction count.

There are several ways to take these measure such as empirical studies where you measure running time or theoretical analysis where the amount of instructions executed are counted.

Experiment based evaluation is limited as some algorithms are hard to test and you are not able to test all of the domain. This is the motivation of theoretical analysis.

## Theoretical Analysis
Time efficiency of theoretical analysis is given by the running time `T(n) ~ Cop * C(n)` where `n` is the input size, `Cop` is the execution time for the basic operation and `C(n)` is the number of times the basic operation was executed.

The advantages are:
1. High level description instead of implementation
2. The running time is a function of `n`
3. Takes into account all inputs
4. Allows us to evaluate the speed independently of hardware

`W(n)` is the worst case, `B(n)` is the best case and `A(n)` is the average over the inputs of size `n`.

If `a` = time taken by the fastest primitive operation and `b` = time taken by the slowest primitive operation then `an <= T(n) <= bn`. Changing the hardware affects T(n) by a constant factor, but does not alter the growth rate of `T(n)`. If Ta(n0) < Tb(n0) for all n >= n0 then algorithm A is better than algorithm B

## CheckPrime(A)
```
{
  for(i=2 to n-1) {
    if(A%i == 1) {
      return false
    }
  }
  return true
}
```
or
```
{
  for each prime i <= (n)^0.5 {
    if(A%i == 0) {
      return false
    }
  }
  return true
}
```
Ta = a*n
Tb = a*n^0.5

# Lecture 4
## Big-Oh Notation
Definition: Given non-negative function f(n) and g(n), we say that f(n) = O(g(n)), if there exists *an integer n0* and *constant k > 0* such that f(n) <= k*g(n) for all integers n >= n0.

f(n) = O(g(n)): f(n) is of order at most g(n) or f(n) if big oh of g(n). f(n) grows no faster than g(n) for large n.

## Example 5n + 10 is O(n)
We need to find a pair (k, n0) such that for all n >= n0, we have 5n + 10 <= kn for n >= n0

1. 10 <= (k-5)n
2. n >= 10/(k-5)
3. Pick k=6 and n0 = 10
4. 5n + 10 < 6n for n >= 10

# Lecture 5
Properties of Asymptotic:
Suppose we know that f1(n) = O(g1(n)) and f2(n) = O(g2(n)) then
* f1(n) + f2(n) = O(max(g1(n), g2(n)))
* f1(n) x f2(n) = O(g1(n) x g2(n))
