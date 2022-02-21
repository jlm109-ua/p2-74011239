// Programación 2 - Práctica 1
// DNI: 74011239E
// Nombre: Juan Llinares Mauri

#include <iostream>
#include <cstdlib> // Para rand(), srand() y atoi()
#include <string.h> // Para strings y sus opciones

using namespace std;

// CONSTANTES NUMÉRICAS

const int KNAME=32; // Número de caracteres en el nombre
const int KENEMIES=5; // Número de enemigos diferentes
const int KPOINTS=200; // Número de puntos de habilidad a repartir
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
const string HP = "Health points: "; // Cadena para mostrar la vida
const string HITPOINTS = "Hit points: "; // Cadena para mostrar los hit points
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

/* Almacena la información de las habilidades principales del héroe y del enemigo */
struct Core{
  int attack;
  int defense;
  int hp;
};

/* Diferentes razas del enemigo */
enum Breed{
  AXOLOTL,
  TROLL,
  ORC,
  HELLHOUND,
  DRAGON
};

/* Almacena la información del enemigo */
struct Enemy{
  Breed name;
  Core features;
};

/* Almacena la información del héroe */
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
bool checkName(string sname);
void setDistribution(Hero &hero);
bool checkDistribution(string distribution,float &attack,float &defense);
void printEnemy(Enemy enemy);
string enemyName(Enemy enemy);
void giveExp(Hero &hero,Enemy &enemy);
void printKills(Hero hero);

int rollDice(){
  return rand()%KDICE+1;
}

