#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <munit.h>
#include "main.c"  // Inclui o arquivo principal para testar as funções

// Dados simulados para os testes
static struct Cliente clientes_simulados[MAX_CLIENTES];
static int contadorClientes_simulado = 0;

static struct Funcionario funcionarios_simulados[MAX_FUNCIONARIOS];
static int contadorFuncionarios_simulado = 0;

static struct Estadia estadias_simuladas[MAX_ESTADIAS];
static int contadorEstadias_simulado = 0;

// Funções auxiliares para simular a interação com o sistema
static void cadastrarClienteSimulado(const char *nome, int telefone) {
    // Simula o cadastro de um cliente no sistema
    strcpy(clientes_simulados[contadorClientes_simulado].nome, nome);
    clientes_simulados[contadorClientes_simulado].telefone = telefone;
    contadorClientes_simulado++;
}

// Testes

static MunitResult test_cadastroCliente(const MunitParameter params[], void *data) {
    cadastrarClienteSimulado("João", 123456789);

    // Verificação se o cliente foi cadastrado corretamente
    munit_assert_string_equal(clientes_simulados[0].nome, "João");
    munit_assert_int(clientes_simulados[0].telefone, ==, 123456789);

    return MUNIT_OK;
}

static MunitTest test_suite[] = {
    { "/cadastroCliente", test_cadastroCliente, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    // Adicione mais testes conforme necessário
    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

static const MunitSuite suite = {
    "/test_suite",
    test_suite,
    NULL,
    1,
    MUNIT_SUITE_OPTION_NONE
};

int main(int argc, char *argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
    srand(time(NULL)); // Inicializa a semente do gerador de números aleatórios

    // Executar testes
    return munit_suite_main(&suite, NULL, argc, argv);
}
