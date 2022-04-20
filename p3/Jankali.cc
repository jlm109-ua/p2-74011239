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
            // eliminar el betonski
        }
    }
}