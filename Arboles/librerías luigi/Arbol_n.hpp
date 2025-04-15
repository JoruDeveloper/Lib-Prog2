#ifndef Arbol_n_h
#define Arbol_n_h

/*
Autor: Luigi Quero C.I: 30.009.785
*/

#include <iostream>
#include <list>
#include <queue>
#include <stack>
#include "Nodo_arbol.hpp"

using namespace std;

template <class E>
class Arbol_n{
	private:
		Nodo_arbol<E>* raiz;
		Nodo_arbol<E>* COPIAR_NODOS(Nodo_arbol<E>* p);
		void DESTRUIR_NODOS(Nodo_arbol<E>* p);
		void DESTRUIR_NODOS();
		void PRE_ORDEN(Nodo_arbol<E>* p, list<E>& li);
		void IN_ORDEN(Nodo_arbol<E>* p, list<E>& li);
		void POST_ORDEN(Nodo_arbol<E>* p, list<E>& li);
		void RECORRIDO_LV(Nodo_arbol<E>* p, list<E>& li);
		void RECORRIDO_LV_EXACTO(Nodo_arbol<E>* p, list<string>& li);
		void ALTURA(Nodo_arbol<E>* p, int& lv_act, int& lv_max);
		void HOJAS(Nodo_arbol<E>* p, list<E>& li);
		void CAMINO_NOD(Nodo_arbol<E>* p, list<E>& li, E& elem, bool& encont);
		void CAMINO_NOD_NOD(Nodo_arbol<E>* p, list<E>& cam_1, list<E>& cam_2, E& elem_1, E& elem_2, bool& encont_1, bool& encont_2);
		void CAMINO_ENTRE_HOJAS(list<E>& diametro, list<E> rama_1, list<E> rama_2);
		void CAMINO_MAS_LARGO(list<E>& diametro, list<E>& rama_1, list<E>& rama_2, list<E>& rama_aux);
		void DIAMETRO(Nodo_arbol<E>* p, list<E>& diametro, list<E>& rama_1, list<E>& rama_2, list<E>& rama_aux);
		void PADRE_HIJO(Nodo_arbol<E>* padre, list<Arbol_n<E> >& lis);
		Nodo_arbol<E>* PRE_ORDEN_PADRE_HIJO(Nodo_arbol<E>* p, E elem, Nodo_arbol<E>** padre, bool& encont);
	public:
		Arbol_n();
		Arbol_n(E elem);
		Arbol_n(E elem, list<Arbol_n<E> > lis);
		E get_raiz();
		list<Arbol_n<E> > hijos();
		bool es_vacio();
		void insertar_sub_arbol(Arbol_n<E> sub);
		void eliminar_sub_arbol(int pos);
		list<E> pre_orden();
		list<E> in_orden();
		list<E> post_orden();
		list<E> recorrido_lv();
		list<string> recorrido_lv_exacto(int lv);
		int altura();
		list<E> hojas();
		list<E> camino_nod(E elem);
		list<E> camino_nod_nod(E elem_1, E elem_2);
		E ancestro(E elem_1, E elem_2);
		list<E> diametro();
		void padre_hijo(E padre, list<Arbol_n<E> > hijos);
		~Arbol_n();
};

template <class E>
Arbol_n<E> :: Arbol_n(){
	raiz = 0;
}

template <class E>
Arbol_n<E> :: Arbol_n(E elem){
	raiz = new Nodo_arbol<E>(elem);
}

template <class E>
Nodo_arbol<E>* Arbol_n<E> :: COPIAR_NODOS(Nodo_arbol<E>* p){
	if(p == 0){
		return 0;
	}else{
		Nodo_arbol<E>* nod = new Nodo_arbol<E>(p->get_elem(), COPIAR_NODOS(p->get_hijo_izq()), COPIAR_NODOS(p->get_hermano_der()));
		return nod;
	}
}

template <class E>
Arbol_n<E> :: Arbol_n(E elem, list<Arbol_n<E> > lis){
	raiz = new Nodo_arbol<E>(elem);
	Nodo_arbol<E>* aux;
	
	if(!lis.empty()){
		raiz->set_hijo_izq(COPIAR_NODOS((*lis.begin()).raiz));
		lis.erase(lis.begin());
		aux = raiz->get_hijo_izq();
		
		while(!lis.empty()){
			aux->set_hermano_der(COPIAR_NODOS((*lis.begin()).raiz));
			lis.erase(lis.begin());
			aux = aux->get_hermano_der();
		}
	}
}

