#include "anillo.h"
#include "aed2_tests.h"

template<typename T>
string to_s(const Anillo<T>* a) {
	ostringstream os;
	os << *a;
	return os.str();
}

void AnilloNuevoEsVacio() {
	Anillo<int>* a = new Anillo<int>();
	ASSERT(a->esVacio());
	ASSERT_EQ(a->tamanio(), 0);
	delete a;
}

void AnilloUnitarioAlEliminarQuedaVacio() {
	Anillo<int>* a = new Anillo<int>();
	ASSERT(a->esVacio());
	ASSERT_EQ(a->tamanio(), 0);
    a->agregar(42);
	ASSERT(!a->esVacio());
	ASSERT_EQ(a->tamanio(), 1);
    a->eliminar(42);
	ASSERT(a->esVacio());
	ASSERT_EQ(a->tamanio(), 0);
	delete a;
}

void AnilloUnitarioDaSiguiente() {
	Anillo<int>* a = new Anillo<int>();
    a->agregar(42);
    ASSERT(!a->esVacio());
    ASSERT_EQ(a->tamanio(), 1);
    ASSERT_EQ(a->siguiente(), 42);
	delete a;
}

void MostrarAnilloVacio() {
	Anillo<int>* a = new Anillo<int>();
	ASSERT_EQ(to_s(a), "[]");
	delete a;
}

void MostrarAnilloConDosElementosYUnoMarcado() {
	Anillo<int>* a = new Anillo<int>();
	a->agregar(4);
	a->agregar(5);
	a->marcar();
	a->agregar(6);
	a->siguiente();
	ASSERT_EQ(to_s(a), "[5*, 4, 6]");
	delete a;
}

void AndanActualMarcadoSiguiente() {
	Anillo<int>* a = new Anillo<int>();
	a->agregar(4);
	a->agregar(5);
	a->marcar();
	a->agregar(6);
	ASSERT_EQ(a->actual(), 6);
	ASSERT_EQ(a->marcado(), 5);
	ASSERT_EQ(a->siguiente(), 6);
	ASSERT_EQ(a->actual(), 5);
	delete a;
}

void UsarConstructorPorCopia() {
	cout << endl;

	Anillo<int>* a = new Anillo<int>();
	a->agregar(4);
	a->agregar(5);
	a->marcar();
	a->agregar(6);
	Anillo<int>* b = new Anillo<int>(*a);

	//cout << "Creó b" << endl;
	//a ->mostrarAnillo(out);

	//delete a;
	cout << "Eliminó a" << endl;
	//cout << "esVacio? false : " << boolalpha << b -> esVacio() << endl;
	//if(b ->esVacio()) {} else {cout << "No es vacio. Actual? 6 : " << b ->actual() << endl;}
	//cout << "Resultado:" << endl;
	ASSERT_EQ(to_s(b), "[6, 5*, 4]");
	delete b;
}

void IgualarDosAnillosIguales() {
	Anillo<int>* a = new Anillo<int>();
	a->agregar(4);
	a->agregar(5);
	a->marcar();
	a->agregar(6);
	Anillo<int>* b = new Anillo<int>(*a);
	ASSERT_EQ(b == a , true);
	delete b;
}

int main(void) {
	RUN_TEST(AnilloNuevoEsVacio);
    RUN_TEST(AnilloUnitarioAlEliminarQuedaVacio);
	RUN_TEST(AnilloUnitarioDaSiguiente);
    RUN_TEST(MostrarAnilloVacio);
    RUN_TEST(MostrarAnilloConDosElementosYUnoMarcado);
    RUN_TEST(AndanActualMarcadoSiguiente);
    cout << "hasta aca todo bien" << endl;
    //RUN_TEST(UsarConstructorPorCopia);

	return 0;
}

