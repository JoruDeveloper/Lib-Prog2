#ifndef Arbol_bin_h
#define Arbol_bin_h

/*
Autor: Luigi Quero C.I: 30.009.785
*/

#include <list>
#include <queue>
#include "Nodo_arbol_bin.hpp"

using namespace std;

template <class E>
class Arbol_bin{
	private:
		Nodo_ab<E>* raiz;
		Nodo_ab<E>* COPIAR_NODOS(Nodo_ab<E>* _nod);
		void PRE_ORDEN(Nodo_ab<E>* nod, list<E>& l);
		void IN_ORDEN(Nodo_ab<E>* nod, list<E>& l);
		void POST_ORDEN(Nodo_ab<E>* nod, list<E>& l);
		void INSERT(E& elem, Nodo_ab<E>* p);
		bool ESTA(Nodo_ab<E>* p, E& elem, bool& ban);
		Nodo_ab<E>* BUSCAR_NODO(Nodo_ab<E>** padre, Nodo_ab<E>* p, E& elem);
		void REEMPLAZAR_NODO(Nodo_ab<E>* padre, Nodo_ab<E>* p);
		void ELIMINAR_HOJA(Nodo_ab<E>* padre, Nodo_ab<E>* hoja);
		void ELIMINAR(Nodo_ab<E>* padre, Nodo_ab<E>* p);
		void CREAR_IN_PRE_ORDEN(Nodo_ab<E>* p, list<E>& in_orden, list<E>& pre_orden, bool lado);
		void LADOS_IN_PRE(list<E>& in_orden, list<E>& pre_orden, list<E>&  in_orden_izq, list<E>& pre_orden_izq, list<E>&  in_orden_der, list<E>& pre_orden_der);
		Nodo_ab<E>* LEER_IN_PRE(list<E>& in_orden, list<E>& pre_orden);
		void CREAR_IN_POST_ORDEN(Nodo_ab<E>* p, list<E>& in_orden, list<E>& post_orden, bool lado);
		void LADOS_IN_POST(list<E>& in_orden, list<E>& post_orden, list<E>&  in_orden_der, list<E>& post_orden_der, list<E>&  in_orden_izq, list<E>& post_orden_izq);
		void RECORRIDO_LV(Nodo_ab<E>* p, list<E>& li);
		void RECORRIDO_LV_EXACTO(Nodo_ab<E>* p, list<int>& li);
		void ALTURA(Nodo_ab<E>* p, int& lv_act, int& lv_max);
		void HOJAS(Nodo_ab<E>* p, list<E>& li);
		void CAMINO_NOD(Nodo_ab<E>* p, list<E>& li, E& elem, bool& encont);
		void CAMINO_NOD_NOD(Nodo_ab<E>* p, list<E>& cam_1, list<E>& cam_2, E& elem_1, E& elem_2, bool& encont_1, bool& encont_2);
		void CAMINO_ENTRE_HOJAS(list<E>& diametro, list<E> rama_1, list<E> rama_2);
		void CAMINO_MAS_LARGO(list<E>& diametro, list<E>& rama_1, list<E>& rama_2, list<E>& rama_aux);
		void DIAMETRO(Nodo_ab<E>* p, list<E>& diametro, list<E>& rama_1, list<E>& rama_2, list<E>& rama_aux);
		void DESTRUCTOR(Nodo_ab<E>* p);	
	public:
		Arbol_bin();
		Arbol_bin(E elem);
		Arbol_bin(E elem, Arbol_bin<E> a1, Arbol_bin<E> a2);
		void copiar(Arbol_bin<E>* a);
		bool es_vacio();
		E get_raiz();
		Arbol_bin<E> hijo_izq();
		Arbol_bin<E> hijo_der();
		list<E> pre_orden();
		list<E> in_orden();
		list<E> post_orden();
		void insert(E elem);
		bool esta(E elem);
		void eliminar(E elem);
		void crear_in_pre(list<E> in_orden, list<E> pre_orden);
		void crear_in_pre_2(list<E> in_orden, list<E> pre_orden);
		void crear_in_post(list<E> in_orden, list<E> post_orden);
		list<E> recorrido_lv();
		list<int> recorrido_lv_exacto(int lv);
		int altura();
		list<E> hojas();
		list<E> camino_nod(E elem);
		list<E> camino_nod_nod(E elem_1, E elem_2);
		E ancestro(E elem_1, E elem_2);
		list<E> diametro();
		~Arbol_bin();
};

