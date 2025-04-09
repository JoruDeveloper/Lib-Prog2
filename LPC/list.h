#ifndef LIST_H_
#define LIST_H_
#include "node.h"
#include <stdexcept>
#include <iostream>
#include <sstream>
#include <string>
#include <limits>
// #include <cstddef>

template <class elem>
class List{
    private:
        Node<elem> *first;
        Node<elem> *last;
        int length;

    public:
    List();
    List(const List<elem> &L);
    ~List();
    void copy(const List<elem> &L);
    bool isEmpty() const;
    bool isElem(elem e);
    elem checkPos(int pos) const;
    int searchElement(const elem& e) const;
    void addElem(elem e, int pos);
    int delete_first_elem(elem e); // Elimina el primer elemento e y retorna su posición
    void delete_all_elem(elem e); // Elimina todos los elementos e
    void delete_all_repeated(); 
    void deleteNode(int pos);
    void modifyNode(elem e, int pos);
    void reverseList();
    void bubbleSort(bool asc);
    void empty();
    // Operadores Miembros
    List<elem>& operator=(const List<elem>&L);
    bool operator==(const List<elem> &L);
    elem operator[](int pos) const;
    bool operator>(const List<elem> &L);
    bool operator<(const List<elem> &L);
    // Set Get
    int getLength() const;
    elem& getElemRefAt(int pos);
    const elem& getElemRefAt(int pos) const;
};

template <class elem>
List<elem>::List() {
    this->first = NULL;
    this->last = NULL;
    this->length = 0;
}

template <class elem>
List<elem>::List(const List<elem> &L){
    this->first = NULL;
    this->last = NULL;
    this->length = 0;
    this->copy(L);
}

template <class elem>
List<elem>::~List() {
    this->empty();
}

template <class elem>
void List<elem>::copy(const List<elem> &L) {
    this->empty();
    Node<elem> *current = L.first;
    int pos = 0;
    while (current) {
        this->addElem(current->getInfo(), pos++);
        current = current->getNext();
    }
}

template <class elem>
bool List<elem>::isEmpty() const{
    return this->length == 0;
}

template <class elem>
bool List<elem>::isElem(elem e) {
    Node<elem> *current = this->first;
    while (current) {
        if (current->getInfo() == e) return true;
        current = current->getNext();
    }
    return false;
}

template <class elem>
elem List<elem>::checkPos(int pos) const{
    if (pos < 0 || pos >= this->length) throw std::out_of_range("Posici\u00f3n fuera de rango");
    Node<elem> *current = this->first;
    for (int i = 0; i < pos; i++) {
        current = current->getNext();
    }
    return current->getInfo();
}

template <class elem>
int List<elem>::searchElement(const elem& e) const {
    Node<elem> *current = this->first;
    int pos = 0;
    while (current != NULL) {
        // Asume que elem tiene operator== definido
        if (current->getInfo() == e) {
            return pos; // Elemento encontrado, retorna la posición actual
        }
        current = current->getNext();
        pos++;
    }
    return -1; // Elemento no encontrado después de recorrer toda la lista
}

template <class elem>
void List<elem>::addElem(elem e, int pos) {
    if (pos < 0 || pos > this->length) throw std::out_of_range("Posici\u00f3n fuera de rango");
    Node<elem> *newNode = new Node<elem>(e);
    if (pos == 0) {
        newNode->setNext(this->first);
        newNode->setPrev(NULL);
        if (this->first) this->first->setPrev(newNode);
        this->first = newNode;
        if (this->length == 0) this->last = newNode;
    } else {
        Node<elem> *current = this->first;
        for (int i = 0; i < pos - 1; i++) {
            current = current->getNext();
        }
        newNode->setNext(current->getNext());
        newNode->setPrev(current);
        if (newNode->getNext()) newNode->getNext()->setPrev(newNode);
        else this->last = newNode;
        current->setNext(newNode);
    }
    this->length++;
}

