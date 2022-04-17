// Juan Llinares Mauri - 74011239E
#include <iostream>
#include <string.h>
#ifndef _BETONSKI_H_
#define _BETONSKI_H_
#include "Coordinate.h"
#include "Util.h"
#include "Map.h"

using namespace std;

class Betonski{
    protected:
        string name;
        int anger;
        vector <Junk> bag;
        Coordinate position;
        bool captured;
    public:
        Betonski(string);
        string getName() const;
        int getAnger() const;
        bool isCaptured() const;
        Coordinate getPosition() const;
        void capture();
        void setPosition(const Coordinate &);
        int calculateValue();
        int calculateValue(JunkType type);
        int spoliation();
        int spoliation(JunkType type);
        int extract(Map &);
        bool move(const Map &);
        friend ostream & operator<<(ostream &,const Betonski &);
};

#endif