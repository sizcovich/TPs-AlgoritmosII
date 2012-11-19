#ifndef LINKLINKIT_H_
#define LINKLINKIT_H_

#include "ArbolCategorias.h"
#include "aed2/Lista.h"

class LinkLinkIt {

	struct InfoLink {
		Link link;
		Categoria categoria;
		Fecha ultAcceso;
		Nat accesos[];
	};

	ArbolCategorias& _aCategorias;
	Lista<InfoLink*> _linksPorCat[];
	DiccString<InfoLink>* _infoLinks;

public:

	class IteradorLinks {
	    Iterador(lista<InfoLink*>) _it;
	    Fecha _ultAcceso;
	private:
		IteradorLinks(Lista<InfoLink>, Fecha);
		friend IteradorLinks linksOrdenadosPorAccesos(const Categoria&);
	public:
		void Avanzar();
		bool HaySiguiente() const;
		Link SiguienteLink() const;
		Link SiguienteCategoria() const;
		Link SiguienteAccesosRecientes() const;
	};

	LinkLinkIt(ArbolCategorias& abCat);
	virtual ~LinkLinkIt();

	void agregarLink(const Link& l, const Categoria& c);
	void accederLink(const Link& l, const Fecha& f);
	Nat cantLinks(const Categoria& c);
	IteradorLinks linksOrdenadosPorAccesos(const Categoria& c);
};

#endif /* LINKLINKIT_H_ */
