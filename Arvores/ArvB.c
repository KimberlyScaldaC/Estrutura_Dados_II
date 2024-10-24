// Kimberly Scaldaferro Colodeti
// Arvore B
#include <stdio.h>
#include <stdlib.h>

// Grau mínimo (número mínimo de filhos)
#define T 3

typedef struct NoArvoreB {
  int *chaves;
  struct NoArvoreB **filhos;
  int numChaves;
  int folha;
} NoArvoreB;

// Prototipação das funções
NoArvoreB *criarNo(int folha);
void dividirFilho(NoArvoreB *pai, int indice, NoArvoreB *filho);
void inserirNaoCheio(NoArvoreB *no, int chave);
void inserir(NoArvoreB **raiz, int chave);
void percorrer(NoArvoreB *no);
int buscar(NoArvoreB *no, int chave);
void mesclar(NoArvoreB *no, int indice);
void removerNaoFolha(NoArvoreB *no, int indice);
void remover(NoArvoreB **raiz, int chave);
void imprimir(NoArvoreB *raiz);

NoArvoreB *criarNo(int folha) {
  NoArvoreB *no = malloc(sizeof(NoArvoreB));
  no->folha = folha;
  no->chaves = malloc((2 * T - 1) * sizeof(int));
  no->filhos = malloc(2 * T * sizeof(NoArvoreB *));
  no->numChaves = 0;
  return no;
}

void dividirFilho(NoArvoreB *pai, int indice, NoArvoreB *filho) {
  NoArvoreB *novoFilho = criarNo(filho->folha);
  novoFilho->numChaves = T - 1;

  for (int i = 0; i < T - 1; i++)
    novoFilho->chaves[i] = filho->chaves[i + T];

  if (!filho->folha) {
    for (int i = 0; i < T; i++)
      novoFilho->filhos[i] = filho->filhos[i + T];
  }

  filho->numChaves = T - 1;

  for (int i = pai->numChaves; i >= indice + 1; i--)
    pai->filhos[i + 1] = pai->filhos[i];

  pai->filhos[indice + 1] = novoFilho;

  for (int i = pai->numChaves - 1; i >= indice; i--)
    pai->chaves[i + 1] = pai->chaves[i];

  pai->chaves[indice] = filho->chaves[T - 1];
  pai->numChaves++;
}

void inserirNaoCheio(NoArvoreB *no, int chave) {
  int i = no->numChaves - 1;

  if (no->folha) {
    while (i >= 0 && chave < no->chaves[i]) {
      no->chaves[i + 1] = no->chaves[i];
      i--;
    }
    no->chaves[i + 1] = chave;
    no->numChaves++;
  } else {
    while (i >= 0 && chave < no->chaves[i])
      i--;

    i++;
    if (no->filhos[i]->numChaves == 2 * T - 1) {
      dividirFilho(no, i, no->filhos[i]);
      if (chave > no->chaves[i])
        i++;
    }
    inserirNaoCheio(no->filhos[i], chave);
  }
}

void inserir(NoArvoreB **raiz, int chave) {
  NoArvoreB *r = *raiz;
  if (r->numChaves == 2 * T - 1) {
    NoArvoreB *s = criarNo(0);
    *raiz = s;
    s->filhos[0] = r;
    dividirFilho(s, 0, r);
    inserirNaoCheio(s, chave);
  } else {
    inserirNaoCheio(r, chave);
  }
}

void percorrer(NoArvoreB *no) {
  for (int i = 0; i < no->numChaves; i++) {
    if (!no->folha)
      percorrer(no->filhos[i]);
    printf("%d ", no->chaves[i]);
  }
  if (!no->folha)
    percorrer(no->filhos[no->numChaves]);
}

int buscar(NoArvoreB *no, int chave) {
  int i = 0;
  while (i < no->numChaves && chave > no->chaves[i])
    i++;

  if (i < no->numChaves && chave == no->chaves[i])
    return 1; // Chave encontrada

  if (no->folha)
    return 0; // Chave não encontrada

  return buscar(no->filhos[i], chave); // Busca no filho apropriado
}

void mesclar(NoArvoreB *no, int indice) {
  NoArvoreB *filho = no->filhos[indice];
  NoArvoreB *irmao = no->filhos[indice + 1];

  filho->chaves[T - 1] = no->chaves[indice];

  for (int i = 0; i < irmao->numChaves; i++)
    filho->chaves[i + T] = irmao->chaves[i];

  if (!filho->folha) {
    for (int i = 0; i <= irmao->numChaves; i++)
      filho->filhos[i + T] = irmao->filhos[i];
  }

  for (int i = indice + 1; i < no->numChaves; i++)
    no->chaves[i - 1] = no->chaves[i];

  for (int i = indice + 1; i <= no->numChaves; i++)
    no->filhos[i] = no->filhos[i + 1];

  filho->numChaves += irmao->numChaves + 1;
  no->numChaves--;
  free(irmao->chaves);
  free(irmao->filhos);
  free(irmao);
}

