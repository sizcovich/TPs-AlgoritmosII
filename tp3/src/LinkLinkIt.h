#ifndef LINKLINKIT_H_
#define LINKLINKIT_H_

#include "ArbolCategorias.h"
#include "aed2/Arreglo.h"
#include "aed2/Lista.h"

class LinkLinkIt {

	struct InfoLink {
		InfoLink(const Link& l, const Categoria& c) : link(l), categoria(c), ultAcceso(0), accesos(Arreglo<Nat>(3)) {
		    for (int i = 0; i < 3; i++)
		    	accesos.Definir(i, 0);
		};

		Link link;
		Categoria categoria;
		Fecha ultAcceso;
		Arreglo<Nat> accesos;

		Nat puntajeDelLink(Fecha f) const;
	};

	ArbolCategorias& _aCategorias;
	Arreglo<Lista<InfoLink*> > _linksPorCat;
	DiccString<InfoLink*> _infoLinks;

public:

	class IteradorLinks;

	LinkLinkIt(ArbolCategorias& abCat);
	virtual ~LinkLinkIt();

	void agregarLink(const Link& l, const Categoria& c);
	void accederLink(const Link& l, const Fecha f);
	Nat cantLinks(const Categoria& c);
	IteradorLinks linksOrdenadosPorAccesos(const Categoria& c);

	class IteradorLinks {
	    Lista<InfoLink*>::const_Iterador _it;
	    Fecha _ultAcceso;
	private:
		IteradorLinks(const Lista<InfoLink*>& ls, Fecha f);
		friend LinkLinkIt::IteradorLinks LinkLinkIt::linksOrdenadosPorAccesos(const Categoria& c);
	public:
		bool HaySiguiente() const;
		const Link& SiguienteLink() const;
		const Categoria& SiguienteCategoria() const;
		Nat SiguienteAccesosRecientes() const;
		void Avanzar();
	};
};

#endif /* LINKLINKIT_H_ */
