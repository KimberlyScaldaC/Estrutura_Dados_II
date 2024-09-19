// Kimberly Scaldaferro Colodeti
// Arvore Red Black
#include <stdio.h>
#include <stdlib.h>

// Definição dos possíveis valores de cor
#define VERMELHO 0
#define PRETO 1

// Definição da estrutura de um nó da árvore Red-Black
struct No {
  int valor;
  int cor;
  struct No *esq;
  struct No *dir;
  struct No *pai;
};

// Define 'No' como um alias para 'struct No'
typedef struct No No; 

// Função para criar um novo nó
No *criarNo(int valor) {
  // Aloca memória para um novo nó
  No *novoNo = (No *)malloc(sizeof(No));
  // Define o valor do nó
  novoNo->valor = valor;
  // Inicialmente, o novo nó é vermelho
  novoNo->cor = VERMELHO;
  // Inicializa os ponteiros como NULL
  novoNo->esq = novoNo->dir = novoNo->pai = NULL;
  // Retorna o novo nó criado
  return novoNo;
}

// Função para fazer a rotação à esquerda
void rotacaoEsquerda(No **raiz, No *x) {
  // y é o filho à direita de x
  No *y = x->dir;
  // A subárvore esquerda de y se torna a subárvore direita de x
  x->dir = y->esq;
  if (y->esq != NULL) {
    // Atualiza o pai do filho esquerdo de y
    y->esq->pai = x;
  }
  // O pai de y se torna o pai de x
  y->pai = x->pai;
  if (x->pai == NULL) {
    // Se x é a raiz, y se torna a nova raiz
    *raiz = y;
  } else if (x == x->pai->esq) {
    // Se x é filho à esquerda, atualiza o ponteiro correspondente
    x->pai->esq = y;
  } else {
    // Se x é filho à direita, atualiza o ponteiro correspondente
    x->pai->dir = y;
  }
  // x se torna o filho esquerdo de y
  y->esq = x;
  // Atualiza o pai de x
  x->pai = y;
}

// Função para fazer a rotação à direita
void rotacaoDireita(No **raiz, No *x) {
  // y é o filho à esquerda de x
  No *y = x->esq;
  // A subárvore direita de y se torna a subárvore esquerda de x
  x->esq = y->dir;
  if (y->dir != NULL) {
    // Atualiza o pai do filho direito de y
    y->dir->pai = x;
  }
  // O pai de y se torna o pai de x
  y->pai = x->pai;
  if (x->pai == NULL) {
    // Se x é a raiz, y se torna a nova raiz
    *raiz = y;
  } else if (x == x->pai->dir) {
    // Se x é filho à direita, atualiza o ponteiro correspondente
    x->pai->dir = y;
  } else {
    // Se x é filho à esquerda, atualiza o ponteiro correspondente
    x->pai->esq = y;
  }
  // x se torna o filho direito de y
  y->dir = x;
  // Atualiza o pai de x
  x->pai = y;
}

// Função para balancear a árvore após a inserção de um nó
void corrigirViolacao(No **raiz, No *z) {
  // Enquanto z não for a raiz e seu pai for vermelho
  while (z != *raiz && z->pai->cor == VERMELHO) {
    // Se o pai de z é filho à esquerda do avô
    if (z->pai == z->pai->pai->esq) {
      // y é o tio de z
      No *y = z->pai->pai->dir;
      // Se o tio y é vermelho
      if (y != NULL && y->cor == VERMELHO) {
        // O pai de z se torna preto
        z->pai->cor = PRETO;
        // O tio y se torna preto
        y->cor = PRETO;
        // O avô se torna vermelho
        z->pai->pai->cor = VERMELHO;
        // Sobe para o avô
        z = z->pai->pai;
      } else {
        // Se z é filho à direita
        if (z == z->pai->dir) {
          // Sobe para o pai
          z = z->pai;
          
          rotacaoEsquerda(raiz, z);
        }
        // O pai de z se torna preto
        z->pai->cor = PRETO;
        // O avô se torna vermelho
        z->pai->pai->cor = VERMELHO;
        
        rotacaoDireita(raiz, z->pai->pai);
      }
    } else // Se o pai de z é filho à direita do avô
    {
      // y é o tio de z
      No *y = z->pai->pai->esq;
      // Se o tio y é vermelho
      if (y != NULL && y->cor == VERMELHO) {
        // O pai de z se torna preto
        z->pai->cor = PRETO;
        // O tio y se torna preto
        y->cor = PRETO;
        // O avô se torna vermelho
        z->pai->pai->cor = VERMELHO;
        // Sobe para o avô
        z = z->pai->pai;
      } else {
        // Se z é filho à esquerda
        if (z == z->pai->esq) {
          // Sobe para o pai
          z = z->pai;
          
          rotacaoDireita(raiz, z);
        }
        // O pai de z se torna preto
        z->pai->cor = PRETO;
        // O avô se torna vermelho
        z->pai->pai->cor = VERMELHO;
        
        rotacaoEsquerda(raiz, z->pai->pai);
      }
    }
  }
  // A raiz sempre deve ser preta
  (*raiz)->cor = PRETO;
}

