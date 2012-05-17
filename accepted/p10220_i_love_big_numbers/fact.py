#!/usr/bin/python

def fact(n):    
    r = 1
    for i in range(1, n):
        r *= i;
    return r

print fact(125)    
    