template <class E>
Arbol_bin<E> :: Arbol_bin(){
	raiz = 0;
}

template <class E>
Arbol_bin<E> :: Arbol_bin(E elem){
	raiz = new Nodo_ab<E>(elem);
}

template <class E>
Nodo_ab<E>* Arbol_bin<E> :: COPIAR_NODOS(Nodo_ab<E>* _nod){
	Nodo_ab<E>* nod;
	
	if(_nod == 0){
		return 0;
	}else{
		nod = new Nodo_ab<E>(_nod->get_elem(), COPIAR_NODOS(_nod->get_hijo_izq()), COPIAR_NODOS(_nod->get_hijo_der()));
		return nod;
	}
}

template <class E>
Arbol_bin<E> :: Arbol_bin(E elem, Arbol_bin<E> _izq, Arbol_bin<E> _der){
	raiz = new Nodo_ab<E>(elem, COPIAR_NODOS(_izq.raiz), COPIAR_NODOS(_der.raiz));
}

template <class E>
void Arbol_bin<E> :: copiar(Arbol_bin<E>* a){
	raiz = COPIAR_NODOS(a.raiz);
}

template <class E>
bool Arbol_bin<E> :: es_vacio(){
	return (raiz == 0);
}

template <class E>
E Arbol_bin<E> :: get_raiz(){
	return raiz->get_elem();
}

template <class E>
Arbol_bin<E> Arbol_bin<E> :: hijo_izq(){
	Arbol_bin<E> hijo;
	
	if(raiz != 0){
		hijo.raiz = COPIAR_NODOS(raiz->get_hijo_izq());
	}else{
		hijo.raiz = 0;
	}
	return hijo;
}

template <class E>
Arbol_bin<E> Arbol_bin<E> :: hijo_der(){
	Arbol_bin<E> hijo;
	
	if(raiz != 0){
		hijo.raiz = COPIAR_NODOS(raiz->get_hijo_der());
	}else{
		hijo.raiz = 0;
	}
	return hijo;
}

template <class E>
void Arbol_bin<E> :: PRE_ORDEN(Nodo_ab<E>* nod, list<E>& l){
	if(nod != 0){
		l.push_back(nod->get_elem());
		PRE_ORDEN(nod->get_hijo_izq(), l);
		PRE_ORDEN(nod->get_hijo_der(), l);
	}
}

template <class E>
void Arbol_bin<E> :: IN_ORDEN(Nodo_ab<E>* nod, list<E>& l){
	if(nod != 0){
		IN_ORDEN(nod->get_hijo_izq(), l);
		l.push_back(nod->get_elem());		
		IN_ORDEN(nod->get_hijo_der(), l);
	}
}

template <class E>
void Arbol_bin<E> :: POST_ORDEN(Nodo_ab<E>* nod, list<E>& l){
	if(nod != 0){
		POST_ORDEN(nod->get_hijo_izq(), l);		
		POST_ORDEN(nod->get_hijo_der(), l);
		l.push_back(nod->get_elem());
	}
}

template <class E>
list<E> Arbol_bin<E> :: pre_orden(){
	list<E> L;
	PRE_ORDEN(this->raiz, L);
	return L;
}

template <class E>
list<E> Arbol_bin<E> :: in_orden(){
	list<E> L;
	IN_ORDEN(this->raiz, L);
	return L;
}

template <class E>
list<E> Arbol_bin<E> :: post_orden(){
	list<E> L;
	POST_ORDEN(this->raiz, L);
	return L;
}

template <class E>
void Arbol_bin<E> :: INSERT(E& elem, Nodo_ab<E>* p){
	if(p != 0){
		if(p->get_elem() > elem){
			if(p->get_hijo_izq() == 0){
				p->set_hijo_izq(new Nodo_ab<E>(elem));
			}else{
				INSERT(elem, p->get_hijo_izq());
			}
		}else{
			if(p->get_hijo_der() == 0){
				p->set_hijo_der(new Nodo_ab<E>(elem));
			}else{
				INSERT(elem, p->get_hijo_der());
			}
		}
	}
}