// Função para inserir um novo nó na árvore Red-Black
void inserir(No **raiz, int valor) {
  // Cria um novo nó com o valor
  No *z = criarNo(valor);
  // Variável para armazenar o pai do novo nó
  No *y = NULL;
  // Começa a busca pela raiz
  No *x = *raiz;

  // Enquanto não chegar a um nó folha
  while (x != NULL) {
    y = x; // Atualiza o pai
    // Se o valor do novo nó é menor que o valor do nó atual
    if (z->valor < x->valor) {
      x = x->esq; // Move para a esquerda
    } else {
      x = x->dir; // Move para a direita
    }
  }
  // Define o pai do novo nó
  z->pai = y;
  if (y == NULL) {
    // Se a árvore estava vazia, o novo nó é a raiz
    *raiz = z;
  } else if (z->valor < y->valor) {
    // O novo nó é o filho à esquerda
    y->esq = z;
  } else {
    // O novo nó é o filho à direita
    y->dir = z;
  }
  // Chama a função para corrigir possíveis violações
  corrigirViolacao(raiz, z);
}

// Função para imprimir a árvore Red-Black em ordem
void emOrdem(No *raiz) {
  // Se o nó não é NULL
  if (raiz != NULL) {
    // Chama a função na subárvore esquerda
    emOrdem(raiz->esq);
    if (raiz->cor == 0) {
      printf("%d -> RED\n", raiz->valor);
    } else {
      printf("%d -> BLACK\n", raiz->valor);
    }
    // Chama a função na subárvore direita
    emOrdem(raiz->dir);
  }
}

// Função para imprimir a árvore com formatação
void imprimeArvoreRB(No *raiz, int b) {
  // Se o nó não é NULL
  if (raiz != NULL) {
    // Chama a função para a subárvore direita
    imprimeArvoreRB(raiz->dir, b + 1);
    // Imprime espaços proporcionais à profundidade do nó
    for (int i = 0; i < b; i++) {
      printf("       ");
    }
    // Imprime o valor do nó, formatado por cor
    if (raiz->cor == 0) {
      printf("%d -> RED\n\n", raiz->valor);
    } else {
      printf("%d -> BLACK\n\n", raiz->valor);
    }
    // Chama a função para a subárvore esquerda
    imprimeArvoreRB(raiz->esq, b + 1);
  }
}

int main() {
  // Inicializa a raiz da árvore como NULL
  struct No *raiz = NULL;
  int opcao, valor; 

  do {
    printf("\n\n------- Menu ---------------\n\n");
    printf("- 1 --- Inserir valor\n");
    printf("- 2 --- Imprimir árvore em ordem\n");
    printf("- 3 --- Imprimir árvore com formatação\n");
    printf("- 0 --- Sair\n\n");
    printf("- Opção --> ");
    scanf("%d", &opcao);

    switch (opcao) {
    case 1:
      printf("\n\n--- Inserir valor\n");
      printf("Digite o valor a ser inserido: ");
      scanf("%d", &valor);
      inserir(&raiz, valor);
      break;

    case 2:
      printf("\n\n--- Imprimir árvore em ordem\n");
      printf("Árvore em ordem:\n");
      emOrdem(raiz);
      break;

    case 3:
      printf("\n\n--- Imprimir árvore com formatação\n");
      printf("Árvore com formatação:\n");
      imprimeArvoreRB(raiz, 0);
      break;

    case 0:
      printf("\n\n--- Sair\n");
      printf("Saindo...\n");
      break;

    default:
      printf("Opção inválida. Tente novamente.\n");
      break;
    }
    printf("\n");
  } while (opcao != 0);

  return 0;
}
