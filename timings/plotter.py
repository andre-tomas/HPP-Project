import matplotlib.pyplot as plt
import numpy as np
import math
import statistics as stat


def orderofacc(x,y):
  logx = [m.log(x) for x in x]
  logy = [m.log(y) for y in y]
  P = np.polyfit(logx,logy,1)
  return abs(P[0])

def spdup(pre,after):

  return [pre/after[i] for i in range(len(after))]

T = [i for i in range(1,33)]
N = [2**n for n in range(4,27)]
NlogN = [n*math.log(n) for n in N]

name = "timings_S_B0_O0.txt"
f = open(name,"r")
S_B0_O0 = [float(line) for line in f]
f.close()

name = "timings_S_B0_O1.txt"
f = open(name,"r")
S_B0_O1 = [float(line) for line in f]
f.close()

name = "timings_S_B0_O2.txt"
f = open(name,"r")
S_B0_O2 = [float(line) for line in f]
f.close()

name = "timings_S_B0_O3.txt"
f = open(name,"r")
S_B0_O3 = [float(line) for line in f]
f.close()

name = "timings_S_B8_O0.txt"
f = open(name,"r")
S_B8_O0 = [float(line) for line in f]
f.close()

name = "timings_S_B8_O1.txt"
f = open(name,"r")
S_B8_O1 = [float(line) for line in f]
f.close()

name = "timings_S_B8_O2.txt"
f = open(name,"r")
S_B8_O2 = [float(line) for line in f]
f.close()

name = "timings_S_B8_O3.txt"
f = open(name,"r")
S_B8_O3 = [float(line) for line in f]
f.close()

name = "timings_P_B0_O0.txt"
f = open(name,"r")
P_B0_O0 = [float(line) for line in f]
f.close()

name = "timings_P_B0_O3.txt"
f = open(name,"r")
P_B0_O3 = [float(line) for line in f]
f.close()

name = "timings_P_B8_O0.txt"
f = open(name,"r")
P_B8_O0 = [float(line) for line in f]
f.close()

name = "timings_P_B8_O3.txt"
f = open(name,"r")
P_B8_O3 = [float(line) for line in f]
f.close()


label = ["-O0", "-O1", "-O2", "-O3", "modified -O0", "modified -O1", "modified -O2", "modified -O3" ]
y = [S_B0_O0, S_B0_O1, S_B0_O2, S_B0_O3, S_B8_O0, S_B8_O1, S_B8_O2, S_B8_O3]

for i in range(len(y)):
    plt.figure(1)
    plt.plot(N,y[i], label = label[i])
    plt.figure(2)
    plt.loglog(N,y[i], label = label[i])
    plt.figure(3)
    plt.plot(NlogN,y[i], label = label[i])

plt.figure(1)
plt.legend()
plt.grid()
plt.figure(2)
plt.legend()
plt.grid()
plt.figure(3)
plt.legend()
plt.grid()


y = [P_B0_O0, P_B0_O3, P_B8_O0, P_B8_O3]
label = ["-O0", "-O3", "modified -O0", "modified -O3"]

for i in range(len(y)):
    plt.figure(4)
    plt.plot(T,y[i], label = label[i])

plt.xlabel("Threads")
plt.legend()
plt.grid()

y = [spdup(P_B0_O0[0],P_B0_O0), spdup(P_B0_O3[0],P_B0_O3) ]
label = ["Speedup -O0", "Speedup -O3"]

for i in range(len(y)):
    plt.figure(5)
    plt.plot(T,y[i], label = label[i])

plt.xlabel("Threads")
plt.legend()
plt.grid()
plt.show()
