// Kimberly Scaldaferro Colodeti
// Arvore Treap
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Estrutura do nó da Treap
typedef struct treap {
  int valor;         // Valor do nó
  int prioridade;    // Prioridade do nó
  struct treap *pai; // Ponteiro para o nó pai
  struct treap *esq; // Ponteiro para o nó à esquerda
  struct treap *dir; // Ponteiro para o nó à direita
} Treap;

// Cria um novo nó com valor e prioridade
Treap *novoNo(int valor, int prioridade) {
  Treap *novo = (Treap *)malloc(sizeof(Treap));
  novo->valor = valor;
  novo->prioridade = prioridade;
  novo->pai = novo->esq = novo->dir = NULL;
  return novo;
}

// Rotação simples à esquerda
Treap *rotacaoEsqSimples(Treap *raiz) {
  Treap *novaRaiz = raiz->dir; // O novo nó raiz é o filho à direita
  raiz->dir = novaRaiz->esq;   // Atualiza o filho à direita do nó raiz
  if (raiz->esq != NULL) {
    raiz->esq->pai = raiz; // Atualiza o pai do filho à esquerda
  }
  novaRaiz->pai = raiz->pai; // Atualiza o pai do novo nó raiz
  novaRaiz->esq = raiz;      // O nó raiz atual se torna o filho à esquerda
  raiz->pai = novaRaiz;      // Atualiza o pai do nó raiz atual
  return novaRaiz;           // Retorna a nova raiz
}

// Rotação simples à direita
Treap *rotacaoDirSimples(Treap *raiz) {
  Treap *novaRaiz = raiz->esq; // O novo nó raiz é o filho à esquerda
  raiz->esq = novaRaiz->dir;   // Atualiza o filho à esquerda do nó raiz
  if (raiz->dir != NULL) {
    raiz->dir->pai = raiz; // Atualiza o pai do filho à direita
  }
  novaRaiz->pai = raiz->pai; // Atualiza o pai do novo nó raiz
  novaRaiz->dir = raiz;      // O nó raiz atual se torna o filho à direita
  raiz->pai = novaRaiz;      // Atualiza o pai do nó raiz atual
  return novaRaiz;           // Retorna a nova raiz
}

// Insere um novo nó na Treap
Treap *InserirNo(Treap *raiz, int valor) {
  int prioridadeNova = rand() % 100; // Atribui uma prioridade aleatória
  if (raiz == NULL)
    return novoNo(valor,
                  prioridadeNova); // Se a raiz está vazia, cria um novo nó

  // Se o valor for menor, insere à esquerda
  if (valor < raiz->valor) {
    raiz->esq = InserirNo(raiz->esq, valor);
    if (raiz->esq->prioridade > raiz->prioridade)
      raiz = rotacaoDirSimples(
          raiz); // Rotaciona para manter a propriedade da Treap
  } else {
    // Se o valor for maior, insere à direita
    raiz->dir = InserirNo(raiz->dir, valor);
    if (raiz->dir->prioridade > raiz->prioridade)
      raiz = rotacaoEsqSimples(
          raiz); // Rotaciona para manter a propriedade da Treap
  }
  return raiz; // Retorna a raiz atualizada
}

// Busca um nó na Treap
Treap *BuscarNo(Treap *raiz, int valor) {
  if (raiz == NULL || raiz->valor == valor)
    return raiz; // Retorna o nó se encontrado ou NULL
  if (valor < raiz->valor)
    return BuscarNo(raiz->esq, valor); // Busca à esquerda
  return BuscarNo(raiz->dir, valor);   // Busca à direita
}