template <class E>
void Arbol_n<E> :: DESTRUIR_NODOS(Nodo_arbol<E>* p){
	if(p != 0){
		if(p->get_hermano_der() != 0){
			DESTRUIR_NODOS(p->get_hermano_der());
		}
		if(p->get_hijo_izq() != 0){
			DESTRUIR_NODOS(p->get_hijo_izq());
		}
		p->~Nodo_arbol<E>();
	}
}

template <class E>
void Arbol_n<E> :: DESTRUIR_NODOS(){
	stack<Nodo_arbol<E>*> p;
	Nodo_arbol<E>* nod;
	
	if(raiz != 0){
		p.push(raiz);
		
		while(!p.empty()){
			nod = p.top();
			p.pop();
			
			if(nod->get_hijo_izq() != 0){
				p.push(nod->get_hijo_izq());
			}
			if(nod->get_hermano_der() != 0){
				p.push(nod->get_hermano_der());	
			}
			nod->~Nodo_arbol<E>();
		}
		raiz = 0;
	}
}

template <class E>
bool Arbol_n<E> :: es_vacio(){
	return raiz == 0;
}

template <class E>
E Arbol_n<E> :: get_raiz(){
	return raiz->get_elem();
}

template <class E>
list<Arbol_n<E> > Arbol_n<E> :: hijos(){
	list<Arbol_n<E> > li;
	Arbol_n<E> arbol;
	Nodo_arbol<E>* nod_act = raiz->get_hijo_izq();
	Nodo_arbol<E>* nod_sig;
	
	if(nod_act != 0){
		nod_sig = nod_act->get_hermano_der();
	}
	
	while(nod_act != 0){
		nod_act->set_hermano_der(0);
		arbol.raiz = COPIAR_NODOS(nod_act);
		li.push_back(arbol);
		nod_act->set_hermano_der(nod_sig);
		nod_act = nod_sig;
		
		if(nod_sig != 0){
			nod_sig = nod_sig->get_hermano_der();
		}		
	}
	return li;
}

template <class E>
void Arbol_n<E> :: insertar_sub_arbol(Arbol_n<E> sub){
	Nodo_arbol<E>* aux;
	
	if(raiz->get_hijo_izq() == 0){
		raiz->set_hijo_izq(COPIAR_NODOS(sub.raiz));
	}else{
		aux = raiz->get_hijo_izq();
		
		while(aux->get_hermano_der() != 0){
			aux = aux->get_hermano_der();
		}
		aux->set_hermano_der(COPIAR_NODOS(sub.raiz));
	}
}

template <class E>
void Arbol_n<E> :: eliminar_sub_arbol(int pos){
	Nodo_arbol<E>* elim;
	Nodo_arbol<E>* aux;
	int i;
	
	if(pos == 1){
		elim = raiz->get_hijo_izq();
		raiz->set_hijo_izq(elim->get_hermano_der());
	}else{
		aux = raiz->get_hijo_izq();
		
		for(i = 2; i < pos; i++){
			aux = aux->get_hermano_der();
		}
		elim = aux->get_hermano_der();
		aux->set_hermano_der(elim->get_hermano_der());
	}
	elim->set_hermano_der(0);
	DESTRUIR_NODOS(elim);
}

template <class E>
void Arbol_n<E> :: PRE_ORDEN(Nodo_arbol<E>* p, list<E>& li){
	Nodo_arbol<E>* aux;
	
	if(p != 0){
		li.push_back(p->get_elem());
		aux = p->get_hijo_izq();
		
		while(aux != 0){
			PRE_ORDEN(aux, li);
			aux = aux->get_hermano_der();
		}
	}
}

template <class E>
void Arbol_n<E> :: IN_ORDEN(Nodo_arbol<E>* p, list<E>& li){
	Nodo_arbol<E>* aux;
	
	if(p != 0){
		IN_ORDEN(p->get_hijo_izq(), li);
		li.push_back(p->get_elem());
	
		if(p->get_hijo_izq() != 0){
			aux = p->get_hijo_izq()->get_hermano_der();
		}else{
			aux = 0;
		}
		
		while(aux != 0){
			IN_ORDEN(aux, li);
			aux = aux->get_hermano_der();
		}
	}
}

template <class E>
void Arbol_n<E> :: POST_ORDEN(Nodo_arbol<E>* p, list<E>& li){
	Nodo_arbol<E>* aux;
	
	if(p != 0){
		aux = p->get_hijo_izq();
		 
		while(aux != 0){
			POST_ORDEN(aux, li);
			aux = aux->get_hermano_der();
		}
		li.push_back(p->get_elem());
	}
}