template <class E>
void Arbol_bin<E> :: insert(E elem){
	if(this->raiz == 0){
		raiz = new Nodo_ab<E>(elem);
	}else{
		INSERT(elem, this->raiz);
	}	
}

template <class E>
bool Arbol_bin<E> :: ESTA(Nodo_ab<E>* p, E& elem, bool& ban){
	if(p != 0){
		if(p->get_elem() == elem){
			ban = true;
		}else if(p->get_elem() > elem){
			return ESTA(p->get_hijo_izq(), elem, ban);
		}else{
			return ESTA(p->get_hijo_der(), elem, ban);
		}
	}
	return ban;
}

template <class E>
bool Arbol_bin<E> :: esta(E elem){
	bool ban = false;
	return ESTA(this->raiz, elem, ban);
}

template <class E>
Nodo_ab<E>* Arbol_bin<E> :: BUSCAR_NODO(Nodo_ab<E>** padre, Nodo_ab<E>* p, E& elem){
	if(p != 0){
		if(p->get_elem() == elem){
			return p;
		}else{
			*padre = p;
			
			if(p->get_elem() > elem){
				return BUSCAR_NODO(padre, p->get_hijo_izq(), elem);
			}else{
				return BUSCAR_NODO(padre, p->get_hijo_der(), elem);
			}
		}
	}
	*padre = 0;
	return 0;
}

template <class E>
void Arbol_bin<E> :: REEMPLAZAR_NODO(Nodo_ab<E>* padre, Nodo_ab<E>* p){
	if(padre == 0){
		if(p->get_hijo_izq() != 0){
			raiz = p->get_hijo_izq();
		
		}else{
			raiz = p->get_hijo_der();
		}
	}else{
		if(p->get_hijo_izq() != 0){
			if(padre->get_hijo_izq() == p){
				padre->set_hijo_izq(p->get_hijo_izq());
			}else{
				padre->set_hijo_der(p->get_hijo_izq());
			}
		}else{
			if(padre->get_hijo_izq() == p){
				padre->set_hijo_izq(p->get_hijo_der());
			}else{
				padre->set_hijo_der(p->get_hijo_der());
			}
		}
	}
	p->~Nodo_ab<E>();
}

template <class E>
void Arbol_bin<E> :: ELIMINAR_HOJA(Nodo_ab<E>* padre, Nodo_ab<E>* hoja){
	if(padre != 0){
		if(padre->get_hijo_izq() == hoja){
			padre->set_hijo_izq(0);
		}else{
			padre->set_hijo_der(0);
		}
	}
	hoja->~Nodo_ab<E>();
}

template <class E>
void Arbol_bin<E> :: ELIMINAR(Nodo_ab<E>* padre, Nodo_ab<E>* p){
	Nodo_ab<E>* aux;
	Nodo_ab<E>* padre_aux;
	
	if(p->get_hijo_izq() != 0 && p->get_hijo_der() != 0){
		aux = p->get_hijo_der();
		padre_aux = p;
		
		while(aux->get_hijo_izq() != 0){
			padre_aux = aux;
			aux = aux->get_hijo_izq();
		}
		
		p->set_elem(aux->get_elem());
		ELIMINAR(padre_aux, aux);
	}else{
		if(p->get_hijo_izq() != 0 || p->get_hijo_der() != 0){
			REEMPLAZAR_NODO(padre, p);
		}else{
			ELIMINAR_HOJA(padre, p);
		}
	}
}

template <class E>
void Arbol_bin<E> :: eliminar(E elem){
	Nodo_ab<E>* padre = 0;
	Nodo_ab<E>* pos;
	
	pos = BUSCAR_NODO(&padre, this->raiz, elem);
	ELIMINAR(padre, pos);
}

