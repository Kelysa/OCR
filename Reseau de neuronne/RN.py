


class Neurone:
    def __init__(self, val=None, child = None, poid=0.5):
        """Init neurone.
        """
            
        if child is None:
            self.child = []
        else:
            self.child = child

        self.poid = poid            
        self.val = val

    def value(self):
        return self.poid * self.val

    def sum(self):
        s=0
        for np in self.child:
            s+= np.value()
        return s

    def func(self):
        if self.sum() >= 1:
            return 1
        else:
            return 0
        
    def upgrate(self):
        if self.child:
            for i in range(len(self.child)):
                self.child[i].poid += self.val* self.child[i].val
        

class Reseau:
    def __init__(self, nEnter=None ,nSortie=None):
        """Init neurone.
        """
        
        if nEnter is None:
            self.nEnter = []
        else:
            self.nEnter = nEnter
        if nSortie is None:
            self.nSortie = []
        else:
            self.nSortie = nSortie


def parcours(T):
    if T.child:
        for i in range(len(T.child)):
            parcours(T.child[i])
        T.val = T.func()

def play(reseau):
    for n in reseau.nSortie:
        parcours(n)
        
def requilibrage_rec(T):
    for i in range(len(T.child)):
        requilibrage_rec(T.child[i])
    T.upgrate()
        
def mise_a_jour (reseau, valfinal): 
    for i in range (len(reseau.nSortie)):
        reseau.nSortie[i].val = valfinal[i]
    for n in (reseau.nSortie):
        requilibrage_rec(n)

def check(R , valfinal):
    for i in range(len(valfinal)):
        if R.nSortie[i].val != valfinal[i]:
            return False
    return True

def training(R, valenter, valfinal):
    p = 0
    while 1:
        for i in range (len(valenter)):
            for j in range(len(valenter[0])):
                R.nEnter[j].val = valenter[i][j]
            play(R)
            if not check(R, valfinal[i]) :
                p+=1
                mise_a_jour(R,valfinal[i])
        if p == 0:
            break
        p=0
        
def prettyPrint(T,i):
    print(T.poid,i)
    if T.child:
        for i in range(len(T.child)):
            prettyPrint(T.child[i],i+1)


def makeR(l):
    li=[]
    R = Reseau()
    for i in range(l[0]):
        li.append(Neurone())
    R.nEnter = li

    for i in range(len(l)-1):
        le =[]
        for i in range(l[i+1]):
            le.append(Neurone(None,li))
        li = le
    R.nSortie = li
    return R



valenter = [[0,0],[0,1],[1,0],[1,1]]
valfinal = [[0],[0],[0],[1]]

        
def Main():
    n = " "
    l=[]
    i = 0
    print("Creation du Reseau Neuronal, entrez la taille de chaque couche. Entrer pour finir.")
    while 1 :
        n = input("taille reseau couche n°{}:".format(i))
        i+=1
        if n == "":
            break
        l.append(int(n))
    R = makeR(l)
    return R
R = Main()
