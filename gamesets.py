from itertools import combinations

def calc_gamesets(
                large = {100, 75, 50, 25},
                small = set(range(1,11))
                 ):
    gamesets = []

    ##### No large #####

    ## 3 doubles
    k=0
    for a,b,c in combinations(small, 3):
        gamesets.append((a,a,b,b,c,c))
        k+=1
    print(k)

    ## 2 doubles
    k=0
    for a,b in combinations(small, 2):
        remaining_small = small.difference(set([a,b]))
        for c,d in combinations(remaining_small, 2):
            gamesets.append((a,a,b,b,c,d))
            k+=1
    print(k)

    ## 1 double
    k=0
    for a in small:
        remaining_small = small.difference(set([a]))
        for b,c,d,e in combinations(remaining_small, 4):
            gamesets.append((a,a,b,c,d,e))
            k+=1
    print(k)

    ## 1 double
    k=0
    for a,b,c,d,e,f in combinations(small, 6):
        gamesets.append((a,b,c,d,e,f))
        k+=1
    print(k)


    ##### 1 large #####
    print()

    ## 2 doubles
    k=0
    for A in large:
        for a,b in combinations(small, 2):
            remaining_small = small.difference(set([a,b]))
            for c in remaining_small:
                gamesets.append((A,a,a,b,b,c))
                k+=1
    print(k)

    ## 1 doubles
    k=0
    for A in large:
        for a in small:
            remaining_small = small.difference(set([a]))
            for b,c,d in combinations(remaining_small, 3):
                gamesets.append((A,a,a,b,c,d))
                k+=1
    print(k)

    ## 0 doubles
    k=0
    for A in large:
        for a,b,c,d,e in combinations(small, 5):
            gamesets.append((A,a,b,c,d,e))
            k+=1
    print(k)

    
    ##### 2 large #####
    print()

    ## 2 doubles
    k=0
    for A, B in combinations(large, 2):
        for a,b in combinations(small, 2):
            gamesets.append((A,B,a,a,b,b))
            k+=1
    print(k)

    ## 1 doubles
    k=0
    for A, B in combinations(large, 2):
        for a in small:
            remaining_small = small.difference(set([a]))
            for b,c in combinations(remaining_small, 2):
                gamesets.append((A,B,a,a,b,c))
                k+=1
    print(k)

    ## 0 doubles
    k=0
    for A, B in combinations(large, 2):
        for a,b,c,d in combinations(small, 4):
            gamesets.append((A,B,a,b,c,d))
            k+=1
    print(k)

    
    ##### 3 large #####
    print()

    ## 1 doubles
    k=0
    for A, B, C in combinations(large, 3):
        for a in small:
            remaining_small = small.difference(set([a]))
            for b in remaining_small:
                gamesets.append((A,B,C,a,a,b))
                k+=1
    print(k)

    ## 0 doubles
    k=0
    for A, B, C in combinations(large, 3):
        for a,b,c in combinations(small, 3):
            gamesets.append((A,B,C,a,b,c))
            k+=1
    print(k)


    ##### 4 large #####
    print()

    ## 1 doubles
    k=0
    for A, B, C, D in combinations(large, 4):
        for a in small:
            gamesets.append((A,B,C,D,a,a))
            k+=1
    print(k)

    ## 0 doubles
    k=0
    for A, B, C, D in combinations(large, 4):
        for a,b in combinations(small, 2):
            gamesets.append((A,B,C,D,a,b))
            k+=1
    print(k)

    return gamesets

# write all gamesets to an input file
with open("_".join(map(str,large)+".res"), "w") as file:
    for gameset in calc_gamesets():
        file.write(" ".join(map(str,gameset))+"\n")

