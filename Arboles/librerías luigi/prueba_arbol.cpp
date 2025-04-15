#include <iostream>
#include <list>
#include "Arbol_n.hpp"

using namespace std;

int main(){
	
	list<string> li;
	list<Arbol_n<string> > l1;
	list<string> l2;
	
	
	Arbol_n<string> arbol;
	
	Arbol_n<string> a = Arbol_n<string>("hijo1");
	Arbol_n<string> b = Arbol_n<string>("hijo2");
	Arbol_n<string> c = Arbol_n<string>("hijo3");
	l1.push_back(a); l1.push_back(b); l1.push_back(c);
	
	arbol.padre_hijo("padre", l1);
	while(!l1.empty()){
		l1.erase(l1.begin());
	}
	
	Arbol_n<string> d = Arbol_n<string>("nieto1");
	Arbol_n<string> e = Arbol_n<string>("nieto2");
	Arbol_n<string> f = Arbol_n<string>("nieto3");
	l1.push_back(d); l1.push_back(e); l1.push_back(f);
	
	
	arbol.padre_hijo("hijo1", l1);
	while(!l1.empty()){
		l1.erase(l1.begin());
	}
	
	Arbol_n<string> g = Arbol_n<string>("nieto4");
	Arbol_n<string> h = Arbol_n<string>("nieto5");
	Arbol_n<string> i = Arbol_n<string>("nieto6");
	l1.push_back(g); l1.push_back(h); l1.push_back(i);
	
	
	arbol.padre_hijo("hijo2", l1);
	while(!l1.empty()){
		l1.erase(l1.begin());
	}
	
	
	li = arbol.recorrido_lv_exacto(0);
	cout << "Recorrido por niveles (0): ";	
	while(!li.empty()){
		cout << li.front() << " ";
		li.pop_front();
	}
	cout << endl;
	
	li = arbol.recorrido_lv_exacto(1);
	cout << "Recorrido por niveles (0): ";	
	while(!li.empty()){
		cout << li.front() << " ";
		li.pop_front();
	}
	cout << endl;
	
	li = arbol.recorrido_lv_exacto(2);
	cout << "Recorrido por niveles (0): ";	
	while(!li.empty()){
		cout << li.front() << " ";
		li.pop_front();
	}
	cout << endl;
	
	
	
	
/*	list<int> li;
	list<Arbol_n<int> > l1;
	list<string> l2;
	
	
	Arbol_n<int> arbol;
	
	Arbol_n<int> a = Arbol_n<int>(1);
	Arbol_n<int> b = Arbol_n<int>(2);
	Arbol_n<int> c = Arbol_n<int>(3);
	l1.push_back(a); l1.push_back(b); l1.push_back(c);
	
	arbol.padre_hijo(-1, l1);
	while(!l1.empty()){
		l1.erase(l1.begin());
	}
	
	Arbol_n<int> d = Arbol_n<int>(4);
	Arbol_n<int> e = Arbol_n<int>(5);
	Arbol_n<int> f = Arbol_n<int>(6);
	l1.push_back(d); l1.push_back(e); l1.push_back(f);
	
	arbol.padre_hijo(1, l1);
	while(!l1.empty()){
		l1.erase(l1.begin());
	}
	
	Arbol_n<int> g = Arbol_n<int>(7);
	Arbol_n<int> h = Arbol_n<int>(8);
	Arbol_n<int> i = Arbol_n<int>(9);
	l1.push_back(g); l1.push_back(h); l1.push_back(i);
	
	arbol.padre_hijo(2, l1);
	while(!l1.empty()){
		l1.erase(l1.begin());
	}
	
	Arbol_n<int> j = Arbol_n<int>(10);
	Arbol_n<int> k = Arbol_n<int>(11);
	Arbol_n<int> l = Arbol_n<int>(12);
	l1.push_back(j); l1.push_back(k); l1.push_back(l);
	
	arbol.padre_hijo(3, l1);
	while(!l1.empty()){
		l1.erase(l1.begin());
	}
	
	Arbol_n<int> m = Arbol_n<int>(13);
	Arbol_n<int> n = Arbol_n<int>(14);
	l1.push_back(m); l1.push_back(n); 
	
	arbol.padre_hijo(6, l1);
	while(!l1.empty()){
		l1.erase(l1.begin());
	}
	
	Arbol_n<int> o = Arbol_n<int>(15);
	l1.push_back(o);
	arbol.padre_hijo(14, l1);
	
	while(!l1.empty()){
		l1.erase(l1.begin());
	}
	
	li = arbol.pre_orden();
	cout << "Pre orden: ";	
	while(!li.empty()){
		cout << *li.begin() << " ";
		li.erase(li.begin());
	}
	cout << endl;

	li = arbol.in_orden();
	cout << "In orden: ";
	while(!li.empty()){
		cout << *li.begin() << " ";
		li.erase(li.begin());
	}
	cout << endl;

	li = arbol.post_orden();
	cout << "Post orden: ";
	while(!li.empty()){
		cout << *li.begin() << " ";
		li.erase(li.begin());
	}
	cout << endl;

	l2 = arbol.recorrido_lv_2();
	cout << "Recorrido por nivel: ";
	while(!l2.empty()){
		cout << l2.front() << " ";
		l2.pop_front();
	}
	cout << endl;
	
/*	Arbol_n<int> a5 = Arbol_n<int>(16);
	
	Arbol_n<int> a4 = Arbol_n<int>(14);
	
	l1.push_back(a5);
	Arbol_n<int> b4 = Arbol_n<int>(15, l1);
	l1.erase(l1.begin());
	
	Arbol_n<int> a3 = Arbol_n<int>(5);
	Arbol_n<int> b3 = Arbol_n<int>(6);
	Arbol_n<int> c3 = Arbol_n<int>(7);
	
	Arbol_n<int> d3 = Arbol_n<int>(8);
	Arbol_n<int> e3 = Arbol_n<int>(9);
	Arbol_n<int> f3 = Arbol_n<int>(10);
	
	Arbol_n<int> g3 = Arbol_n<int>(11);
	Arbol_n<int> h3 = Arbol_n<int>(12);
	
	
	l1.push_back(a4); l1.push_back(b4);
	Arbol_n<int> i3 = Arbol_n<int>(13, l1);
	while(!l1.empty()){
		l1.erase(l1.begin());
	}

	l1.push_back(a3); l1.push_back(b3); l1.push_back(c3);
	Arbol_n<int> a2 = Arbol_n<int>(2, l1);
	while(!l1.empty()){
		l1.erase(l1.begin());
	}
	
	l1.push_back(d3); l1.push_back(e3); l1.push_back(f3);
	Arbol_n<int> b2 = Arbol_n<int>(3, l1);
	while(!l1.empty()){
		l1.erase(l1.begin());
	}
	
	
	l1.push_back(g3); l1.push_back(h3); l1.push_back(i3);
	Arbol_n<int> c2 = Arbol_n<int>(4, l1);	
	while(!l1.empty()){
		l1.erase(l1.begin());
	}
	
	l1.push_back(a2); l1.push_back(b2); l1.push_back(c2);
	Arbol_n<int> arbol = Arbol_n<int>(1, l1);
	while(!l1.empty()){
		l1.erase(l1.begin());
	}
	
	
	li = arbol.pre_orden();
	vector<int> pre(li.begin(), li.end());
	cout << "Pre orden: ";	
	while(!li.empty()){
		cout << *li.begin() << " ";
		li.erase(li.begin());
	}
	cout << endl;

	li = arbol.in_orden();
	vector<int> in(li.begin(), li.end());
	cout << "In orden: ";
	while(!li.empty()){
		cout << *li.begin() << " ";
		li.erase(li.begin());
	}
	cout << endl;

	li = arbol.post_orden();
	cout << "Post orden: ";
	vector<int> post(li.begin(), li.end());
	while(!li.empty()){
		cout << *li.begin() << " ";
		li.erase(li.begin());
	}
	cout << endl << endl;
	
	li = arbol.recorrido_lv();
	cout << "Recorrido por nivel: ";
	while(!li.empty()){
		cout << *li.begin() << " ";
		li.erase(li.begin());
	}
	cout << endl << endl;

	cout << "Altura del arbol: " << arbol.altura() << endl;
	
	li = arbol.hojas();
	cout << "Hojas del arbol: ";
	while(!li.empty()){
		cout << *li.begin() << " ";
		li.erase(li.begin());
	}
	cout << endl;
	
	li = arbol.camino_nod(8);
	cout << "Camino al nodo: ";
	while(!li.empty()){
		cout << *li.begin() << " ";
		li.erase(li.begin());
	}
	cout << endl;

	li = arbol.camino_nod_nod(8, 2);
	cout << "Camino de nodo a nodo: ";
	while(!li.empty()){
		cout << *li.begin() << " ";
		li.erase(li.begin());
	}
	cout << endl;

	cout << "Ancestro comun: " << arbol.ancestro(13, 2) << endl;
	
	li = arbol.diametro(),
	cout << "Diametro: ";
	while(!li.empty()){
		cout << *li.begin() << " ";
		li.erase(li.begin());
	}
	cout << endl;
	
*/
	return 0;
}