// Remove um nó da Treap
Treap *RemoverNo(Treap *raiz, int valor) {
  if (raiz == NULL)
    return raiz; // Se a raiz é NULL, retorna

  // Se o valor for menor, continua à esquerda
  if (valor < raiz->valor) {
    raiz->esq = RemoverNo(raiz->esq, valor);
  } else if (valor > raiz->valor) {
    raiz->dir = RemoverNo(raiz->dir, valor);
  } else {
    // Se o nó tem no máximo um filho
    if (raiz->esq == NULL) {
      Treap *temp = raiz->dir; // Salva o filho à direita
      free(raiz);              // Libera a memória do nó atual
      return temp;             // Retorna o filho à direita
    } else if (raiz->dir == NULL) {
      Treap *temp = raiz->esq; // Salva o filho à esquerda
      free(raiz);              // Libera a memória do nó atual
      return temp;             // Retorna o filho à esquerda
    }
    // Se o nó tem dois filhos, rotaciona
    if (raiz->esq->prioridade > raiz->dir->prioridade) {
      raiz = rotacaoDirSimples(raiz);
      raiz->dir = RemoverNo(raiz->dir, valor);
    } else {
      raiz = rotacaoEsqSimples(raiz);
      raiz->esq = RemoverNo(raiz->esq, valor);
    }
  }
  return raiz; // Retorna a raiz atualizada
}

// Função de travessia in-order
void inorder(Treap *raiz) {
  if (raiz != NULL) {
    inorder(raiz->esq); // Visita o filho à esquerda
    printf("%d (prioridade: %d) ", raiz->valor,
           raiz->prioridade); // Imprime o valor e a prioridade
    inorder(raiz->dir);       // Visita o filho à direita
  }
}

// Função para imprimir a árvore com formatação
void imprimeArvore(Treap *raiz, int espacos) {
  if (raiz == NULL)
    return;                          // Se a raiz é NULL, retorna
  espacos += 10;                     // Aumenta o espaço entre os nós
  imprimeArvore(raiz->dir, espacos); // Imprime o filho à direita
  printf("\n");
  for (int i = 10; i < espacos; i++)
    printf(" "); // Adiciona espaços para formatação
  printf("%d (prioridade: %d)\n", raiz->valor,
         raiz->prioridade);          // Imprime o valor e a prioridade
  imprimeArvore(raiz->esq, espacos); // Imprime o filho à esquerda
}

int main() {
  srand(time(NULL));  // Inicializa a semente para números aleatórios
  Treap *raiz = NULL; // Inicializa a raiz como NULL
  int opcao, valor;   // Variáveis para a opção do menu e o valor

  do {
    // Exibe o menu
    printf("\n\n------- Menu ---------------\n\n");
    printf("- 1 --- Inserir valor\n");
    printf("- 2 --- Imprimir árvore em ordem\n");
    printf("- 3 --- Imprimir árvore com formatação\n");
    printf("- 4 --- Buscar valor\n");
    printf("- 5 --- Remover valor\n");
    printf("- 0 --- Sair\n\n");
    printf("- Opção --> ");
    scanf("%d", &opcao); // Lê a opção do usuário

    switch (opcao) {
    case 1:
      printf("\n\n--- Inserir valor\n");
      printf("Digite o valor a ser inserido: ");
      scanf("%d", &valor);
      raiz = InserirNo(raiz, valor); // Insere o valor na Treap
      break;

    case 2:
      printf("\n\n--- Imprimir árvore em ordem\n");
      printf("Árvore em ordem:\n");
      inorder(raiz); // Imprime a árvore em ordem
      break;

    case 3:
      printf("\n\n--- Imprimir árvore com formatação\n");
      printf("Árvore com formatação:\n");
      imprimeArvore(raiz, 0); // Imprime a árvore com formatação
      break;

    case 4:
      printf("\n\n--- Buscar valor\n");
      printf("Digite o valor a ser buscado: ");
      scanf("%d", &valor);
      Treap *resultado = BuscarNo(raiz, valor); // Busca o valor na Treap
      if (resultado)
        printf("Valor %d encontrado com prioridade %d.\n", resultado->valor,
               resultado->prioridade);
      else
        printf("Valor %d não encontrado.\n", valor);
      break;

    case 5:
      printf("\n\n--- Remover valor\n");
      printf("Digite o valor a ser removido: ");
      scanf("%d", &valor);
      raiz = RemoverNo(raiz, valor); // Remove o valor da Treap
      printf("Valor %d removido.\n", valor);
      break;

    case 0:
      printf("\n\n--- Sair\n");
      printf("Saindo...\n"); // Mensagem de saída
      break;

    default:
      printf("Opção inválida. Tente novamente.\n"); // Mensagem de erro
      break;
    }
    printf("\n");
  } while (opcao != 0); // Continua até que o usuário escolha sair

  return 0; // Finaliza o programa
}
