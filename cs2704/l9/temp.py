# -*- coding: utf-8 -*-
# print("1. Write the output of the following program. All questions are supposed be answered in sequence.")
# print("(a)", end=" ")
# import seaborn as sns
# iris = sns.load_dataset("iris")
# print(type(iris))
# print("(b)", end=" ")
# sns.catplot(x="species",y="sepal_length",kind="bar",data=iris)
# print("(c)", end=" ")
# sns.catplot(x="species",y="sepal_length",data=iris)
# print("(d)", end=" ")
# sns.catplot(x="species",y="sepal_length",jitter=False,data=iris)
# print("(e)", end=" ")
# sns.catplot(x="species",y="sepal_length",kind="swarm",data=iris)
# print("(f)", end=" ")
# sns.catplot(x="species",y="sepal_length",kind="box",data=iris)
# print("(g)", end=" ")
# sns.catplot(x="species",y="sepal_length",kind="boxen",data=iris)
# print("(h)", end=" ")
# sns.catplot(x="species",y="sepal_length",kind="violin",data=iris)

print("2. Answer the questions about the following system of linear equations")
print("(a) What are x and y that satisfy both of the above equations?")
print("20x + 10y = 350")
print("10x = 350 - 10y")
print("y = 35 - 2x")
print()

print("17x + 22y = 500")
print("17x + 22(35 - 2x) = 500")
print("17x + 770 - 44x = 500")
print("-27x = -270")
print("x = 10")

print()
print("y = 35 - 2x")
print("y = 35 - 2(10)")
print("y = 35 - 2(10)")
print("y = -5")

print("\n∴ x=10 and y=-5")

print("\n(b)", end=" ")
import numpy as np
A = np.array([[20, 10], [17, 22]])
B = np.array([350, 500])
X = np.linalg.solve(A,B)
print(X)

print("\n3. Answer the questions about the following matrix")
print("(a)")
print("A = ⌈20 10⌉")
print("    ⌊17 22⌋")

print()
print("A^-1 = 1/(20 * 22 - 10 * 17) ⌈22 -10⌉")
print("                             ⌊-17 20⌋")
print("A^-1 = ⌈0.0814  -0.0370⌉")
print("       ⌊-0.0629  0.0740⌋")

print("\n(b)")
print("A^-1 * 270 = ⌈22  -10⌉")
print("             ⌊-17  20⌋")


print("(c)")
import numpy as np
A = np.matrix([[20,10],[17,22]])
B = np.matrix([350,500]).transpose()
A_inv = np.linalg.inv(A)
print(A_inv * B)
print(270 * A_inv)
