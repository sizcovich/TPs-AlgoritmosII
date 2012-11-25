#include "Driver.h"
#include "aed2_tests.h"

void driverCtor() {
	Driver d;
}

/**
 * Testea:
 * 		DiccString::
 * 			definir(key)
 * 			obtener(key)
 * 			definido(key)
 * 			significados()
 * 			claves()
 */
void pruebaDiccString() {
	DiccString<Nat> dicc = DiccString<Nat>();
	dicc.definir("Barabas, Ariel",    77511);
	dicc.definir("Izcovich, Sabrina", 55011);
	dicc.definir("Otero, Fernando",   42411);
	dicc.definir("Vita, Sebastian",   14911);

    ASSERT_EQ(dicc.definido("Izcovich, Sabrina"), true);
    ASSERT_EQ(dicc.definido("Barabas, Ariel"), true);
    ASSERT_EQ(dicc.definido("Arroz con pollo"), false);

	ASSERT_EQ(dicc.obtener("Izcovich, Sabrina"), 55011);
	ASSERT_EQ(dicc.obtener("Otero, Fernando"), 42411);
	ASSERT_EQ(dicc.obtener("Vita, Sebastian"), 14911);
	ASSERT_EQ(dicc.obtener("Barabas, Ariel"), 77511);

	ASSERT_EQ(dicc.significados().Longitud(), dicc._elementosEnTrie);
	ASSERT_EQ(dicc.significados().Primero(), 77511);

	ASSERT_EQ(dicc.claves().Longitud(), 4);
	ASSERT_EQ(dicc.claves().Primero(), "Barabas, Ariel");
}

/**
 * Testea:
 * 		ArbolCategorias::
 * 			ArbolCategorias(raiz)
 * 			agregar(padre, hija)
 */
Driver crearArbolDePrueba() {
	Driver d;
    /**
     * cat1
     *  |- cat2
     *  \- cat3
     *      \- cat4
     */
    d.nuevoArbol("cat1");
    d.agregarCategoria("cat1","cat2");
    d.agregarCategoria("cat1","cat3");
    d.agregarCategoria("cat3","cat4");

    return d;
}

/**
 * Testea:
 * 		ArbolCategorias::
 * 			hijas(cat)
 * 			IteradorHijas::
 * 				IteradorHijas(lista)
 * 				HaySiguiente()
 * 				Avanzar()
 */
void agregarCategorias() {
	Driver d = crearArbolDePrueba();

    ASSERT_EQ(d.cantCategoriasHijas("cat1"), 2);
    ASSERT_EQ(d.cantCategoriasHijas("cat2"), 0);
    ASSERT_EQ(d.cantCategoriasHijas("cat3"), 1);
}

/**
 * Testea:
 * 		ArbolCategorias::id(cat)
 */
void agregaCategoriasConId() {
	Driver d = crearArbolDePrueba();

    ASSERT_EQ(d.id("cat1"), 1);
    ASSERT_EQ(d.id("cat2"), 2);
    ASSERT_EQ(d.id("cat3"), 3);
    ASSERT_EQ(d.id("cat4"), 4);
}

/**
 * Testea:
 * 		LinkLinkIt::
 * 			LinkLinkIt(ab)
 * 			agregarLink(link, categoria)
 */
Driver crearLinkLinkIt() {
	Driver d = crearArbolDePrueba();

	d.nuevoLink("http://zuma.aws.af.cm/",   "cat1");
	d.nuevoLink("http://www.dc.uba.ar/",    "cat2");
	d.nuevoLink("http://www.facebook.com/", "cat3");
	d.nuevoLink("http://www.9gag.com/",     "cat4");
    ASSERT_EQ(d.cantLinks("cat1"), 1);
	return d;
}


int main(void) {
    RUN_TEST(driverCtor);
    RUN_TEST(pruebaDiccString);
    RUN_TEST(crearArbolDePrueba);
    RUN_TEST(agregarCategorias);
    RUN_TEST(agregaCategoriasConId);
    RUN_TEST(crearLinkLinkIt);
	return 0;
}