template <class elem>
int List<elem>::delete_first_elem(elem e) {
    Node<elem> *current = this->first;
    int pos = 0;

    while (current) {
        if (current->getInfo() == e) {
            if (current->getPrev()) current->getPrev()->setNext(current->getNext());
            else this->first = current->getNext(); // Si es el primero, actualizar `first`

            if (current->getNext()) current->getNext()->setPrev(current->getPrev());
            else this->last = current->getPrev(); // Si es el último, actualizar `last`

            delete current;
            this->length--;
            return pos;
        }
        current = current->getNext();
        pos++;
    }
    return -1;
}

template <class elem>
void List<elem>::delete_all_elem(elem e) {
    Node<elem> *current = this->first;
    while (current) {
        if (current->getInfo() == e) {
            Node<elem> *toDelete = current;
            if (current->getPrev()) current->getPrev()->setNext(current->getNext());
            else this->first = current->getNext();

            if (current->getNext()) current->getNext()->setPrev(current->getPrev());
            else this->last = current->getPrev();

            current = current->getNext();
            delete toDelete;
            this->length--;
        } else {
            current = current->getNext();
        }
    }
}

template <class elem>
void List<elem>::delete_all_repeated() {
    if (this->length < 2) {
        return;
    }
    Node<elem>* outerCurrent = this->first;
    int outerPos = 0;
    // Usar NULL en lugar de nullptr
    while (outerCurrent != NULL) {
        Node<elem>* innerCurrent = this->first;
        int innerPos = 0;
        bool isDuplicate = false;
        while (innerPos < outerPos) {
            if (innerCurrent->getInfo() == outerCurrent->getInfo()) {
                isDuplicate = true;
                break;
            }
            innerCurrent = innerCurrent->getNext();
            innerPos++;
             // Usar NULL en lugar de nullptr
             if(innerCurrent == NULL && innerPos < outerPos) {
                 throw std::logic_error("Inconsistencia detectada en delete_all_repeated (inner loop)");
             }
        }
        Node<elem>* nextNode = outerCurrent->getNext();
        if (isDuplicate) {
            // Asumiendo que deleteNode también usa NULL internamente
            this->deleteNode(outerPos);
        } else {
            outerPos++;
        }
        outerCurrent = nextNode;
    }
}


// void List<elem>::deleteNode(int pos) {
//     if (pos < 0 || pos >= this->length) throw std::out_of_range("Posicion fuera de rango");
//     Node<elem> *current = this->first;
//     for (int i = 0; i < pos; i++) {
//         current = current->getNext();
//     }
//     if (current->getPrev()) current->getPrev()->setNext(current->getNext());
//     else this->first = current->getNext();
//     if (current->getNext()) current->getNext()->setPrev(current->getPrev());
//     else this->last = current->getPrev();
//     delete current;
//     this->length--;
// }

template <class elem>
void List<elem>::deleteNode(int pos) {
    if (pos < 0 || pos >= this->length) throw std::out_of_range("Posicion fuera de rango en deleteNode");
    Node<elem> *current = this->first;
    for (int i = 0; i < pos; i++) {
        current = current->getNext();
    }

    if (current->getPrev()) {
        current->getPrev()->setNext(current->getNext());
    } else {
        this->first = current->getNext();
    }

    if (current->getNext()) {
        current->getNext()->setPrev(current->getPrev());
    } else {
        this->last = current->getPrev();
    }

    if (this->length == 1) {
        this->first = NULL;
        this->last = NULL;
    }

    delete current;
    this->length--;
}

template <class elem>
void List<elem>::modifyNode(elem e, int pos) {
    if (pos < 0 || pos >= length) throw std::out_of_range("Posici\u00f3n fuera de rango");
    Node<elem> *current = this->first;
    for (int i = 0; i < pos; i++) {
        current = current->getNext();
    }
    current->setInfo(e);
}

template <class elem>
void List<elem>::reverseList() {
    Node<elem> *current = this->first, *next = NULL;
    this->last = this->first;
    while (current) {
        next = current->getNext();
        current->setNext(current->getPrev());
        current->setPrev(next);
        if (next == NULL) this->first = current;
        current = next;
    }
}

