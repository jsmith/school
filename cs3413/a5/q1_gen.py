import random

MAX = 99999

time = 0
for i in range(500):
  time += random.randint(1, 15)
  sector = random.randint(0, MAX)
  print(f"{sector} {time}")
