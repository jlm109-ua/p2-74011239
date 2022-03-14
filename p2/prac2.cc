// Programación 2 - Práctica 2
// DNI: 74011239E
// Nombre: Juan Llinares Mauri

#include <iostream>
#include <vector>
#include <cctype>
#include <string.h>
#include <cstdlib>
#include <fstream>

using namespace std;

const int KMAXSTRING = 50;

const string EBT = "Enter book title: "; // Cadena para pedir el título del libro
const string EAUTH = "Enter author(s): "; // Cadena para pedir los autores del libro
const string EPY = "Enter publication year: "; // Cadena para pedir el año de publicación del libro
const string EP = "Enter price: "; // Cadena para pedir el precio del libro
const string EBI = "Enter book id: "; // Cadena para pedir el Id de un libro
const string EFN = "Enter filename: "; // Cadena para pedir el nombre del fichero


enum Error {
  ERR_OPTION,
  ERR_BOOK_TITLE,
  ERR_BOOK_AUTHORS,
  ERR_BOOK_DATE,
  ERR_BOOK_PRICE,
  ERR_ID,
  ERR_FILE,
  ERR_ARGS
};

struct Book {
  unsigned int id;
  string title;
  string authors;
  int year;
  string slug;
  float price;
};

struct BinBook {
  unsigned int id;
  char title[KMAXSTRING];
  char authors[KMAXSTRING];
  int year;
  char slug[KMAXSTRING];
  float price;
};

struct BookStore {
  string name;
  vector<Book> books;
  unsigned int nextId;
};

struct BinBookStore {
  char name[KMAXSTRING];
  unsigned int nextId;
};

void error(Error e) {
  switch (e) {
    case ERR_OPTION:
      cout << "ERROR: wrong menu option" << endl;
      break;
    case ERR_BOOK_TITLE:
      cout << "ERROR: wrong book title" << endl;
      break;
    case ERR_BOOK_AUTHORS:
      cout << "ERROR: wrong author(s)" << endl;
      break;
    case ERR_BOOK_DATE:
      cout << "ERROR: wrong date" << endl;
      break;
    case ERR_BOOK_PRICE:
      cout << "ERROR: wrong price" << endl;
      break;
    case ERR_ID:
      cout << "ERROR: wrong book id" << endl;
      break;
    case ERR_FILE:
      cout << "ERROR: cannot open file" << endl;
      break;
    case ERR_ARGS:
      cout << "ERROR: wrong arguments" << endl;
      break;
  }
}

/* Métodos usados en el programa */

void showMainMenu();
void showCatalog(const BookStore &bookStore);
void showExtendedCatalog(const BookStore &bookStore);
void addBook(BookStore &bookStore);
void deleteBook(BookStore &bookStore);
void importExportMenu(BookStore &bookStore);
void importFromCsv(BookStore &bookStore);
void exportToCsv(const BookStore &bookStore);
void loadData(BookStore &bookStore);
void saveData(const BookStore &bookStore);
bool checkString(string saux);
string createSlug(string title);
bool checkIsNumber(string saux);

void showMainMenu() {
  cout << "[Options]" << endl
       << "1- Show catalog" << endl
       << "2- Show extended catalog" << endl
       << "3- Add book" << endl
       << "4- Delete book" << endl
       << "5- Import/export" << endl
       << "q- Quit" << endl
       << "Option: ";
}

/* Función para mostrar el catálogo
 * Parámetro: BookStore -> Variable que almacena los books en un vector
 */
void showCatalog(const BookStore &bookStore) {
    for(unsigned i=0;i<bookStore.books.size();i++){
      cout << bookStore.books[i].id << ". " << bookStore.books[i].title << " (" << bookStore.books[i].year << "), " << bookStore.books[i].price << endl;
    }
}

/* Función para mostrar el catálogo de forma extensa
 * Parámetro: BookStore -> Variable que almacena los books en un vector
 */
