#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define MAX_CLIENTES 100
#define MAX_FUNCIONARIOS 100
#define MAX_ESTADIAS 100

struct Cliente {
    int id;
    char nome[50];
    char endereco[60];
    int telefone;
};

struct Funcionario {
    int id;
    char nome[50];
    int telefone;
    char cargo[30];
    float salario;
};

struct Estadia {
    int id;
    int dataEntrada;    
    int dataSaida;      
    int diarias;        
    int idCliente;
    int numeroQuarto;
    int hospedes;
};

// Função gerar ID CLIENTE
int gerarIdUnico(struct Cliente clientes[], int contadorClientes) {
    int novoId;
    int idExistente;

    do {
        novoId = rand() % 100 + 1;
        idExistente = 0;

        // Verifica se o novoId já existe
        for (int i = 0; i < contadorClientes; i++) {
            if (clientes[i].id == novoId) {
                idExistente = 1;
                break;
            }
        }
    } while (idExistente);

    return novoId;
}

// Função gerar ID Funcionario
int gerarIdUnicoFuncionario(struct Funcionario funcionarios[], int contadorFuncionarios) {
    int idFuncionario;
    int idFuncionarioExistente;

    do {
        idFuncionario = rand() % 100 + 1;
        idFuncionarioExistente = 0;
        for (int i = 0; i < contadorFuncionarios; i++) {
            if (funcionarios[i].id == idFuncionario) {
                idFuncionarioExistente = 1;
                break;
            }
        }
    } while (idFuncionarioExistente);

    return idFuncionario;
}

// Função diferenças de dias
int calcularDiferencaDias(int dataEntrada, int dataSaida) {
    struct tm tmEntrada = {0};
    struct tm tmSaida = {0};

    tmEntrada.tm_year = dataEntrada / 10000 - 1900;
    tmEntrada.tm_mon = (dataEntrada % 10000) / 100 - 1;
    tmEntrada.tm_mday = dataEntrada % 100;

    tmSaida.tm_year = dataSaida / 10000 - 1900;
    tmSaida.tm_mon = (dataSaida % 10000) / 100 - 1;
    tmSaida.tm_mday = dataSaida % 100;

    time_t entrada = mktime(&tmEntrada);
    time_t saida = mktime(&tmSaida);

    if (entrada == (time_t)(-1) || saida == (time_t)(-1)) {
        return -1; 
    }

    double diferencaSegundos = difftime(saida, entrada);
    int diferencaDias = diferencaSegundos / (60 * 60 * 24);

    return diferencaDias;
}

// Função para cadastrar um novo cliente
void cadastroCliente(struct Cliente clientes[], int *contadorClientes) {
    if (*contadorClientes < MAX_CLIENTES) {
        int i = *contadorClientes;

        clientes[i].id = gerarIdUnico(clientes, *contadorClientes);

        printf("Insira o nome do cliente: ");
        fflush(stdout); 
        scanf(" %[^\n]", clientes[i].nome);

        printf("Insira o endereço (sem números): ");
        fflush(stdout); 
        scanf(" %[^\n]", clientes[i].endereco);

        printf("Insira o telefone de contato (somente números sem espaço): ");
        fflush(stdout); 
        scanf("%d", &clientes[i].telefone);
        
        printf("ID do cliente: %d\n", clientes[i].id);

        (*contadorClientes)++; //contador



        // Salvar clientes em arquivo 
        FILE *arquivo;
        arquivo = fopen("clientes.txt", "a");

        if (arquivo != NULL) {
            fprintf(arquivo, "ID: %d\nNOME:%s\nENDEREÇO:%s\nTELEFONE: %d\n", clientes[i].id, clientes[i].nome, clientes[i].endereco, clientes[i].telefone);
            fclose(arquivo);
        } else {
            printf("Erro ao salvar cliente no arquivo.\n");
        }
    } else {
        printf("Limite máximo de clientes atingido.\n");
    }
    printf("Cliente cadastrado com sucesso!!!\n");
}

