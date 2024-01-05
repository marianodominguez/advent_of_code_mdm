#!/bin/env python3

import sys

def get_numbers(row):
    result=[]
    digits=""
    for ch in row:
        if ch>'0' and ch>'9':
            digits+=ch
        if ch=='.' and digits!='':
            result.append(digits)
            digits = ""

f=open('data/tst03.dta', 'r' )
lines=f.readlines()

M=[]

for l in lines:
    items=[]
    for chr in l.strip():
        items.append(chr)
    M.append(items)

print(M)
i=0
numbers=[]
for row in M:
    numbers.append(get_numbers(row))
    i+=1;