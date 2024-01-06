#!/bin/env python3

import re

f=open("data/day02.dta","r")
#f=open("data/tst02.dta","r")
sum=0

cubes = {"blue":14,"red":12,"green":13 }

#Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green

linef=r"^Game (\d+):"

lines = f.readlines()
for l in lines:
    possible=1
    game_id=re.search(linef,l).group(1)
    print(game_id)
    subsets=[x.strip() for x in  l[l.index(":")+1:].split(';')]

    for subset in subsets:
        play=[ x.strip() for x in subset.split(',')]
        #print(play)
        playobj= {"blue":0,"red":0,"green":0 }
        for pl in play:
            kv=pl.split(' ')
            playobj[kv[1]]=int(kv[0])
        print(playobj)

        for k,v in playobj.items():
            if cubes[k]<v:
                possible=0
                break;
        if possible==0: break
    if possible: sum+=int(game_id)
print(sum)
