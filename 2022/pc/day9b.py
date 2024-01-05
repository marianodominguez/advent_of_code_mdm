XMAX=500
YMAX=500
NNODES=9
hx,hy=XMAX//2,YMAX//2
nodes=[]
tx,ty=hx,hy
xmax=0;
ymax=0;
xmin=XMAX
ymin=YMAX

cmd=[]
visitedht={(tx,ty):1}
for i in range(0,NNODES):
    nodes.append((tx,ty))

def sign(a):
    if a!=0:return a//abs(a)
    return 0

def move_tail(dir, visitedht,headx,heady):
    global xmax,ymax,xmin,ymin,nodes,NNODES
    tx=0
    ty=0
    for i in range(0,NNODES):
        tx,ty=nodes[i]
        if i==0:
            hx=headx
            hy=heady
        else:
            hx=nodes[i-1][0]
            hy=nodes[i-1][1]
        dx=hx-tx
        dy=hy-ty
        if abs(dx)<=1 and abs(dy)<=1: continue     
        if (abs(dx)>=2) or (abs(dy)>=2):
            tx+=sign(dx)
            ty+=sign(dy)
            dir="X"
        if dir=='L': tx-=1
        if dir=='R': tx+=1
        if dir=='U': ty-=1
        if dir=='D': ty+=1

        xmax=max(hx,xmax)
        ymax=max(hy,ymax)
        xmin=min(hx,xmin)
        ymin=min(hy,ymin)
        nodes[i]=(tx,ty)

    tx,ty=nodes[NNODES-1]
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
        move_tail(dir,visitedht,hx,hy);


nvisited=0
f = open("./resources/test_data9b.txt")
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
    for y in range(hy-20,hy+20):
        for x in range(hy-20,hy+20):
            if (x,y) in nodes:
                print(nodes.index((x,y))+1,end="")
            elif (x,y)==(hx,hy):
                print("H", end="")
            else:
                print(".", end="")
        print("")
for key in visitedht:
    if visitedht[key]==1: 
        nvisited+=1
print(f" visited={nvisited}")
    