#!/usr/bin/python

b = 43945
p = 7
m = 7

from math import fmod

r = fmod(pow(fmod(b,m), p), m)
print r    
