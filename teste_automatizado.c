#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <munit.h>
#include "hotel.c"  // Inclui o arquivo principal para testar as funções

// Teste para gerarIdUnico
static MunitResult test_gerarIdUnico(const MunitParameter params[], void *data) {
    struct Cliente clientes[MAX_CLIENTES];  // Simulando um array de clientes
    int contadorClientes = 0;

    // Teste 1: Verificar se gera IDs únicos
    int id1 = gerarIdUnico(clientes, contadorClientes);
    int id2 = gerarIdUnico(clientes, contadorClientes);

    munit_assert_int(id1, !=, id2);

    return MUNIT_OK;
}

// Funções de setup e teardown (opcional)
static void *test_setup(const MunitParameter params[], void *user_data) {
    // Pode ser usado para inicialização antes de cada teste
    return NULL;
}

static void test_teardown(void *fixture) {
    // Pode ser usado para limpeza após cada teste
}

// Array de casos de teste
static MunitTest test_suite[] = {
    { "/gerarIdUnico", test_gerarIdUnico, test_setup, test_teardown, MUNIT_TEST_OPTION_NONE, NULL },
    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

// Definir o conjunto de testes
static const MunitSuite suite = {
    "/test_suite",   // nome da suíte de testes
    test_suite,      // array de testes
    NULL,            // inicialização global (opcional)
    1,               // número máximo de fios a serem executados simultaneamente (0 para ilimitado)
    MUNIT_SUITE_OPTION_NONE
};

// Função principal para rodar os testes
int main(int argc, char *argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
    return munit_suite_main(&suite, NULL, argc, argv);
}