template <class E>
list<E> Arbol_n<E> :: pre_orden(){
	list<E> li;
	PRE_ORDEN(this->raiz, li);
	return li;
}

template <class E>
list<E> Arbol_n<E> :: in_orden(){
	list<E> li;
	IN_ORDEN(this->raiz, li);
	return li;
}

template <class E>
list<E> Arbol_n<E> :: post_orden(){
	list<E> li;
	POST_ORDEN(this->raiz, li);
	return li;
}

template <class E>
void Arbol_n<E> :: RECORRIDO_LV(Nodo_arbol<E>* p, list<E>& li){
	queue<Nodo_arbol<E>*> col;
	Nodo_arbol<E>* aux;
	
	if(p != 0){
		col.push(p);
		aux = p->get_hermano_der();
		
		while(!col.empty()){
			while(aux != 0){
				col.push(aux);
				aux = aux->get_hermano_der();
			}
			
			li.push_back(col.front()->get_elem());
			aux = col.front()->get_hijo_izq();
			col.pop();
			if(aux != 0){
				col.push(aux);
				aux = aux->get_hermano_der();
			}
		}	
	}
}

template <class E>
list<E> Arbol_n<E> :: recorrido_lv(){
	list<E> li;
	RECORRIDO_LV(this->raiz, li);
	return li;
}

template <class E>
void Arbol_n<E> :: RECORRIDO_LV_EXACTO(Nodo_arbol<E>* p, list<string>& li){
	queue<Nodo_arbol<E>*> col;
	Nodo_arbol<E>* aux;
	
	if(p != 0){
		col.push(p);
		aux = p->get_hermano_der();
		col.push(0);
		
		while(!col.empty()){
			while(aux != 0){
				col.push(aux);
				aux = aux->get_hermano_der();
			}
			
			if(col.front() == 0){
				col.pop();
				if(!col.empty()){
					col.push(0);
					li.push_back("-");
				}						
			}

			if(!col.empty()){		
				li.push_back(col.front()->get_elem());
				aux = col.front()->get_hijo_izq();
				col.pop();
			}
	
			if(aux != 0){
				col.push(aux);
				aux = aux->get_hermano_der();
			}
		}	
	}
}

template <class E>
list<string> Arbol_n<E> :: recorrido_lv_exacto(int lv){
	list<string> li;
	list<string> li_lv;
	
	RECORRIDO_LV_EXACTO(this->raiz, li);
	
	while(!li.empty()){
		if(lv == 0 && li.front() != "-"){
			li_lv.push_back(li.front());
		}
		if(li.front() == "-"){
			lv--;
		}
		li.pop_front();
	}	
	
	return li_lv;
}

template <class E>
void Arbol_n<E> :: ALTURA(Nodo_arbol<E>* p, int& lv_act, int& lv_max){
	Nodo_arbol<E>* aux;

	if(p != 0){
		lv_act++;
		
		if(lv_act > lv_max){
			lv_max = lv_act;
		}
		
		aux = p->get_hijo_izq();
		while(aux != 0){
			ALTURA(aux, lv_act, lv_max);
			aux = aux->get_hermano_der();
		}
		
		lv_act--;
	}
}

template <class E>
int Arbol_n<E> :: altura(){
	int lv_max = -1, lv_act = -1;
	ALTURA(this->raiz, lv_act, lv_max);
	return lv_max;
}

template <class E>
void Arbol_n<E> :: HOJAS(Nodo_arbol<E>* p, list<E>& li){
	Nodo_arbol<E>* aux;
	
	if(p != 0){
		if(p->get_hijo_izq() == 0 ){
			li.push_back(p->get_elem());
		}
		
		aux = p->get_hijo_izq();
		while(aux != 0){
			HOJAS(aux, li);
			aux = aux->get_hermano_der();
		}
	}
}

template <class E>
list<E> Arbol_n<E> :: hojas(){
	list<E> li;
	HOJAS(this->raiz, li);
	return li;
}

template <class E>
void Arbol_n<E> :: CAMINO_NOD(Nodo_arbol<E>* p, list<E>& li, E& elem, bool& encont){
	Nodo_arbol<E>* aux;

	if(p != 0){
		if(!encont){
			li.push_back(p->get_elem());
			
			if(p->get_elem() == elem){
				encont = true;
			}	
		}
		
		aux = p->get_hijo_izq();
		while(aux != 0 && !encont){
			CAMINO_NOD(aux, li, elem, encont);
			aux = aux->get_hermano_der();
		}
		
		if(!encont){
			li.erase(--li.end());
		}
		
	}
}

