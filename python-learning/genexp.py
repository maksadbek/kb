#!/usr/bin/env python3
import array

symbols = "abcdefg"
t = tuple(ord(s) for s in symbols)
print(t)

arr = array.array("I",(ord(s) for s in symbols))
print(arr)

colors = ["B", "W"]
sizes = ["S", "M", "L"]

for tshirt in ("%s %s" % (c,s) for c in colors for s in sizes):
    print(tshirt)
