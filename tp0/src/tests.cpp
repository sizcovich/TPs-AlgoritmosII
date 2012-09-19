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

void MasNuevosQuedanPrimeros() {
   Anillo<int>* a = new Anillo<int>();
   a->agregar(42);
   a->agregar(20);
   a->agregar(10);
   ASSERT_EQ(a->actual(), 10);
   ASSERT_EQ(a->siguiente(), 20);
   ASSERT_EQ(a->siguiente(), 42);
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
	a->retroceder();
	ASSERT_EQ(a->actual(), 4);
	delete a;
}

void UsarConstructorPorCopia() {
	Anillo<int>* a = new Anillo<int>();
	a->agregar(4);
	a->agregar(5);
	a->marcar();
	a->agregar(6);
	Anillo<int>* b = new Anillo<int>(*a);
	delete a;
	ASSERT_EQ(to_s(b), "[6, 5*, 4]");
	b->siguiente();
	ASSERT_EQ(to_s(b), "[5*, 4, 6]");
	delete b;
}

void IgualarDosAnillosIguales() {
	Anillo<int>* a = new Anillo<int>();
	a->agregar(4);
	a->agregar(5);
	a->marcar();
	a->agregar(6);
	Anillo<int>* b = new Anillo<int>(*a);
	ASSERT_EQ(*b == *a , true);
	delete a;
	delete b;
}

void IgualarDosAnillosDiferentes() {
	Anillo<int>* a = new Anillo<int>();
	a->agregar(4);
	a->agregar(5);
	a->agregar(6);
	Anillo<int>* b = new Anillo<int>(*a);
	a->marcar();
	ASSERT_EQ(*b == *a , false);
	b->marcar();
	ASSERT(*b == *a);
	b->siguiente();
	ASSERT_EQ(*b == *a , false);
	b->marcar();
	b->retroceder();
	ASSERT_EQ(*b == *a , false);
	delete a;
	delete b;
}

int main(void) {
	RUN_TEST(AnilloNuevoEsVacio);
    RUN_TEST(AnilloUnitarioAlEliminarQuedaVacio);
	RUN_TEST(AnilloUnitarioDaSiguiente);
    RUN_TEST(MostrarAnilloVacio);
    RUN_TEST(MasNuevosQuedanPrimeros);
    RUN_TEST(MostrarAnilloConDosElementosYUnoMarcado);
    RUN_TEST(AndanActualMarcadoSiguiente);
    RUN_TEST(UsarConstructorPorCopia);
    RUN_TEST(IgualarDosAnillosIguales);
    RUN_TEST(IgualarDosAnillosDiferentes);
	return 0;
}

