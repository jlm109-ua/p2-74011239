// Programación 2 - Práctica 1
// DNI: 74011239E
// Nombre: Juan Llinares Mauri
 
#include <iostream>
#include <cstdlib> // Para rand(), srand() y atoi()
#include <string.h>

using namespace std;

const int KNAME=32;
const int KENEMIES=5;
const int KPOINTS=200;
const int KDICE=20; // Número de caras del dado
const String ERR_Wrong_Name = "ERROR: wrong name";

struct Core{
  int attack;
  int defense;
  int hp;
};

enum Breed{
  AXOLOTL,
  TROLL,
  ORC,
  HELLHOUND,
  DRAGON
};

struct Enemy{
  Breed name;
  Core features;
};

struct Hero{
  char name[KNAME];
  Core features;
  bool special;
  int runaways;
  int exp;
  int kills[KENEMIES];
};

int rollDice(){
  return rand()%KDICE+1;
}

Hero createHero(){
    Hero hero; // Héroe
    String sname; // Cadena para el nombre
    bool isNameIncorrect = false; // Boolean para comprobar si el nombre es correcto
    
    do{
        cout<<"Enter hero name: "; // Pedimos nombre
        cin>>sname; // Guardamos nombre en la string auxiliar
        
        if(sname.length == 0){
            cout<<ERR_Wrong_Name; // Emitimos error si el nombre es incorrecto
            isNameIncorrect = true; // La variable Boolean la ponemos como true para que vuelva a repetir el bucle
        }else
            hero.name = sname; // Le asignamos el nombre al héroe
    }while(isNameIncorrect);

}

Enemy createEnemy(){
}

void fight(Hero &hero,Enemy &enemy){
}

void report(const Hero &hero){
}

void showMenu(){
  cout << "[Options]" << endl
       << "1- Fight" << endl
       << "2- Run away" << endl
       << "3- Special" << endl 
       << "4- Report" << endl
       << "q- Quit" << endl
       << "Option: ";
}

int main(int argc,char *argv[]){
  if(argc!=2){ // Si los parámetros no son correctos, el programa termina inmediatamente
    cout << "Usage: " << argv[0] << " <seed>" << endl;
  }
  else{
    srand(atoi(argv[1])); // Introducimos la semilla para generar números aleatorios
    
    // Aquí vendrá todo tu código del "main"...
  }
}