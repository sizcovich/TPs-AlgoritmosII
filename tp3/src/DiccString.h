#ifndef DICCSTRING_H_
#define DICCSTRING_H_

#include "aed2/TiposBasicos.h"

using namespace aed2;

template<class T>
class DiccString {

	struct Nodo {
		Nodo(char letra) : _letra(letra), _hermano(NULL), _hijo(NULL), _finPalabra(false) {};

		bool _finPalabra;
		char _letra;
		Nodo* _hermano;
		Nodo* _hijo;
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

	/*
template<class T>
Lista<String> DiccString<T>::clavesAux(const Nodo* nodo, const string prefijo) const {

}
	  */

template<class T>
Lista<T> DiccString<T>::significados() const
/*
{
	// FUNCION RECURSIVA
	Lista<T> res;
    if (_trie == NULL)
        {return res;}
    else
    {
        if (_trie->_finPalabra == true)
            {res.AgregarAtras(_trie->_elem);}
        if (_trie->_hermano != NULL)
            {res.concatenar(significadoAux(_trie->_hermano));}
        if (_trie->_hijo != NULL)
            {res.concatenar(significadoAux(_trie->_hijo));}
    }
    return res;
}

template<class T>
Lista<T> DiccString<T>::significadoAux(const Nodo* nodo) const {
	Lista<T> res;
    if (nodo == NULL)
        {return res;}
    else
    {
        if (_trie->_finPalabra == true)
            {res.AgregarAtras(nodo->_elem);}
        if (nodo->_hermano != NULL)
            {res.concatenar(significadoAux(nodo->_hermano));}
        if (nodo->_hijo != NULL)
            {res.concatenar(significadoAux(nodo->_hijo));}
    }
    return res;
}
*/
/*
{
	Nodo* nodo = _trie;
	Lista<Nodo*> anteriores;
	Lista<T> res;
	while(nodo != NULL && ((nodo->_hermano != NULL || nodo->_hijo != NULL) && anteriores.EsVacia()))  //VERIFICAR
	{//NULL es para cuando miro la raiz, y el resto es sin interrupciones xq se tiene q cummplir todo para q haya llegado al final

		if(nodo->_finPalabra == true)
			res.AgregarAtras(nodo->_elem);

		if(nodo->_hijo != NULL) //si tiene hijo, guardo el padre y avanzo hacia abajo
		{
			anteriores.AgregarAtras(nodo);
			nodo = nodo->_hijo;
		}
		else
		{
			//res.AgregarAtras(nodo->_elem); //si no tiene hijo, tiene informacion. MAL

			if(nodo->_hermano != NULL) //si tiene hermano, sigo recorriendo este nivel.
			{
				nodo = nodo->_hermano;
			}
			else //si no tiene hijo ni hermano, tengo que volver hacia arriba.
			{
				if(!(anteriores.EsVacia()))
				{
					if(anteriores.Ultimo()->_hermano != NULL)
						nodo = anteriores.Ultimo()->_hermano;
					else //si el padre al q volvi no tiene hermano, tengo q ir a su padre
					{
						while(anteriores.Ultimo() != NULL && anteriores.Ultimo()->_hermano != NULL)
							if(!(anteriores.EsVacia()))
								anteriores.Comienzo();
					}
				}
			}
		}
	}
	cout << res << endl;
	return res;
}*/
{ return _significados;}


template<class T>
void DiccString<T>::definir(const char* k, T s) {
	String key = k;

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

	nodo->_elem = s;
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
