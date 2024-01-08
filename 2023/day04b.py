#!/usr/bin/env python3

def get_cards():
    result={}
    f=open("data/day04.dta","r")
    lines=f.readlines()
    for l in lines:
        cardLine = l.split('|')[1]
        winLine =  l.split('|')[0]
        numbers=[ int(x) for x in winLine[winLine.index(': ')+1:].split(" ") if x != '']
        deck=[ int(x) for x in cardLine.split(" ") if x != '']
        id=int( l[4:l.index(':')].strip() )
        result[id] = {"numbers":numbers, "card":deck, 'n':1 }
    return result

deck=get_cards()

i=1
n=len(deck.items());
while i<=n:
    c=deck[i]
    matches=[x for x in c['card'] if x in c['numbers']]
    print(i, ", ", matches," ")
    for j in range(i+1,min(i+len(matches)+1, len(deck)+1)):
        deck[j]['n']+=deck[i]['n']
        #print(deck[j]['n'], ", ",i," " )
    i+=1

#print(deck)

print("sum: ",sum( [x['n'] for x in deck.values() ] ))