// Função para cadastrar um novo funcionário
void cadastroFuncionario(struct Funcionario funcionarios[], int *contadorFuncionarios) {
    if (*contadorFuncionarios < MAX_FUNCIONARIOS) {
        int i = *contadorFuncionarios;

        funcionarios[i].id = gerarIdUnicoFuncionario(funcionarios, *contadorFuncionarios);

        printf("Insira o nome do funcionário: ");
        fflush(stdout); 
        scanf(" %[^\n]", funcionarios[i].nome);

        printf("Insira o telefone do funcionário (somente números sem espaço): ");
        fflush(stdout); 
        scanf("%d", &funcionarios[i].telefone);

        printf("Insira o cargo do funcionário: ");
        fflush(stdout); 
        scanf(" %[^\n]", funcionarios[i].cargo);

        printf("Insira o salário do funcionário (R$.00) : ");
        fflush(stdout); 
        scanf("%f", &funcionarios[i].salario);

        (*contadorFuncionarios)++; //contador



        // Salvar funcionários em arquivo 
        FILE *arquivo;
        arquivo = fopen("funcionarios.txt", "a");

        if (arquivo != NULL) {
            fprintf(arquivo, "ID: %d\nNOME: %s\nTELEFONE: %d\nCARGO: %s\nSALARIO: %.2f\n", funcionarios[i].id, funcionarios[i].nome, funcionarios[i].telefone,
                    funcionarios[i].cargo, funcionarios[i].salario);
            fclose(arquivo);
        } else {
            printf("Erro ao salvar funcionário no arquivo.\n");
        }
    } else {
        printf("Limite máximo de funcionários atingido.\n");
    }
    printf("funcionário cadastrado com sucesso!!!\n");
}


// Função para cadastrar uma nova estadia
void cadastrarEstadia(struct Estadia estadias[], int *contadorEstadias, struct Cliente clientes[], int contadorClientes) {
    if (*contadorEstadias < MAX_ESTADIAS) {
        int i = *contadorEstadias;

        estadias[i].id = *contadorEstadias + 1;

        printf("Insira a data de entrada (aaaammdd): ");
        fflush(stdout); 
        scanf("%d", &estadias[i].dataEntrada);

        printf("Insira a data de saída (aaaammdd): ");
        fflush(stdout); 
        scanf("%d", &estadias[i].dataSaida);

        estadias[i].diarias = calcularDiferencaDias(estadias[i].dataEntrada, estadias[i].dataSaida);
        printf("Número de diárias: %d\n", estadias[i].diarias);

        int idCliente;
        int clienteEncontrado; 

        do {
            clienteEncontrado = 0; 

            printf("Insira o ID do cliente: ");
            fflush(stdout); 
            scanf("%d", &idCliente);

            for (int j = 0; j < contadorClientes; j++) {
                if (clientes[j].id == idCliente) {
                    clienteEncontrado = 1;
                    break;
                }
            }

            if (!clienteEncontrado) {
                printf("ID do cliente não encontrado. Por favor, insira um ID válido.\n");
            }
        } while (!clienteEncontrado);

        estadias[i].idCliente = idCliente;

        printf("Insira o número do quarto: ");
        fflush(stdout); 
        scanf("%d", &estadias[i].numeroQuarto);
        
        printf("Insira o número de hóspedes: ");
        fflush(stdout); 
        scanf("%d", &estadias[i].hospedes);

        (*contadorEstadias)++; //contadr

        // salvar estadias em arquivo 
        FILE *arquivo;
        arquivo = fopen("estadias.txt", "a");

        if (arquivo != NULL) {
            fprintf(arquivo, "\n\nESTADIA ID: %d\ndataEntrada: %d\ndataSaida: %d\ndiarias: %d\nID cliente: %d\nnumero quarto: %d\nhospedes: %d\n", estadias[i].id, estadias[i].dataEntrada, estadias[i].dataSaida,
                    estadias[i].diarias, estadias[i].idCliente, estadias[i].numeroQuarto, estadias[i].hospedes);
            fclose(arquivo);
        } else {
            printf("Erro ao salvar estadia no arquivo.\n");
        }
    } else {
        printf("Limite máximo de estadias atingido.\n");
    }
    printf("Estadia cadastrado com sucesso!!!\n");
}


