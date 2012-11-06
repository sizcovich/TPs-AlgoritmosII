#include "ArbolCategorias.h"


ArbolCategorias::ArbolCategorias(const Categoria& raiz) :
		_categorias(DiccString<CatInfo*>()), _raiz(raiz), _ultId(1) {
	CatInfo* infoRaiz = new CatInfo(_ultId);
	_categorias.definir(raiz, infoRaiz);
}

ArbolCategorias::~ArbolCategorias() {
	Lista<CatInfo*> infoCats = _categorias.significados();
	Lista<CatInfo*>::Iterador it = infoCats.CrearIt();
	while (it.HaySiguiente()) {
		delete it.Siguiente();
		it.Avanzar();
	}
}

const Categoria ArbolCategorias::raiz() const {
	return _raiz;
}

void ArbolCategorias::agregar(const Categoria& padre, const Categoria& hija) {
	CatInfo* infoPadre = _categorias.obtener(padre);

	CatInfo* infoHija = new CatInfo(++_ultId);
	infoHija->_padre = infoPadre;

	_categorias.definir(hija, infoHija);

	infoPadre->_hijas.AgregarAtras(hija);
}

ArbolCategorias::IteradorHijas ArbolCategorias::hijas(const Categoria& padre) const {
	CatInfo* nodoPadre = _categorias.obtener(padre);
	return ArbolCategorias::IteradorHijas(&nodoPadre->_hijas);
}

ArbolCategorias::IteradorPadres ArbolCategorias::padres(const Categoria& hija) const {
	CatInfo* nodoHija = _categorias.obtener(hija);
	return IteradorPadres(nodoHija);
}

Nat ArbolCategorias::id(const Categoria& c) const {
	return _categorias.obtener(c)->_id;
}

Nat ArbolCategorias::cantCategorias() const {
	return _ultId;
}


// IteradorHijas
ArbolCategorias::IteradorHijas::IteradorHijas(Lista<Categoria>* lista) {
	_it = lista->CrearIt();
}

void ArbolCategorias::IteradorHijas::Avanzar() {
	_it.Avanzar();
}

bool ArbolCategorias::IteradorHijas::HaySiguiente() const {
	return _it.HaySiguiente();
}

Categoria ArbolCategorias::IteradorHijas::Siguiente() const {
	return _it.Siguiente();
}


// IteradorPadres
ArbolCategorias::IteradorPadres::IteradorPadres(CatInfo* catInfo) :
		_catInfo(catInfo) {
}

void ArbolCategorias::IteradorPadres::Avanzar() {
	_catInfo = _catInfo->_padre;
}

bool ArbolCategorias::IteradorPadres::HaySiguiente() const {
	return _catInfo->_padre != NULL;
}

Nat ArbolCategorias::IteradorPadres::Siguiente() const {
	return _catInfo->_id;
}
