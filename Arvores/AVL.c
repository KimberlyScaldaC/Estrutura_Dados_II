// Kimberly Scaldaferro Colodeti
// Arvore AVL
#include <stdio.h>
#include <stdlib.h>

struct NoAVL {
  int dado;
  struct NoAVL *esq;
  struct NoAVL *dir;
  int altura;
};

// Função para criar um novo nó na árvore
struct NoAVL *criarNo(int dado) {
  // Aloca memória
  struct NoAVL *novoNo = (struct NoAVL *)malloc(sizeof(struct NoAVL));
  if (novoNo == NULL) {
    printf("Erro -> Falha ao alocar memória\n");
    exit(-1);
  }
  novoNo->dado = dado;
  // Como é um novo nó os filhos são NULL
  novoNo->esq = NULL;
  novoNo->dir = NULL;
  novoNo->altura = 0;
  return novoNo;
}

int calcularAlturaNo(struct NoAVL *no) {
  // Verifica se o nó é nulo
  if (no == NULL) {
    return -1;
  }
  return no->altura;
}

// Função para calcular o fator de balanceamento de um nó
int fatorBalanceamentoNo(struct NoAVL *no) {
  if (no == NULL) {
    return 0;
  }
  // Calcula o fator de balanceamento subArv Esq - subArv Dir
  return calcularAlturaNo(no->esq) - calcularAlturaNo(no->dir);
}

// Arvore desbalanciada com fator de balanciamento = +2
struct NoAVL *rotacaoDireita(struct NoAVL *no) {
  // Define a nova raiz como o nó à esquerda
  struct NoAVL *novaRaiz = no->esq;
  // Define a subárvore como a subárvore direita da nova raiz
  struct NoAVL *subArvore = novaRaiz->dir;

  // Fazendo a rotação
  novaRaiz->dir = no;
  no->esq = subArvore;

  // Atualiza as alturas
  if (calcularAlturaNo(no->esq) > calcularAlturaNo(no->dir)) {
    no->altura = 1 + calcularAlturaNo(no->esq);
  } else {
    no->altura = 1 + calcularAlturaNo(no->dir);
  }
  if (calcularAlturaNo(novaRaiz->esq) > calcularAlturaNo(novaRaiz->dir)) {
    novaRaiz->altura = 1 + calcularAlturaNo(novaRaiz->esq);
  } else {
    novaRaiz->altura = 1 + calcularAlturaNo(novaRaiz->dir);
  }

  return novaRaiz;
}

// Arvore desbalanciada com fator de balanciamento = -2
struct NoAVL *rotacaoEsquerda(struct NoAVL *no) {
  // Define a nova raiz como o nó à direita
  struct NoAVL *novaRaiz = no->dir;
  struct NoAVL *subArvore = novaRaiz->esq;

  // Fazendo a rotação
  novaRaiz->esq = no;
  no->dir = subArvore;

  // Atualiza as alturas
  if (calcularAlturaNo(no->esq) > calcularAlturaNo(no->dir)) {
    no->altura = 1 + calcularAlturaNo(no->esq);
  } else {
    no->altura = 1 + calcularAlturaNo(no->dir);
  }
  if (calcularAlturaNo(novaRaiz->esq) > calcularAlturaNo(novaRaiz->dir)) {
    novaRaiz->altura = 1 + calcularAlturaNo(novaRaiz->esq);
  } else {
    novaRaiz->altura = 1 + calcularAlturaNo(novaRaiz->dir);
  }

  return novaRaiz;
}

// Função que vai realizar o balanceamento da árvore
struct NoAVL *balanceamentoArv(struct NoAVL *raiz, int dado) {

  if (raiz == NULL) {
    return raiz;
  }
  if (calcularAlturaNo(raiz->esq) > calcularAlturaNo(raiz->dir)) {
    raiz->altura = 1 + calcularAlturaNo(raiz->esq);
  } else {
    raiz->altura = 1 + calcularAlturaNo(raiz->dir);
  }

  // Calcula o fator de balanceamento deste nó
  // para verificar se ele se tornou desbalanceado

  // Calcula o fator de balanceamento da raiz
  int balanceamento = fatorBalanceamentoNo(raiz);

  // Caso de desbalanceamento à esquerda-esquerda
  // Fator de balanceamento = +2
  if (balanceamento > 1 && dado < raiz->esq->dado) {
    return rotacaoDireita(raiz); // RSD
  }
  // Caso de desbalanceamento à direita-direita
  // Fator de balanceamento = -2
  if (balanceamento < -1 && dado > raiz->dir->dado) {
    return rotacaoEsquerda(raiz); // RSE
  }
  // Caso de desbalanceamento à esquerda-direita
  // RDD
  if (balanceamento > 1 && dado > raiz->esq->dado) {
    raiz->esq = rotacaoEsquerda(raiz->esq);
    return rotacaoDireita(raiz);
  }

