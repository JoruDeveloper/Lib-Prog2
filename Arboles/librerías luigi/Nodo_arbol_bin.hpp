#ifndef nodo_arbol_bin_h
#define nodo_arbol_bin_h

/*
Autor: Luigi Quero C.I: 30.009.785
*/

template <class E>
class Nodo_ab{
	private:
		E elem;
		Nodo_ab<E>* hijo_izq;
		Nodo_ab<E>* hijo_der;
	public:
		Nodo_ab(E _elem);
		Nodo_ab(E _elem, Nodo_ab<E>* _izq, Nodo_ab<E>* _der);
		void set_elem(E _elem);
		void set_hijo_izq(Nodo_ab<E>* _izq);
		void set_hijo_der(Nodo_ab<E>* _der);
		void set_hijos(Nodo_ab<E>* _izq, Nodo_ab<E>* _der);
		E get_elem();
		Nodo_ab<E>* get_hijo_izq();
		Nodo_ab<E>* get_hijo_der();
};

template <class E>
Nodo_ab<E> :: Nodo_ab(E _elem){
	elem = _elem;
	hijo_izq = 0;
	hijo_der = 0;
}

template <class E>
Nodo_ab<E> :: Nodo_ab(E _elem, Nodo_ab<E>* _izq, Nodo_ab<E>* _der){
	elem = _elem;
	hijo_izq = _izq;
	hijo_der = _der;
}

template <class E>
void Nodo_ab<E> :: set_elem(E _elem){
	elem = _elem;
}

template <class E>
void Nodo_ab<E> :: set_hijo_izq(Nodo_ab<E>* _izq){
	hijo_izq = _izq;
}

template <class E>
void Nodo_ab<E> :: set_hijo_der(Nodo_ab<E>* _der){
	hijo_der = _der;
}

template <class E>
void Nodo_ab<E> :: set_hijos(Nodo_ab<E>* _izq, Nodo_ab<E>* _der){
	hijo_izq = _izq;
	hijo_der = _der;
}

template <class E>
E Nodo_ab<E> :: get_elem(){
	return elem;
}

template <class E>
Nodo_ab<E>* Nodo_ab<E> :: get_hijo_izq(){
	return hijo_izq;
}

template <class E>
Nodo_ab<E>* Nodo_ab<E> :: get_hijo_der(){
	return hijo_der;
}

#endif