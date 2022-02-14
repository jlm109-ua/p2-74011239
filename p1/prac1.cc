// Programación 2 - Práctica 1
// DNI: 74011239E
// Nombre: Juan Llinares Mauri

#include <iostream>
#include <cstdlib> // Para rand(), srand() y atoi()
#include <string.h> // Para strings y sus opciones

using namespace std;

// CONSTANTES NUMÉRICAS

const int KNAME=32;
const int KENEMIES=5;
const int KPOINTS=200;
const int KDICE=20; // Número de caras del dado

// CONSTANTES DE ERROR

const string ERR_WRONG_NAME = "ERROR: wrong name"; // Error para cuando el nombre introducido es incorrecto
const string ERR_WRONG_DISTRIBUTION = "ERROR: wrong distribution"; // Error para cuando la distribución es errónea
const string ERR_WRONG_OPTION = "ERROR: wrong option"; // Error para cuando se elige una opción errónea en el menú
const string ERR_CANNOT_RUN_AWAY = "ERROR: cannot run away"; // Error para cuando no se pueda escapar
const string ERR_SPECIAL_NOT_AVAILABLE = "ERROR: special not available"; // Error para cuando el ataque especial no esté disponible

// CONSTANTES STRING DEL PROGRAMA

const string EHN = "Enter hero name: "; // Cadena para pedir el nombre del héroe
const string EAD = "Enter attack/defense: "; // Cadena para pedir la distribución del ataque y la defensa del héroe
const string ENEMY = "[Enemy]"; // Cadena para mostrar un enemigo
const string BREED = "Breed: "; // Cadena para mostrar la raza de un enemigo
const string ATTACK = "Attack: "; // Cadena para mostrar el ataque
const string DEFENSE = "Defense: "; // Cadena para mostrar la defensa
const string HP = "Health Points: "; // Cadena para mostrar la vida
const string HITPOINTS = "Hit Points: "; // Cadena para mostrar los hit points
const string ENEMYHP = "Enemy health points: "; // Cadena para mostrar la vida del enemigo
const string HEROHP = "Hero health points: "; // Cadena para mostrar la vida del héroe
const string ENEMYKILLED = "Enemy killed"; // Cadena para mostrar cuando un enemigo ha muerto
const string HERODEAD = "You are dead"; // Cadena para mostrar que el héroe ha muerto
const string HERO_FIGHT_ENEMY = "[Hero -> Enemy]"; // Cadena para imprimir por pantalla que el héroe va a luchar contra el enemigo
const string ENEMY_FIGHT_HERO = "[Enemy -> Hero]"; // Cadena para imprimir por pantalla que el enemigo va a luchar contra el héroe
const string RUNAWAY = "You run away"; // Cadena para informar de que el héroe ha huído
const string NAME = "Name: "; // Cadena para mostrar el nombre
const string SPECIAL = "Special: "; // Cadena para mostrar si el ataque especial está disponible
const string RUNAWAYS = "Runaways: "; // Cadena para mostrar los runaways del héroe restantes
const string EXP = "Exp: "; // Cadena para mostrar la experiencia del héroe
const string KILLS = "Enemies killed: "; // Cadena para mostrar los enemigos derrotados

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

// RECOPILATORIO DE LAS FUNCIONES DEL PROGRAMA

void fight(Hero &hero,Enemy &enemy,bool speAtt);
void report(const Hero &hero);
void showMenu();
void nameHero(Hero &hero);
void setDistribution(Hero hero);
bool checkDistribution(string distribution,float &attack,float &defense);
void printEnemy(Enemy enemy);
void giveExp(Hero &hero,Enemy &enemy);
void printKills(Hero hero);

int rollDice(){
  return rand()%KDICE+1;
}

Hero createHero(){
  Hero hero;
    
  nameHero(hero); // Nombra al héroe
  setDistribution(hero); // Distribuye el ataque y la defensa del héroe
  hero.special = true; // Inicializamos su especial a true para que pueda ser usado.
  hero.exp = 0; // Inicializamos su experiencia a 0
  hero.runaways = 3;
  
  for(int i = 0;i < 5;i++) // Inicializamos sus kills a 0
    hero.kills[i] = 0;

  return hero;
}

