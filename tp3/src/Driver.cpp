#include "Driver.h"

#include <iostream>
#include <sstream>

Driver::Driver() {
    arbol = NULL;
    sistema = NULL;
}

Driver::~Driver() {
    // el arbol de categorías se destruye si fue creado
    if (arbol != NULL)
        delete arbol;

    // el linklinkit se destruye si fue creado
    if (sistema != NULL)
        delete sistema;
}

void Driver::nuevoArbol(const Categoria& raiz)
{
    if (arbol != NULL)
        delete arbol;
    arbol = new ArbolCategorias(raiz);
}

void Driver::agregarCategoria(const Categoria& c, const Categoria& h)
{
    arbol->agregar(c,h);
}

const Categoria& Driver::raiz()
{
    return arbol->raiz();
}

int Driver::id(const Categoria& c)
{
    return arbol->id(c);
}

int Driver::cantCategoriasHijas(const Categoria& c)
{
    int i = 0;
    ArbolCategorias::IteradorHijas it = arbol->hijas(c);
    while(it.HaySiguiente())
    {
        ++i;
        it.Avanzar();
    }
    return i;
}

const Categoria& Driver::obtenerIesimaCategoriaHija(const Categoria& c, int i)
{
    int j = 0;
    ArbolCategorias::IteradorHijas it = arbol->hijas(c);
    while(j < i)
    {
        ++j;
        it.Avanzar();
    }
    return it.Siguiente();
}

void Driver::nuevoLink(const Link& l, const Categoria& c)
{
    if (sistema == NULL)
        sistema = new LinkLinkIt(*arbol);

    sistema->agregarLink(l,c);
}

void Driver::acceso(const Link& l, Fecha f)
{
    sistema->accederLink(l, f);
}

int Driver::cantLinks(const Categoria& c)
{
    return sistema->cantLinks(c);
}

const Nat Driver::obtenerCantidadLinksOrdenadosPorAccesos(const Categoria& c) {
	Nat i = 0;
	LinkLinkIt::IteradorLinks itLinks = sistema->linksOrdenadosPorAccesos(c);
	while (itLinks.HaySiguiente()) {
		i++;
		itLinks.Avanzar();
	}
	return i;
}

const Link& Driver::obtenerIesimoLinkOrdenadoPorAccesos(const Categoria& c, int i)
{
    int j = 0;
    LinkLinkIt::IteradorLinks it = sistema->linksOrdenadosPorAccesos(c);
    while(j < i)
    {
        ++j;
        it.Avanzar();
    }
    return it.SiguienteLink();
}

const Categoria& Driver::obtenerCategoriaIesimoLinkOrdenadoPorAccesos(const Categoria& c, int i)
{

    int j = 0;
    LinkLinkIt::IteradorLinks it = sistema->linksOrdenadosPorAccesos(c);
    while(j < i)
    {
        ++j;
        it.Avanzar();
    }
    return it.SiguienteCategoria();
}

int Driver::obtenerCantidadAccesosIesimoLinkOrdenadoPorAccesos(const Categoria& c, int i)
{
    int j = 0;
    LinkLinkIt::IteradorLinks it = sistema->linksOrdenadosPorAccesos(c);
    while(j < i)
    {
        ++j;
        it.Avanzar();
    }
    return it.SiguienteAccesosRecientes();
}
