n = int(input())

ms = []
xs = []

result_a = -1
result_b = 0

for i in range(n):
    m, x = map(int, input().split())

    for j in range(i):
        for k in range(j):
            if ms[j] != m and ms[k] != m and ms[k] != ms[j]:
                result_b = max(result_b, min(x - xs[j], xs[j] - xs[k]))
                if result_a == -1:
                    result_a = max(x - xs[j], xs[j] - xs[k])
                else:
                    result_a = min(result_a, max(x - xs[j], xs[j] - xs[k]))

    ms.append(m)
    xs.append(x)

if result_a == -1:
    result_a = 0
print(result_a, result_b)
