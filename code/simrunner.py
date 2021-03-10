import os
import sys
import subprocess
from subprocess import call


def correctness():
    name = "check.txt"
    open(name, 'w').close()
    f = open(name,"w")


    N =  [2**n for n in range(4,20)]
    max = 300


    for i in range(len(N)):
        print("Starting N = " + strN([i]) + " simulation.")
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


def timing(threads,bubbleflag):
    name = "timings.txt"
    open(name, 'w').close()
    f = open(name,"w")


    N =  [2**n for n in range(4,27)]



    for i in range(len(N)):
        print("Starting N = " + str(N[i]) + " simulation.")
        string = "./merge " + str(N[i]) + " " +  str(bubbleflag) + " " +  str(threads) + " >> out.txt"
        print(string)
        call(string, shell = True)
        ff = open("out.txt","r")
        res = ff.read()
        f.write(res)
        ff.close()
        os.remove("out.txt")

    f.close()
    print("done :)")



def threadrunner(bubbleflag):


    
    N = 2**24
    thread = [i for i in range(1,33)]


    for i in range(len(thread)):
        print("Starting thread = " + str(thread[i]) + " simulation.")
        string = "./merge " + str(N) + " " +  str(bubbleflag) + " " +  str(thread[i]) + " >> out.txt"
        print(string)
        call(string, shell = True)
        ff = open("out.txt","r")
        res = ff.read()
        f.write(res)
        ff.close()
        os.remove("out.txt")
        
    f.close()
    print("done :)")






timing(4,8)
#threadrunner(0)
#correctness()

    
