import matplotlib.pyplot as plt
 
timeLog = open("TimeLogDC.txt")
data = timeLog.read().split()


x = [1024,2048,4096]
y = [0.0,0.0,0.0]
c = [0,0,0]

i = 1
while(i < len(data)):
    index = x.index(int(data[i-1]))
    n = float(data[i])
    y[index] = y[index] + n
    c[index] = c[index] + 1
    i = i + 2

for i in range(0,2):
    y[i] = y[i]/c[i]

plt.plot(x,y)
plt.show()
print(y)