template <class E>
void Arbol_bin<E> :: CREAR_IN_PRE_ORDEN(Nodo_ab<E>* p, list<E>& in_orden, list<E>& pre_orden, bool lado){
	if(!pre_orden.empty()){
		if(pre_orden.size() == 1){
			if(lado){
				p->set_hijo_der(new Nodo_ab<E>(pre_orden.front()));
			}else{
				p->set_hijo_izq(new Nodo_ab<E>(pre_orden.front()));
			}
		}else{
			if(lado){
				p->set_hijo_der(new Nodo_ab<E>(pre_orden.front()));
			}else{
				p->set_hijo_izq(new Nodo_ab<E>(pre_orden.front()));
			}
			
			list<E> in_orden_izq; list<E> pre_orden_izq;
			list<E> in_orden_der; list<E> pre_orden_der;
			
			LADOS_IN_PRE(in_orden, pre_orden, in_orden_izq, pre_orden_izq, in_orden_der, pre_orden_der);
				
			if(lado){
				CREAR_IN_PRE_ORDEN(p->get_hijo_der(), in_orden_izq, pre_orden_izq, false);
				CREAR_IN_PRE_ORDEN(p->get_hijo_der(), in_orden_der, pre_orden_der, true);
			}else{
				CREAR_IN_PRE_ORDEN(p->get_hijo_izq(), in_orden_izq, pre_orden_izq, false);
				CREAR_IN_PRE_ORDEN(p->get_hijo_izq(), in_orden_der, pre_orden_der, true);
			}		
		}
	}	
}

template <class E>
void Arbol_bin<E> :: LADOS_IN_PRE(list<E>& in_orden, list<E>& pre_orden, list<E>&  in_orden_izq, list<E>& pre_orden_izq, list<E>&  in_orden_der, list<E>& pre_orden_der){
	E elem = pre_orden.front();

	pre_orden.pop_front();
	while(in_orden.front() != elem){
		in_orden_izq.push_back(in_orden.front());
		pre_orden_izq.push_back(pre_orden.front());
		in_orden.pop_front();
		pre_orden.pop_front();
	}
	in_orden.pop_front();

	while(!pre_orden.empty()){
		in_orden_der.push_back(in_orden.front());
		pre_orden_der.push_back(pre_orden.front());
		in_orden.pop_front();
		pre_orden.pop_front();
	}

}

template <class E>
void Arbol_bin<E> :: crear_in_pre(list<E> in_orden, list<E> pre_orden){
	if(!pre_orden.empty() && !in_orden.empty()){
		this->raiz = new Nodo_ab<E>(pre_orden.front());
		list<E> in_orden_izq; list<E> pre_orden_izq;
		list<E> in_orden_der; list<E> pre_orden_der;
		
		LADOS_IN_PRE(in_orden, pre_orden, in_orden_izq, pre_orden_izq, in_orden_der, pre_orden_der);

		CREAR_IN_PRE_ORDEN(this->raiz, in_orden_izq, pre_orden_izq, false);
		CREAR_IN_PRE_ORDEN(this->raiz, in_orden_der, pre_orden_der, true);
	}
}

template <class E>
Nodo_ab<E>* Arbol_bin<E> :: LEER_IN_PRE(list<E>& in_orden, list<E>& pre_orden){
	E elem;
	list<E> in_orden_izq; list<E> pre_orden_izq;
	list<E> in_orden_der; list<E> pre_orden_der;
	
	if(pre_orden.size() == 0){
		return 0;
	}
	if(pre_orden.size() == 1){
		return new Nodo_ab<E>(pre_orden.front());
	}
	elem = pre_orden.front();
	pre_orden.pop_front();
	while(in_orden.front() != elem){
		in_orden_izq.push_back(in_orden.front());
		pre_orden_izq.push_back(pre_orden.front());
		in_orden.pop_front();
		pre_orden.pop_front();
	}
	in_orden.pop_front();
	while(!pre_orden.empty()){
		in_orden_der.push_back(in_orden.front());
		pre_orden_der.push_back(pre_orden.front());
		in_orden.pop_front();
		pre_orden.pop_front();
	}	
	return new Nodo_ab<E>(elem, LEER_IN_PRE(in_orden_izq, pre_orden_izq), LEER_IN_PRE(in_orden_der, pre_orden_der));
}

template <class E>
void Arbol_bin<E> :: crear_in_pre_2(list<E> in_orden, list<E> pre_orden){
	this->raiz = LEER_IN_PRE(in_orden, pre_orden);
}

