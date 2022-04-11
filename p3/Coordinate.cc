// Juan Llinares Mauri - 74011239E
#include <iostream>
#include "Coordinate.h"

using namespace std;

// Constructor por defecto de Coordinate.
Coordinate::Coordinate(){
    row = column = -1;
}

// Constructor de Coordinate con parámetros de entrada.
Coordinate::Coordinate(int row,int column){
    this->row = row;
    this->column = column;
}

// Getter del atributo row.
int Coordinate::getRow() const{
    return row;
}

// Getter del atributo column.
int Coordinate::getColumn() const{
    return column;
}

// Setter del atributo row.
void Coordinate::setRow(int row){
    this->row = row;
}

// Setter del atributo column.
void Coordinate::setColumn(int column){
    this->column = column;
}

/* Función que compara dos Coordinate.
 * Parámetros:
   -  const Coordinate coord: Coordenada a comparar con la actual.
 * Returns:
   - true: Si son iguales.
   - false: En cualquier otro caso.
 */
bool Coordinate::compare(const Coordinate coord) const{
    return ((this->row == coord.row) && (this->column == coord.column));
}

// Sobrecarga del operador de salida de Coordinate.
ostream & operator<<(ostream &os,const Coordinate &coord){
    os << "[" << coord.getRow() << "," << coord.getColumn() << "]";
    return os;
}