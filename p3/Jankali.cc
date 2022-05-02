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
    for(unsigned i = 0;i < betonskis.size();i++){
        for(unsigned j = 0;j < traps.size();j++){
            if((!betonskis[i]->isCaptured()) && traps[i].compare(betonskis[i]->getPosition())){
                subdued.push_back(betonskis[i]);
                betonskis[i]->capture();
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
    for(unsigned i = 0;i < traps.size();i++){
        if(traps[i].compare(coord))
            return false;
    }

    int trapCost = ((coord.getRow()+2)*(coord.getColumn()+2));

    if(power < trapCost)
        return false;

    power -= trapCost;
    
    traps.push_back(coord);

    return true;
}

// Función para expoliar a todos los betonski capturados.
void Jankali::spoil(){
    for(unsigned i = 0;i < subdued.size();i++){
        try{
            power = subdued[i]->spoliation();
        }catch(Exception ex){
            for(int i = subdued.size();i >= 0;i--){
                if((subdued[i]->getAnger() == subdued[i]->getAnger()) && (subdued[i]->getName() == subdued[i]->getName()) && (subdued[i]->getPosition().compare(subdued[i]->getPosition()))){
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
    for(unsigned i = 0;i < subdued.size();i++){
        try{
            power = subdued[i]->spoliation(type);
        }catch(Exception ex){
            for(unsigned i = subdued.size();i >= 0;i--){
                if((subdued[i]->getAnger() == subdued[i]->getAnger()) && (subdued[i]->getName() == subdued[i]->getName()) && (subdued[i]->getPosition().compare(subdued[i]->getPosition()))){
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
    if(pos >= 0){
        unsigned u = pos;

        if(u < subdued.size())
            subdued[u]->spoliation();
    }
}

// Sobrecarga del operador de salida.
ostream & operator<<(ostream &os,const Jankali &jankali){
    os << "Jankali " << '"' << jankali.getName() << '"' << " " << jankali.getPower() << endl;
    for(unsigned i = 0;i < jankali.subdued.size();i++){
        os << jankali.subdued[i] << endl;
    }
    os << "Traps ";
    for(unsigned i = 0;i < jankali.traps.size();i++){
        os << jankali.traps[i];
    }

    return os;
}