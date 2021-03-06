#include "LinkLinkIt.h"
#include "aed2/Lista.h"
#include "aed2/TiposBasicos.h"


LinkLinkIt::LinkLinkIt(ArbolCategorias& abCat) : _aCategorias(abCat) {
	_infoLinks = DiccString<InfoLink*>();
	_linksPorCat = Arreglo<Lista<InfoLink*> >(abCat.cantCategorias());

	for (Nat i = 0; i < abCat.cantCategorias(); i++) {
		Lista<InfoLink*> a;
		_linksPorCat.Definir(i, a);
	}
}

LinkLinkIt::~LinkLinkIt() {
    Lista<InfoLink*> info = _infoLinks.significados();
	Lista<InfoLink*>::Iterador it = info.CrearIt();
	while (it.HaySiguiente()) {
		delete it.Siguiente();
		it.Avanzar();
	}
}

Nat LinkLinkIt::cantLinks(const Categoria& c) {
    Nat categoriaID = _aCategorias.id(c);
    return _linksPorCat[categoriaID - 1].Longitud();
}


void LinkLinkIt::agregarLink(const Link& l, const Categoria& c) {
    Nat categoriaID = _aCategorias.id(c);
    InfoLink* info = new InfoLink(l, c);
    _infoLinks.definir(l, info);

    _linksPorCat[categoriaID-1].AgregarAtras(info);

    ArbolCategorias::IteradorPadres it = _aCategorias.padres(c);
    while (it.HaySiguiente())
    {
        it.Avanzar();
        categoriaID = it.Siguiente();
        _linksPorCat[categoriaID-1].AgregarAtras(info);
    }
}

void LinkLinkIt::accederLink(const Link& l, const Fecha f) {
    InfoLink* link = _infoLinks.obtener(l);
 /*   Nat diff = f - link->ultAcceso;

    Nat i = 0;
    while (i < (3 - diff)) {
    	if (i + diff < 3 && i + diff >= 0 && i >= 0 && i < 3)
    		link->accesos.Definir(i, link->accesos[i + diff]);
        i++;
    }

    i = 0;
    while (i < diff && i < 3) {
    	link->accesos.Definir(2 - i, 0);
        i++;
    }*/


    if(f == link->ultAcceso + 1)
    {
    	link->accesos.Definir(0, link->accesos[1]);
    	link->accesos.Definir(1, link->accesos[2]);
    	link->accesos.Definir(2, 0);
    }

    if(f == link->ultAcceso + 2)
    {
    	link->accesos.Definir(0, link->accesos[2]);
    	link->accesos.Definir(1, 0);
    	link->accesos.Definir(2, 0);
    }
    if(f > link->ultAcceso + 2)
    {
    	link->accesos.Definir(0, 0);
    	link->accesos.Definir(1, 0);
    	link->accesos.Definir(2, 0);
    }

    link->ultAcceso = f;
    link->accesos.Definir(2, link->accesos[2] + 1);

}


Nat max(Nat a, Nat b) {
	if (a > b)
		return a;
	return b;
}


Nat LinkLinkIt::InfoLink::puntajeDelLink(Fecha f) const {
	Nat res = 0;
	Nat i = 3;
	while ((f - ultAcceso) < i) {
        i--;
        res += accesos[i];
	}
	return res;
}


LinkLinkIt::IteradorLinks LinkLinkIt::linksOrdenadosPorAccesos(const Categoria& c){
    Nat categoriaID = _aCategorias.id(c);
    Lista<InfoLink*>& lista = _linksPorCat[categoriaID - 1];

    if (lista.EsVacia()) {
    	return IteradorLinks(lista, 0);
    }

    Lista<InfoLink*>::Iterador it = lista.CrearIt();
    Fecha f = 0;

    while(it.HaySiguiente()) {
        f = max(it.Siguiente()->ultAcceso, f);
        it.Avanzar();
    }

    it = lista.CrearIt();
    bool estaOrdenada = true;
    Nat ultPuntaje = it.Siguiente()->puntajeDelLink(f);
    while(it.HaySiguiente() && estaOrdenada) {
		estaOrdenada = ultPuntaje >= it.Siguiente()->puntajeDelLink(f);
        ultPuntaje = it.Siguiente()->puntajeDelLink(f);
        it.Avanzar();
    }
    if (estaOrdenada)
        return IteradorLinks(lista, f);

    Lista<InfoLink*> listaOrdenada;
    Lista<InfoLink*>::Iterador itOrd = listaOrdenada.CrearIt();
    while (!lista.EsVacia()) {
        Lista<InfoLink*>::Iterador itRes = lista.CrearIt(),
        						   itMaxAccesos = lista.CrearIt();
        while (itRes.HaySiguiente()) {
            if (itRes.Siguiente()->puntajeDelLink(f) > itMaxAccesos.Siguiente()->puntajeDelLink(f))
                itMaxAccesos = Lista<InfoLink*>::Iterador(itRes);
			itRes.Avanzar();
        }
        itOrd.AgregarComoAnterior(itMaxAccesos.Siguiente());
        itMaxAccesos.EliminarSiguiente();
    }

    _linksPorCat[categoriaID - 1] = listaOrdenada;
    return IteradorLinks(_linksPorCat[categoriaID - 1], f);
}

LinkLinkIt::IteradorLinks::IteradorLinks(const Lista<InfoLink*>& ls, Fecha f) {
    _it = ls.CrearIt();
    _ultAcceso = f;
}

const Link& LinkLinkIt::IteradorLinks::SiguienteLink() const {
    return _it.Siguiente()->link;
}

const Categoria& LinkLinkIt::IteradorLinks::SiguienteCategoria() const {
    return _it.Siguiente()->categoria;
}

Nat LinkLinkIt::IteradorLinks::SiguienteAccesosRecientes() const {
    return _it.Siguiente()->puntajeDelLink(_ultAcceso);
}

bool LinkLinkIt::IteradorLinks::HaySiguiente() const {
    if (_it.HaySiguiente() && _it.Siguiente() != NULL)
        return _it.Siguiente()->puntajeDelLink(_ultAcceso) > 0;

    return false;
}

void LinkLinkIt::IteradorLinks::Avanzar() {
	_it.Avanzar();
}
