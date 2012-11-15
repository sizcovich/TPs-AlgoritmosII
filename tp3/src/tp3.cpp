#include "Driver.h"
#include "aed2_tests.h"

void driverCtor() {
	Driver d;
}

void pruebaDiccString() {
	DiccString<Nat> dicc = DiccString<Nat>();
	dicc.definir("Barabas, Ariel", 77511);
	dicc.definir("Izcovich, Sabrina", 55011);
	dicc.definir("Otero, Fernando", 42411);
	dicc.definir("Vita, Sebastián", 14911);

	ASSERT_EQ(dicc.obtener("Barabas, Ariel"), 77511);
	ASSERT_EQ(dicc.significados().Longitud(), 4);
	ASSERT_EQ(dicc.claves().Longitud(), 4);
    ASSERT_EQ(dicc.definido("Izcovich, Sabrina"), true);
    ASSERT_EQ(dicc.definido("Arroz con pollo"), false);
    //significados
    
    ASSERT_EQ(ArbolCategorias("tomate").raiz(), "tomate");
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


int main(void) {
    //RUN_TEST(driverCtor);
    RUN_TEST(pruebaDiccString);
    //RUN_TEST(crearArbolDePrueba);
    //RUN_TEST(agregarCategorias);
    //RUN_TEST(agregaCategoriasConId);
	return 0;
}
