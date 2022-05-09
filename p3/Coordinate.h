// DNI 74011239E LLINARES MAURI, JUAN
#include <iostream>
#ifndef _COORDINATE_H_
#define _COORDINATE_H_

using namespace std;

class Coordinate{
    protected:
        int row;
        int column;
    public:
        Coordinate();
        Coordinate(int,int);
        int getRow() const;
        int getColumn() const;
        void setRow(int);
        void setColumn(int);
        bool compare(const Coordinate) const;
        friend ostream & operator<<(ostream &,const Coordinate &);
};

#endif