Enemy createEnemy(){
  int dice = rollDice();

  Enemy enemy;

  if(dice >= 1 && dice <= 6){ // Creamos un ajolote
    enemy.name = AXOLOTL;
    enemy.features.attack = 40;
    enemy.features.defense = 40;
    enemy.features.hp = enemy.features.defense*2;
  }else if(dice >= 7 && dice <= 11){ // Creamos un Trol
    enemy.name = TROLL;
    enemy.features.attack = 60;
    enemy.features.defense = 80;
    enemy.features.hp = enemy.features.defense*2;
  }else if(dice >= 12 && dice <= 15){ // Creamos un Ogro
    enemy.name = ORC;
    enemy.features.attack = 80;
    enemy.features.defense = 120;
    enemy.features.hp = enemy.features.defense*2;
  }else if(dice >= 16 && dice <= 18){ // Creamos un perro del infierno
    enemy.name = HELLHOUND;
    enemy.features.attack = 120;
    enemy.features.defense = 100;
    enemy.features.hp = enemy.features.defense*2;
  }else if(dice >= 19 && dice <= 20){ // Creamos un Dragon
    enemy.name = DRAGON;
    enemy.features.attack = 160;
    enemy.features.defense = 140;
    enemy.features.hp = enemy.features.defense*2;
  }

  printEnemy(enemy);

  return enemy;
}

void fight(Hero &hero,Enemy &enemy,bool speAtt){
  cout<<HERO_FIGHT_ENEMY<<endl; // Imprimimos la lucha del héroe contra el enemigo

  int attackHero = rollDice()*5; // Guardamos el ataque obtenido por el dado
  if(hero.special && speAtt){
    attackHero = attackHero * 3;
  }
  cout<<ATTACK<<hero.features.attack<<" + "<<attackHero<<endl; // Imprimimos por pantalla el ataque que tendrá el héroe
  attackHero += hero.features.attack; // Guardamos el ataque del héroe para esta batalla

  int defenseEnemy = rollDice()*5; // Guardamos la defensa obtenida por el dado
  cout<<DEFENSE<<enemy.features.defense<<" + "<<defenseEnemy<<endl; // Imprimimos por pantalla la defensa que tendrá el enemigo
  defenseEnemy += enemy.features.defense; // Guardamos la defensa del enemigo para esta batalla

  int hitPoints =  attackHero - defenseEnemy; // Guardamos los hit points en una variable
  
  if(hitPoints < 0) // Si los hitPoints son negativos los ponemos a 0
    hitPoints = 0;

  cout<<HITPOINTS<<hitPoints<<endl; // Imprimimos por pantalla los hit points
  enemy.features.hp -= hitPoints; // Hacemos daño al enemigo

  if(enemy.features.hp < 0) // Si la salud del enemigo es negativa la ponemos a 0
    enemy.features.hp = 0;
  
  cout<<ENEMYHP<<enemy.features.hp<<endl; // Imprimimos por pantalla la salud del enemigo

  if(enemy.features.hp <= 0){
    cout<<ENEMYKILLED<<endl; // Imprimimos por pantalla que el enemigo ha sido derrotado
    giveExp(hero,enemy); // Damos experiencia al héroe
    hero.kills[enemy.name]++; // Aumentamos el contador de kills
  }else{ // Si el enemigo sigue vivo, el combate continua
    cout<<ENEMY_FIGHT_HERO<<endl; // Imprimimos la lucha del enemigo contra el héroe

    int attackEnemy = rollDice()*5; // Guardamos el ataque obtenido por el dado
    cout<<ATTACK<<enemy.features.attack<<" + "<<attackEnemy<<endl; // Imprimimos por pantalla el ataque que tendrá el enemigo
    attackEnemy += enemy.features.attack; // Guardamos el ataque del enemigo para esta batalla

    int defenseHero = rollDice()*5; // Guardamos la defensa obtenida por el dado
    cout<<DEFENSE<<hero.features.defense<<" + "<<defenseHero<<endl; // Imprimimos por pantalla la defensa que tendrá el héroe
    defenseHero += hero.features.defense; // Guardamos la defensa del héroe para esta batalla

    int hitPoints = attackEnemy - defenseHero; // Guardamos los hit points en una variable

    if(hitPoints < 0) // Si los hitPoints son negativos los ponemos a 0
      hitPoints = 0;

    cout<<HITPOINTS<<hitPoints<<endl; // Imprimimos por pantalla los hit points
    hero.features.hp -= hitPoints; // Hacemos daño al héroe

    if(hero.features.hp < 0) // Si la salud del héroe es negativa la ponemos a 0
      hero.features.hp = 0;
    
    cout<<HEROHP<<hero.features.hp<<endl; // Imprimimos por pantalla la salud del héroe

    if(hero.features.hp == 0){
      cout<<HERODEAD<<endl; // Imprimimos que el héroe ha sido derrotado
      report(hero);
    }
  }
}

