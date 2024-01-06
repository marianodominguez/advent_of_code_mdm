#!/bin/env python3

digits=["zero","one","two","three","four","five","six","seven","eight", "nine"]
f=open("data/day01.dta","r")
#f=open("data/tst01.dta","r")
sum=0


lines = f.readlines()
for l in lines:
    first={}
    last={}
    l=l.strip()
    for digit,num in enumerate(digits):
        if num in l:
            first[digit] = l.index(num)
            last[digit] = l.rindex(num)
    min_index=len(l)
    max_index=0
    #print(l)
    #print(first,last)

    for k,v in first.items():
        if v<min_index:
            min_index=v
            tmp=k
    for k,v in last.items():
        if v>max_index:
            max_index=v
            d2=k
    i=0
    d1=0
    for d in l:
        if d>='0' and d<='9':
            if i>=max_index : d2=int(d)
            if i<=min_index and d1==0: d1=int(d)
        i+=1
    if d1==0: d1=tmp

    print(f"{l} {10*d1+d2}\n" )
    sum+=10*d1+d2
print(f"Sum: {sum}" )