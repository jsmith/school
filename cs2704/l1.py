print("Q1")
def f1(n):
    if n == 0:
        return 1
    else:
        return n * f1(n - 1)

print(f1(5))

print("Q2")
def f2a(n):
    if n == 0:
        return 0
    else:
        return n * f2a(n - 1)

print(f2a(5))

def f2b(n):
    if n == 0:
        return 0
    else:
        return n + f2b(n - 1)

print(f2b(5))

print("Q3")
print([2 * x + 1 for x in range(5)])
print([3 * x + 1 for x in range(5)])

print("Q4")
def f4(n):
    if n <= 2:
        return 1
    else:
        return f4(n - 1) + f4(n - 2)

print(f4(10))

print("Q5")
x = [1, 2, 3, 4]
print(sum(x))

m = [x for x in range(10) if x % 3 == 1]
n = [x for x in range(10) if x % 3 == 2]
y = [t * u for t in m for u in n]
print(sum(y))

print("Q6")

# import matplotlib.pyplot as plt
# import math
# x =  [(t/1000 - 0.5)*20 for t in range(1000)]
# def graph(f, x):
#     y = [f(t) for t in x]
#     plt.plot(x, y)
#     plt.show()

# def f7(x):
#     return 1/math.exp(x**2)*math.cos(5*x)

# graph(f7, x)
