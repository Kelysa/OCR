def pprint(m):
    for i in range(len(m)):
        print()
        for j in range(len(m[0])):
            print(str(round(m[i][j],2))+ " ",end='')
                       

def init_matrix(hauteur, largeur):
    L =[]
    for i in range(hauteur):
        l = []
        for j in range(largeur):
            l.append(0)
        L.append(l)
    return L

def Convolution(matrix, pattern):
    """patern 3*3"""
    # init de la new list
    hauteur, largeur = len(matrix) , len(matrix[0])
    L = init_matrix(hauteur-2, largeur-2)

    
    for i in range(hauteur -2):
        for j in range(largeur -2):
            res = 0
            for y in range(3):
                for x in range(3):
                    if i+y < hauteur and j+x < largeur:
                        if matrix[i+y][j+x] == pattern[y][x]:
                                  res += 1
                        else:
                                  res -=1
            L[i][j] = res / 9
    return L

def Pooling(matrix):
    hauteur, largeur = len(matrix) , len(matrix[0])
    h, l = len(matrix) , len(matrix[0])
    if h % 2 != 0:
        h+=1
        l+=1
    L = init_matrix(int(h/2), int(l/2))

    for i in range(int(h/2)):
        for j in range(int(l/2)):
            a1 = matrix[i*2][j*2]
            if i*2+1 > hauteur -1 or  j*2+1 > largeur -1:
                a2 = -1
            else: a2 = matrix[i*2+1][j*2+1]
            
            if i*2+1 > hauteur -1: 
                a3 = -1
            else: a3 = matrix[i*2+1][j*2]

            if j*2+1 > largeur -1:
                a4 = -1
            else: a4 = matrix[i*2][j*2+1]

            L[i][j] = max(a1,a2,a3,a4)
    return L

def ReLUs(matrix):
    hauteur, largeur = len(matrix) , len(matrix[0])
    for i in range(hauteur):
        for j in range(largeur):
            if matrix[i][j] < 0:
                matrix[i][j] =0

def Main():
    Matrix = [[-1, -1, -1, -1, -1, -1, -1, -1, -1],
          [-1,  1, -1, -1, -1, -1, -1,  1, -1],
          [-1, -1,  1, -1, -1, -1,  1, -1, -1],
          [-1, -1, -1,  1, -1,  1, -1, -1, -1],                 # X
          [-1, -1, -1, -1,  1, -1, -1, -1, -1],
          [-1, -1, -1,  1, -1,  1, -1, -1, -1],
          [-1, -1,  1, -1, -1, -1,  1, -1, -1],
          [-1,  1, -1, -1, -1, -1, -1,  1, -1],
          [-1, -1, -1, -1, -1, -1, -1, -1, -1]]

    pattern1 = [[ 1, -1, -1],
                [-1,  1, -1],
                [-1, -1,  1]];
    #l = Convolution(Matrix , pattern1)
    #print("convolution")
    #pprint(l)
    #print("")
    #ReLUs(l)
    #pprint(l)
    #print("pooling")
    #v = Pooling(l)
    #pprint(v)
    l = Convolution(Matrix , pattern1)
    ReLUs(l)
    l = Convolution(l , pattern1)
    ReLUs(l)
    l = Pooling(l)
    l = Convolution(l , pattern1)
    ReLUs(l)
    l = Pooling(l)
    pprint(l)

Main()
