import matplotlib.pyplot as plt
 
timeLog = open("TimeLog.txt")
data = timeLog.read().split()


x = [4,8,16,32,64]
y = [0.0,0.0,0.0,0.0,0.0]
c = [0,0,0,0,0]

i = 1
while(i < len(data)):
    index = x.index(int(data[i-1]))
    n = float(data[i])
    y[index] = y[index] + n
    c[index] = c[index] + 1
    i = i + 2

for i in range(0,5):
    y[i] = y[i]/c[i]

plt.plot(x,y)
plt.show()
print(y)