template <class elem>
void List<elem>::bubbleSort(bool asc) {
    if (this->length < 2) return;
    for (int i = 0; i < this->length - 1; i++) {
        Node<elem> *current = first;
        for (int j = 0; j < this->length - i - 1; j++) {
            if ((asc && current->getInfo() > current->getNext()->getInfo()) || (!asc && current->getInfo() < current->getNext()->getInfo())) {
                elem temp = current->getInfo();
                current->setInfo(current->getNext()->getInfo());
                current->getNext()->setInfo(temp);
            }
            current = current->getNext();
        }
    }
}

template <class elem>
void List<elem>::empty() {
    while (this->first != NULL) {
        Node<elem> *toDelete = this->first;
        this->first = this->first->getNext();
        delete toDelete;
    }
    this->last = NULL;
    this->length = 0;
}

template <class elem>
List<elem>& List<elem>::operator=(const List<elem>& L) {
    if (this != &L) this->copy(L);
    return *this;
}

template <class elem>
bool List<elem>::operator==(const List<elem> &L) {
    if (this->length != L.length) return false;
    Node<elem> *current1 = this->first, *current2 = L.first;
    while (current1 && current2) {
        if (current1->getInfo() != current2->getInfo()) return false;
        current1 = current1->getNext();
        current2 = current2->getNext();
    }
    if((current1==NULL)&&(current2==NULL)) return true;

    return false;
}

template <class elem>
elem List<elem>::operator[](int pos) const{
    return this->checkPos(pos);
}

template <class elem>
bool List<elem>::operator>(const List<elem> &L) {
    return this->length > L.length;
}

template <class elem>
bool List<elem>::operator<(const List<elem> &L) {
    return this->length < L.length;
}

template <class elem>
int List<elem>::getLength() const{
    return this->length;
}

template <class elem>
elem& List<elem>::getElemRefAt(int pos) {
    if (pos < 0 || pos >= this->length) {
        throw std::out_of_range("Posicion fuera de rango en getElemRefAt");
    }
    Node<elem> *current = this->first;

    for (int i = 0; i < pos; ++i) {
        current = current->getNext();
    }

    return current->getInfoRef();
}

template <class elem>
const elem& List<elem>::getElemRefAt(int pos) const {

    if (pos < 0 || pos >= this->length) {
        throw std::out_of_range("Posicion fuera de rango en getElemRefAt (const)");
    }
    const Node<elem> *current = this->first;

    for (int i = 0; i < pos; ++i) {
        current = current->getNext();
    }

    return current->getInfoRef();
}

template <class elem>
void readColumnsToList(List<List<elem> >& resultList) {
    int columns;

    resultList.empty();

    if ((std::cin >> columns) && columns > 0) {

        std::cin.ignore();

            for (int i = 0; i < columns; ++i) {
                List<elem> columnList;
                resultList.addElem(columnList, i);
            }

        std::string linea;
        while (std::getline(std::cin, linea)) {
            if (linea.empty()) continue;
            
            std::istringstream ss(linea);
            elem value;
            int current_col_index = 0;

            while (ss >> value && current_col_index < columns) {
                
                    List<elem>& target_column_list = resultList.getElemRefAt(current_col_index);
                    
                    target_column_list.addElem(value, target_column_list.getLength());

            current_col_index++;
        }
    }
}
}

void readRowToList(List<std::string>& resultList) {
    resultList.empty();

    std::string line;
    if (std::getline(std::cin, line)) {

        if (!line.empty()) {

            std::istringstream ss(line);
            std::string item;


            while (ss >> item) {
                resultList.addElem(item, resultList.getLength());
            }
        }
    }
    // readColumnsToList<std::string>(L);
}