template <class E>
void Arbol_bin<E> :: CREAR_IN_POST_ORDEN(Nodo_ab<E>* p, list<E>& in_orden, list<E>& post_orden, bool lado){
	if(!post_orden.empty()){
		if(post_orden.size() == 1){
			if(lado){
				p->set_hijo_der(new Nodo_ab<E>(post_orden.front()));
			}else{
				p->set_hijo_izq(new Nodo_ab<E>(post_orden.front()));
			}
		}else{
			if(lado){
				p->set_hijo_der(new Nodo_ab<E>(post_orden.back()));
			}else{
				p->set_hijo_izq(new Nodo_ab<E>(post_orden.back()));
			}
			
			list<E> in_orden_izq; list<E> post_orden_izq;
			list<E> in_orden_der; list<E> post_orden_der;
			
			LADOS_IN_POST(in_orden, post_orden, in_orden_der, post_orden_der, in_orden_izq, post_orden_izq);
	
			if(lado){
				CREAR_IN_POST_ORDEN(p->get_hijo_der(), in_orden_izq, post_orden_izq, false);
				CREAR_IN_POST_ORDEN(p->get_hijo_der(), in_orden_der, post_orden_der, true);
			}else{
				CREAR_IN_POST_ORDEN(p->get_hijo_izq(), in_orden_izq, post_orden_izq, false);
				CREAR_IN_POST_ORDEN(p->get_hijo_izq(), in_orden_der, post_orden_der, true);
			}		
		}
	}	
}

template <class E>
void Arbol_bin<E> :: LADOS_IN_POST(list<E>& in_orden, list<E>& post_orden, list<E>&  in_orden_der, list<E>& post_orden_der, list<E>&  in_orden_izq, list<E>& post_orden_izq){
	while(in_orden.front() != post_orden.back()){
		in_orden_izq.push_back(in_orden.front());
		post_orden_izq.push_back(post_orden.front());
		in_orden.pop_front();
		post_orden.pop_front();
	}
	in_orden.pop_front(); 
	post_orden.pop_back();
	
	while(!post_orden.empty()){
		in_orden_der.push_back(in_orden.front());
		post_orden_der.push_back(post_orden.front());
		in_orden.pop_front();
		post_orden.pop_front();
	}

}

template <class E>
void Arbol_bin<E> :: crear_in_post(list<E> in_orden, list<E> post_orden){	
	if(!post_orden.empty() && !in_orden.empty()){
		this->raiz = new Nodo_ab<E>(post_orden.back());

		list<E> in_orden_izq; list<E> post_orden_izq;
		list<E> in_orden_der; list<E> post_orden_der;
		
		LADOS_IN_POST(in_orden, post_orden, in_orden_der, post_orden_der, in_orden_izq, post_orden_izq);

		CREAR_IN_POST_ORDEN(this->raiz, in_orden_izq, post_orden_izq, false);
		CREAR_IN_POST_ORDEN(this->raiz, in_orden_der, post_orden_der, true);
	}
}

template <class E>
void Arbol_bin<E> :: RECORRIDO_LV(Nodo_ab<E>* p, list<E>& li){
	queue<Nodo_ab<E>*> col;
	
	if(p != 0){
		col.push(p);
	}	
	while(!col.empty()){
		if(col.front()->get_hijo_izq() != 0){
			col.push(col.front()->get_hijo_izq());
		}
		if(col.front()->get_hijo_der() != 0){
			col.push(col.front()->get_hijo_der());
		}
		li.push_back(col.front()->get_elem());
		col.pop();
	}
}

template <class E>
list<E> Arbol_bin<E> :: recorrido_lv(){
	list<E> li;
	RECORRIDO_LV(this->raiz, li);
	return li;
}

template <class E>
void Arbol_bin<E> :: RECORRIDO_LV_EXACTO(Nodo_ab<E>* p, list<int>& li){
	queue<Nodo_ab<E>*> col;
	
	if(p != 0){
		col.push(p);
		col.push(0);
	}	
	while(!col.empty()){
		if(col.front()->get_hijo_izq() != 0){
			col.push(col.front()->get_hijo_izq());
		}
		if(col.front()->get_hijo_der() != 0){
			col.push(col.front()->get_hijo_der());
		}
		li.push_back(col.front()->get_elem());
		col.pop();
		
		if(col.front() == 0){
			col.pop();
			
			if(!col.empty()){
				li.push_back(-1);
				col.push(0);
			}
		}
	}
}
	
