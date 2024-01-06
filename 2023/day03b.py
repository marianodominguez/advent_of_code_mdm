#!/usr/bin/env python3

import sys

digits= [str(x) for x in range(10)]
non_part=digits.copy()
non_part.append('.') 

def get_parts(i,j,M):
    result = []
    d=str()
    for y in range(max(0,i-1),min(i+2, len(M))):
        for x in range(max(0,j-1), min(j+2, len(M[y])) ):
            d=""
            if(M[y][x]) in digits:
                d=M[y][x]
                r=1
                while x+r<len(M[y]) and M[y][x+r] in digits: 
                    d+=M[y][x+r]
                    r+=1
                r=1
                while x-r>=0 and M[y][x-r] in digits:
                    d=M[y][x-r]+d
                    r+=1
                if d not in result : result.append(d);
                d=''
    if len(result)==1: return []
    return result

def get_gears(M):
    result=[]
    i=0
    for row in M:
        j=0
        for elem in row:
            if M[i][j]=='*':
                result.append(get_parts(i,j,M))
            j+=1
        i+=1
    return result

f=open('data/day03.dta', 'r' )
#f=open('data/tst03.dta', 'r' )
lines=f.readlines()

M=[]

for l in lines:
    items=[]
    for chr in l.strip():
        items.append(chr)
    M.append(items)

numbers=[]
numbers.extend(get_gears(M))

print(numbers) 
print(sum( [int(x[0])*int(x[1]) for x in numbers if len(x)==2] ))