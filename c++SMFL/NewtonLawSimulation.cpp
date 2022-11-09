#include <iostream>
#include <cmath>
#include <vector>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class Obje {

public:

    long double G = 6.67e-11;

    long double mass, posx, posy, velx, vely, accx, accy;

    string name;

    Obje(string name, long double mass,
        long double posx, long double posy,
        long double velx, long double vely,
        long double accx = 0, long double accy = 0) {

        this->name = name;
        this->mass = mass;
        this->posx = posx;
        this->posy = posy;
        this->velx = velx;
        this->vely = vely;
        this->accx = accx;
        this->accy = accy;
    }

    long double distance(Obje& otherobje) {
        return pow((pow((this->posx - otherobje.posx), 2) + pow((this->posy - otherobje.posy), 2)), 0.5);
    }
    long double force(Obje& otherobje) {
        return (this->mass * otherobje.mass * G / pow((this->distance(otherobje)), 2));
    }
    long double fx(Obje& otherobje) {
        return this->force(otherobje) * (otherobje.posx - this->posx) / this->distance(otherobje);
    }
    long double fy(Obje& otherobje) {
        return this->force(otherobje) * (otherobje.posy - this->posy) / this->distance(otherobje);
    }

};


void editaccx(Obje& a, vector<Obje>& vec) {

    vector<Obje> tempvec = vec;

    for (vector<Obje>::iterator it = tempvec.begin(); it != tempvec.end(); ++it) {
        if (it->name == a.name) {
            tempvec.erase(it);
            break;
        }
    }

    long double F = 0;

    for (vector<Obje>::iterator it = tempvec.begin(); it != tempvec.end(); ++it) {

        F = F + a.fx(*it);
    }
    long double acc = F / a.mass;
    a.accx = acc;
}

void editaccy(Obje& a, vector<Obje>& vec) {

    vector<Obje> tempvec = vec;

    for (vector<Obje>::iterator it = tempvec.begin(); it != tempvec.end(); ++it) {
        if (it->name == a.name) {
            tempvec.erase(it);
            break;
        }
    }

    long double F = 0;

    for (vector<Obje>::iterator it = tempvec.begin(); it != tempvec.end(); ++it) {

        F = F + a.fy(*it);
    }
    long double acc = F / a.mass;
    a.accy = acc;
}

void editvelx(Obje& a, double long t) {

    a.velx = a.velx + a.accx * t;

}

void editvely(Obje& a, double long t) {

    a.vely = a.vely + a.accy * t;

}

void editposx(Obje& a, double long t) {

    a.posx = a.posx + a.velx * t;
}

void editposy(Obje& a, double long t) {

    a.posy = a.posy + a.vely * t;
}


int main()
{
    vector<Obje> planets;
    Obje planet1("gez1", 10000000, 600, 600, 0, 0.008);
    Obje planet2("gez2", 100000000, 700, 700, 0, 0);
    Obje planet3("gez3", 10000000, 800, 800, 0, -0.008);

    planets.push_back(planet1);
    planets.push_back(planet2);
    planets.push_back(planet3);

    long double t = 5;

    RenderWindow pencere(VideoMode(2000, 1300), "FizikSimulasyonu");

    CircleShape planetin1(10);
    CircleShape planetin2(10);
    CircleShape planetin3(10);


    planetin1.setFillColor(Color::Red);
    planetin2.setFillColor(Color::Blue);
    planetin3.setFillColor(Color::Green);

    while (pencere.isOpen())
    {
        editaccx(planet1, planets);
        editaccx(planet2, planets);
        editaccx(planet3, planets);

        editaccy(planet1, planets);
        editaccy(planet2, planets);
        editaccy(planet3, planets);

        editvelx(planet1, t);
        editvelx(planet2, t);
        editvelx(planet3, t);

        editvely(planet1, t);
        editvely(planet2, t);
        editvely(planet3, t);

        editposx(planet1, t);
        editposx(planet2, t);
        editposx(planet3, t);

        editposy(planet1, t);
        editposy(planet2, t);
        editposy(planet3, t);

        Event olay;
        while (pencere.pollEvent(olay)) {

            if (olay.type == Event::Closed)
                pencere.close();

        }


        planetin1.setPosition(Vector2f(planet1.posx, planet1.posy));
        planetin2.setPosition(Vector2f(planet2.posx, planet2.posy));
        planetin3.setPosition(Vector2f(planet3.posx, planet3.posy));

        pencere.clear();


        pencere.draw(planetin1);
        pencere.draw(planetin2);
        pencere.draw(planetin3);


        pencere.display();


    }


}