// Juan Llinares Mauri - 74011239E
#include <iostream>
#include "Betonski.h"

using namespace std;

// Constructor por defecto de Betonski
Betonski::Betonski(string name){
    if(name.empty())
        throw EXCEPTION_NAME;

    this->name = name;
    this->anger = 0;
    this->position = Coordinate(-1,-1);
    this->captured = false;
}

// Getter del atributo name.
string Betonski::getName() const{
    return name;
}

// Getter del atributo anger
int Betonski::getAnger() const{
    return anger;    
}

// Getter del atributo captured
bool Betonski::isCaptured() const{
    return captured;
}

// Getter del atributo position
Coordinate Betonski::getPosition() const{
    return position;
}

// Indica al Betonski que ha sido capturado.
void Betonski::capture(){
    captured = true;
}

/* Función que asigna una posición al Betonski.
 * Parámetros:
   - const Coordinate coord: Posición a asignar.
 */
void Betonski::setPosition(const Coordinate &coord){
    position = coord;
}

/* Función que calcula el valor de todos los Junk recogidos por el Betonski.
 * Returns: int -> Valor total de la Junk almacenada por el Betonski.
 */
int Betonski::calculateValue(){
    int value = 0;

    for(unsigned i = 0;i < bag.size();i++){
        value += bag[i].getValue();
    }

    return value;
}

int Betonski::calculateValue(JunkType type){
    int value = 0;

    for(unsigned i = 0;i < bag.size();i++){
        if(bag[i].getType() == type){
            value += bag[i].getValue();
        }
    }

    return value;
}

/* Función para expoliar a los Betonski.
 * Returns: int -> Valor de los elementos recogidos por el Betonski.
 */
int Betonski::spoliation(){
    int value = calculateValue();

    if(captured){
        if((value + anger) > 5000){
            captured = false;
            anger = 0;

            throw EXCEPTION_REBELION;
        }else{
            anger += value;
            bag.clear();

            return value;
        }
    }else
        throw BETONSKI_NOT_CAPTURED;
}

/* Función para expoliar a los Betonski.
 * Parámetros: JunkType type: Tipo de elemento a expoliar.
 * Returns: int -> Valor de los elementos recogidos por el Betonski.
 */
int Betonski::spoliation(JunkType type){
    int value = calculateValue(type);

    if(captured){
        if((value + anger) > 5000){
            captured = false;
            anger = 0;

            throw EXCEPTION_REBELION;
        }else{
            anger += value;
            
            for(int i = (bag.size() - 1);i >= 0;i--){
                if(bag[i].getType() == type){
                    bag.erase(bag.begin() + i);
                }
            }

            return value;
        }
    }else
        throw BETONSKI_NOT_CAPTURED;
}

int Betonski::extract(Map &map){
    if(map.isInside(position)){
        Junk junk = map.collectJunk(position);
        if(junk.getType() != WASTELAND){
            bag.push_back(junk);

            return junk.getValue();
        }
    }

    return 0;
}

/* Función para mover al Betonski por el mapa.
 * Parámetros: const Map map: Mapa en el que se situa el Betonski.
 * Returns:
   - true: Si se ha podido mover.
   - false: En cualquier otro caso.
 */
bool Betonski::move(const Map &map){
    if(map.isInside(position)){
        int value = Util::getRandomNumber(8);

        Coordinate aux;
        switch(value){
            case 0:
                aux = Coordinate(position.getRow(),position.getColumn() - 1);
                break;
            case 1:
                aux = Coordinate(position.getRow() + 1,position.getColumn() - 1);
                break;
            case 2:
                aux = Coordinate(position.getRow() + 1,position.getColumn());
                break;
            case 3:
                aux = Coordinate(position.getRow() + 1,position.getColumn() + 1);
                break;
            case 4:
                aux = Coordinate(position.getRow(),position.getColumn() + 1);
                break;
            case 5:
                aux = Coordinate(position.getRow() - 1,position.getColumn() + 1);
                break;
            case 6:
                aux = Coordinate(position.getRow() - 1,position.getColumn());
                break;
            case 7:
                aux = Coordinate(position.getRow() - 1,position.getColumn() - 1);
        }
        
        if(map.isInside(aux)){
            position = aux;

            return true;
        }else
            return false;
    }else{
        throw EXCEPTION_OUTSIDE;
    }
}

ostream & operator<<(ostream &os,const Betonski &betonski){
    os << "Betonski " << '"' << betonski.getName() << '"' << " ";
    if(betonski.isCaptured())
        os << "Captured ";
    else
        os << "Free ";

    os << betonski.getAnger() << betonski.getPosition() << endl;

    for(unsigned i = 0;i < betonski.bag.size();i++){
        os << betonski.bag[i];
    }

    return os;
}