Hero createHero(){
  Hero hero;
    
  nameHero(hero); // Nombra al héroe
  setDistribution(hero); // Distribuye el ataque y la defensa del héroe
  hero.special = true; // Inicializamos su especial a true para que pueda ser usado
  hero.exp = 0;
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

/* Función para simular la pelea entre el héroe y un enemigo 
 * Parámetros: Héroe, enemigo e indicador por si el jugador ha seleccionado la opción 3 del menú
 */
void fight(Hero &hero,Enemy &enemy,bool speAtt){
  cout<<HERO_FIGHT_ENEMY<<endl; // Imprimimos la lucha del héroe contra el enemigo

  int attackHero = rollDice()*5; // Guardamos el ataque obtenido por el dado
  if(hero.special && speAtt){ // Si se ha selecionado la opción 3 del menú y el héroe tiene disponible el ataque especial...
    attackHero = attackHero * 3;
    hero.special = false;
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

/* Función para imprimir toda la información del héroe
 * Parámetros: Héroe
 */
void report(const Hero &hero){
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
      <<KILLS<<endl;
  printKills(hero); // Imprimimos las kills que ha logrado el héroe
}

/* Función para imprimir el menú del juego
 */
void showMenu(){
  cout << "[Options]" << endl
       << "1- Fight" << endl
       << "2- Run away" << endl
       << "3- Special" << endl 
       << "4- Report" << endl
       << "q- Quit" << endl
       << "Option: ";
}

/* Función para nombrar al héroe
 * Parámetro: Héroe
 */
void nameHero(Hero &hero){
  string sname; // Cadena auxiliar para el nombre
  bool isNameIncorrect = false; // Boolean para comprobar si el nombre es correcto
    
  do{
      cout<<EHN; // Pedimos nombre
      getline(cin,sname,'\n'); // Guardamos nombre en la string auxiliar
      
      if(sname.length() == 0 || !checkName(sname)){
        cout<<ERR_WRONG_NAME<<endl; // Emitimos error si el nombre es incorrecto
        isNameIncorrect = true; // La variable Boolean la ponemos como true para que vuelva a repetir el bucle
      }else{ // Le asignamos el nombre al héroe
        isNameIncorrect = false;
        if(sname.length() > KNAME - 1){ // Si el nombre que se quiere poner es mayor que KNAME...
          char auxs[KNAME]; // Cadena auxiliar 
          strncpy(auxs,sname.c_str(),KNAME-1); // Copiamos 31 elementos del nombre
          auxs[KNAME] = '\0'; // Ponemos a '\0' el elemento 32 del nombre
          strcpy(hero.name,auxs); // Nombramos al héroe con este nuevo nombre de 32 elementos
        }else
          strcpy(hero.name,sname.c_str());
      }
  }while(isNameIncorrect);
}

/* Función que comprueba si el nombre del héroe es correcto
 * Parámetro: String sname -> Cadena a comprobar
 * Returns:
    true: si el nombre es correcto
    false: si el nombre es erróneo
 */
bool checkName(string sname){
  if(!isalpha(sname[0])) // Comprobamos que el primer caracter sea alfanumérico
    return false;
  if(sname.length() > 1){
    for(unsigned i = 1;i < sname.length();i++){
      if(!isalnum(sname[i])){ // Comprobamos que no haya caracteres que no sean números, espacios en blanco o alfanuméricos.
        if(!isspace(sname[i])){
          return false;
          break;
        }
      }
    }
  }
  return true;
}

/* Función que implementa el ataque y defensa del héroe
 * Parámetro: Héroe
 */
void setDistribution(Hero &hero){
  string distribution; // Cadena auxiliar para la distribución
  bool isDistributionIncorrect = false; // Boolean para comprobar si la distribución es correcta
  float attack = 0; // Float para definir el ataque del héroe
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

/* Función para guardar la distribución ataque/defensa del héroe
 * Parámetros: Distribución elegida y floats de ataque y defensa.
 * Returns: 
    true: en caso de error
    false: cuando está todo correcto
 */
bool checkDistribution(string distribution,float &attack,float &defense){
  if(distribution.empty()){ // Si la cadena está vacía --> Error
    return true;
  }

  string satt; // Cadena auxiliar para ataque
  string sdef; // Cadena auxiliar para defensa
  size_t pos = distribution.find("/"); // Posición del caracter "/" que separa ataque y defensa

  satt = distribution.substr(0,pos); // Extraemos el ataque
  sdef = distribution.substr(pos+1); // Extraemos la defensa

  float iattack = atoi(satt.c_str()); // Convertimos el ataque a int
  float idefense = atoi(sdef.c_str()); // Convertim la defensa a int

  if(((iattack + idefense) != 100)) // Comprobamos las restricciones
    return true;

  if(iattack <= 0 || idefense <= 0)
      return true;

  attack = iattack/100; // Establecemos el porcentaje de ataque
  defense = idefense/100; // Establecemos el porcentaje de defensa

  return false;
}

/* Función para imprimir toda la información del enemigo por pantalla.
 * Parámetros: Enemigo a imprimir.
 */
void printEnemy(Enemy enemy){ // 
  cout
    <<ENEMY<<endl
    <<BREED<<enemyName(enemy)<<endl
    <<ATTACK<<enemy.features.attack<<endl
    <<DEFENSE<<enemy.features.defense<<endl
    <<HP<<enemy.features.hp<<endl;
}

/* Función que identifica la raza del enemigo y devuelve su nombre
 * Parámetros: Enemy
 * Returns: String
 */
string enemyName(Enemy enemy){
  if(enemy.name == AXOLOTL){
    return "Axolotl";
  }else if(enemy.name == TROLL){
    return "Troll";
  }else if(enemy.name == ORC){
    return "Orc";
  }else if(enemy.name == HELLHOUND){
    return "Hellhound";
  }else if(enemy.name == DRAGON){
    return "Dragon";
  }
  return "";
}

/* Función para dar experiencia al héroe
 * Parámetros: Héroe y enemigo
 */
void giveExp(Hero &hero,Enemy &enemy){
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

/* Función para imprimir por pantalla los enemigos derrotados
 * Parámetro: Héroe
 */
void printKills(Hero hero){
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
      if(option != '1' && option != '2' && option != '3' && option != '4' && option != 'q'){ //  Si la opción es errónea imprimimos el error por pantalla
        cout<<ERR_WRONG_OPTION<<endl;
      }else
        if(option == '1'){ // Si option == 1 --> Fight
          fight(hero,enemy,speAtt); // Lucha contra el enemigo
          canRunAway = true; // Activamos canRunAway pues ha habido una pelea
          if(enemy.features.hp == 0)
            enemy = createEnemy(); // Si la vida del enemigo llega a 0, creamos uno nuevo.
          if(hero.features.hp == 0){
            isOptionIncorrect = false;
          }
        }else if(option == '2'){ // Si option == 2 --> Run Away
          if(hero.runaways > 0 && canRunAway){ // Comprobamos que no haya huido antes y que le queden runaways
            cout<<RUNAWAY<<endl; // Imprimimos el éxito de la huída
            enemy = createEnemy(); // Creamos un nuevo enemigo
            hero.runaways--; // Le quitamos un runaway al héroe
            canRunAway = false; // Desactivamos el canRunAway
          }else
            cout<<ERR_CANNOT_RUN_AWAY<<endl; // Informamos de que no ha podido huir del enemigo
        }else if(option == '3'){ // Si option == 3 --> Special
          if(hero.special){
            speAtt = true; // Activamos la opción del ataque especial
            fight(hero,enemy,speAtt); // Llamamos al fight para que luche
            if(enemy.features.hp == 0) // Si el enemigo es derrotado con el ataque especial creamos otro nuevo
              enemy = createEnemy();
            speAtt = false; // Desactivamos la opción del ataque especial
            if(hero.features.hp == 0) // Si el héroe es derrotado termina el juego
              isOptionIncorrect = false; 
          }else
            cout<<ERR_SPECIAL_NOT_AVAILABLE<<endl;
        }else if(option == '4'){ // Si option == 4 --> Report
          report(hero);
        }else if(option == 'q'){ // Si option == 4 --> Quit
          isOptionIncorrect = false;
        }
    }while(isOptionIncorrect);
  }
}