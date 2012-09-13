#ifndef ANILLO_H_
#define ANILLO_H_

#include <iostream>
#include <cassert>
using namespace std;

//se puede asumir que el tipo T tiene constructor por copia
//y operator==
//no se puede asumir que el tipo T tenga operator=
template<typename T>
class Anillo {
public:

	/*
	 * constructor por defecto, crea un anillo
	 */
	Anillo();

	/*
	 * constructor por copia, una vez copiado, ambos anillos deben ser
	 * independientes, es decir, cuando se borre uno no debe morir el otro.
	 */
	Anillo(const Anillo<T>&);

	/*
	 * Destructor. Acordarse de liberar toda la memoria!
	 */
	~Anillo();

	/*
	 * Devuelve true si los anillos son iguales
	 */
	bool operator==(const Anillo<T>&) const;

	/*
	 * Dice si el anillo es vacío.
	 */
	bool esVacio() const;

	/*
	 * Dice el tamaño del anillo
	 */
	int tamanio() const;

	/*
	 * Devuelve el elemento actual del anillo
	 * PRE: no es vacío el anillo.
	 */
    const T& actual() const;

	/*
	 * Devuelve el próximo elemento según el orden del anillo.
	 * El anillo debe rotar. Con lo cual sucesivas llamadas a esta función
	 * retornan distintos valores.
	 *
	 * El valor retornado pasa a ser el anterior.
	 *
	 * PRE: no es vacío el anillo.
	 */
	const T& siguiente();
	
	/*
	 * Agrega el elemento al anillo. Recordar que el último agregado es el
	 * actual
	 */
	void agregar(const T&);

	/*
	 * Elimina una ocurrencia del elemento en el anillo.
	 */
	void eliminar(const T&);

	/*
	 * Marca el elemento actual.
	 *
	 * PRE: no es vacío el anillo.
	 */
    void marcar();

	/*
	 * Indica si algún del anillo está marcado.
	 */
	bool hayMarcado() const;

	/*
	 * Indica cuál es el elemento marcado la última vez.
	 *
	 * PRE: hayMarcado
	 */
	const T& marcado() const;

	/*
	 * Vuelve hacia atrás un elemento.
	 * El anterior, en caso de existir, no debe alterarse.
	 */
	void retroceder();

	/*
	 * debe mostrar el anillo en el stream (y retornar el mismo).
	 * Anillo vacío: []
	 * Anillo con 2 elementos (e1 es el actual): [e1, e2]
	 * Anillo con 2 elementos (e2 es el actual y e1 fue marcado): [e2, e1*]
	 * Anillo con 3 elementos (e3 es el actual, e2 fue agregado antes que e3,
	 * e1 fue agregado antes que e2): [e3, e2, e1]
	 */
	ostream& mostrarAnillo(ostream&) const;

private:
	// No se puede modificar esta función.
	Anillo<T>& operator=(const Anillo<T>& otro) {
		assert(false);
		return *this;
	}

	// Acá va la implementación del nodo.
	struct Nodo {
		const T *valor;
		Nodo *siguiente;
		Nodo *anterior;
	};

	ostream& mostrarNodo(ostream &out, const Nodo *a) const;

	Nodo *este;

	Nodo *seleccion;

	int total;

};

template<class T>
ostream& operator<<(ostream& out, const Anillo<T>& a) {
	return a.mostrarAnillo(out);
}


template<typename T>
Anillo<T>::Anillo() {
	este = NULL;
	seleccion = NULL;
	total = 0;
}


template<typename T>
Anillo<T>::Anillo(const Anillo<T>& otro) {
	int i = otro.total;
	este = NULL;
	total = 0;
	seleccion = NULL;
	if(!otro.esVacio())
	{

		Nodo *sig;
		agregar(*otro.este->valor);
		if(otro.seleccion == otro.este)
		{
			seleccion = este;
		}
		sig = otro.este ->anterior;
		while (i-- > 1) {
			agregar(*sig ->valor);
			if(otro.seleccion == sig)
			{
				seleccion = este;
			}
			sig = sig -> anterior;
		}

		este = este -> anterior;

	}
}


template<typename T>
Anillo<T>::~Anillo() {
	int i = total;
	while (i-- > 0) {
		eliminar(*este->valor);
	}
}


template<typename T>
bool Anillo<T>::operator==(const Anillo<T>& otro) const {
	//bool retorno1 = (*este == *otro -> este) && (total == otro -> total) && (seleccion == otro.seleccion || *seleccion == *otro -> seleccion);
	bool retorno2 = true;
	int i = total;
	while(i-- > 0)
	{
		//otro.siguiente();
		//retorno2 == retorno2 && (*este == *otro -> este);
	}

	//return retorno1 && retorno2;
	return false;
}


template<typename T>
bool Anillo<T>::esVacio() const {
	return (total == 0);
}


template<typename T>
int Anillo<T>::tamanio() const {
	return total;
}


template<typename T>
const T& Anillo<T>::actual() const {
	return *este->valor;
}


template<typename T>
const T& Anillo<T>::siguiente() {
	este = este->siguiente;
	return *este->anterior->valor;
}


template<typename T>
void Anillo<T>::agregar(const T& nuevoValor) {
	Nodo *nuevoNodo = new Nodo();
	nuevoNodo->valor = &nuevoValor;

	if (total > 0) {
		nuevoNodo->siguiente = este;
		nuevoNodo->anterior = este->anterior;
		este->anterior->siguiente = nuevoNodo;
		este->anterior = nuevoNodo;
	} else {
		nuevoNodo->siguiente = nuevoNodo->anterior = nuevoNodo;
	}

	este = nuevoNodo;
	total++;
}


template<typename T>
void Anillo<T>::eliminar(const T& valorAEliminar) {
	int i = total;
	Nodo *elem = este;
	while (i-- > 0) {
		if (*elem->valor == valorAEliminar) {

			if (seleccion == elem) {
				seleccion = NULL;
			}

			if (este == elem) {
				este = elem->siguiente;
			}

			elem->anterior->siguiente = elem->siguiente;
			elem->siguiente->anterior = elem->anterior;
			delete elem;

			total--;
			break;
		}

		elem = elem->siguiente;
	}

	if (total == 0) {
		este = NULL;
	}
}


template<typename T>
void Anillo<T>::marcar() {
	seleccion = este;
}


template<typename T>
bool Anillo<T>::hayMarcado() const {
	return seleccion != NULL;
}


template<typename T>
const T& Anillo<T>::marcado() const {
	return *seleccion->valor;
}


template<typename T>
void Anillo<T>::retroceder() {
	este = este->anterior;
}


template<typename T>
ostream& Anillo<T>::mostrarAnillo(ostream &out) const {
	out << "[";
	int i = total;
	if (i > 0) {
		Nodo *elem = este;
		while (--i > 0) {
			mostrarNodo(out, elem) << ", ";

			elem = elem->siguiente;
		}

		mostrarNodo(out, elem);
	}
	return out << "]";
}


template<typename T>
ostream& Anillo<T>::mostrarNodo(ostream &out, const Nodo *elem) const {
	out << *elem->valor;

	if (seleccion == elem)
		out << "*";

	return out;
}



#endif //ANILLO_H_