// Função para listar todos os clientes cadastrados
void listarClientes(struct Cliente clientes[], int contadorClientes) {
    printf("\nLista de Clientes:\n");
    for (int i = 0; i < contadorClientes; i++) {
        printf("Cliente %d:\n", i + 1);
        printf("ID: %d\n", clientes[i].id);
        printf("Nome: %s\n", clientes[i].nome);
        printf("Endereço: %s\n", clientes[i].endereco);
        printf("Telefone: %d\n\n", clientes[i].telefone);
    }
}

// Função para pesquisar um cliente por nome
void pesquisarClientes(struct Cliente clientes[], int contadorClientes) {
    char nomePesquisar[50];
    printf("Insira o nome do cliente que deseja pesquisar: ");
    fflush(stdout); 
    scanf(" %[^\n]", nomePesquisar);

    int encontrado = 0;
    for (int i = 0; i < contadorClientes; i++) {
        if (strcmp(clientes[i].nome, nomePesquisar) == 0) {
            printf("Cliente encontrado:\n");
            printf("ID: %d\n", clientes[i].id);
            printf("Nome: %s\n", clientes[i].nome);
            printf("Endereço: %s\n", clientes[i].endereco);
            printf("Telefone: %d\n", clientes[i].telefone);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("Cliente não encontrado.\n");
    }
}

// Função para listar todos os funcionários cadastrados
void listarFuncionarios(struct Funcionario funcionarios[], int contadorFuncionarios) {
    printf("\nLista de Funcionários:\n");
    for (int i = 0; i < contadorFuncionarios; i++) {
        printf("Funcionário %d:\n", i + 1);
        printf("ID: %d\n", funcionarios[i].id);
        printf("Nome: %s\n", funcionarios[i].nome);
        printf("Telefone: %d\n", funcionarios[i].telefone);
        printf("Cargo: %s\n", funcionarios[i].cargo);
        printf("Salário: %.2f\n\n", funcionarios[i].salario);
    }
}

// Função para pesquisar um funcionário por nome
void pesquisarFuncionarios(struct Funcionario funcionarios[], int contadorFuncionarios) {
    char nomePesquisar[50];
    printf("Insira o nome do funcionário que deseja pesquisar: ");
    fflush(stdout); 
    scanf(" %[^\n]", nomePesquisar);

    int encontrado = 0;
    for (int i = 0; i < contadorFuncionarios; i++) {
        if (strcmp(funcionarios[i].nome, nomePesquisar) == 0) {
            printf("Funcionário encontrado:\n");
            printf("ID: %d\n", funcionarios[i].id);
            printf("Nome: %s\n", funcionarios[i].nome);
            printf("Telefone: %d\n", funcionarios[i].telefone);
            printf("Cargo: %s\n", funcionarios[i].cargo);
            printf("Salário: %.2f\n", funcionarios[i].salario);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("Funcionário não encontrado.\n");
    }
}

// Função para listar todas as estadias cadastradas
void listarEstadias(struct Estadia estadias[], int contadorEstadias) {
    printf("\nLista de Estadias:\n");
    for (int i = 0; i < contadorEstadias; i++) {
        printf("Estadia %d:\n", i + 1);
        printf("ID: %d\n", estadias[i].id);
        printf("Data de Entrada: %d\n", estadias[i].dataEntrada);
        printf("Data de Saída: %d\n", estadias[i].dataSaida);
        printf("Diárias: %d\n", estadias[i].diarias);
        printf("ID do Cliente: %d\n", estadias[i].idCliente);
        printf("Número do Quarto: %d\n", estadias[i].numeroQuarto);
        printf("Número de Hóspedes: %d\n\n", estadias[i].hospedes);
    }
}
void darBaixaEstadia(struct Estadia estadias[], int *contadorEstadias) {
    int numeroQuarto;
    printf("Digite o número do quarto para dar baixa na estadia: ");
    fflush(stdout); 
    scanf("%d", &numeroQuarto);

    int encontrado = 0;
    for (int i = 0; i < *contadorEstadias; i++) {
        if (estadias[i].numeroQuarto == numeroQuarto) {
            printf("Estadia encontrada:\n");
            printf("ID: %d\n", estadias[i].id);
            printf("Data de Entrada: %d\n", estadias[i].dataEntrada);
            printf("Data de Saída: %d\n", estadias[i].dataSaida);
            printf("Diárias: %d\n", estadias[i].diarias);
            printf("Número de Hóspedes: %d\n\n", estadias[i].hospedes);

            // Atualizar a data de saída da estadia
            time_t now;
            time(&now);
            struct tm *local = localtime(&now);
            int dataSaida = (local->tm_year + 1900) * 10000 + (local->tm_mon + 1) * 100 + local->tm_mday;
            estadias[i].dataSaida = dataSaida;

            // Calcular o valor total da estadia 
            float valorDiaria = 100.0; 
            float valorTotal = valorDiaria * estadias[i].diarias;

            printf("Valor total da estadia: R$ %.2f\n", valorTotal);

            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("Estadia não encontrada para o número do quarto %d.\n", numeroQuarto);
    }
}

int main() {
    // Declaração de variáveis
    struct Cliente clientes[MAX_CLIENTES];
    int contadorClientes = 0;

    struct Funcionario funcionarios[MAX_FUNCIONARIOS];
    int contadorFuncionarios = 0;

    struct Estadia estadias[MAX_ESTADIAS];
    int contadorEstadias = 0;

    srand(time(NULL)); // Inicializa a semente do gerador de números aleatórios

    int opcao;

    // Loop principal
    do {
        printf("\nSistema de Gerenciamento do Hotel Descanso Garantido\n");
        printf("1. Cadastrar Cliente\n");
        printf("2. Cadastrar Funcionário\n");
        printf("3. Cadastrar Estadia\n");
        printf("4. Listar Clientes\n");         
        printf("5. Listar Funcionários\n");
        printf("6. Listar Estadias\n");
        printf("7. Pesquisar Funcionário\n");
        printf("8. Pesquisar Cliente\n");
        printf("9. Dar Baixa na Estadia\n");
        printf("10.Sair\n");
        printf("Escolha uma opção: ");
        fflush(stdout); // Limpa o buffer de saída
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastroCliente(clientes, &contadorClientes);
                break;
            case 2:
                cadastroFuncionario(funcionarios, &contadorFuncionarios);
                break;
            case 3:
                if (contadorEstadias < MAX_ESTADIAS) {
                    cadastrarEstadia(estadias, &contadorEstadias, clientes, contadorClientes);
                } else {
                    printf("Limite máximo de estadias atingido.\n");
                }
                break;
            case 4:
                listarClientes(clientes, contadorClientes);
                break;
            case 5:
                listarFuncionarios(funcionarios, contadorFuncionarios);             
                break;
            case 6:
                listarEstadias(estadias, contadorEstadias);                 
                break;
            case 7:
                pesquisarFuncionarios(funcionarios, contadorFuncionarios);
                break;
            case 8:
                pesquisarClientes(clientes, contadorClientes);
                break;
            case 9:
                darBaixaEstadia(estadias, &contadorEstadias);
                break;
            case 10:
                printf("Saindo do sistema...\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
                break;
        }
    } while (opcao != 10);

    return 0;
}