void showExtendedCatalog(const BookStore &bookStore) {
    for(unsigned i=0;i<bookStore.books.size();i++){
        cout << '"' << bookStore.books[i].title << '"' << "," << '"' << bookStore.books[i].authors << '"' << "," << bookStore.books[i].year << "," << '"' << bookStore.books[i].slug << '"' << "," << bookStore.books[i].price << endl;
    }
}

/* Función que añade un libro nuevo al programa
 * Parámetro: bookStore -> Variable para almacenar los books
 */
void addBook(BookStore &bookStore) {
    Book b;
    string saux; // String auxiliar para las comprobaciones
    bool wrongData = false; // Boleano para repetir los do-while en caso de obtener datos erróneos del usuario

    do{
        cout << EBT;
        getline(cin,saux,'\n'); // Pedimos y guardamos el título en la strin auxiliar
        if(!checkString(saux) || saux.empty()){ // Hacemos las comprobaciones
          error(ERR_BOOK_TITLE); // Emitimos error si contiene algún caracter incorrecto
          wrongData = true; // Ponemos el booleano a true para que repita el do-while
        }else{
          wrongData = false;
        }
    }while(wrongData);

    b.title = saux; // Copiamos el contenido de la string auxiliar al título del libro

    do{ // Repetimos lo que hicimos con el título, pero esta vez con autores
        cout << EAUTH;
        getline(cin,saux,'\n');
        if(!checkString(saux) || saux.empty()){
          error(ERR_BOOK_AUTHORS);
          wrongData = true;
        }else{
          wrongData = false;
        }
    }while(wrongData);

    b.authors = saux; // Introducimos los autores al libro

    do{ // Repetimos lo que hicimos con el título, pero esta vez con la fecha de publicación
        cout << EPY;
        cin >> saux;
        cin.get();
        if(!checkIsNumber(saux) || saux.empty()){ // Si no es un número o la cadena está vacía...
            error(ERR_BOOK_DATE);
            wrongData = true;
        }else if(checkIsNumber(saux)){ // Si es un número...
            if(stoi(saux)<1440 || stoi(saux)>2022){ // Comprobamos que las fechas sean correctas
              error(ERR_BOOK_DATE);
              wrongData = true;
            }else{
              wrongData = false;
            }
        }
    }while(wrongData);

    b.year = stoi(saux); // Convertimos la string a int y lo guardamos en el libro

    do{ // Repetimos lo que hicimos con la fecha de publicación, pero esta vez con el precio
        cout << EP;
        cin >> saux;
        cin.get();
        if(!checkIsNumber(saux) || saux.empty()){ // Si no es un número o la cadena está vacía...
            error(ERR_BOOK_PRICE);
            wrongData = true;
        }else if(checkIsNumber(saux)){ // Si es un número...
            if(stof(saux)<= 0){ // Comprobamos que el precio sea correcto
                error(ERR_BOOK_PRICE);
                wrongData = true;
            }else{
              wrongData = false;
            }
        }
    }while(wrongData);

    b.price = stof(saux); // Convertimos la string a float y lo guardamos en el libro
    b.slug = createSlug(b.title);
    b.id = bookStore.nextId;
    bookStore.nextId++; // Aumentamos el Id general para los siguientes libros

    bookStore.books.push_back(b); // Añadimos el libro a la colección
}

/* Función para eliminar un libro a partir de su id
 * Parámetro: bookStore -> Variable que almacena los libros
 */
void deleteBook(BookStore &bookStore) {
    unsigned id = 0;
    bool bookDeleted = false; // Booleano para comprobar si se ha eliminado algún libro
    cout << EBI;
    cin >> id; // Pedimos y guardamos el id del libro
    
    for(unsigned i = 0;i < bookStore.books.size();i++){ // Buscamos el libro con el id especificado 
        if( bookStore.books[i].id == id ){
            bookStore.books.erase(bookStore.books.begin() + i); // Eliminamos el libro
            bookDeleted = true;
            break;
        }
    }

    if(!bookDeleted){ // Si no está avisamos al usuario y volemos al menú principal
        error(ERR_ID);
    }
}