template <class E>
list<E> Arbol_n<E> :: camino_nod(E elem){
	list<E> li;
	bool encont = false;
	CAMINO_NOD(this->raiz, li, elem, encont);
	return li;
}

template <class E>
void Arbol_n<E> :: CAMINO_NOD_NOD(Nodo_arbol<E>* p, list<E>& cam_1, list<E>& cam_2, E& elem_1, E& elem_2, bool& encont_1, bool& encont_2){
	Nodo_arbol<E>* aux;

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
		
		aux = p->get_hijo_izq();
		while(aux != 0 && (!encont_1 || !encont_2)){
			CAMINO_NOD_NOD(aux, cam_1, cam_2, elem_1, elem_2, encont_1, encont_2);
			aux = aux->get_hermano_der();
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
list<E> Arbol_n<E> :: camino_nod_nod(E elem_1, E elem_2){
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
E Arbol_n<E> :: ancestro(E elem_1, E elem_2){
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
void Arbol_n<E> :: CAMINO_ENTRE_HOJAS(list<E>& diametro, list<E> rama_1, list<E> rama_2){
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
void Arbol_n<E> :: CAMINO_MAS_LARGO(list<E>& diametro, list<E>& rama_1, list<E>& rama_2, list<E>& rama_aux){
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
void Arbol_n<E> :: DIAMETRO(Nodo_arbol<E>* p, list<E>& diametro, list<E>& rama_1, list<E>& rama_2, list<E>& rama_aux){
	Nodo_arbol<E>* aux;
	
	if(p != 0){
		rama_aux.push_back(p->get_elem());
		
		if(p->get_hijo_izq() == 0){
			CAMINO_MAS_LARGO(diametro, rama_1, rama_2, rama_aux);
		}
		
		aux = p->get_hijo_izq();
		while(aux != 0){
			DIAMETRO(aux, diametro, rama_1, rama_2, rama_aux);
			aux = aux->get_hermano_der();
		}

		rama_aux.pop_back();
	}
}

template <class E>
list<E> Arbol_n<E> :: diametro(){
	list<E> li, rama_1, rama_2, rama_aux;
	DIAMETRO(this->raiz, li, rama_1, rama_2, rama_aux);
	
	if(rama_2.empty()){
		return rama_1;
	}else{
		return li;
	}
}

template <class E>
void Arbol_n<E> :: PADRE_HIJO(Nodo_arbol<E>* padre, list<Arbol_n<E> >& lis){
	Nodo_arbol<E>* aux;
	
	if(!lis.empty()){
		padre->set_hijo_izq(COPIAR_NODOS(lis.front().raiz));
		lis.pop_front();
		aux = padre->get_hijo_izq();
		
		while(!lis.empty()){
			aux->set_hermano_der(COPIAR_NODOS(lis.front().raiz));
			lis.pop_front();
			aux = aux->get_hermano_der();
		}
	}
}

template <class E>
Nodo_arbol<E>* Arbol_n<E> :: PRE_ORDEN_PADRE_HIJO(Nodo_arbol<E>* p, E elem, Nodo_arbol<E>** padre, bool& encont){
	Nodo_arbol<E>* aux;
	
	if(p != 0){
		if(p->get_elem() == elem){
			*padre = p;
			encont = true;
		}
		aux = p->get_hijo_izq();
		
		while(aux != 0 && !encont){
			PRE_ORDEN_PADRE_HIJO(aux, elem, padre, encont);
			aux = aux->get_hermano_der();
		}
	}
}

template <class E>
void Arbol_n<E> :: padre_hijo(E padre, list<Arbol_n<E> > hijos){
	bool encont = false;
	Nodo_arbol<E>* pad;
	
	if(this->raiz == 0){
		this->raiz = new Nodo_arbol<E>(padre);
		PADRE_HIJO(raiz, hijos);
	}else{
		PRE_ORDEN_PADRE_HIJO(this->raiz, padre, &pad, encont);
		
		if(encont){
			PADRE_HIJO(pad, hijos);
		}
	}	
}

template <class E>
Arbol_n<E> :: ~Arbol_n<E>(){
	DESTRUIR_NODOS();
}

#endif