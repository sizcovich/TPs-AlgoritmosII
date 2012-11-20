#include "LinkLinkIt.h"
#include "aed2/Lista.h"
#include "aed2/TiposBasicos.h"


LinkLinkIt::LinkLinkIt(ArbolCategorias& abCat) : _aCategorias(abCat) {
	_infoLinks = DiccString<InfoLink*>();
	_linksPorCat = Arreglo<Lista<InfoLink*> >(abCat.cantCategorias());
}

LinkLinkIt::~LinkLinkIt() {
}

Nat LinkLinkIt::cantLinks(const Categoria& c) {
    int categoriaID = _aCategorias.id(c);
    return _linksPorCat[categoriaID].Longitud();
}


void LinkLinkIt::agregarLink(const Link& l, const Categoria& c) {
    int categoriaID = _aCategorias.id(c);

    InfoLink* info = new InfoLink(l, c);

    _infoLinks.definir(l, info);
    _linksPorCat[categoriaID-1].AgregarAtras(info);

    ArbolCategorias::IteradorPadres it = _aCategorias.padres(c);
    while (it.HaySiguiente())
    {
        it.Avanzar();
        categoriaID = it.HaySiguiente();
        _linksPorCat[categoriaID-1].AgregarAtras(info);
    }
}

void LinkLinkIt::accederLink(const Link& l, const Fecha& f) {
    InfoLink* link = _infoLinks.obtener(l);
    int diff = f - link->ultAcceso;

    int i = 0;
    while (i < (3 - diff)) {
        link->accesos[i] = link->accesos[i + diff];
        i++;
    }

    i = 0;
    while (i < diff && i < 3) {
        link->accesos[2 - i] = 0;
        i++;
    }

    link->ultAcceso = f;
    link->accesos[2] += 1;
}


Nat max(Nat a, Nat b) {
	if (a > b)
		return a;
	return b;
}


Nat LinkLinkIt::InfoLink::puntajeDelLink(Fecha f) const {
	Nat res = 0;
	int i = 3;
	while ((f - ultAcceso) < i) {
        i--;
        res += accesos[i];
	}

	return res;
}


LinkLinkIt::IteradorLinks LinkLinkIt::linksOrdenadosPorAccesos(const Categoria& c){
    int categoriaID = _aCategorias.id(c);
    Lista<InfoLink*> lista = _linksPorCat[categoriaID - 1];

    Lista<InfoLink*>::Iterador it = lista.CrearIt();
    Fecha f = 0;

    while(it.HaySiguiente()) {
        f = max(it.Siguiente()->ultAcceso, f);
        it.Avanzar();
    }

    it = lista.CrearIt();
    bool estaOrdenada = true;
    Nat ultPuntaje = 0;
    while(it.HaySiguiente() && estaOrdenada) {
        if (ultPuntaje > 0)
            estaOrdenada = ultPuntaje >= it.Siguiente()->puntajeDelLink(f);
        ultPuntaje = it.Siguiente()->puntajeDelLink(f);
    }
    if (estaOrdenada)
        return IteradorLinks(lista, f);

    Lista<InfoLink*> listaOrdenada = Lista<InfoLink*>();
    Lista<InfoLink*>::Iterador itOrd = listaOrdenada.CrearIt();
    while (!lista.EsVacia()) {
        Lista<InfoLink*>::Iterador itRes = lista.CrearIt(),
        						   itMaxAccesos = lista.CrearIt();
        while (itRes.HaySiguiente()) {
            if (itRes.Siguiente()->puntajeDelLink(f) > itMaxAccesos.Siguiente()->puntajeDelLink(f))
                itMaxAccesos = itRes;
        }
        itOrd.AgregarComoAnterior(itMaxAccesos.Siguiente());
        itMaxAccesos.EliminarSiguiente();

    }
    _linksPorCat[categoriaID - 1] = listaOrdenada;
    return IteradorLinks(listaOrdenada, f);
}

LinkLinkIt::IteradorLinks::IteradorLinks(Lista<InfoLink*>& ls, Fecha f) {
    _it = ls.CrearIt();
    _ultAcceso = f;
}

Link LinkLinkIt::IteradorLinks::SiguienteLink() const {
    return _it.Siguiente()->link;
}

Categoria LinkLinkIt::IteradorLinks::SiguienteCategoria() const {
    return _it.Siguiente()->categoria;
}


Nat LinkLinkIt::IteradorLinks::SiguienteAccesosRecientes() const {
    return _it.Siguiente()->puntajeDelLink(_ultAcceso);
}

bool LinkLinkIt::IteradorLinks::HaySiguiente() const {
    return _it.HaySiguiente() && _it.Siguiente()->puntajeDelLink(_ultAcceso) > 0;
}

void LinkLinkIt::IteradorLinks::Avanzar() {
	_it.Avanzar();
}
