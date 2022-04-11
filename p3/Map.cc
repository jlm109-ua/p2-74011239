// Juan Llinares Mauri - 74011239E
#include <iostream>
#include "Map.h"

using namespace std;

// Constructor por defecto de Map.
Map::Map(int rows,int columns){
    if((rows<5) || (columns<5))
        throw EXCEPTION_SIZE;
    
    this->rows = rows;
    this->columns = columns;

    for(int i = 0;i < rows;i++){
        Junk junk;
        vector<Junk> vj;
        for(int j = 0;j < columns;j++){
            vj.push_back(junk);
        }
        junks.push_back(vj);
    }
}

/* Booleano que comprueba si la coordenada está dentro del mapa.
 * Parámetro: const Coordinate coord: Coordenada a comprobar.
 * Returns:
   - true: Si sí que está dentro del mapa.
   - false: Si no está dentro del mapa.
 */
bool Map::isInside(const Coordinate &coord) const{
    return (((coord.getRow()>=0) && (coord.getRow()<=rows)) && ((coord.getColumn()>=0) && (coord.getColumn()<=columns)));
}

/* Función que modifica el Junk que hay en una determinada coordenada.
 * Parámetros:
   - const Junk junk: Junk que se desea introducir en el mapa.
   - const Coordinate coord: Coordenada en la que se desea introducir el Junk.
 * Throws:
   - EXCEPTION_OUTSIDE: Excepción por si la coordenada no se encuentra dentro del mapa.
 */ 
void Map::putJunk(const Junk &junk,const Coordinate &coord){
    if(!isInside(coord))
        throw EXCEPTION_OUTSIDE;

    junks[coord.getRow()][coord.getColumn()] = junk;
}

/* Getter del Junk de una determinada coordenada.
 * Returns: Junk: Junk que contiene la coordenada.
 * Throws:
   - EXCEPTION_OUTSIDE: Excepción por si la coordenada no se encuentra dentro del mapa.
 */
Junk Map::getJunk(const Coordinate &coord) const{
    if(!isInside(coord))
        throw EXCEPTION_OUTSIDE;
    
    return junks[coord.getRow()][coord.getColumn()];
}

/* Función que devuelve y modifica el Junk que hay en una determinada coordenada por un Junk de tipo WASTELAND.
 * Parámetros:
   - const Coordinate coord: Coordenada en la que se desea recolectar el Junk.
 * Returns: Junk: Junk que contiene la coordenada.
 * Throws:
   - EXCEPTION_OUTSIDE: Excepción por si la coordenada no se encuentra dentro del mapa.
 */ 
Junk Map::collectJunk(const Coordinate &coord){
    if(!isInside(coord))
        throw EXCEPTION_OUTSIDE;
    
    Junk junk(junks[coord.getRow()][coord.getColumn()]);
    Junk wasteland;

    junks[coord.getRow()][coord.getColumn()] == wasteland;

    return junk;
}

// Sobrecarga del operador de salida de Map.
ostream & operator<<(ostream &os,const Map &map){
    if((map.columns < 10) && (map.rows < 10)){
        
    }else{

    }

    return os;
}