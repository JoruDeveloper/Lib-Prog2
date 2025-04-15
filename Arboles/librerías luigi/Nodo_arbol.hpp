#ifndef nodo_arbol_h
#define nodo_arbol_h

/*
Autor: Luigi Quero C.I: 30.009.785
*/

template <class E>
class Nodo_arbol{
	private:
		E elem;
		Nodo_arbol<E>* hijo_izq;
		Nodo_arbol<E>* hermano_der;
	public:
		Nodo_arbol(E elem);
		Nodo_arbol(E elem, Nodo_arbol<E>* izq, Nodo_arbol<E>* der);
		E get_elem();
		Nodo_arbol<E>* get_hijo_izq();
		Nodo_arbol<E>* get_hermano_der();
		void set_elem(E _elem);
		void set_hijo_izq(Nodo_arbol<E>* izq);
		void set_hermano_der(Nodo_arbol<E>* der);
};

template <class E>
Nodo_arbol<E> :: Nodo_arbol(E _elem){
	elem = _elem;
	hijo_izq = 0;
	hermano_der = 0;
}

template <class E>
Nodo_arbol<E> :: Nodo_arbol(E _elem, Nodo_arbol<E>* izq, Nodo_arbol<E>* der){
	elem = _elem;
	hijo_izq = izq;
	hermano_der = der;
}

template <class E>
E Nodo_arbol<E> :: get_elem(){
	return elem;
}

template <class E>
Nodo_arbol<E>* Nodo_arbol<E> :: get_hijo_izq(){
	return hijo_izq;
}

template <class E>
Nodo_arbol<E>* Nodo_arbol<E> :: get_hermano_der(){
	return hermano_der;
}

template <class E>
void Nodo_arbol<E> :: set_elem(E _elem){
	elem = _elem;
}

template <class E>
void Nodo_arbol<E> :: set_hijo_izq(Nodo_arbol<E>* izq){
	hijo_izq = izq;
}

template <class E>
void Nodo_arbol<E> :: set_hermano_der(Nodo_arbol<E>* der){
	hermano_der = der;
}

#endif