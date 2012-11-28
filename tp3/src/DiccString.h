#ifndef DICCSTRING_H_
#define DICCSTRING_H_

#include "aed2/TiposBasicos.h"

using namespace aed2;

template<class T>
class DiccString {

	struct Nodo {
		Nodo(char letra) : _letra(letra), _hermano(NULL), _hijo(NULL), _finPalabra(false) {};

		char _letra;
		Nodo* _hermano;
		Nodo* _hijo;
		bool _finPalabra;
        T _elem;
	};

	Nodo* _trie;

	void borrarNodo(Nodo* nodo);

public:
    Lista<T> _significados;
    Lista<String> _claves;
	int _elementosEnTrie;  //PARA HACER TESTS

	DiccString();
	virtual ~DiccString();

	Lista<String> claves() const;
	Lista<T> significados() const;
    Lista<T> significadoAux(const Nodo* nodo) const;
	void definir(const char* k, T s);
	void definir(const String& k, T& s);
	bool definido(const String& k) const;
	T& obtener(const String& k) const;
};


template<class T>
DiccString<T>::DiccString() : _trie(NULL), _elementosEnTrie(0) {
}

template<class T>
DiccString<T>::~DiccString() {
	if (_trie != NULL) {
		borrarNodo(_trie);
		delete _trie;
	}
}

template<class T>
void DiccString<T>::borrarNodo(Nodo* nodo) {
	if (nodo->_hermano != NULL) {
		borrarNodo(nodo->_hermano);
		delete nodo->_hermano;
	}

	if (nodo->_hijo != NULL) {
		borrarNodo(nodo->_hijo);
		delete nodo->_hijo;
	}
}

template<class T>
Lista<String> DiccString<T>::claves() const {
    return _claves;
}


template<class T>
Lista<T> DiccString<T>::significados() const

{ return _significados;}


template<class T>
void DiccString<T>::definir(const char* k, T s) {
	String key = String(k);

	definir(key, s);
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

	nodo->_elem = T(s);
	nodo->_finPalabra = true;
	_elementosEnTrie++;
	_significados.AgregarAtras(s);
	_claves.AgregarAtras(k);
}

template<class T>
bool DiccString<T>::definido(const String& k) const {
	Nodo* nodo = _trie;
	Nat i = 0;

	if (nodo == NULL)
		return false;

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
