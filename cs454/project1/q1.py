#!/usr/bin/python
m = 100 #have user input
a = [0] * (m + 1)

#base cases
a[1] = 1 # one black
a[2] = 2 # two black, one red
a[3] = 4 # black/red, red/black, green, 3black
a[4] = 8 # red/red, red/black/black, black/black/red, black/red/black, green/black, black/green, blue, 4 black
for i in range(5,m + 1):
    a[i] = a[i - 1] + a[i - 2] + a[i - 3] + a[i - 4]
    total = a[-1]
print total
