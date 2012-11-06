#ifndef DICCSTRING_H_
#define DICCSTRING_H_

#include "aed2/TiposBasicos.h"

using namespace aed2;

template<class T>
class DiccString {

	struct Nodo {
		Nodo(char letra) : _letra(letra), _hermano(NULL), _hijo(NULL) {};

		T _elem;
		char _letra;
		Nodo* _hermano;
		Nodo* _hijo;
	};

	Nodo* _trie;

public:
	DiccString();
	virtual ~DiccString();

	Lista<String> claves() const;
	Lista<T> significados() const;
	void definir(const String& k, T& s);
	bool definido(const String& k) const;
	T& obtener(const String& k) const;
};


template<class T>
DiccString<T>::DiccString() : _trie(NULL) {
}

template<class T>
DiccString<T>::~DiccString() {
}

template<class T>
Lista<String> DiccString<T>::claves() const {
	return Lista<String>();
}

template<class T>
Lista<T> DiccString<T>::significados() const {
	return Lista<T>();
}

template<class T>
void DiccString<T>::definir(const String& k, T& s) {
	bool cargoTodo = _trie == NULL;
	Nat i = 0;

	Nodo* nodo;
	if (cargoTodo) {
		_trie = nodo = new Nodo(k[i++]);
	} else {
		nodo = _trie;
	}

	while (i < k.size()) {
		if (cargoTodo) {
			Nodo* nodoVacio = new Nodo(k[i++]);
			nodo->_hijo = nodoVacio;
			nodo = nodoVacio;
		} else {
			if (nodo->_letra == k[i]) {
				cargoTodo = nodo->_hijo == NULL;
				i++;
				if (!cargoTodo) {
					nodo = nodo->_hijo;
				}
			} else {
				cargoTodo = nodo->_hermano == NULL;
				if (!cargoTodo) {
					nodo = nodo->_hermano;
				} else {
					Nodo* nodoVacio = new Nodo(k[i++]);
					nodo->_hermano = nodoVacio;
					nodo = nodoVacio;
				}
			}
		}
	}

	nodo->_elem = s;
}

template<class T>
bool DiccString<T>::definido(const String& k) const {
	Nodo* nodo;
	Nat i = 0;

	while (i < k.size()) {
		if (nodo->_letra == k[i]) {
			if (++i == k.size()) {
				return true;
			} else {
				if (nodo->_hijo == NULL) {
					return false;
				} else {
					nodo = nodo->_hijo;
				}
			}
		} else {
			if (nodo->_hermano != NULL) {
				nodo = nodo->_hermano;
			} else {
				return false;
			}
		}
	}

	return false;
}

template<class T>
T& DiccString<T>::obtener(const String& k) const {
	Nodo* nodo = _trie;
	Nat i = 0;

	while (i < k.size()) {
		if (nodo->_letra == k[i]) {
			if (++i == k.size()) {
				return nodo->_elem;
			} else {
				nodo = nodo->_hijo;
			}
		} else {
			nodo = nodo->_hermano;
		}
	}

	return nodo->_elem;
}


#endif /* DICCSTRING_H_ */