/* Función para imprimir el menú "Import/export"
 * Parámetro: bookStore -> Variable donde almacenamos los libros
 */
void importExportMenu(BookStore &bookStore) {
  cout << "[Import/export options]" << endl
       << "1- Import from CSV" << endl
       << "2- Export to CSV" << endl
       << "3- Load data" << endl
       << "4- Save data" << endl
       << "b- Back to main menu" << endl
       << "Option: ";
}

/* Función para importar libros desde Csv
 * Parámetro: bookStore -> Variable donde almacenamos los libros
 */
void importFromCsv(BookStore &bookStore){
  string filename;
  cout << EFN;
  getline(cin,filename,'\n');

  ifstream ifs(filename);

  if(ifs.is_open()){ // Si el fichero se ha podido abrir...
    string fileline; // String auxiliar para procesar las líneas que contiene el fichero
    while(getline(ifs,fileline)){ // Mientras haya líneas en el fichero...
      Book b;
      string aux; // Variable auxiliar para hacer las comprobaciones
      bool isCorrect = true; // Variable para comprobar que todos los campos del libro son correctos 
      
      fileline = fileline.substr(1); // Quitamos el primer '"'
      size_t pos = fileline.find('"'); // Buscamos el segundo '"'
      aux = fileline.substr(0,pos-1); // Cogemos el título del libro
      if(!checkString(aux) || aux.empty()){ // Comprobamos el título
        error(ERR_BOOK_TITLE);
        isCorrect = false;
      }else{
        b.title = aux;
      }

      if(isCorrect){
        fileline = fileline.substr(pos+3); // Quitamos la parte del título de la cadena y los caracteres ',"' para acceder directamente al/los autor/es
        pos = fileline.find('"');
        aux = fileline.substr(0,pos-1); // Cogemos al/los autor/es
        if(!checkString(aux) || aux.empty()){ // Comprobamos el los autores
          error(ERR_BOOK_AUTHORS);
          isCorrect = false;
        }else{
          b.authors = aux;
        }

        if(isCorrect){
          fileline = fileline.substr(pos+2); // Quitamos la parte de los autores
          aux = fileline.substr(0,4); // Cogemos el año del libro
          if(!checkIsNumber(aux)){ // Si no es un número...
            error(ERR_BOOK_DATE);
            isCorrect = false;
        }else if(checkIsNumber(saux)){
            if(stoi(aux)<1440 || stoi(aux)>2022){ // Comprobamos que las fechas sean correctas
              error(ERR_BOOK_DATE);
              isCorrect = false;
            }else{
              b.price = stoi(aux);
            }
        }

          if(isCorrect){
            fileline = fileline.substr(7); // Quitamos la parte del año
            pos = fileline.find('"');
            b.slug = fileline.substr(0,pos-1); // Cogemos el slug del libro
            fileline = fileline.substr(pos+2); // Quitamos la parte del slug
            aux = fileline; // Cogemos el precio del libro
            if(!checkIsNumber(aux)){ // Si no es un número...
              error(ERR_BOOK_PRICE);
              isCorrect = false;
            }else if(checkIsNumber(saux)){
              if(stof(aux)<= 0){ // Comprobamos que el precio sea correcto
                error(ERR_BOOK_PRICE);
                isCorrect = false;
              }else{
                b.price = stof(aux);
                bookStore.books.push_back(b); // Añadimos el libro
              }
            }
          }
        }  
      }
    }
  
    ifs.close();
  }else{
    error(ERR_FILE);
  }

}

void exportToCsv(const BookStore &bookStore){
}

void loadData(BookStore &bookStore){
}

void saveData(const BookStore &bookStore){
}