template <class E>
list<int> Arbol_bin<E> :: recorrido_lv_exacto(int lv){
	list<int> li;
	list<int> li_lv;
	
	RECORRIDO_LV_EXACTO(this->raiz, li);
	
	while(!li.empty()){
		if(lv == 0 && li.front() != -1){
			li_lv.push_back(li.front());
		}
		if(li.front() == -1){
			lv--;
		}
		li.pop_front();
	}	
	
	return li_lv;
}

template <class E>
void Arbol_bin<E> :: ALTURA(Nodo_ab<E>* p, int& lv_act, int& lv_max){
	if(p != 0){
		lv_act++;
		
		if(lv_act > lv_max){
			lv_max = lv_act;
		}
		
		ALTURA(p->get_hijo_izq(), lv_act, lv_max);
		ALTURA(p->get_hijo_der(), lv_act, lv_max);
		
		lv_act--;
	}
}

template <class E>
int Arbol_bin<E> :: altura(){
	int lv_max = -1, lv_act = -1;
	ALTURA(this->raiz, lv_act, lv_max);
	return lv_max;
}

template <class E>
void Arbol_bin<E> :: HOJAS(Nodo_ab<E>* p, list<E>& li){
	if(p != 0){
		if(p->get_hijo_izq() == 0 && p->get_hijo_der() == 0){
			li.push_back(p->get_elem());
		}
		
		HOJAS(p->get_hijo_izq(), li);
		HOJAS(p->get_hijo_der(), li);
	}
}

template <class E>
list<E> Arbol_bin<E> :: hojas(){
	list<E> li;
	HOJAS(this->raiz, li);
	return li;
}

template <class E>
void Arbol_bin<E> :: CAMINO_NOD(Nodo_ab<E>* p, list<E>& li, E& elem, bool& encont){
	if(p != 0){
		if(!encont){
			li.push_back(p->get_elem());
			
			if(p->get_elem() == elem){
				encont = true;
			}	
		}
		
		if(!encont){
			CAMINO_NOD(p->get_hijo_izq(), li, elem, encont);
			CAMINO_NOD(p->get_hijo_der(), li, elem, encont);
		}
		
		if(!encont){
			li.erase(--li.end());
		}
		
	}
}

template <class E>
list<E> Arbol_bin<E> :: camino_nod(E elem){
	list<E> li;
	bool encont = false;
	CAMINO_NOD(this->raiz, li, elem, encont);
	return li;
}

template <class E>
void Arbol_bin<E> :: CAMINO_NOD_NOD(Nodo_ab<E>* p, list<E>& cam_1, list<E>& cam_2, E& elem_1, E& elem_2, bool& encont_1, bool& encont_2){
	if(p != 0){
		if(!encont_1){
			cam_1.push_back(p->get_elem());	
			
			if(p->get_elem() == elem_1){
				encont_1 = true;
			}
		}
		if(!encont_2){
			cam_2.push_back(p->get_elem());	
			
			if(p->get_elem() == elem_2){
				encont_2 = true;
			}
		}
		
		if(!encont_1 || !encont_2){
			CAMINO_NOD_NOD(p->get_hijo_izq(), cam_1, cam_2, elem_1, elem_2, encont_1, encont_2);
			CAMINO_NOD_NOD(p->get_hijo_der(), cam_1, cam_2, elem_1, elem_2, encont_1, encont_2);
		}
		
		if(!encont_1){
			cam_1.erase(--cam_1.end());
		}
		if(!encont_2){
			cam_2.erase(--cam_2.end());
		}
	}	
}

template <class E>
list<E> Arbol_bin<E> :: camino_nod_nod(E elem_1, E elem_2){
	list<E> li, cam_1, cam_2;
	E aux;
	bool encont_1 = false, encont_2 = false;
	
	CAMINO_NOD_NOD(this->raiz, cam_1, cam_2, elem_1, elem_2, encont_1, encont_2);

	if(encont_1 && encont_2){
		while(!cam_1.empty() && cam_1.front() == cam_2.front()){
			aux = cam_1.front();
			cam_1.pop_front(); cam_2.pop_front();
		}
		li.push_back(aux);
	
		while(!cam_1.empty()){
			li.push_front(cam_1.front());
			cam_1.pop_front();
		}
	
		while(!cam_2.empty()){
			li.push_back(cam_2.front());
			cam_2.pop_front();
		}
	}
	
	return li;
}

