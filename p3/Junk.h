// DNI 74011239E LLINARES MAURI, JUAN
#include <iostream>
#include "Util.h"
#ifndef _JUNK_H_
#define _JUNK_H_

using namespace std;

class Junk{
    protected:
        JunkType type;
        int quantity;
    public:
        Junk();
        Junk(JunkType,int);
        JunkType getType() const;
        int getQuantity() const;
        char getTypeChar() const;
        int getValue() const;
        friend ostream & operator<<(ostream &,const Junk &);
};

#endif