  // Caso de desbalanceamento à direita-esquerda
  // RDE
  if (balanceamento < -1 && dado < raiz->dir->dado) {
    raiz->dir = rotacaoDireita(raiz->dir);
    return rotacaoEsquerda(raiz);
  }

  return raiz;
}

// Função para inserir um novo nó na árvore AVL
struct NoAVL *adicionaNo(struct NoAVL *raiz, int dado) {

  if (raiz == NULL) {
    return criarNo(dado);
  }

  // Se o dado a ser inserido for menor que o valor da raiz atual, insere
  // recursivamente na subárvore esquerda
  if (dado < raiz->dado) {
    raiz->esq = adicionaNo(raiz->esq, dado);
  }  else if (dado > raiz->dado) {
    raiz->dir = adicionaNo(raiz->dir, dado);
  } else {
    return raiz;
  }

  return balanceamentoArv(raiz, dado);
}

// Encontra o menor valor na árvore AVL
struct NoAVL *encontrarMinimo(struct NoAVL *no) {
  struct NoAVL *atual = no;

  // Percorre a subárvore esquerda até encontrar o nó mais à esquerda
  while (atual && atual->esq != NULL)
    atual = atual->esq;

  return atual;
}

struct NoAVL *encontrarMaximo(struct NoAVL *no) {
  if (no == NULL)
    return NULL;

  // Percorre a subárvore à esquerda até encontrar o nó mais à direita
  while (no->dir != NULL) {
    no = no->dir;
  }

  return no;
}

// Função para excluir um nó na árvore AVL
struct NoAVL *excluir(struct NoAVL *raiz, int valor) {
  if (raiz == NULL) {
    return raiz;
  }

  // Verifica se o dado está à esquerda
  if (valor < raiz->dado) {
    raiz->esq = excluir(raiz->esq, valor);
  } else if (valor > raiz->dado){
    raiz->dir = excluir(raiz->dir, valor); 
  } else  {
    // Caso 1: Nó folha ou nó com apenas um filho
    // Se tiver apenas filhos à direita
    if (raiz->esq == NULL) {
      struct NoAVL *temp = raiz->dir; 
      free(raiz);                     
      return temp;                
    } else if (raiz->dir == NULL) // Se tiver apenas filhos à esquerda
    {
      struct NoAVL *temp = raiz->esq; 
      free(raiz);                     
      return temp; 
    }

    // Caso 2: Nó com dois filhos
    // Verifica o balanceamento antes de decidir entre o valor maior à direita
    // da subárvore esquerda ou o menor valor à esquerda da subárvore direita
    if (calcularAlturaNo(raiz->esq) >= calcularAlturaNo(raiz->dir)) {
      // Se a altura da subárvore esquerda for maior,
      // escolhe o maior valor à direita da subárvore esquerda
      struct NoAVL *temp = encontrarMaximo(raiz->esq);
      raiz->dado = temp->dado; 
      raiz->esq = excluir(raiz->esq,temp->dado); 
    } else {
      // Caso contrário, escolhe o menor valor à esquerda da subárvore direita
      struct NoAVL *temp = encontrarMinimo(raiz->dir);   
      raiz->dado = temp->dado; 
      raiz->dir = excluir(raiz->dir, temp->dado);
    }
  }
  return balanceamentoArv(raiz, valor);
}

// Função para percorrer a árvore em ordem
void percorrerEmOrdem(struct NoAVL *raiz) {
  if (raiz != NULL) 
  {
    percorrerEmOrdem(raiz->esq); 
    printf("%d ", raiz->dado);   
    percorrerEmOrdem(raiz->dir); 
  }
}

// Função para percorrer a árvore em pré-ordem
void percorrerPreOrdem(struct NoAVL *raiz) {
  if (raiz != NULL) {
    printf("%d ", raiz->dado);   
    percorrerEmOrdem(raiz->esq); 
    percorrerEmOrdem(raiz->dir); 
  }
}

// Função para percorrer a árvore em pós-ordem
void percorrerPosOrdem(struct NoAVL *raiz) {
  if (raiz != NULL) 
  {
    percorrerEmOrdem(raiz->esq); 
    percorrerEmOrdem(raiz->dir); 
    printf("%d ", raiz->dado);   
  }
}

void imprimeNo(int c, int b) {
  int i;
  for (i = 0; i < b; i++) {
    printf("   ");
  }
  printf("%i\n", c); 
}