template <class E>
E Arbol_bin<E> :: ancestro(E elem_1, E elem_2){
	list<E> li, cam_1, cam_2;
	E aux_1, aux_2;
	bool encont_1 = false, encont_2 = false;
	int cont = 0;
	
	CAMINO_NOD_NOD(this->raiz, cam_1, cam_2, elem_1, elem_2, encont_1, encont_2);

	if(encont_1 && encont_2){
		while(!cam_1.empty() && cam_1.front() == cam_2.front()){
			if(cont % 2 == 0){
				aux_1 = cam_1.front();
				
			}else{
				aux_2 = cam_1.front();
			}	
			cont++;	
			cam_1.pop_front(); cam_2.pop_front();
		}
		
	}
	
	if(cont % 2 != 0){
		if(aux_1 == elem_1 || aux_1 == elem_2){
			if(aux_1 == this->get_raiz()){
				return aux_1;
			}else{
				return aux_2;
			}
		}else{
			return aux_1;
		}	
	}else{
		if(aux_2 == elem_1 || aux_2 == elem_2){
			if(aux_2 == this->get_raiz()){
				return aux_2;
			}else{
				return aux_1;
			}
		}else{
			return aux_2;
		}	
	}
}

template <class E>
void Arbol_bin<E> :: DESTRUCTOR(Nodo_ab<E>* p){	
	if(p != 0){
		DESTRUCTOR(p->get_hijo_izq());
		DESTRUCTOR(p->get_hijo_der());
		p->~Nodo_ab();
	}
}

template <class E>
void Arbol_bin<E> :: CAMINO_ENTRE_HOJAS(list<E>& diametro, list<E> rama_1, list<E> rama_2){
	E aux;
	
	while(!rama_1.empty() && rama_1.front() == rama_2.front()){
		aux = rama_1.front();
		rama_1.pop_front(); rama_2.pop_front();
	}
	diametro.push_back(aux);
	
	while(!rama_1.empty()){
		diametro.push_front(rama_1.front());
		rama_1.pop_front();
	}
	
	while(!rama_2.empty()){
		diametro.push_back(rama_2.front());
		rama_2.pop_front();
	}
}

template <class E>
void Arbol_bin<E> :: CAMINO_MAS_LARGO(list<E>& diametro, list<E>& rama_1, list<E>& rama_2, list<E>& rama_aux){
	list<E> diametro_1, diametro_2;
	
	if(!rama_1.empty()){
		CAMINO_ENTRE_HOJAS(diametro_1, rama_1, rama_aux);
		
		if(!rama_2.empty()){
			CAMINO_ENTRE_HOJAS(diametro_2, rama_2, rama_aux);
		}else{
			rama_2 = rama_aux;
		}
		
		if(diametro_1.size() >= diametro_2.size()){
			if(diametro_1.size() > diametro.size()){
				rama_2.clear();
				diametro.clear();
				rama_2 = rama_aux;
				diametro = diametro_1;
			}
		}else{
			if(diametro_2.size() > diametro.size()){
				rama_1.clear();
				diametro.clear();
				rama_1 = rama_aux;
				diametro = diametro_2;
			}
		}
		
	}else{
		rama_1 = rama_aux;
	}
}

template <class E>
void Arbol_bin<E> :: DIAMETRO(Nodo_ab<E>* p, list<E>& diametro, list<E>& rama_1, list<E>& rama_2, list<E>& rama_aux){
	if(p != 0){
		rama_aux.push_back(p->get_elem());
		
		if(p->get_hijo_izq() == 0 && p->get_hijo_der() == 0){
			CAMINO_MAS_LARGO(diametro, rama_1, rama_2, rama_aux);
		}
		
		DIAMETRO(p->get_hijo_izq(), diametro, rama_1, rama_2, rama_aux);
		DIAMETRO(p->get_hijo_der(), diametro, rama_1, rama_2, rama_aux);

		rama_aux.pop_back();
	}
}

template <class E>
list<E> Arbol_bin<E> :: diametro(){
	list<E> li, rama_1, rama_2, rama_aux;
	DIAMETRO(this->raiz, li, rama_1, rama_2, rama_aux);
	
	if(rama_2.empty()){
		return rama_1;
	}else{
		return li;
	}
}

template <class E>
Arbol_bin<E> :: ~Arbol_bin(){
	DESTRUCTOR(this->raiz);
}

#endif