// Kimberly Scaldaferro Colodeti
#include <stdio.h>
#include <stdlib.h>
// quando coloca o typedef nao precisa coloca o struct no resto
typedef struct {
  int dado;
  struct NoArvore *esq;
  struct NoArvore *dir;
} NoArvore;

// Função auxiliar para imprimir um caractere precedido por uma quantidade
// específica de espaços
void imprimiNo(int valor, int dado) {
  int i;
  for (i = 0; i < dado; i++)
    printf("   ");
  printf("%i\n", valor);
}

void mostraArvore(NoArvore *raiz, int dado) {
  if (raiz == NULL) {
    return;
  }
  mostraArvore(raiz->dir, dado + 1);
  // Convertendo para caractere para imprimir
  imprimiNo(raiz->dado, dado);
  mostraArvore(raiz->esq, dado + 1);
}

NoArvore *criarNo(int dado) {
  // alocar memoria
  NoArvore *novoNo = (NoArvore *)malloc(sizeof(NoArvore));
  // verifica se alocou na memoria
  if (novoNo == NULL) {
    printf("Erro: Falha ao alocar memória para o novo nó.\n");
    exit(-1);
  }

  novoNo->dado = dado;
  novoNo->esq = NULL;
  novoNo->dir = NULL;
  return novoNo;
}

NoArvore *adicionaElemento(NoArvore *raiz, int dado) {
  // Não tem nem um no na arvore
  if (raiz == NULL) {
    raiz = criarNo(dado);
  } else {
    if (dado <= raiz->dado) {
      raiz->esq = adicionaElemento(raiz->esq, dado);
    } else {
      raiz->dir = adicionaElemento(raiz->dir, dado);
    }
  }
  return raiz;
}

// Achar o no folha
NoArvore *encontrarMinimo(NoArvore *raiz) {
  NoArvore *atual = raiz;
  while (atual->esq != NULL) {
    atual = atual->esq;
  }
  return atual;
}

// excluir um no
NoArvore *excluirElemento(NoArvore *raiz, int valor) {
  if (raiz == NULL) {
    return raiz;
  }

  if (valor < raiz->dado) {
    raiz->esq = excluirElemento(raiz->esq, valor);
  } else if (valor > raiz->dado) {
    raiz->dir = excluirElemento(raiz->dir, valor);
  } else {
    // Caso 1: Nó folha ou nó com apenas um filho
    if (raiz->esq == NULL) {
      NoArvore *temp = raiz->dir;
      free(raiz);
      return temp;
    } else if (raiz->dir == NULL) {
      NoArvore *temp = raiz->esq;
      free(raiz);
      return temp;
    }
    // Caso 2: Nó com dois filhos, encontra o sucessor in-order (menor valor na
    // subárvore direita)
    NoArvore *temp = encontrarMinimo(raiz->dir);
    raiz->dado = temp->dado;
    raiz->dir = excluirElemento(raiz->dir, temp->dado);
  }
  return raiz;
}

void posOrdem(NoArvore *raiz) {
  // ESQ,DIR,RAIZ
  if (raiz != NULL) {
    posOrdem(raiz->esq);
    posOrdem(raiz->dir);
    printf(" %d |", raiz->dado);
  }
  return;
}

void preOrdem(NoArvore *raiz) {
  // RAIZ,ESQ,DIR
  if (raiz != NULL) {
    printf(" %d |", raiz->dado);
    posOrdem(raiz->esq);
    posOrdem(raiz->dir);
  }
  return;
}

void inOrdem(NoArvore *raiz) {
  // ESQ,RAIZ,DIR
  if (raiz != NULL) {
    posOrdem(raiz->esq);
    printf(" %d |", raiz->dado);
    posOrdem(raiz->dir);
  }
  return;
}

int main(void) {
  int op = -1, valor;
  struct NoArvore *raiz = NULL;
  while (op != 0) {
    printf("\n\n------- Menu ---------------\n\n");
    printf("- 1 --- Adiciona Elemento(no)\n");
    printf("- 2 --- Excluir Elemento(no)\n");
    printf("- 3 --- Imprimir Arvore\n");
    printf("- 4 --- Imprimir Pos-Ordem\n");
    printf("- 5 --- Imprimir In-Ordem\n");
    printf("- 6 --- Imprimir Pre-Ordem\n");
    printf("- 0 --- Sair\n\n");
    printf("- Opção --> ");
    scanf("%d", &op);

    switch (op) {
    case 1:
      printf("\n\n--- Adiciona Elemento(no)\n");
      printf("\nDigite o valor do no ->");
      scanf("%d", &valor);
      adicionaElemento(raiz, valor);
      break;

    case 2:
      printf("\n\n--- Excluir Elemento(no)\n");
      printf("\nDigite o valor do no ->");
      scanf("%d", &valor);
      excluirElemento(raiz, valor);
      break;

    case 3:
      printf("\n\n--- Imprimir Arvore\n");
      printf("\nDigite o valor do no ->");
      scanf("%d", &valor);
      mostraArvore(raiz, valor);
      break;

    case 4:
      printf("\n\n--- Imprimir Pos-Ordem\n\n");
      posOrdem(raiz);
      break;

    case 5:
      printf("\n\n--- Imprimir In-Ordem\n\n");
      inOrdem(raiz);
      break;

    case 6:
      printf("\n\n--- Imprimir Pre-Ordem\n\n");
      preOrdem(raiz);
      break;

    case 0:
      op = 0;
      printf("\nSistema finalizado com sucesso!\n");
      break;

    default:
      printf("Digite uma opcao valida\n");
    }
  }
  return 0;
}
