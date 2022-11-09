from matplotlib import pyplot as plt

G=6.67*10**-11

# Kütle, pozisyon, hız, ivme özellikleri olan bir obje sınıfı oluşturduk.(Vektörleri x ve y bileşenlerine ayırdık)
# We created an object class with mass, position, velocity, acceleration properties.(We split the vectors into x and y components)
# Not:İstersek 3 boyut için z bileşenini de ekleyebiliriz.
# Note: We can also add the z component if we want for 3D.
class Obje():
    def __init__(self,mass,posx,posy,velx,vely,accx=0,accy=0):
        self.mass=mass
        self.posx=posx
        self.posy=posy
        self.velx=velx
        self.vely=vely
        self.accx=accx
        self.accy=accy

# Objenin diğer cisime olan uzaklığı ve buna bağlı olarak aralarındaki kuvveti belirleyen foksiyonlar oluşturduk.
# We created functions that determine the distance of the object to the other object and, accordingly, the force between them.    
    def distance(self, otherObje):
        return ((self.posx-otherObje.posx)**2 +(self.posy-otherObje.posy)**2)**0.5
    
    def force (self, otherObje):
        return (self.mass*otherObje.mass*G)/(self.distance(otherObje)**2)
    
    def forcex (self, otherObje):
        return self.force(otherObje)*(otherObje.posx-self.posx)/self.distance(otherObje)
    
    def forcey (self, otherObje):
        return self.force(otherObje)*(otherObje.posy-self.posy)/self.distance(otherObje)
        


# Örnek objeleri oluşturabiliriz.
# We can create sample objects.
planets=(Obje(1000000,0,0,0, 0.005),
         Obje(10000000,10,10,0,0),
         Obje(1000000,20,20,-0.002,-0.008))


# Bir objenin listenin diğer elemanlarıyla olan etkileşiminden doğan kuvvetlerin toplamını hesaplayan kuvvet. 
# The force that calculates the sum of the forces resulting from the interaction of an object with other elements of the list.
# Not: Bu fonksiyon objelerin etkileşimlerini her obje için ayrı ayrı hesaplıyor, optimize edilebilir.
# Note: This function calculates the interaction of objects separately for each object, it can be optimized.

def instantaccx(Obje,liste):
    templist=list(liste)
    templist.remove(Obje)
    F=0
    for i in templist:
        F=F+Obje.forcex(i)   
    a=F/Obje.mass
    Obje.accx=a
    
def instantaccy(Obje,liste):
    templist=list(liste)
    templist.remove(Obje)
    F=0
    for i in templist:
        F=F+Obje.forcey(i)   
    a=F/Obje.mass
    Obje.accy=a


# Objelerin t saniye sonraki hızını hesaplayan fonksiyon.    
# Function that calculates the velocity of objects after t seconds.
def instantvelx(Obje,t):
    Obje.velx=Obje.velx+Obje.accx*t
    
def instantvely(Obje,t):
    Obje.vely=Obje.vely+Obje.accy*t
    
# Objelerin t saniye sonraki pozisyonunu hesaplayan fonksiyon.
# Function that calculates the position of objects after t seconds.       
def instantposx(Obje,t):
    Obje.posx=Obje.posx+Obje.velx*t
    
def instantposy(Obje,t):
    Obje.posy=Obje.posy+Obje.vely*t
    

# Objelerin sırasıyla ivme, hız, pozisyonunu güncelleyen döngü.
# A loop that updates the acceleration, velocity, position of the objects, respectively.
while(1):
    t=30

    for i in planets:
        instantaccx(i,planets)
        instantaccy(i,planets)
        
    for i in planets:
        instantvelx(i,t)
        instantvely(i,t)
        
    for i in planets:
        instantposx(i,t)
        instantposy(i,t)
 
# Ve bunu izleyelim.
# And let's watch this.
    plt.cla()
    for i in planets:
        plt.scatter(i.posx,i.posy)
        
    plt.xlim([-50,80])
    plt.ylim([-50,80])
    plt.pause(0.001)


    
    
    