// Juan Llinares Mauri - 74011239E
#include <iostream>
#include "Jankali.h"

using namespace std;

// Constructor de Jankali a partir del nombre.
Jankali::Jankali(string name){
    if(name.empty())
        throw EXCEPTION_NAME;

    this->name = name;
    power = 300;
}

// Getter del nombre del Jankali.
string Jankali::getName() const{
    return name;
}

// Getter del poder del Jankali.
int Jankali::getPower() const{
    return power;
}

/* Función que busca a los Betonski atrapados en las trampas.
 * Parámetros:
   - vector<Betonski *> betonskis: Betonskis a capturar.
 */
void Jankali::hunt(vector<Betonski *> betonskis){
    for(Betonski betonski : betonskis){
        for(Coordinate trap : traps){
            if(!betonski.isCaptured() && trap.compare(betonski.getPosition())){
                subdued.push_back(betonski);
                betonski.capture();
        }
        }
    }
}

/* Función para colocar trampas en el mapa.
 * Parámetros:
   - const Coordinate &coord: Coordenada de la trampa.
 * Returns:
   - true: Si se ha conseguido colocar la trampa.
   - false: En cualquier otro caso.
 */
bool Jankali::setTrap(const Coordinate &coord){
    for(Coordinate trap : traps){
        if(trap.compare(coord)){
            return false;
        }
    }

    int trapCost = ((coord.getRow()+2)*(coord.getColumn()+2));

    if(power < trapCost){
        return false;
    }

    power -= trapCost;
    traps.push_back(coord);
}

// Función para expoliar a todos los betonski capturados.
void Jankali::spoil(){
    for(Betonski betonski : subdued){
        try{
            power = betonski.spoliation();
        }catch(Exception ex){
            for(int i = subdued.size();i >= 0;i--){
                if((subdued[i]->getAnger() == betonski.getAnger()) && (subdued[i]->getName() == betonski.getName()) && (subdued[i]->getPosition().compare(betonski.getPosition()))){
                    subdued.erase(subdued.begin() + i);
                }

            }
        }
    }
}

/* Función para expoliar los recursos de todos los betonski capturados.
 * Parámetros: JunkType type: Recuso a expoliar.
 */
void Jankali::spoil(JunkType type){
    for(Betonski betonski : subdued){
        try{
            power = betonski.spoliation(type);
        }catch(Exception ex){
            for(int i = subdued.size();i >= 0;i--){
                if((subdued[i]->getAnger() == betonski.getAnger()) && (subdued[i]->getName() == betonski.getName()) && (subdued[i]->getPosition().compare(betonski.getPosition()))){
                    subdued.erase(subdued.begin() + i);
                }

            }
        }
    }
}

/* Función para expoliar los recursos de todos los betonski capturados.
 * Parámetros: JunkType type: Recuso a expoliar.
 */
void Jankali::spoil(JunkType type){
    for(Betonski betonski : subdued){
        try{
            power = betonski.spoliation(type);
        }catch(Exception ex){
            for(int i = subdued.size();i >= 0;i--){
                if((subdued[i]->getAnger() == betonski.getAnger()) && (subdued[i]->getName() == betonski.getName()) && (subdued[i]->getPosition().compare(betonski.getPosition()))){
                    subdued.erase(subdued.begin() + i);
                }

            }
        }
    }
}

/* Función para expoliar a un Betonski en concreto.
 * Parámetros: int pos: Posición del Betonski en el vector subdued.
 */
void Jankali::spoil(int pos){
    if((pos < subdued.size()) || (pos >= 0)){
        subdued[pos]->spoliation();
    }
}

// Sobrecarga del operador de salida.
ostream & operator<<(ostream &os,const Jankali &jankali){
    os << "Jankali " << '"' << jankali.getName() << '"' << " " << jankali.getPower() << endl;
    for(Betonski betonski : jankali.subdued){
        os << betonski << endl;
    }
    os << "Traps ";
    for(Coordinate coord : jankali.traps){
        os << coord;
    }
}