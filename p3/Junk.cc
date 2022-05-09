// DNI 74011239E LLINARES MAURI, JUAN
#include <iostream>
#include "Junk.h"

using namespace std;

const string SJUNKTYPE[] = {"WASTELAND","GOLD","METAL","FOOD","STONE"};

// Constructor por defecto de Junk.
Junk::Junk(){
    type = WASTELAND;
    quantity = 0;
}

// Constructor con parámetros de Junk.
Junk::Junk(JunkType type,int quantity){
    this->type = type;
    if(quantity>=0)
        this->quantity = quantity;
    else
        throw EXCEPTION_QUANTITY;
}

// Getter del atributo type de Junk.
JunkType Junk::getType() const{
    return type;
}

// Getter del atributo quantity de Junk.
int Junk::getQuantity() const{
    return quantity;
}

// Devuelve el primer caracter del tipo del Junk.
char Junk::getTypeChar() const{
    if(type==WASTELAND)
        return 'W';
    else if(type==GOLD)
        return 'G';
    else if(type==METAL)
        return 'M';
    else if(type==FOOD)
        return 'F';
    else
        return 'S';
}

// Devuelve el valor del Junk multiplicado por su cantidad.
int Junk::getValue() const{
    if(type==WASTELAND)
        return 0;
    else if(type==GOLD)
        return quantity*500;
    else if(type==METAL)
        return quantity*100;
    else if(type==FOOD)
        return quantity*50;
    else
        return quantity*20;
}

// Operador de salida de Junk.
ostream & operator<<(ostream &os,const Junk &junk){
    os << "[" << SJUNKTYPE[junk.getType()] << ":" << junk.getQuantity() << "]";
    return os;
}