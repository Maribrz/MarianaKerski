#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX_CPF 12
#define MAX_SENHA 20
#define BANCO_DE_DADOS "banco_de_dados.txt"
#define MAX_LINHA 1024
#define CATALOGO_FILMES "catalogo_filmes.txt"
#define AVALIACOES_FILMES "avaliacoes_filmes.txt"
#define ALUGAR "alugar.txt"

void registrar_usuario() {
    char cpf[MAX_CPF];
    char senha[MAX_SENHA];

    printf("Digite seu CPF: ");
    scanf("%11s", cpf);

    printf("Digite sua senha: ");
    scanf("%19s", senha);

    FILE *fp = fopen(BANCO_DE_DADOS, "a");
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo de banco de dados!\n");
        return;
    }

    fprintf(fp, "CPF:%s- SENHA:%s\n", cpf, senha);
    fclose(fp);

    printf("Usuário registrado com sucesso!\n\n");
    return main2();
}

int login_usuario() {
    char cpf[MAX_CPF];
    char senha[MAX_SENHA];

    printf("Digite seu CPF: ");
    scanf("%11s", cpf);

    printf("Digite sua senha: ");
    scanf("%19s", senha);

    FILE *fp = fopen(BANCO_DE_DADOS, "r");
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo de banco de dados!\n");
        return 0;
    }

    char linha[256];
    while (fgets(linha, sizeof(linha), fp)) {
        char *token = strtok(linha, ":");
        if (strcmp(token, cpf) == 0) {
            token = strtok(NULL, "\n");
            if (strcmp(token, senha) == 0) {
                fclose(fp);
                return 1; // login bem-sucedido
            }
        }
    }

    fclose(fp);
    int escolha1;
    printf("Deseja Registrar-se ou tentar novamente?\n");
    printf("1. Registrar\n2. Tentar novamente\n");
    printf("Digite sua escolha: ");
    scanf("%d", &escolha1);

    if (escolha1 == 1) {
        registrar_usuario();
    } else if (escolha1 == 2) {
        login_usuario();
    }
    return 0; // login falhou
}

int main1() {
    int escolha;
    printf("1. Registrar\n2. Login\n");
    printf("Digite sua escolha: ");
    scanf("%d", &escolha);

    if (escolha == 1) {
        registrar_usuario();
    } else if (escolha == 2) {
        if (login_usuario()) {
            printf("Login bem-sucedido!\n");
            main2(); // Chamar main2() após login bem-sucedido
        } else {
            printf("CPF ou senha inválidos!\n");
        }
    } else {
        printf("Escolha inválida!\n");
        return main2();
    }

    return 0;
}

