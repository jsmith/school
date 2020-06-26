# print("1. The following example trains a neural network to learn XOR problem")

# import numpy as np
# import matplotlib.pyplot as plt

# training_input=np.array(([0,0,1],[0,1,1],[1,0,1],[1,1,1]), dtype=float)
# training_output=np.array(([0],[1],[1],[0]), dtype=float)

# def sigmoid(t):
#   return 1/(1+np.exp(-t))

# def sigmoid_derivative(p):
#   return p * (1 - p)

# class NeuralNetwork3:
#   def __init__(self, training_input,training_output, num_hidden):
#     self.input = training_input
#     self.w1= np.random.rand(self.input.shape[1],num_hidden)
#     self.w2 = np.random.rand(num_hidden,training_output.shape[1])
#     self.output = np. zeros(training_output.shape)
#     self.y = training_output

#   def feedforward(self):
#     self.layer1 = sigmoid(np.dot(self.input, self.w1))
#     self.layer2 = sigmoid(np.dot(self.layer1, self.w2))
#     self.output = self.layer2
  
#   def backprop(self):
#     y1 = self.output
#     dy = (self.y - y1)
#     dw2 = np.dot(self.layer1.T, 2*dy*sigmoid_derivative(y1))
#     dh = np.dot(2*dy*sigmoid_derivative(self.output), self.w2.T)
#     dw1 = np.dot(self.input.T, dh*sigmoid_derivative(self.layer1))
#     self.w1 += dw1
#     self.w2 += dw2

# def test(num_hidden, max_epoch):
#   NN = NeuralNetwork3(training_input,training_output,num_hidden)
#   hist = []
#   for i in range(max_epoch):
#     NN.feedforward()
#     hist.append(NN.output)
#     NN.backprop()

#   return hist

# print("(a) Excute the following code and submit the output screen")
# hist = test(3,500)
# x = [i for i in range(len(hist))]
# y0 = [y[0] for y in hist]
# y1 = [y[1] for y in hist]
# y2 = [y[2] for y in hist]
# y3 = [y[3] for y in hist]
# plt.plot(x,y0,x,y1,x,y2,x,y3)

# print("(b) Excute the following code and submit the output screen")
# hist = test(3,1500)
# x = [i for i in range(len(hist))]
# y0 = [y[0] for y in hist]
# y1 = [y[1] for y in hist]
# y2 = [y[2] for y in hist]
# y3 = [y[3] for y in hist]
# plt.plot(x,y0,x,y1,x,y2,x,y3)

# print("(c) Excute the following code and submit the output screen")
# hist = test(30,1500)
# x = [i for i in range(len(hist))]
# y0 = [y[0] for y in hist]
# y1 = [y[1] for y in hist]
# y2 = [y[2] for y in hist]
# y3 = [y[3] for y in hist]
# plt.plot(x,y0,x,y1,x,y2,x,y3)

print("2. Write the output of the following python programs")
# print("(a)", end=" ")
# if "x" in globals():
#   del x,y,z,t

# print(((x+y)**2 * (x + 1)))

print("(b)", end=" ")
if "x" in globals():
  del x,y,z,t

from sympy import *

(x,y,z,t) = symbols("x y z t")
((x+y)**2 * (x + 1)).expand()

# print("(c)", end=" ")
# if "x" in globals():
#   del x,y,z,t

# from sympy import *
# (x,y,z,t) = symbols("x y z t")
# solve([Eq(x + 5*y, 2), Eq(-3*x + 6*y, 15)], [x, y])

# print("(d)", end=" ")
# if "x" in globals():
#   del x,y,z,t
# from sympy import *

# (x,y,z,t) = symbols("x y z t")
# print(limit((sin(x)-x)/x**3, x, 0))

# print("(e)", end=" ")
# if "x" in globals():
#   del x,y,z,t

# from sympy import *
# (x,y,z,t) = symbols("x y z t")
# print(diff(cos(x**2)**2 / (1+x), x))

# print("(f)", end=" ")
# if "x" in globals():
#   del x,y,z,t

# from sympy import *
# (x,y,z,t) = symbols("x y z t")
# print(integrate(x**2 * cos(x), x))

# print("(g)", end=" ")
# if "x" in globals():
#   del x,y,z,t

# from sympy import *
# (x,y,z,t) = symbols("x y z t")
# f = Function("f")
# print(dsolve(Eq(Derivative(f(x),x) + 9*f(x), 1), f(x)))

# print("3. Given the following function f(x), answer the follwing questions. You may use sympy package")
# if "x" in globals():
#   del x,y,z,t

# from sympy import *
# (x,y,z,t) = symbols("x y z t")
# print(integrate(x**2 * cos(x), x))

# print(diff(x**2 * cos(x), x))