void removerNaoFolha(NoArvoreB *no, int indice) {
  int chave = no->chaves[indice];

  if (no->filhos[indice]->numChaves >= T) {
    NoArvoreB *filho = no->filhos[indice];
    while (filho->numChaves >= T)
      filho = filho->filhos[filho->numChaves];

    int chaveSubstituta = filho->chaves[filho->numChaves - 1];
    remover(no->filhos[indice], chaveSubstituta);
    no->chaves[indice] = chaveSubstituta;
  } else if (no->filhos[indice + 1]->numChaves >= T) {
    NoArvoreB *irmao = no->filhos[indice + 1];
    int chaveSubstituta = irmao->chaves[0];

    if (!irmao->folha) {
      while (!irmao->folha)
        irmao = irmao->filhos[0];
    }

    remover(no->filhos[indice + 1], chaveSubstituta);
    no->chaves[indice] = chaveSubstituta;
  } else {
    mesclar(no, indice);
    remover(no->filhos[indice], chave);
  }
}

void remover(NoArvoreB **raiz, int chave) {
  NoArvoreB *r = *raiz;

  if (!r) {
    printf("Árvore está vazia.\n");
    return;
  }

  int indice = 0;
  while (indice < r->numChaves && chave > r->chaves[indice])
    indice++;

  if (indice < r->numChaves && chave == r->chaves[indice]) {
    if (r->folha) {
      for (int i = indice + 1; i < r->numChaves; i++)
        r->chaves[i - 1] = r->chaves[i];
      r->numChaves--;
    } else {
      removerNaoFolha(r, indice);
    }
  } else {
    if (r->folha) {
      printf("Chave não encontrada.\n");
      return;
    }

    int temFilho = (indice < r->numChaves) ? r->filhos[indice]->numChaves : 0;

    if (temFilho < T) {
      if (indice != r->numChaves && r->filhos[indice + 1]->numChaves >= T) {
        NoArvoreB *filho = r->filhos[indice];
        NoArvoreB *irmao = r->filhos[indice + 1];

        filho->chaves[filho->numChaves] = r->chaves[indice];
        filho->numChaves++;

        r->chaves[indice] = irmao->chaves[0];

        for (int i = 1; i < irmao->numChaves; i++)
          irmao->chaves[i - 1] = irmao->chaves[i];

        if (!filho->folha) {
          filho->filhos[filho->numChaves] = irmao->filhos[0];
          filho->numChaves++;
          for (int i = 0; i <= irmao->numChaves; i++)
            irmao->filhos[i] = irmao->filhos[i + 1];
        }

        irmao->numChaves--;
        remover(filho, chave);
      } else if (indice != 0 && r->filhos[indice - 1]->numChaves >= T) {
        NoArvoreB *filho = r->filhos[indice];
        NoArvoreB *irmao = r->filhos[indice - 1];

        for (int i = filho->numChaves; i > 0; i--)
          filho->chaves[i] = filho->chaves[i - 1];

        filho->chaves[0] = r->chaves[indice - 1];

        if (!filho->folha)
          filho->filhos[filho->numChaves + 1] = filho->filhos[filho->numChaves];

        filho->numChaves++;

        r->chaves[indice - 1] = irmao->chaves[irmao->numChaves - 1];
        irmao->numChaves--;
        remover(filho, chave);
      } else {
        if (indice != r->numChaves)
          mesclar(r, indice);
        else
          mesclar(r, indice - 1);
        remover(r->filhos[indice], chave);
      }
    } else {
      remover(r->filhos[indice], chave);
    }
  }
}

void imprimir(NoArvoreB *raiz) {
  percorrer(raiz);
  printf("\n");
}

int main() {
  NoArvoreB *raiz = criarNo(1); // Cria a raiz da árvore B
  int opcao, valor;

  do {
    printf("\n\n------- Menu Árvore B ---------------\n\n");
    printf("- 1 --- Inserir valor\n");
    printf("- 2 --- Imprimir árvore em ordem\n");
    printf("- 3 --- Buscar valor\n");
    printf("- 4 --- Remover valor\n");
    printf("- 0 --- Sair\n\n");
    printf("- Opção --> ");
    scanf("%d", &opcao);

    switch (opcao) {
    case 1: {
      printf("\n\n--- Inserir valor\n");
      printf("Digite o valor a ser inserido: ");
      scanf("%d", &valor);
      inserir(&raiz, valor);
      break;
    }

    case 2: {
      printf("\n\n--- Imprimir árvore em ordem\n");
      printf("Árvore em ordem:\n");
      percorrer(raiz);
      printf("\n");
      break;
    }

    case 3: {
      printf("\n\n--- Buscar No\n");
      printf("Digite o valor a ser buscado: ");
      scanf("%d", &valor);
      if (buscar(raiz, valor)) {
        printf("Valor %d encontrado.\n", valor);
      } else {
        printf("Valor %d não encontrado.\n", valor);
      }
      break;
    }

    case 4: {
      printf("\n\n--- Remover No\n");
      printf("Digite o valor a ser removido: ");
      scanf("%d", &valor);
      remover(&raiz, valor);
      printf("Valor %d removido.\n", valor);
      break;
    }

    case 0: {
      printf("\n\n--- Sair\n");
      printf("Saindo...\n");
      break;
    }

    default: {
      printf("Opção inválida. Tente novamente.\n");
      break;
    }
    }
  } while (opcao != 0);

  return 0;
}
