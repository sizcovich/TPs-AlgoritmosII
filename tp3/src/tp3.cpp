#include "Driver.h"
#include "aed2_tests.h"
#include "LinkLinkIt.h"

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

using namespace std;


                    
                    

                    
using namespace std;


void diccVacioEsVacio(){
    DiccString<string> d;
    ASSERT((d.claves()).EsVacia());
}

void construirDicc(){
    DiccString<string> d;
    const string sign1 = "signif1";
    d.definir("clave2", "signif2");
    d.definir("clave1", sign1);
    ASSERT(d.definido("clave1"));
    ASSERT(d.definido("clave3"));
}

void signifNoConstEsModificable(){
    DiccString<string>* d = new DiccString<string>;
    d->definir("clave1", "signif1"); //Agrega bien
    ASSERT(d->obtener("clave1") == "signif1");
    
    d->obtener("clave1") = "mod!"; //Se pueden modificar los significados
    ASSERT(d->obtener("clave1") == "mod!");
    
    d->definir("clave1", "pepe"); //No se pueden agregar claves repetidas
    ASSERT(d->obtener("clave1") == "mod!");
    
    delete d;
}

/*
void iteradorFunciona()
    diccT<string> d;
    diccT<string>::ItDiccT itaux = d.agregarT("clave4", "signif4");//Devuelve un iterador correcto
    ASSERT(itaux.ClaveActualItT() == "clave4");
    ASSERT(itaux.SignificadoActualItT() == "signif4");
    d.agregarT("clave3", "signif3");
    itaux = d.agregarT("clave2", "signif2");//Devuelve un iterador correcto
    ASSERT(itaux.ClaveActualItT() == "clave2");
    ASSERT(itaux.SignificadoActualItT() == "signif2");
    d.agregarT("clave1", "signif1");
    diccT<string>::ItDiccT it = d.CrearItT();
    ASSERT(it.HaySiguienteItT()==true);
    ASSERT(it.ClaveActualItT() == "clave1");
    ASSERT(it.SignificadoActualItT() == "signif1");
    it.AvanzarItT();
    ASSERT(it.ClaveActualItT() == "clave2");
    ASSERT(it.SignificadoActualItT() == "signif2");
    it.SignificadoActualItT() = "cambiado"; //Porque permite modificar el significado
    ASSERT(it.SignificadoActualItT() == "cambiado");
    it.AvanzarItT();
    ASSERT(it.ClaveActualItT() == "clave3");
    ASSERT(it.SignificadoActualItT() == "signif3");
    it.AvanzarItT();
    ASSERT(it.ClaveActualItT() == "clave4");
    ASSERT(it.SignificadoActualItT() == "signif4");
    it.AvanzarItT();
    ASSERT(it.HaySiguienteItT()==false);
}
/*
void iteradorConstFunciona()
    diccT<string> d;
    d.agregarT("clave4", "signif4");
    d.agregarT("clave3", "signif3");
    d.agregarT("clave2", "signif2");
    d.agregarT("clave1", "signif1");
    diccT<string>::ItDiccT_const it = d.CrearItT_const();
    ASSERT(it.HaySiguienteItT()==true);
    ASSERT(it.ClaveActualItT() == "clave1");
    ASSERT(it.SignificadoActualItT() == "signif1");
    it.AvanzarItT();
    ASSERT(it.ClaveActualItT() == "clave2");
    ASSERT(it.SignificadoActualItT() == "signif2");
    //it.SignificadoActualItT() = "cambiado"; //SI SACO EL COMENTARIO NO COMPILA PORQUE ES CONSTANTE (ERA LA IDEA)
    it.AvanzarItT();
    ASSERT(it.ClaveActualItT() == "clave3");
    ASSERT(it.SignificadoActualItT() == "signif3");
    it.AvanzarItT();
    ASSERT(it.ClaveActualItT() == "clave4");
    ASSERT(it.SignificadoActualItT() == "signif4");
    it.AvanzarItT();
    ASSERT(it.HaySiguienteItT()==false);
}

void constructorPorCopia()
    diccT<string> d;
    d.agregarT("clave4", "signif4");
    d.agregarT("clave3", "signif3");
    d.agregarT("clave2", "signif2");
    d.agregarT("clave1", "signif1");
                        
    diccT<string> m(d);
                        
    ASSERT(m.obtenerT("clave4")== d.obtenerT("clave4"));
                    
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

/*void crearArbolCategorias()
{
    ArbolCategorias r("Muebles"); //Normal //Id:1
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
    r.agregar("Sillones","Dobles");//Id: 13
    
    ASSERT(r.id("Muebles")==1);
    ASSERT(r.id("Comedor")==7);
    ASSERT(r.id("Dobles")==13);
    
    ArbolCategorias r2(r); //Por copia
    
    ASSERT(r2.id("Muebles")==1);
    ASSERT(r2.id("Comedor")==7);
    ASSERT(r2.id("Dobles")==13);
    
    /** A PARTIR DE ACA TESTEO FUNCIONES QUE NECESITO PARA LINKLINKIT */
    
