#include "LinkLinkIt.h"

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


}*/


