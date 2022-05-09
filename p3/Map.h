// DNI 74011239E LLINARES MAURI, JUAN
#include <iostream>
#include <vector>
#include "Coordinate.h"
#include "Junk.h"
#ifndef _MAP_H_
#define _MAP_H_

using namespace std;

class Map{
    protected:
        int rows;
        int columns;
        vector<vector<Junk> > junks;
    public:
        Map(int,int);
        bool isInside(const Coordinate &) const;
        void putJunk(const Junk &,const Coordinate &);
        Junk getJunk(const Coordinate &) const;
        Junk collectJunk(const Coordinate &);
        friend ostream & operator<<(ostream &,const Map &); 
};

#endif