//    //UltimoId() anda
//    ASSERT(r._ultId()==r2._ultId());
//    ASSERT(r._ultId()==13);
//    
//    //itCat (Categorias() ) anda
//    ArbolCategorias::itCat it = r.Categorias();
//    ASSERT_EQ(it.HaySiguiente(),true);
//    ASSERT(it.IdActualItCat()==1); //Empieza apuntando al primero agregado
//    ASSERT(it.IdPadreActualItCat()==1);
//    it.SiguienteItCatH();
//    ASSERT_EQ(it.HaySiguienteItCat(),true);
//    ASSERT(it.IdActualItCat()==2);
//    ASSERT(it.IdPadreActualItCat()==1);
//    it.SiguienteItCatH();
//    it.SiguienteItCatH();
//    it.SiguienteItCatH();
//    ASSERT_EQ(it.HaySiguienteItCat(),true);
//    ASSERT(it.IdActualItCat()==5);
//    ASSERT(it.IdPadreActualItCat()==4);
//    for (int i=0;i<9;i++)
//    {it.SiguienteItCatH();}
//    ASSERT_EQ(it.HaySiguienteItCat(),false);
//    ASSERT(it.IdActualItCat()==13);
//    ASSERT(it.IdPadreActualItCat()==10);
//    it.SiguienteItCatH();
//    ASSERT_EQ(it.HaySiguienteItCat(),false);
//    //
//    
//}


 /* Testea:
 * 		ArbolCategorias::
 * 			raiz()
 * 			hijas(cat)
 * 			IteradorHijas::
 * 				IteradorHijas(lista)
 * 				HaySiguiente()
 * 				Avanzar()
 */
void agregarCategorias(){
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
    d.nuevoLink("www.gmail.com",	"cat3");
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
    d.acceso("www.gmail.com",  1); // cat3
    d.acceso("www.gmail.com",  2); // cat3
    d.acceso("www.gmail.com",  3); // cat3

    ASSERT_EQ(d.obtenerIesimoLinkOrdenadoPorAccesos("cat3", 1), "www.gmail.com");
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
//    ASSERT_EQ(llt2.puntajeDelLink(1), 3);

    
//    LinkLinkIt::IteradorLinks it = ->linksOrdenadosPorAccesos(llt2);
//    llt2.linksOrdenadosPorAccesos("Muebles");
//    ASSERT(llt2.SiguienteLink()=="romero.com");
//    llt2.Avanzar();
//    ASSERT(llt2.SiguienteLink()=="marcelo.com");
    
}



int main(void) {
//    RUN_TEST(driverCtor);
//    RUN_TEST(pruebaDiccString);
//    RUN_TEST(diccVacioEsVacio);
//    RUN_TEST(construirDiccT);
//    RUN_TEST(signifNoConstEsModificable);
//    RUN_TEST(iteradorFunciona);
//    RUN_TEST(iteradorConstFunciona);
//    RUN_TEST(constructorPorCopia);
//    RUN_TEST(crearArbolDePrueba);
//    RUN_TEST(crearArbolCategorias);
//    RUN_TEST(agregarCategorias);
//    RUN_TEST(agregaCategoriasConId);
//    RUN_TEST(crearLinkLinkIt);
//    RUN_TEST(probarCantLinks);
//    RUN_TEST(obtenerIesimoLink);
//    RUN_TEST(obtenerCategoriaIesima);
    RUN_TEST(obtenerCantidadAccesos);
//    RUN_TEST(crearLinklinkitbis);
//    RUN_TEST(agregarLinksAnda);
//    RUN_TEST(losAccesosSonCorrectos);

	return 0;
}
