import os
import sys
import subprocess
from subprocess import call


def correctness():
    name = "check.txt"
    open(name, 'w').close()
    f = open(name,"w")


    N =  [2**n for n in range(4,24)]
    max = 300


    for i in range(len(N)):
        print(f"Starting N = {N[i]} simulation.")
        string = "./merge " + str(N[i]) + " " +  str(max) + " >> out.txt"
        print(string)
        call(string, shell = True)
        ff = open("out.txt","r")
        res = ff.read()
        f.write(res)
        ff.close()
        os.remove("out.txt")

    f.close()
    print("done :)")


def timing():
    name = "timings.txt"
    open(name, 'w').close()
    f = open(name,"w")


    N =  [2**n for n in range(4,30)]
    max = 300


    for i in range(len(N)):
        print(f"Starting N = {N[i]} simulation.")
        string = "./merge " + str(N[i]) + " " +  str(max) + " >> out.txt"
        print(string)
        call(string, shell = True)
        ff = open("out.txt","r")
        res = ff.read()
        f.write(res)
        ff.close()
        os.remove("out.txt")

    f.close()
    print("done :)")

timing()
#correctness()

    