void report(const Hero &hero){ // Imprimimos por pantalla toda la información del héroe
  cout<<"[Report]"<<endl
      <<NAME<<hero.name<<endl // Imprimimos el nombre del héroe
      <<ATTACK<<hero.features.attack<<endl // Imprimimos el ataque del héroe
      <<DEFENSE<<hero.features.defense<<endl // Imprimimos la defensa del héroe
      <<HP<<hero.features.hp<<endl; // Imprimimos la vida del héroe
  
  if(hero.special) // Si el héroe tiene el ataque especial disponible imprimimos "yes", en otro caso: "no"
    cout<<SPECIAL<<"yes"<<endl;
  else
    cout<<SPECIAL<<"no"<<endl;

  cout<<RUNAWAYS<<hero.runaways<<endl // Imprimimos las huídas que tiene disponible
      <<EXP<<hero.exp<<endl // Imprimimos la experiencia que tiene el héroe
      <<KILLS;
  printKills(hero); // Imprimimos las kills que ha logrado el héroe
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
      
      if(sname.length() == 0){
        cout<<ERR_WRONG_NAME<<endl; // Emitimos error si el nombre es incorrecto
        isNameIncorrect = true; // La variable Boolean la ponemos como true para que vuelva a repetir el bucle
      }else
        isNameIncorrect = false;
        hero.name = sname; // Le asignamos el nombre al héroe
  }while(isNameIncorrect);
}

