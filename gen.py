from random import randint

n = randint(10, 100)
print(n)

r = 0

for i in range(n):
    r += randint(0, randint(10,n))
    print(randint(1, n) , r)
