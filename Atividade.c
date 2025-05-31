#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAX_LIVROS 100

//1)
void lerFrase(char frase[]) {
    printf("digite uma frase: ");
    fgets(frase, 200, stdin);
    frase[strcspn(frase, "\n")] = '\0';
}

int contarVogais(char frase[]) {
    int count = 0;
    for (int i = 0; frase[i] != '\0'; i++) {
        char c = tolower(frase[i]);
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
            count++;
        }
    }
    return count;
}

void capitalizarPalavras(char frase[]) {
    int novaPalavra = 1;
    for (int i = 0; frase[i] != '\0'; i++) {
        if (frase[i] == ' ') {
            novaPalavra = 1;
        } else if (novaPalavra && frase[i] >= 'a' && frase[i] <= 'z') {
            frase[i] = frase[i] - 32;
            novaPalavra = 0;
        } else {
            novaPalavra = 0;
        }
    }
}

//2)
typedef struct {
    char titulo[100];
    char autor[100];
    char editora[100];
    int anoPublicacao;
    int qtdPaginas;
} Livro;

void preencherVetor(Livro livros[], int *n) {
    printf("quantos livros deseja cadastrar? ");
    scanf("%d", n);
    getchar();

    for (int i = 0; i < *n; i++) {
        printf("livro %d:\n", i + 1);
        printf("titulo: ");
        fgets(livros[i].titulo, 100, stdin);
        livros[i].titulo[strcspn(livros[i].titulo, "\n")] = '\0';

        printf("autor: ");
        fgets(livros[i].autor, 100, stdin);
        livros[i].autor[strcspn(livros[i].autor, "\n")] = '\0';

        printf("editora: ");
        fgets(livros[i].editora, 100, stdin);
        livros[i].editora[strcspn(livros[i].editora, "\n")] = '\0';

        printf("ano de publicacao: ");
        scanf("%d", &livros[i].anoPublicacao);

        printf("quantidade de paginas: ");
        scanf("%d", &livros[i].qtdPaginas);
        getchar();
    }
}

void imprimirVetor(Livro livros[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%s | %s | %s | %d | %d\n",
               livros[i].titulo, livros[i].autor, livros[i].editora,
               livros[i].anoPublicacao, livros[i].qtdPaginas);
    }
}

int buscarPorTitulo(Livro livros[], int n, char titulo[]) {
    for (int i = 0; i < n; i++) {
        if (strcmp(livros[i].titulo, titulo) == 0) {
            return i;
        }
    }
    return -1;
}

void ordenarPorTitulo(Livro livros[], int n) {
    Livro temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (strcmp(livros[j].titulo, livros[j + 1].titulo) > 0) {
                temp = livros[j];
                livros[j] = livros[j + 1];
                livros[j + 1] = temp;
            }
        }
    }
}

int buscaBinariaPorTitulo(Livro livros[], int n, char titulo[]) {
    int esq = 0, dir = n - 1;
    while (esq <= dir) {
        int meio = (esq + dir) / 2;
        int cmp = strcmp(livros[meio].titulo, titulo);
        if (cmp == 0) return meio;
        else if (cmp < 0) esq = meio + 1;
        else dir = meio - 1;
    }
    return -1;
}

int main() {
    char frase[200];
    lerFrase(frase);

    printf("Frase digitada: %s\n", frase);
    printf("Quantidade de vogais: %d\n", contarVogais(frase));
    capitalizarPalavras(frase);
    printf("Frase capitalizada: %s\n\n", frase);

    Livro livros[MAX_LIVROS];
    int n;

    preencherVetor(livros, &n);
    printf("\n--- Lista de livros cadastrados ---\n");
    imprimirVetor(livros, n);

    char tituloBusca[100];
    printf("\nDigite um título para busca sequencial: ");
    fgets(tituloBusca, 100, stdin);
    tituloBusca[strcspn(tituloBusca, "\n")] = '\0';

    int pos = buscarPorTitulo(livros, n, tituloBusca);
    if (pos != -1)
        printf("Livro encontrado na posicao %d.\n", pos);
    else
        printf("Livro nao encontrado.\n");

    ordenarPorTitulo(livros, n);
    printf("\n--- Lista ordenada por título ---\n");
    imprimirVetor(livros, n);
    printf("\nDigite um título para busca binária: ");
    fgets(tituloBusca, 100, stdin);

    tituloBusca[strcspn(tituloBusca, "\n")] = '\0';
    pos = buscaBinariaPorTitulo(livros, n, tituloBusca);
    if (pos != -1)
        printf("Livro encontrado na posicao %d.\n", pos);
    else
        printf("Livro nao encontrado.\n");

    return 0;
}