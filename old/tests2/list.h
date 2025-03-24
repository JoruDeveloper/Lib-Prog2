#ifndef LIST_H_
#define LIST_H_
#include "node.h"

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
    bool isEmpty();
    bool isElem(elem e);
    elem checkPos(int pos);
    void addElem(elem e, int pos);
    int delete_first_elem(elem e); // Elimina el primer elemento e y retorna su posición
    void delete_all_elem(elem e); // Elimina todos los elementos e
    void deleteNode(int pos);
    void modifyNode(elem e, int pos);
    void reverseList();
    void bubbleSort(bool asc);
    void empty();
    // Operadores Miembros
    List<elem>& operator=(const List<elem>&L);
    bool operator==(const List<elem> &L);
    elem operator[](int pos);
    bool operator>(const List<elem> &L);
    bool operator<(const List<elem> &L);
    // Set Get
    int getLength();
};

#endif