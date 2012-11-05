#ifndef ARBOLCATEGORIAS_H_
#define ARBOLCATEGORIAS_H_

#include "aed2/TiposBasicos.h"
#include "Tipos.h"

#include "aed2/Lista.h"
#include "DiccString.h"

using namespace aed2;

class ArbolCategorias {

	struct CatInfo {
		CatInfo() : _id(0), _padre(NULL), _hijas(Lista<Categoria>()) {}
		CatInfo(Nat id) : _id(id), _padre(NULL), _hijas(Lista<Categoria>()) {}

		Nat _id;
		CatInfo* _padre;
		Lista<Categoria> _hijas;
	};

	DiccString<CatInfo*> _categorias;
	Categoria _raiz;
	Nat _ultId;

public:

	class IteradorHijas;
	class IteradorPadres;

	ArbolCategorias(const Categoria& raiz);
	virtual ~ArbolCategorias();

	const Categoria raiz() const;
	void agregar(const Categoria& padre, const Categoria& hija);
	IteradorHijas hijas(const Categoria& padre) const;
	IteradorPadres padres(const Categoria& hija) const;
	Nat id(const Categoria& c) const;
	Nat cantCategorias() const;

	class IteradorHijas {
		Lista<Categoria>::Iterador _it;
		IteradorHijas(Lista<Categoria>* lista);
		friend class ArbolCategorias::IteradorHijas ArbolCategorias::hijas(const Categoria& padre) const;

	public:
		void Avanzar();
		bool HaySiguiente() const;
		Categoria Siguiente() const;
	};

	class IteradorPadres {
		CatInfo* _catInfo;

		IteradorPadres(CatInfo* catInfo);
		friend class ArbolCategorias::IteradorPadres ArbolCategorias::padres(const Categoria& padre) const;

	public:
		void Avanzar();
		bool HaySiguiente() const;
		Nat Siguiente() const;
	};
};

#endif /* ARBOLCATEGORIAS_H_ */
