from random import randint

n = 0
k = randint(1, 3)
if k == 1:
    n = randint(1, 10)
elif k == 2:
    n = randint(11, 30)
else:
    n = randint(31, 100)

print(n)

h_bound = n
x_bound = n
k = randint(1, 3)
if k == 1:
    h_bound = randint(1, 4)
elif k == 2:
    h_bound = randint(5, 10)
else:
    h_bound = randint(1, n)

k = randint(1, 3)
if k == 1:
    x_bound = randint(1, max(1, n // 10))
elif k == 2:
    x_bound = randint(1, max(1, n // 2))
else:
    x_bound = randint(1, n * 5)

xs = [randint(0, x_bound) for i in range(n)]
xs.sort()

for i in range(n):
    print(randint(0, h_bound), xs[i])
