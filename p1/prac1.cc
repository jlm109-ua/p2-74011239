// Programación 2 - Práctica 1
// DNI: 74011239E
// Nombre: Juan Llinares Mauri

#include <iostream>
#include <cstdlib> // Para rand(), srand() y atoi()
#include <string.h> // Para strings y sus opciones

using namespace std;

const int KNAME=32;
const int KENEMIES=5;
const int KPOINTS=200;
const int KDICE=20; // Número de caras del dado

const string ERR_WRONG_NAME = "ERROR: wrong name"; // Error para cuando el nombre introducido es incorrecto
const string ERR_WRONG_DISTRIBUTION = "ERROR: wrong distribution"; // Error para cuando la distribución es errónea

const string EHN = "Enter hero name: "; // Cadena para pedir el nombre del héroe
const string EAD = "Enter attack/defense: "; // Cadena para pedir la distribución del ataque y la defensa del héroe

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
    
  nameHero(hero); // Nombra al héroe
  setDistribution(hero); // Distribuye el ataque y la defensa del héroe
  
  // SEGUIR CON EL ATAQUE ESPECIAL

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

void nameHero(Hero &hero){ // Función para nombrar al héroe
  string sname; // Cadena auxiliar para el nombre
  bool isNameIncorrect = false; // Boolean para comprobar si el nombre es correcto
    
  do{
      cout<<EHN; // Pedimos nombre
      getline(cin,sname,'\n'); // Guardamos nombre en la string auxiliar
      
      if(sname.length == 0){
        cout<<ERR_Wrong_Name; // Emitimos error si el nombre es incorrecto
        isNameIncorrect = true; // La variable Boolean la ponemos como true para que vuelva a repetir el bucle
      }else
        isNameIncorrect = false;
        hero.name = sname; // Le asignamos el nombre al héroe
  }while(isNameIncorrect);
}

void setDistribution(hero){ // Funcion que implementa el ataque y defensa del héroe
  string distribution; // Cadena auxiliar para la distribución
  bool isDistributionIncorrect = false; // Boolean para comprobar si la distribución es correcta
  float attack = 0;
  float defense = 0;

  do{
    cout<<EAD; // Pedimos la distribución
    getline(cin,distribution,'\n'); // Guardamos la distribución en una cadena auxiliar


    if(checkDistribution(distribution)){ // Comprobamos si hay algún fallo
      cout<<ERR_WRONG_DISTRIBUTION;
      isDistributionIncorrect = true;
    }else{ // Definimos sus estadísticas
      isDistributionIncorrect = false;
      hero.features.attack = KPOINTS*attack;
      hero.features.defense = KPOINTS*defense;
      hero.features.hp = hero.features.defense*2;
    }
  }while(isDistributionIncorrect);
}

bool checkDistribution(string distribution,float &attack,float &defense){ // Devuelve true en caso de error y false cuando está todo correcto
  if(distribution.length = 0){ // Si la cadena está vacía --> Error
    return true;
  }

  string satt; 
  string sdef; // Cadenas auxiliares para ataque y defensa
  size_t pos = distribution.find("/"); // Posición del caracter "/" que separa ataque y defensa

  satt = distribution.substr(0,pos-1); // Extraemos el ataque
  sdef = distribution.substr(pos+1); // Extraemos la defensa

  int iattack = stoi(satt); 
  int idefense = stoi(sdef); // Convertimos ataque y defensa a int

  if((iattack + idefense) <= 100 && (iattack + idefense) > 0 && iattack > 0 && idefense > 0){ // Comprobamos las restricciones
    return true;
  } 

  attack = iattack/100;
  defense = idefense/100;

  return false;
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