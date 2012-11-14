#ifndef LINKLINKIT_H_
#define LINKLINKIT_H_

#include "ArbolCategorias.h"

class LinkLinkIt {

	struct InfoLink {
		Link link;
		Categoria categoria;
		Fecha ultAcceso;
		Nat accesos[];
	};

	ArbolCategorias& _aCategorias;
	Lista<InfoLink*>* _linksPorCat;
	DiccString<InfoLink>* _infoLinks;

public:

	class IteradorLinks {
	private:
		IteradorLinks();
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
