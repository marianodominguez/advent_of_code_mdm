#!/usr/bin/env python3

import sys

digits= [str(x) for x in range(10)]
non_part=digits.copy()
non_part.append('.') 

def part_number(number,i,j):
    min_x=i-len(number)-1
    if min_x<0: min_x=0
    max_x=i;
    if max_x>len(M[i])-1: max_x=len(M[i])-1
    min_y=j-1
    if min_y<0: min_y=0
    max_y=j+1
    if max_y>len(M)-1: max_y=len(M)-1

    for x in range(min_x, max_x+1):
        for y in range(min_y,max_y+1):
            if M[y][x] not in non_part: return True
    return False

def get_numbers(row,j):
    result=[]
    digits=""
    i=0
    for ch in row:
        if ch>='0' and ch<='9':
            digits+=ch
        if (ch not in digits or i==len(row)-1) and digits!='':
            if part_number(digits,i,j): result.append(digits)
            #print(digits)
            digits = ""
        i+=1;
    return result

f=open('data/day03.dta', 'r' )
lines=f.readlines()

M=[]

for l in lines:
    items=[]
    for chr in l.strip():
        items.append(chr)
    M.append(items)

i=0
numbers=[]
for row in M:
    numbers.extend(get_numbers(row,i))
    i+=1;

print(numbers) 
print(sum( [int(x) for x in numbers] ))