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
 * 			raiz()
 * 			hijas(cat)
 * 			IteradorHijas::
 * 				IteradorHijas(lista)
 * 				HaySiguiente()
 * 				Avanzar()
 */
void agregarCategorias() {
	Driver d = crearArbolDePrueba();

	ASSERT_EQ(d.raiz(), "cat1");

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
    d.nuevoLink("http://www.gmail.com/",	"cat3");
	d.nuevoLink("http://www.facebook.com/", "cat3");
	d.nuevoLink("http://www.9gag.com/",     "cat4");

	return d;
}

/**
 * Testea:
 *		LinkLinkIt::cantLinks(cat)
 */
void probarCantLinks(){
    Driver d = crearLinkLinkIt();

    ASSERT_EQ(d.cantLinks("cat1"), 5);
    ASSERT_EQ(d.cantLinks("cat4"), 1);
    ASSERT_EQ(d.cantLinks("cat3"), 3);
    ASSERT_EQ(d.cantLinks("cat2"), 1);
}

/**
 * Testea:
 *		LinkLinkIt::
 *			linksOrdenadosPorAccesos(cat)
 *			acceso(link, fecha)
 *			Avanzar()
 *			SiguienteLink()
 */
void obtenerIesimoLink(){
    Driver d = crearLinkLinkIt();

    d.acceso("http://zuma.aws.af.cm/", 1); // cat1
    d.acceso("http://www.gmail.com/",  1); // cat3
    d.acceso("http://www.gmail.com/",  2); // cat3
    d.acceso("http://www.gmail.com/",  3); // cat3

    ASSERT_EQ(d.obtenerIesimoLinkOrdenadoPorAccesos("cat3", 2), "http://www.gmail.com/");
}

/**
 * Testea:
 *		LinkLinkIt::
 *			linksOrdenadosPorAccesos(cat)
 *			acceso(link, fecha)
 *			Avanzar()
 *			SiguienteCategoria()
 */
void obtenerCategoriaIesima(){
    Driver d = crearLinkLinkIt();
    d.acceso("http://www.9gag.com/", 1);
    d.acceso("http://www.9gag.com/", 2);
    ASSERT_EQ(d.obtenerCategoriaIesimoLinkOrdenadoPorAccesos("cat1", 1), "cat4");
    ASSERT_EQ(d.obtenerCategoriaIesimoLinkOrdenadoPorAccesos("cat1", 2), "cat4");
}


/**
 * Testea:
 *		LinkLinkIt::
 *			linksOrdenadosPorAccesos(cat)
 *			acceso(link, fecha)
 *			Avanzar()
 *			SiguienteAccesosRecientes()
 */
void obtenerCantidadAccesos(){
    Driver d = crearLinkLinkIt();
    d.acceso("http://www.9gag.com/", 1);
    d.acceso("http://www.9gag.com/", 2);
    ASSERT_EQ(d.obtenerCantidadAccesosIesimoLinkOrdenadoPorAccesos("cat4", 1), 2);
}

void crearLinklinkitbis()
{
    ArbolCategorias r("Muebles");
    r.agregar("Muebles","Sillas");
    r.agregar("Muebles","Mesas");
    r.agregar("Muebles","Armarios");
    r.agregar("Armarios","Cajoneras");
    r.agregar("Armarios","Roperos");
    r.agregar("Sillas","Comedor");
    r.agregar("Sillas","Playa");
    r.agregar("Sillas","Living");
    r.agregar("Living","Sillones");
    r.agregar("Living","Sofa");
    r.agregar("Sillones","Simples");
    r.agregar("Sillones","Dobles");
    LinkLinkIt llt(r);
}

void agregarLinksAnda()
{
    ArbolCategorias r2("Muebles");
    r2.agregar("Muebles","Sillas");
    r2.agregar("Muebles","Mesas");
    r2.agregar("Muebles","Armarios");
    r2.agregar("Armarios","Cajoneras");
    r2.agregar("Armarios","Roperos");
    r2.agregar("Sillas","Comedor");
    r2.agregar("Sillas","Playa");
    r2.agregar("Sillas","Living");
    r2.agregar("Living","Sillones");
    r2.agregar("Living","Sofa");
    r2.agregar("Sillones","Simples");
    r2.agregar("Sillones","Dobles");
    LinkLinkIt llt2(r2);
    llt2.agregarLink("pedro.com","Muebles");
    llt2.agregarLink("sandro.com","Muebles");
    llt2.agregarLink("romero.com","Cajoneras");
    llt2.agregarLink("roco.com","Playa");
    llt2.agregarLink("marcelo.com","Playa");
    llt2.agregarLink("matias.com","Playa");
    ASSERT(llt2.cantLinks("Muebles")==6);
    ASSERT(llt2.cantLinks("Playa")==3);
    ASSERT(llt2.cantLinks("Dobles")==0);
}

void losAccesosSonCorrectos()
{
    ArbolCategorias r2("Muebles");
    r2.agregar("Muebles","Sillas");
    r2.agregar("Muebles","Mesas");
    r2.agregar("Muebles","Armarios");
    r2.agregar("Armarios","Cajoneras");
    r2.agregar("Armarios","Roperos");
    r2.agregar("Sillas","Comedor");
    r2.agregar("Sillas","Playa");
    r2.agregar("Sillas","Living");
    r2.agregar("Living","Sillones");
    r2.agregar("Living","Sofa");
    r2.agregar("Sillones","Simples");
    r2.agregar("Sillones","Dobles");
    LinkLinkIt llt2(r2);
    llt2.agregarLink("pedro.com","Muebles");
    llt2.agregarLink("sandro.com","Muebles");
    llt2.agregarLink("romero.com","Cajoneras");
    llt2.agregarLink("roco.com","Playa");
    llt2.agregarLink("marcelo.com","Playa");
    llt2.agregarLink("matias.com","Playa");
    //El orden esperado es: sandro - romero - marcelo - matias
    llt2.accederLink("matias.com",1);
    llt2.accederLink("matias.com",1);
    llt2.accederLink("matias.com",1);
    llt2.accederLink("marcelo.com",3);
    llt2.accederLink("marcelo.com",3);
    llt2.accederLink("sandro.com",5);
    llt2.accederLink("romero.com",5);
    llt2.accederLink("sandro.com",6);
    llt2.accederLink("sandro.com",7);
    
    
//    LinkLinkIt::itOrdLlt it = llt2.linksOrdPorAccesoLlt("Muebles");
//    ASSERT(it.nombreActualItLlt()=="sandro.com");
//    it.siguienteItLlt();
//    ASSERT(it.nombreActualItLlt()=="romero.com");
    
}



int main(void) {
    RUN_TEST(driverCtor);
    RUN_TEST(pruebaDiccString);
    RUN_TEST(crearArbolDePrueba);
    RUN_TEST(agregarCategorias);
    RUN_TEST(agregaCategoriasConId);
    RUN_TEST(crearLinkLinkIt);
    RUN_TEST(probarCantLinks);
    RUN_TEST(obtenerIesimoLink);
    RUN_TEST(obtenerCategoriaIesima);
    RUN_TEST(obtenerCantidadAccesos);
    RUN_TEST(crearLinklinkitbis);
    RUN_TEST(agregarLinksAnda);
    RUN_TEST(losAccesosSonCorrectos);

	return 0;
}
