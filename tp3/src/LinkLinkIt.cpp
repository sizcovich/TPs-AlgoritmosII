#include "LinkLinkIt.h"
#include "aed2/Lista.h"
#include "aed2/TiposBasicos.h"


LinkLinkIt::LinkLinkIt(ArbolCategorias& abCat) : _aCategorias(abCat) {
	_infoLinks = new DiccString<InfoLink>();
}

LinkLinkIt::~LinkLinkIt() {
	delete _infoLinks;
}

Nat LinkLinkIt::cantLinks(const Categoria& c) {
    int categoriaID = _aCategorias.id(c);
    return _linksPorCat[categoriaID].Longitud();
}


void LinkLinkIt::agregarLink(const Link& l, const Categoria& c) {
    int categoriaID = _aCategorias.id(c);

    InfoLink* info = new InfoLink;
    info->link = l;
    info->categoria = c;
    info->ultAcceso = 0;
    for (int i = 0; i < 3; i++)
        info->accesos[i] = 0;

    _infoLinks->definir(l,*info);
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
    InfoLink link = _infoLinks->obtener(l);
    int diff = f - link.ultAcceso;

    int i = 0;
    while(i < (3 - diff)) {
        link.accesos[i] = link.accesos[i + diff];
        i++;
    }

    i = 0;
    while(i < diff && i < 3) {
        link.accesos[2 - i] = 0;
        i++;
    }

    link.ultAcceso = f;
    link.accesos[2] += 1;
}

/*
LinkLinkIt::IteradorLinks LinkLinkIt::linksOrdenadosPorAccesos(const Categoria& c){
    int categoriaID = _aCategorias.id(c);
    Lista<InfoLink*> lista = _linksPorCat[categoriaID - 1];

    const_Iterador it = lista.CrearIt();
    int f = 0;

    while(it.HaySiguiente()) {
        f = max(it.Siguiente.ultAcceso, f);
        it.Avanza();
    }

    const_Iterador it = lista.CrearIt();
    bool estaOrdenada = true;
    int ultPuntaje = -1;
    while(it.HaySiguiente() && estaOrdenada) {
        if(ultPuntaje > -1)
            estaOrdenada = ultPuntaje >= puntajeDelLink(it.Siguiente(), f);
        ultPuntaje = puntajeDelLink(it.Siguiente(), f);
    }
    if(estaOrdenada)
        return IteradorLinks(lista, f);

    Lista listaOrdenada = Lista();
    const_Iterador itOrd = listaOrdenada.CrearIt();
    while(!lista.esVacia()) {
        const_Iterador itRes, itMaxAccesos = lista.CrearIt();
        while(itRes.HaySiguiente())
            if (puntajeDelLink(itRes.Siguiente(), f) > puntajeDelLink(itMaxAccesos.Siguiente, f))
                itMaxAccesos = itRes;
        itOrd.AgregarComoAnterior(itMaxAccesos.Siguiente())
        itMaxAccesos.EliminarSiguiente();

    }
    _linksPorCat[categoriaID - 1] = listaOrdenada;
    return IteradorLinks(listaOrdenada, f);
}*/

LinkLinkIt::IteradorLinks LinkLinkIt::IteradorLinks::IteradorLinks(Lista<InfoLink> ls, Fecha f) {
    _it = ls.Iterador();
    _ultAcceso = f;
}

Link LinkLinkIt::IteradorLinks::SiguienteLink(IteradorLinks itl) {
    return itl._it.Siguiente().link;
}

Categoria LinkLinkIt::IteradorLinks::SiguienteCategoria(IteradorLinks itl) {
    return itl._it.Siguiente().categoria;
}

///HAY Q ARREGLAR PUNTAJE DEL LINK, RECIVE 2 PARAMETROS Y SIEMPRE LE PASAN 3
/*
Nat LinkLinkIt::IteradorLinks::SiguienteAccesosRecientes(IteradorLinks itl) {
    return puntajeDelLink();
}

bool LinkLinkIt::IteradorLinks::HaySiguiente(IteradorLinks itl) {
    return itl._it.Siguiente().categoria;
}*/

 LinkLinkIt::IteradorLinks::Avanzar()(IteradorLinks itl) {
    return itl._it.Avanzar();
}
