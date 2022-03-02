// Programación 2 - Práctica 2
// DNI: 74011239E
// Nombre: Juan Llinares Mauri

#include <iostream>
#include <vector>
#include <cctype>
#include <string.h>
#include <cstdlib)

using namespace std;

const int KMAXSTRING = 50;

const string EBT = "Enter book title: "; // Cadena para pedir el título del libro
const string EAUTH = "Enter author(s): "; // Cadena para pedir los autores del libro
const string EPY = "Enter publication year: "; // Cadena para pedir el año de publicación del libro
const string EP = "Enter price: "; // Cadena para pedir el precio del libro
const string EBI = "Enter book id: "; // Cadena para pedir el Id de un libro


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
    for(Book b : bookStore.books){ // Para cada libro en books...
        cout << b.id << ". " << b.title << " (" << b.year << "), " << b.price; // <<endl? PROBAR
    }
}

/* Función para mostrar el catálogo de forma extensa
 * Parámetro: BookStore -> Variable que almacena los books en un vector
 */
void showExtendedCatalog(const BookStore &bookStore) {
    for(Book b : bookStore.books){
        cout << '"' << b.title << '"' << "," << '"' << b.author << '"' << "," << b.year << "," << '"' << b.slug << '"' << "," << b.price; // <<endl? PROBAR
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
        cout << EBT << endl;
        cin >> saux; // Pedimos y guardamos el título en la strin auxiliar
        if(!checkString(saux) || saux.empty()){ // Hacemos las comprobaciones
            error(ERR_BOOK_TITLE); // Emitimos error si contiene algún caracter incorrecto
            wrongData = true; // Ponemos el booleano a true para que repita el do-while
        }
    }while(wrongData);

    strcpy(b.title,saux); // Copiamos el contenido de la string auxiliar al título del libro

    do{ // Repetimos lo que hicimos con el título, pero esta vez con autores
        cout << EAUTH << endl;
        cin >> saux;
        if(!checkString(saux) || saux.empty()){
            error(ERR_BOOK_AUTHORS);
            wrongData = true;
        }
    }while(wrongData);

    strcpy(b.authors,saux); // Introducimos los autores al libro

    do{ // Repetimos lo que hicimos con el título, pero esta vez con la fecha de publicación
        cout << EPY << endl;
        cin >> saux;
        if(!isdigit(saux) || saux.empty()){ // Si no es un número o la cadena está vacía...
            error(ERR_BOOK_DATE);
            wrongData = true;
        }else if(isdigit(saux)){ // Si es un número...
            if(stoi(saux)<1440 || stoi(saux)>2022) // Comprobamos que las fechas sean correctas
                wrongData = true;
        }
    }while(wrongData);

    b.year = stoi(saux); // Convertimos la string a int y lo guardamos en el libro

    do{ // Repetimos lo que hicimos con la fecha de publicación, pero esta vez con el precio
        cout << EP << endl;
        cin >> saux;
        if(!isdigit(saux) || saux.empty()){ // Si no es un número o la cadena está vacía...
            error(ERR_BOOK_PRICE);
            wrongData = true;
        }else if(isdigit(saux)){ // Si es un número...
            if(stof(saux)<= 0) // Comprobamos que el precio sea correcto
                wrongData = true;
        }
    }while(wrongData);

    b.price = stof(saux); // Convertimos la string a float y lo guardamos en el libro
    strcpy(b.slug,createSlug(b.title));
    b.id = nextId;
    nextId++;

    bookStore.books.push_back(b);
}

/* Función para eliminar un libro a partir de su id
 * Parámetro: bookStore -> Variable que almacena los libros
 */
void deleteBook(BookStore &bookStore) {
    int id = 0;
    bool bookDeleted = false; // Booleano para comprobar si se ha eliminado algún libro
    cout << EBI << endl;
    cin >> id; // Pedimos y guardamos el id del libro
    
    for(int i = 0;i < bookStore.books.size();i++){ // Buscamos el libro con el id especificado 
        if( bookStore.books[i].id == id ){
            bookStore.books[i].erase(bookStore.books.begin() + i); // Eliminamos el libro
            bookDeleted = true;
            break;
        }
    }

    if(!bookDeleted){ // Si no está avisamos al usuario y volemos al menú principal
        cout << error(ERR_ID) << endl;
    }
}

void importExportMenu(BookStore &bookStore) {
}

void importFromCsv(BookStore &bookStore){
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
    for(int i = 0;i < saux.length();i++){
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

    for(char c : title){ // Para cada caracter de la string...
        if(isalpha(c)) // Si es una letra lo pasamos a minúscula
            slug += tolower(c);
        else if(isdigit(c)) // Si es un número lo añadimos directamente
            slug += c;
        else // Si no es ni número ni letra añadimos un guión
            slug += '-';
    }

    for(int i = 0;i < slug.length;i++){ // Comprobamos los guiones que pueda haber repetidos
        if(slug[i] == '-' && slug[i+1] == '-')
             slug.erase(i,1); // Borra el guión // SI NO FUNCIONA PROBAR A LA INVERSA
    }
}

int main(int argc, char *argv[]) {
  BookStore bookStore;
  bookStore.name = "My Book Store";
  bookStore.nextId = 1;

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
        importExportMenu(bookStore);
        break;
      case 'q':
        break;
      default:
        error(ERR_OPTION);
    }
  } while (option != 'q');

  return 0;
}