void setDistribution(Hero &hero){ // Funcion que implementa el ataque y defensa del héroe
  string distribution; // Cadena auxiliar para la distribución
  bool isDistributionIncorrect = false; // Boolean para comprobar si la distribución es correcta
  float attack = 0; // Float para definir el ataque el héroe
  float defense = 0; // Float para definir la defensa del héroe

  do{
    cout<<EAD; // Pedimos la distribución
    getline(cin,distribution,'\n'); // Guardamos la distribución en una cadena auxiliar


    if(checkDistribution(distribution,attack,defense)){ // Comprobamos si hay algún fallo
      cout<<ERR_WRONG_DISTRIBUTION<<endl; // Imprimimos el error por pantalla
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
  if(distribution.empty()){ // Si la cadena está vacía --> Error
    return true;
  }

  string satt; // Cadena auxiliar para ataque
  string sdef; // Cadena auxiliar para defensa
  size_t pos = distribution.find("/"); // Posición del caracter "/" que separa ataque y defensa

  satt = distribution.substr(0,pos-1); // Extraemos el ataque
  sdef = distribution.substr(pos+1); // Extraemos la defensa

  int iattack = atoi(satt); // Convertimos el ataque a int
  int idefense = atoi(sdef); // Convertim la defensa a int

  if((iattack + idefense) <= 100 && (iattack + idefense) > 0 && iattack > 0 && idefense > 0){ // Comprobamos las restricciones
    return true;
  } 

  attack = iattack/100; // Establecemos el porcentaje de ataque
  defense = idefense/100; // Establecemos el porcentaje de defensa

  return false;
}

void printEnemy(Enemy enemy){ // Función para imprimir toda la información del enemigo por pantalla
  cout
    <<ENEMY<<endl
    <<BREED<<enemy.name<<endl
    <<ATTACK<<enemy.features.attack<<endl
    <<DEFENSE<<enemy.features.defense<<endl
    <<HP<<enemy.features.hp<<endl;
}

void giveExp(Hero &hero,Enemy &enemy){ // Función para repartir la experiencia al héroe según el enemigo derrotado
  if(enemy.name == AXOLOTL){
    hero.exp += 100;
  }else if(enemy.name == TROLL){
    hero.exp += 150;
  }else if(enemy.name == ORC){
    hero.exp += 200;
  }else if(enemy.name == HELLHOUND){
    hero.exp += 300;
  }else if(enemy.name == DRAGON){
    hero.exp += 400;
  }
}

void printKills(Hero hero){ // Función para imprimir por pantalla los enemigos derrotados
  cout<<"- Axolotl: "<<hero.kills[0]<<endl
      <<"- Troll: "<<hero.kills[1]<<endl
      <<"- Orc: "<<hero.kills[2]<<endl
      <<"- Hellhound: "<<hero.kills[3]<<endl
      <<"- Dragon: "<<hero.kills[4]<<endl
      <<"- Total: "<<hero.kills[0]+hero.kills[1]+hero.kills[2]+hero.kills[3]+hero.kills[4]<<endl;
}

int main(int argc,char *argv[]){
  if(argc!=2){ // Si los parámetros no son correctos, el programa termina inmediatamente
    cout << "Usage: " << argv[0] << " <seed>" << endl;
  }
  else{
    srand(atoi(argv[1])); // Introducimos la semilla para generar números aleatorios
    
    char option; // Variable para las opciones del menú
    bool isOptionIncorrect = true; // Booleano para comprobar que la opción escogida es correcta
    bool canRunAway = true; // Booleano para comprobar que el héroe no huya consecutivamente
    bool speAtt = false; // Booleano para saber cuando se usa el ataque especial

    Hero hero = createHero(); // Creamos el héroe
    Enemy enemy = createEnemy(); // Creamos el enemigo
    do{
      showMenu(); // Imprimimos el menú por pantalla
      cin>>option;
      if(option != 1 && option != 2 && option != 3 && option != 4 && option != 'q'){ //  Si la opción es errónea imprimimos el error por pantalla
        cout<<ERR_WRONG_OPTION<<endl;
      }else
        if(option == 1){ // Si option == 1 --> Fight
          fight(hero,enemy,speAtt); // Lucha contra el enemigo
          canRunAway = true; // Activamos canRunAway pues ha habido una pelea
          if(enemy.features.hp == 0)
            enemy = createEnemy(); // Si la vida del enemigo llega a 0, creamos uno nuevo.
        }else if(option == 2){ // Si option == 2 --> Run Away
          if(hero.runaways > 0 && canRunAway){ // Comprobamos que no haya huido antes y que le queden runaways
            cout<<RUNAWAY<<endl; // Imprimimos el éxito de la huída
            enemy = createEnemy(); // Creamos un nuevo enemigo
            hero.runaways--; // Le quitamos un runaway al héroe
            canRunAway = false; // Desactivamos el canRunAway
          }else
            cout<<ERR_CANNOT_RUN_AWAY<<endl; // Informamos de que no ha podido huir del enemigo
        }else if(option == 3){ // Si option == 3 --> Special
          if(hero.special){
            speAtt = true; // Activamos la opción del ataque especial
            fight(hero,enemy,speAtt); // Llamamos al fight para que luche
            speAtt = false; // Desactivamos la opción del ataque especial
          }else
            cout<<ERR_SPECIAL_NOT_AVAILABLE<<endl;
        }else if(option == 4){ // Si option == 4 --> Report
          report(hero);
        }else if(option == 'q'){ // Si option == 4 --> Quit
          isOptionIncorrect = false;
        }
    }while(isOptionIncorrect);
  }
}