void readRowToListWithSeparator(List<std::string>& resultList, char delimiter) {
    resultList.empty(); // Vacía la lista antes de empezar

    std::string line;
    // Lee una línea completa de la entrada estándar
    if (std::getline(std::cin, line)) {

        // Solo procesa si la línea no está vacía
        if (!line.empty()) {
            std::string item;
            // Crea un stream a partir de la línea leída
            std::istringstream lineStream(line);

            // Lee del stream de la línea hasta encontrar el delimitador
            // std::getline(stream, string_destino, delimitador)
            while (std::getline(lineStream, item, delimiter)) {
                // Añade el elemento extraído al final de la lista
                resultList.addElem(item, resultList.getLength());
            }

            // Nota: Si la línea termina con el delimitador (ej: "a,b,"),
            // std::getline agregará una cadena vacía al final, lo cual
            // suele ser el comportamiento deseado para CSV.
            // Si la línea está vacía o solo contiene delimitadores,
            // se añadirán las correspondientes cadenas vacías.
        }
    }
}

void readRowToListWithQuotedFields(List<std::string>& resultList, char delimiter) {
    resultList.empty(); // Vacía la lista antes de empezar

    std::string line;
    // Lee una línea completa de la entrada estándar
    if (std::getline(std::cin, line)) {
        if (line.empty()) {
            return; // Línea vacía, lista vacía (ya está vacía)
        }

        std::string currentField; // Para construir el campo actual
        bool inQuotes = false;    // Flag para saber si estamos dentro de comillas

        for (size_t i = 0; i < line.length(); ++i) {
            char c = line[i];

            if (c == '"') {
                // Caso 1: Comillas dobles escapadas ("") dentro de un campo entrecomillado
                if (inQuotes && (i + 1 < line.length()) && line[i + 1] == '"') {
                    currentField += '"'; // Añade una comilla literal al campo
                    i++; // Salta la siguiente comilla
                }
                // Caso 2: Comilla de inicio o fin de campo
                else {
                    inQuotes = !inQuotes; // Cambia el estado (entra o sale de las comillas)
                    // No añadimos la comilla delimitadora al campo en sí
                }
            } else if (c == delimiter && !inQuotes) {
                // Caso 3: Delimitador encontrado FUERA de comillas
                // Fin del campo actual, añadirlo a la lista
                resultList.addElem(currentField, resultList.getLength());
                currentField.clear(); // Reinicia para el siguiente campo
            } else {
                // Caso 4: Carácter normal o delimitador DENTRO de comillas
                currentField += c; // Añade el carácter al campo actual
            }
        }

        // Después de procesar toda la línea, añadir el último campo acumulado
        resultList.addElem(currentField, resultList.getLength());
    }
}


int stringToInt(const std::string& str) {
    std::istringstream iss(str);
    int num;
    
    iss >> num;

    long long temp;
    std::istringstream iss_ll(str);
    iss_ll >> temp;
    
    // std::string cadena = "12123123";
    // int num = stringToInt(cadena);

    return num;
}

std::string cleanString(const std::string& dirtyString, const std::string& unwantedSymbol) {
    std::string cleanedString;

    for (size_t i = 0; i < dirtyString.size(); ++i) {
        bool isUnwanted = false;
        
        for (size_t j = 0; j < unwantedSymbol.size(); ++j) {
            if (dirtyString[i] == unwantedSymbol[j]) {
                isUnwanted = true;
                break;
            }
        }
        
        if (!isUnwanted) {
            cleanedString += dirtyString[i];
        }
    }
    
    return cleanedString;
}

template <class elem>
elem findMax(const List<elem>& list) {
    if (list.isEmpty()) {
        throw std::runtime_error("La lista está vacía");
    }

    elem max = list[0];
    
    for (int i = 1; i < list.getLength(); ++i) {
        if (list[i] > max) {
            max = list[i];
        }
    }
    
    return max;
}

template <class elem>
elem findMin(const List<elem>& list) {
    if (list.isEmpty()) {
        throw std::runtime_error("La lista está vacía");
    }

    elem min = list[0];

    for (int i = 1; i < list.getLength(); ++i) {
        if (list[i] < min) {
            min = list[i];
        }
    }
    
    return min;
}

#endif