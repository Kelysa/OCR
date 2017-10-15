from random import *
from math import *


class Neurone:
    def __init__(self, val=None, child = None):
        """Init neurone.
        """
            
        if child is None:
            self.child = []
        else:
            self.child = child
            
                   
        self.val = val


    def sum(self):
        s=0
        for i in range(len(self.child)):
            s+= self.child[i][0].val * self.child[i][1]
        return s

    def func(self):
        s = 1/(1+exp(-(self.sum())))
        return s
        
    def upgrate(self):
        if self.child:
            for i in range(len(self.child)):
                self.child[i][1] += self.val* self.child[i][0].val
        

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
            parcours(T.child[i][0])
        T.val = T.func()

def play(reseau):
    for n in reseau.nSortie:
        parcours(n)
        
def requilibrage_rec(T):
    for i in range(len(T.child)):
        requilibrage_rec(T.child[i][0])
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
        
def prettyPrint(T):
    for i in range(len(T.child)):
        print(T.child[i][1])
    if T.child:
        for i in range(len(T.child)):
            prettyPrint(T.child[i][0])


def makeR(l):
    li=[]
    l1=[]
    R = Reseau()
    for i in range(l[0]):
        a = Neurone()
        li.append([a,0.5])
        l1.append(a)
    R.nEnter = l1

    for i in range(len(l)-1):
        le =[]
        l2=[]
        for i in range(l[i+1]):
            a = Neurone(None,li)
            le.append([a,0.5])
            l2.append(a)
        li = le
    R.nSortie = l2
    return R



valenter = [[0,0],[0,1],[1,0],[1,1]]
valfinal = [[0],[1],[1],[1]]

        
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
