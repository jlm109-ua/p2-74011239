// Juan Llinares Mauri - 74011239E
#include <iostream>
#include "Betonski.h"
#include "Util.h"

#ifndef _JANKALI_H_
#define _JANKALI_H_

using namespace std;

class Jankali{
    protected:
        vector<Betonski *> subdued;
        vector<Coordinate> traps;
        string name;
        int power;
    public:
        Jankali(string);
        string getName() const;
        int getPower() const;
        void hunt(vector<Betonski *>);
        bool setTrap(const Coordinate &);
        void spoil();
        void spoil(JunkType type);
        void spoil(int pos);
        friend ostream & operator<<(ostream &,const Jankali &);
};

#endif