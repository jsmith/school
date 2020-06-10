import random

SIZES = [(i + 1) * 10 for i in range(10)]

threads = list(reversed([i for i in range(100)]))
running = []

while len(threads) > 0 or len(running) > 0:
  if random.randint(1, 3) < 3:
    if len(threads) == 0:
      continue

    thread = threads.pop()
    size = SIZES[random.randint(0, 9)]
    print(f"N{thread} {size}")
    running.append(thread)
  else:
    if len(running) == 0:
      continue

    i = random.randint(0, len(running) - 1)
    thread = running[i]
    print(f"T{thread}")
    del running[i]


  if random.randint(0, 100) == 0:
    print(len(threads), len(running))
    break
