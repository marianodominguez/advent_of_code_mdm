#!/usr/bin/env python3

def get_cards():
    result=[]
    f=open("data/day04.dta","r")
    lines=f.readlines()
    for l in lines:
        cardLine = l.split('|')[1]
        winLine =  l.split('|')[0]
        numbers=[ int(x) for x in winLine[winLine.index(': ')+1:].split(" ") if x != '']
        deck=[ int(x) for x in cardLine.split(" ") if x != '']
        result.append({"numbers":numbers, "card":deck})
    return result

deck=get_cards()
print(deck)

total_score=0;
for line in deck:
    score=0
    for number in line['card']:
        if number in line['numbers']:
            if score==0:
                score =1
            else:
                score*=2
    total_score+=score

print(total_score)