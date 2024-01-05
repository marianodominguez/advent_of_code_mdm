XMAX=450
YMAX=600
hx,hy=XMAX//2,YMAX//2
tx,ty=hx,hy
xmax=0;
ymax=0;
xmin=XMAX
ymin=YMAX

cmd=[]
visitedht={(tx,ty):1}

def move_tail(dir, visitedht):
    global tx,ty,hx,hy,xmax,ymax,xmin,ymin
    dx=hx-tx
    dy=hy-ty
    if abs(dx)<=1 and abs(dy)<=1: return    
    if abs(dx)>=2 and abs(dy)>0:
        tx+=dx//abs(dx)
        ty+=dy//abs(dy)
        dir="X"
    if abs(dy)>=2 and abs(dx)>0:
        tx+=dx//abs(dx)
        ty+=dy//abs(dy)
        dir="X"
    if dir=='L': tx-=1
    if dir=='R': tx+=1
    if dir=='U': ty-=1
    if dir=='D': ty+=1

    xmax=max(hx,xmax)
    ymax=max(hy,ymax)
    xmin=min(hx,xmin)
    ymin=min(hy,ymin)

    if (tx,ty) not in visitedht:
        visitedht[(tx,ty)]=1

def move_head(dir,size,visitedht):
    global tx,ty,hx,hy
    dx=0
    dy=0
    i=0
    if dir=="D": dy=1
    if dir=="U": dy=-1
    if dir=="R": dx=1
    if dir=="L": dx=-1

    for i in range(size):
        hx+=dx
        hy+=dy
        move_tail(dir,visitedht);


nvisited=0
f = open("../resources/data9.txt")
for line in f:
    cmd.append(line);

for l in cmd:
    dir=l[0]
    size=int(l[2:])
    move_head(dir, size,visitedht)
    print("\033c", end="")
    print(f"{dir} {size}")
    print(f"{tx},{ty}")
    print(f"{hx},{hy}")
    print(f" max: {xmax},{ymax}")
    print(f" min: {xmin},{ymin}")
for key in visitedht:
    if visitedht[key]==1: 
        nvisited+=1
print(f" visited={nvisited}")
    