// Função para exibir a árvore no formato esquerda-raiz-direita
void mostraArvore(struct NoAVL *a, int b) {
  if (a != NULL) {
    // Chama a função recursivamente para percorrer a subárvore direita
    mostraArvore(a->dir, b + 1);
    // Imprime o nó atual com um espaçamento proporcional à sua profundidade
    imprimeNo(a->dado, b);
    // Chama a função recursivamente para percorrer a subárvore esquerda
    mostraArvore(a->esq, b + 1);
  }
}

// Função para calcular a altura de uma árvore AVL
int alturaTree(struct NoAVL *no) {
  if (no == NULL) {
    return -1;
  }

  // Calcula a altura da subárvore esquerda e direita
  int altura_esquerda = alturaTree(no->esq) + 1;
  int altura_direita = alturaTree(no->dir) + 1;

  // Retorna a maior altura entre a subárvore esquerda e direita, somada à
  // altura do nó atual
  if (1 + ((altura_esquerda > altura_direita))) {
    return altura_esquerda;
  } else {
    return altura_direita;
  }
}

// Buscar elemento na árvore
struct NoAVL *buscarNo(struct NoAVL *raiz, int valor) {
  if (raiz == NULL || raiz->dado == valor)
    return raiz;

  if (valor < raiz->dado)
    return buscarNo(raiz->esq, valor);
  else
    return buscarNo(raiz->dir, valor);
}

int main() {
    int op = -1, valor;
    struct NoAVL *raiz = NULL;
    while (op != 0) {
      printf("\n\n------- Menu ---------------\n\n");
      printf("- 1 --- Adiciona Elemento(no)\n");
      printf("- 2 --- Excluir Elemento(no)\n");
      printf("- 3 --- Automatico\n");
      printf("- 0 --- Sair\n\n");
      printf("- Opção --> ");
      scanf("%d", &op);

      switch (op) {
      case 1:
        printf("\n\n--- Adiciona Elemento(no)\n");
        printf("\nDigite o valor do no ->");
        scanf("%d", &valor);
        raiz = adicionaNo(raiz, valor);
        mostraArvore(raiz, 3);
        break;

      case 2:
        printf("\n\n--- Excluir Elemento(no)\n");
        printf("\nDigite o valor do no ->");
        scanf("%d", &valor);
        raiz = excluir(raiz, valor);
        mostraArvore(raiz, 3);
        break;

      case 3:
        printf("\n\n--- Automatico\n");
        // Inserindo elementos na árvore AVL
        raiz = adicionaNo(raiz, 30);
        raiz = adicionaNo(raiz, 24);
        raiz = adicionaNo(raiz, 20);
        raiz = adicionaNo(raiz, 35);
        raiz = adicionaNo(raiz, 27);
        raiz = adicionaNo(raiz, 33);
        raiz = adicionaNo(raiz, 38);
        raiz = adicionaNo(raiz, 25);
        raiz = adicionaNo(raiz, 22);
        raiz = adicionaNo(raiz, 34);
        raiz = adicionaNo(raiz, 40);
        raiz = adicionaNo(raiz, 29);
        mostraArvore(raiz, 3);

        printf("\nLetra A - Insere 31 ---------------------------\n");
        raiz = adicionaNo(raiz, 31);
        mostraArvore(raiz, 3);

        printf("\nLetra B - Insere 15 ---------------------------\n");
        raiz = adicionaNo(raiz, 15);
        mostraArvore(raiz, 3);

        printf("\nLetra C - Insere 23 ----------------------------\n");
        raiz = adicionaNo(raiz, 23);
        mostraArvore(raiz, 3);

        printf("\nLetra D - Exclui 24 ---------------------------\n");
        raiz = excluir(raiz, 24);
        mostraArvore(raiz, 3);

        printf("\nLetra E - Exclui 35 ---------------------------\n");
        raiz = excluir(raiz, 35);
        mostraArvore(raiz, 3);

        printf("\nLetra F - Inserir 24 ---------------------------\n");
        raiz = adicionaNo(raiz, 24);
        mostraArvore(raiz, 3);

        printf("\nLetra G - Exclui 27 ---------------------------\n");
        raiz = excluir(raiz, 27);
        mostraArvore(raiz, 3);

        printf("\nLetra H - Inserir 32 ---------------------------\n");
        raiz = adicionaNo(raiz, 32);
        mostraArvore(raiz, 3);

        printf("\nLetra I - Exclui 30 ---------------------------\n");
        raiz = excluir(raiz, 30);
        mostraArvore(raiz, 3);

        printf("\nLetra J - Inserir 21 ---------------------------\n");
        raiz = adicionaNo(raiz, 21);
        mostraArvore(raiz, 3);
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