/* Función auxiliar que comprueba todos los caracteres del título de un libro
 * Parámetro: string -> Título a comprobar
 * Returns:
    - true: Si está todo correcto
    - false: Si hay algún caracter erróneo
 */
bool checkString(string saux){
    for(unsigned i = 0;i < saux.length();i++){
        if(isalnum(saux[i]) || isblank(saux[i]) || saux[i] == ':' || saux[i] == '-' || saux[i] == ','){
        }else{
            return false;
        }
    }
    return true;
}

/* Función para crear el slug del libro a partir de su título
 * Parámetro: string -> Título del libro
 */
string createSlug(string title){
    string slug = "";

    for(unsigned i = 0;i < title.size();i++){
      if(isalpha(title[i])) // Si es una letra lo pasamos a minúscula
            slug += tolower(title[i]);
        else if(isdigit(title[i])) // Si es un número lo añadimos directamente
            slug += title[i];
        else // Si no es ni número ni letra añadimos un guión
            slug += '-';
    }

    for(int i = slug.length();i >= 0 ;i--){ // Comprobamos los guiones que pueda haber repetidos
        if(slug[i] == '-' && slug[i-1] == '-')
             slug.erase(i,1); // Borra el guión // SI NO FUNCIONA PROBAR A LA INVERSA
    }
    slug.push_back('\0');

    return slug;
}

/* Función que comprueba si la cadena pasada como parámetro es un número tanto int como float
 * Parámetro: String -> Cadena a comprobar
 * Returns:
   - true: si es un número
   - false: en cualquier otro caso
 */
bool checkIsNumber(string saux){
  for(unsigned i = 0;i < saux.length();i++){
    if(!isdigit(saux[i])){
      if(saux[i]!='.'){
        return false;
      }
    }
  }

  return true;
}

/* Función para manejar los argumentos del programa
 * Parámetros:
   - Int -> Número de argumentos
   - Char* -> Array con los argumentos 
 */
void checkArgs(int argc,char *argv[]){
  if(argc%2!=0){
    if(argc>5){
      error(ERR_ARGS);
    }else{
      if(argc==3){
        if(strcmp(argv[1],"-l")==0){
          // Terminar
        }else if(strcmp(argv[1],"-i")==0){
          // Terminar
        }else{
          error(ERR_ARGS);
        }
      }else if(argc==5){
        if(strcmp(argv[1],"-l")==0){
          // Terminar
        }else if(strcmp(argv[1],"-i")==0){
          // Terminar
        }else if(strcmp(argv[3],"-l")==0){
          // Terminar
        }else if(strcmp(argv[3],"-i")==0){
          // Terminar
        }else{
          error(ERR_ARGS);
        }
      }
    }
  }else if(argc!=1){
    error(ERR_ARGS);
  }
}

int main(int argc, char *argv[]) {
  BookStore bookStore;
  bookStore.name = "My Book Store";
  bookStore.nextId = 1;

  checkArgs(argc,argv);
    
  char option;
  do {
    showMainMenu();
    cin >> option;
    cin.get();

    switch (option) {
      case '1':
        showCatalog(bookStore);
        break;
      case '2':
        showExtendedCatalog(bookStore);
        break;
      case '3':
        addBook(bookStore);
        break;
      case '4':
        deleteBook(bookStore);
        break;
      case '5':
        do{
          importExportMenu(bookStore);
          cin >> option;
          cin.get();
          switch(option){
            case '1':
              importFromCsv(bookStore);
              break;
            case '2':
              exportToCsv(bookStore);
              break;
            case '3':
              loadData(bookStore);
              break;
            case '4':
              saveData(bookStore);
              break;
            case 'b':
              break;
            default:
              error(ERR_OPTION);
          }
        }while(option != 'b');
        break;
      case 'q':
        break;
      default:
        error(ERR_OPTION);
    }
  } while (option != 'q');

  return 0;
}
