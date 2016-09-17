#!/usr/bin/env python3

symbols = "abcdefg"

# codes = []
# 
# for symbol in symbols:
#     codes.append(ord(symbol))

codes = [ord(symbol) for symbol in symbols]
print(codes)

# beyond some char
# beyond = list(filter(lambda c: c > 100, map(ord, symbols)))
# print(beyond)
beyond = [ord(symbol) for symbol in symbols if ord(symbol) > 100]
print(beyond)


colors = ["black", "white"]
sizes = ["S", "M", "L"]
tshirts = [(color, size) for color in colors for size in sizes]
print(tshirts)