int main2() {
    int option;
    FILE *arquivo;
    char linha[MAX_LINHA];

    do {
        printf("\n");
        printf("Seja bem vindo!\n");
        printf("1. Ver catálogo de filmes\n");
        printf("2. Avaliar filmes\n");
        printf("3. Alugar filmes\n");
        printf("4. Sair\n");
        printf("\nEscolha uma opção: \n");

        scanf("%d", &option);
        getchar(); // Limpar o buffer de entrada

        switch (option) {
            case 1:
                printf("\nVocê escolheu ver catálogo de filmes.\n\n");

                // Abrir o arquivo de texto
                arquivo = fopen(CATALOGO_FILMES, "r");
                if (arquivo == NULL) {
                    printf("Erro ao abrir o arquivo.\n");
                    break;
                }

                // Ler e exibir o catálogo de filmes
                while (fgets(linha, MAX_LINHA, arquivo) != NULL) {
                    printf("%s", linha);
                }

                // Fechar o arquivo de texto
                fclose(arquivo);
                break;
            case 2:
                printf("Você escolheu avaliar filmes.\n");

                // Abrir o arquivo de texto para ler o catálogo de filmes
                arquivo = fopen(CATALOGO_FILMES, "r");
                if (arquivo == NULL) {
                    printf("Erro ao abrir o arquivo.\n");
                    break;
                }

                // Ler o catálogo de filmes e exibir as opções para avaliação
                int filme_id = 1;
                while (fgets(linha, MAX_LINHA, arquivo) != NULL) {
                    printf("%d. %s", filme_id, linha);
                    filme_id++;
                }

                // Fechar o arquivo de texto
                fclose(arquivo);

                // Solicitar ao usuário escolher um filme para avaliar
                int filme_escolhido;
                printf("\n\nEscolha um filme para avaliar (digite o número do filme): ");
                scanf("%d", &filme_escolhido);
                getchar(); // Limpar o buffer de entrada

                // Solicitar ao usuário avaliar o filme com uma nota de 1 a 5
                float nota;
                printf("\nAvalie o filme com uma nota de 1 a 5: ");
                scanf("%f", &nota);
                getchar(); // Limpar o buffer de entrada

                // Verificar se a nota é válida
                if (nota < 1 || nota > 5) {
                    printf("Nota inválida. Tente novamente.\n");
                    break;
                }

                // Solicitar ao usuário adicionar sua opinião sobre o filme
                char opiniao[MAX_LINHA];
                printf("\nAdicione sua opinião sobre o filme: \n");
                fgets(opiniao, MAX_LINHA, stdin);

                // Remover o caractere de newline da opinião
                opiniao[strcspn(opiniao, "\n")] = 0;

                // Abrir o arquivo de texto para salvar a avaliação
                arquivo = fopen(AVALIACOES_FILMES, "a+");
                if (arquivo == NULL) {
                // Criar o arquivo se ele não existir
                arquivo = fopen(AVALIACOES_FILMES,"W");
                if (arquivo == NULL) {
                    printf("Erro ao criar o arquivo.\n");
                   break;
                    }
                }

                // Salvar a avaliação no arquivo
                fprintf(arquivo, "Filme %d: Nota %f - Opinião: %s\n", filme_escolhido, nota, opiniao);

                // Fechar o arquivo de texto
                fclose(arquivo);

                printf("Avaliação salva com sucesso!\n");
                break;

            case 3:
                printf("Você escolheu alugar filmes.\n");

                // Abrir o arquivo de texto para ler o catálogo de filmes
                arquivo = fopen(CATALOGO_FILMES, "r");
                if (arquivo == NULL) {
                    printf("Erro ao abrir o arquivo.\n");
                    break;
                }

                // Ler o catálogo de filmes e exibir as opções
                int filme_alugado;
                printf("Escolha um filme para alugar:\n");
                int j = 1;
                while (fgets(linha, MAX_LINHA, arquivo) != NULL) {
                    printf("%d. %s", j, linha);
                    j++;
                }

                fclose(arquivo);

                printf("\nDigite o número do filme: ");
                scanf("%d", &filme_alugado);

                char cpf[MAX_CPF];
                printf("Digite seu CPF: ");
                scanf("%11s", cpf);

                // Save the rented movie to a file
                FILE *alugados = fopen("alugados.txt", "a"); // open in append mode
                if (alugados == NULL) {
                    printf("Erro ao abrir o arquivo de alugados.\n");
                    break;
                }

                // Write the rented movie to the file
                time_t data_aluguel = time(NULL); // Armazenar a data de aluguel
                struct tm *info = localtime(&data_aluguel);
                char data_aluguel_str[20];
                strftime(data_aluguel_str, sizeof(data_aluguel_str), "%d/%m/%Y", info);

                info->tm_mday += 30; // Adicionar 30 dias
                time_t data_vencimento = mktime(info);
                char data_vencimento_str[20];
                strftime(data_vencimento_str, sizeof(data_vencimento_str), "%d/%m/%Y", info);

                fprintf(alugados, "CPF:%s - FILME:%d - DATA_ALUGUEL:%s - DATA_VENCIMENTO:%s\n", cpf, filme_alugado, data_aluguel_str, data_vencimento_str);

                fclose(alugados);

                printf("\nFilme alugado com sucesso!\n\n");
                break;
            case 4:
                printf("Você escolheu sair.\n");
                return 0;
            default:
                printf("Escolha inválida!\n");
        }
    } while (option != 4);

    return 0;
}

void verificar_vencimento() {
    FILE *alugados = fopen("alugados.txt", "r");
    if (alugados == NULL) {
        printf("Erro ao abrir o arquivo de alugados.\n");
        return;
    }

    char linha[MAX_LINHA];
    while (fgets(linha, MAX_LINHA, alugados) != NULL) {
        char *token = strtok(linha, "-");
        char *cpf = token;
        token = strtok(NULL, "-");
        int filme_alugado = atoi(token);
        token = strtok(NULL, "-");
        char *data_aluguel_str = token;
        token = strtok(NULL, "-");
        char *data_vencimento_str = token;

        printf("CPF: %s - FILME: %d - DATA_ALUGUEL: %s - DATA_VENCIMENTO: %s\n", cpf, filme_alugado, data_aluguel_str, data_vencimento_str);

        // Verificar se a data de vencimento é hoje ou anterior
        time_t agora = time(NULL);
        struct tm *info_agora = localtime(&agora);
        struct tm info_vencimento = *info_agora;
        sscanf(data_vencimento_str, "%d/%d/%d", &info_vencimento.tm_mday, &info_vencimento.tm_mon, &info_vencimento.tm_year);
        info_vencimento.tm_mon -= 1; // ajustar para o formato de mês do tm
        info_vencimento.tm_year -= 1900; // ajustar para o formato de ano do tm

        if (mktime(&info_vencimento) <= agora) {
            printf("Filme %d do CPF %s está vencido!\n", filme_alugado, cpf);
        }
    }

    fclose(alugados);
}

int main() {
    main1();
    return 0;
}
