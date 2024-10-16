
// --------------------------------------

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

// --------------------------------------

// // Kimberly Scaldaferro Colodeti
// #include <stdio.h>
// #include <stdlib.h>

// int filhoEsq(int ind_parente) { return (2 * ind_parente + 1); }

// int filhoDir(int ind_parente) { return (2 * ind_parente + 2); }

// int pai(int heap) { return (int)(heap - 1) / 2; }

// int verificaArv(int *vetor[], int size) {
//   int pai, filhoEsq, filhoDir;
//   for (int i = 0; i < size / 2; i++) {
//     pai = vetor[pai(i)];
//     filhoEsq = vetor[filhoEsq(i)];
//     filhoDir = vetor[filhoDir(i)];
//   }
//   return 0;
// }

// int main() {
//   int vetor[7] = {30, 15, 25, 12, 10, 21, 23};

//   for (int i = 0; i < (sizeof(vetor) / sizeof(int)) / 2; i++) {
//     printf("\nPai -> %d - Filho Esq- %d e Filho Dir- %d", vetor[i],
//            vetor[filhoEsq(i)], vetor[filhoDir(i)]);
//   }

//   return 0;
// }

// --------------------------------------

// // Kimberly Scaldaferro Colodeti
// // Arvore Red Black
// #include <stdio.h>
// #include <stdlib.h>

// // Definição dos possíveis valores de cor
// #define VERMELHO 0
// #define PRETO 1

// // Definição da estrutura de um nó da árvore Red-Black
// struct No {
//   int valor;
//   int cor;
//   struct No *esq;
//   struct No *dir;
//   struct No *pai;
// };

// // Define 'No' como um alias para 'struct No'
// typedef struct No No;

// // Função para criar um novo nó
// No *criarNo(int valor) {
//   // Aloca memória para um novo nó
//   No *novoNo = (No *)malloc(sizeof(No));
//   // Define o valor do nó
//   novoNo->valor = valor;
//   // Inicialmente, o novo nó é vermelho
//   novoNo->cor = VERMELHO;
//   // Inicializa os ponteiros como NULL
//   novoNo->esq = novoNo->dir = novoNo->pai = NULL;
//   // Retorna o novo nó criado
//   return novoNo;
// }

// // Função para fazer a rotação à esquerda
// void rotacaoEsquerda(No **raiz, No *x) {
//   // y é o filho à direita de x
//   No *y = x->dir;
//   // A subárvore esquerda de y se torna a subárvore direita de x
//   x->dir = y->esq;
//   if (y->esq != NULL) {
//     // Atualiza o pai do filho esquerdo de y
//     y->esq->pai = x;
//   }
//   // O pai de y se torna o pai de x
//   y->pai = x->pai;
//   if (x->pai == NULL) {
//     // Se x é a raiz, y se torna a nova raiz
//     *raiz = y;
//   } else if (x == x->pai->esq) {
//     // Se x é filho à esquerda, atualiza o ponteiro correspondente
//     x->pai->esq = y;
//   } else {
//     // Se x é filho à direita, atualiza o ponteiro correspondente
//     x->pai->dir = y;
//   }
//   // x se torna o filho esquerdo de y
//   y->esq = x;
//   // Atualiza o pai de x
//   x->pai = y;
// }

// // Função para fazer a rotação à direita
// void rotacaoDireita(No **raiz, No *x) {
//   // y é o filho à esquerda de x
//   No *y = x->esq;
//   // A subárvore direita de y se torna a subárvore esquerda de x
//   x->esq = y->dir;
//   if (y->dir != NULL) {
//     // Atualiza o pai do filho direito de y
//     y->dir->pai = x;
//   }
//   // O pai de y se torna o pai de x
//   y->pai = x->pai;
//   if (x->pai == NULL) {
//     // Se x é a raiz, y se torna a nova raiz
//     *raiz = y;
//   } else if (x == x->pai->dir) {
//     // Se x é filho à direita, atualiza o ponteiro correspondente
//     x->pai->dir = y;
//   } else {
//     // Se x é filho à esquerda, atualiza o ponteiro correspondente
//     x->pai->esq = y;
//   }
//   // x se torna o filho direito de y
//   y->dir = x;
//   // Atualiza o pai de x
//   x->pai = y;
// }

// // Função para balancear a árvore após a inserção de um nó
// void corrigirViolacao(No **raiz, No *z) {
//   // Enquanto z não for a raiz e seu pai for vermelho
//   while (z != *raiz && z->pai->cor == VERMELHO) {
//     // Se o pai de z é filho à esquerda do avô
//     if (z->pai == z->pai->pai->esq) {
//       // y é o tio de z
//       No *y = z->pai->pai->dir;
//       // Se o tio y é vermelho
//       if (y != NULL && y->cor == VERMELHO) {
//         // O pai de z se torna preto
//         z->pai->cor = PRETO;
//         // O tio y se torna preto
//         y->cor = PRETO;
//         // O avô se torna vermelho
//         z->pai->pai->cor = VERMELHO;
//         // Sobe para o avô
//         z = z->pai->pai;
//       } else {
//         // Se z é filho à direita
//         if (z == z->pai->dir) {
//           // Sobe para o pai
//           z = z->pai;

//           rotacaoEsquerda(raiz, z);
//         }
//         // O pai de z se torna preto
//         z->pai->cor = PRETO;
//         // O avô se torna vermelho
//         z->pai->pai->cor = VERMELHO;

//         rotacaoDireita(raiz, z->pai->pai);
//       }
//     } else // Se o pai de z é filho à direita do avô
//     {
//       // y é o tio de z
//       No *y = z->pai->pai->esq;
//       // Se o tio y é vermelho
//       if (y != NULL && y->cor == VERMELHO) {
//         // O pai de z se torna preto
//         z->pai->cor = PRETO;
//         // O tio y se torna preto
//         y->cor = PRETO;
//         // O avô se torna vermelho
//         z->pai->pai->cor = VERMELHO;
//         // Sobe para o avô
//         z = z->pai->pai;
//       } else {
//         // Se z é filho à esquerda
//         if (z == z->pai->esq) {
//           // Sobe para o pai
//           z = z->pai;

//           rotacaoDireita(raiz, z);
//         }
//         // O pai de z se torna preto
//         z->pai->cor = PRETO;
//         // O avô se torna vermelho
//         z->pai->pai->cor = VERMELHO;

//         rotacaoEsquerda(raiz, z->pai->pai);
//       }
//     }
//   }
//   // A raiz sempre deve ser preta
//   (*raiz)->cor = PRETO;
// }

// // Função para inserir um novo nó na árvore Red-Black
// void inserir(No **raiz, int valor) {
//   // Cria um novo nó com o valor
//   No *z = criarNo(valor);
//   // Variável para armazenar o pai do novo nó
//   No *y = NULL;
//   // Começa a busca pela raiz
//   No *x = *raiz;

//   // Enquanto não chegar a um nó folha
//   while (x != NULL) {
//     y = x; // Atualiza o pai
//     // Se o valor do novo nó é menor que o valor do nó atual
//     if (z->valor < x->valor) {
//       x = x->esq; // Move para a esquerda
//     } else {
//       x = x->dir; // Move para a direita
//     }
//   }
//   // Define o pai do novo nó
//   z->pai = y;
//   if (y == NULL) {
//     // Se a árvore estava vazia, o novo nó é a raiz
//     *raiz = z;
//   } else if (z->valor < y->valor) {
//     // O novo nó é o filho à esquerda
//     y->esq = z;
//   } else {
//     // O novo nó é o filho à direita
//     y->dir = z;
//   }
//   // Chama a função para corrigir possíveis violações
//   corrigirViolacao(raiz, z);
// }

// // Função para imprimir a árvore Red-Black em ordem
// void emOrdem(No *raiz) {
//   // Se o nó não é NULL
//   if (raiz != NULL) {
//     // Chama a função na subárvore esquerda
//     emOrdem(raiz->esq);
//     if (raiz->cor == 0) {
//       printf("%d -> RED\n", raiz->valor);
//     } else {
//       printf("%d -> BLACK\n", raiz->valor);
//     }
//     // Chama a função na subárvore direita
//     emOrdem(raiz->dir);
//   }
// }

// // Função para imprimir a árvore com formatação
// void imprimeArvoreRB(No *raiz, int b) {
//   // Se o nó não é NULL
//   if (raiz != NULL) {
//     // Chama a função para a subárvore direita
//     imprimeArvoreRB(raiz->dir, b + 1);
//     // Imprime espaços proporcionais à profundidade do nó
//     for (int i = 0; i < b; i++) {
//       printf("       ");
//     }
//     // Imprime o valor do nó, formatado por cor
//     if (raiz->cor == 0) {
//       printf("%d -> RED\n\n", raiz->valor);
//     } else {
//       printf("%d -> BLACK\n\n", raiz->valor);
//     }
//     // Chama a função para a subárvore esquerda
//     imprimeArvoreRB(raiz->esq, b + 1);
//   }
// }

// int main() {
//   // Inicializa a raiz da árvore como NULL
//   struct No *raiz = NULL;
//   int opcao, valor;

//   do {
//     printf("\n\n------- Menu ---------------\n\n");
//     printf("- 1 --- Inserir valor\n");
//     printf("- 2 --- Imprimir árvore em ordem\n");
//     printf("- 3 --- Imprimir árvore com formatação\n");
//     printf("- 0 --- Sair\n\n");
//     printf("- Opção --> ");
//     scanf("%d", &opcao);

//     switch (opcao) {
//     case 1:
//       printf("\n\n--- Inserir valor\n");
//       printf("Digite o valor a ser inserido: ");
//       scanf("%d", &valor);
//       inserir(&raiz, valor);
//       break;

//     case 2:
//       printf("\n\n--- Imprimir árvore em ordem\n");
//       printf("Árvore em ordem:\n");
//       emOrdem(raiz);
//       break;

//     case 3:
//       printf("\n\n--- Imprimir árvore com formatação\n");
//       printf("Árvore com formatação:\n");
//       imprimeArvoreRB(raiz, 0);
//       break;

//     case 0:
//       printf("\n\n--- Sair\n");
//       printf("Saindo...\n");
//       break;

//     default:
//       printf("Opção inválida. Tente novamente.\n");
//       break;
//     }
//     printf("\n");
//   } while (opcao != 0);

//   return 0;
// }

// --------------------------------------

// // Kimberly Scaldaferro Colodeti
// // Arvore AVL
// #include <stdio.h>
// #include <stdlib.h>

// struct NoAVL {
//   int dado;
//   struct NoAVL *esq;
//   struct NoAVL *dir;
//   int altura;
// };

// // Função para criar um novo nó na árvore
// struct NoAVL *criarNo(int dado) {
//   // Aloca memória
//   struct NoAVL *novoNo = (struct NoAVL *)malloc(sizeof(struct NoAVL));
//   if (novoNo == NULL) {
//     printf("Erro -> Falha ao alocar memória\n");
//     exit(-1);
//   }
//   novoNo->dado = dado;
//   // Como é um novo nó os filhos são NULL
//   novoNo->esq = NULL;
//   novoNo->dir = NULL;
//   novoNo->altura = 0;
//   return novoNo;
// }

// int calcularAlturaNo(struct NoAVL *no) {
//   // Verifica se o nó é nulo
//   if (no == NULL) {
//     return -1;
//   }
//   return no->altura;
// }

// // Função para calcular o fator de balanceamento de um nó
// int fatorBalanceamentoNo(struct NoAVL *no) {
//   if (no == NULL) {
//     return 0;
//   }
//   // Calcula o fator de balanceamento subArv Esq - subArv Dir
//   return calcularAlturaNo(no->esq) - calcularAlturaNo(no->dir);
// }

// // Arvore desbalanciada com fator de balanciamento = +2
// struct NoAVL *rotacaoDireita(struct NoAVL *no) {
//   // Define a nova raiz como o nó à esquerda
//   struct NoAVL *novaRaiz = no->esq;
//   // Define a subárvore como a subárvore direita da nova raiz
//   struct NoAVL *subArvore = novaRaiz->dir;

//   // Fazendo a rotação
//   novaRaiz->dir = no;
//   no->esq = subArvore;

//   // Atualiza as alturas
//   if (calcularAlturaNo(no->esq) > calcularAlturaNo(no->dir)) {
//     no->altura = 1 + calcularAlturaNo(no->esq);
//   } else {
//     no->altura = 1 + calcularAlturaNo(no->dir);
//   }
//   if (calcularAlturaNo(novaRaiz->esq) > calcularAlturaNo(novaRaiz->dir)) {
//     novaRaiz->altura = 1 + calcularAlturaNo(novaRaiz->esq);
//   } else {
//     novaRaiz->altura = 1 + calcularAlturaNo(novaRaiz->dir);
//   }

//   return novaRaiz;
// }

// // Arvore desbalanciada com fator de balanciamento = -2
// struct NoAVL *rotacaoEsquerda(struct NoAVL *no) {
//   // Define a nova raiz como o nó à direita
//   struct NoAVL *novaRaiz = no->dir;
//   struct NoAVL *subArvore = novaRaiz->esq;

//   // Fazendo a rotação
//   novaRaiz->esq = no;
//   no->dir = subArvore;

//   // Atualiza as alturas
//   if (calcularAlturaNo(no->esq) > calcularAlturaNo(no->dir)) {
//     no->altura = 1 + calcularAlturaNo(no->esq);
//   } else {
//     no->altura = 1 + calcularAlturaNo(no->dir);
//   }
//   if (calcularAlturaNo(novaRaiz->esq) > calcularAlturaNo(novaRaiz->dir)) {
//     novaRaiz->altura = 1 + calcularAlturaNo(novaRaiz->esq);
//   } else {
//     novaRaiz->altura = 1 + calcularAlturaNo(novaRaiz->dir);
//   }

//   return novaRaiz;
// }

// // Função que vai realizar o balanceamento da árvore
// struct NoAVL *balanceamentoArv(struct NoAVL *raiz, int dado) {

//   if (raiz == NULL) {
//     return raiz;
//   }
//   if (calcularAlturaNo(raiz->esq) > calcularAlturaNo(raiz->dir)) {
//     raiz->altura = 1 + calcularAlturaNo(raiz->esq);
//   } else {
//     raiz->altura = 1 + calcularAlturaNo(raiz->dir);
//   }

//   // Calcula o fator de balanceamento deste nó
//   // para verificar se ele se tornou desbalanceado

//   // Calcula o fator de balanceamento da raiz
//   int balanceamento = fatorBalanceamentoNo(raiz);

//   // Caso de desbalanceamento à esquerda-esquerda
//   // Fator de balanceamento = +2
//   if (balanceamento > 1 && dado < raiz->esq->dado) {
//     return rotacaoDireita(raiz); // RSD
//   }
//   // Caso de desbalanceamento à direita-direita
//   // Fator de balanceamento = -2
//   if (balanceamento < -1 && dado > raiz->dir->dado) {
//     return rotacaoEsquerda(raiz); // RSE
//   }
//   // Caso de desbalanceamento à esquerda-direita
//   // RDD
//   if (balanceamento > 1 && dado > raiz->esq->dado) {
//     raiz->esq = rotacaoEsquerda(raiz->esq);
//     return rotacaoDireita(raiz);
//   }

//   // Caso de desbalanceamento à direita-esquerda
//   // RDE
//   if (balanceamento < -1 && dado < raiz->dir->dado) {
//     raiz->dir = rotacaoDireita(raiz->dir);
//     return rotacaoEsquerda(raiz);
//   }

//   return raiz;
// }

// // Função para inserir um novo nó na árvore AVL
// struct NoAVL *adicionaNo(struct NoAVL *raiz, int dado) {

//   if (raiz == NULL) {
//     return criarNo(dado);
//   }

//   // Se o dado a ser inserido for menor que o valor da raiz atual, insere
//   // recursivamente na subárvore esquerda
//   if (dado < raiz->dado) {
//     raiz->esq = adicionaNo(raiz->esq, dado);
//   }  else if (dado > raiz->dado) {
//     raiz->dir = adicionaNo(raiz->dir, dado);
//   } else {
//     return raiz;
//   }

//   return balanceamentoArv(raiz, dado);
// }

// // Encontra o menor valor na árvore AVL
// struct NoAVL *encontrarMinimo(struct NoAVL *no) {
//   struct NoAVL *atual = no;

//   // Percorre a subárvore esquerda até encontrar o nó mais à esquerda
//   while (atual && atual->esq != NULL)
//     atual = atual->esq;

//   return atual;
// }

// struct NoAVL *encontrarMaximo(struct NoAVL *no) {
//   if (no == NULL)
//     return NULL;

//   // Percorre a subárvore à esquerda até encontrar o nó mais à direita
//   while (no->dir != NULL) {
//     no = no->dir;
//   }

//   return no;
// }

// // Função para excluir um nó na árvore AVL
// struct NoAVL *excluir(struct NoAVL *raiz, int valor) {
//   if (raiz == NULL) {
//     return raiz;
//   }

//   // Verifica se o dado está à esquerda
//   if (valor < raiz->dado) {
//     raiz->esq = excluir(raiz->esq, valor);
//   } else if (valor > raiz->dado){
//     raiz->dir = excluir(raiz->dir, valor);
//   } else  {
//     // Caso 1: Nó folha ou nó com apenas um filho
//     // Se tiver apenas filhos à direita
//     if (raiz->esq == NULL) {
//       struct NoAVL *temp = raiz->dir;
//       free(raiz);
//       return temp;
//     } else if (raiz->dir == NULL) // Se tiver apenas filhos à esquerda
//     {
//       struct NoAVL *temp = raiz->esq;
//       free(raiz);
//       return temp;
//     }

//     // Caso 2: Nó com dois filhos
//     // Verifica o balanceamento antes de decidir entre o valor maior à
//     direita
//     // da subárvore esquerda ou o menor valor à esquerda da subárvore direita
//     if (calcularAlturaNo(raiz->esq) >= calcularAlturaNo(raiz->dir)) {
//       // Se a altura da subárvore esquerda for maior,
//       // escolhe o maior valor à direita da subárvore esquerda
//       struct NoAVL *temp = encontrarMaximo(raiz->esq);
//       raiz->dado = temp->dado;
//       raiz->esq = excluir(raiz->esq,temp->dado);
//     } else {
//       // Caso contrário, escolhe o menor valor à esquerda da subárvore
//       direita struct NoAVL *temp = encontrarMinimo(raiz->dir); raiz->dado =
//       temp->dado; raiz->dir = excluir(raiz->dir, temp->dado);
//     }
//   }
//   return balanceamentoArv(raiz, valor);
// }

// // Função para percorrer a árvore em ordem
// void percorrerEmOrdem(struct NoAVL *raiz) {
//   if (raiz != NULL)
//   {
//     percorrerEmOrdem(raiz->esq);
//     printf("%d ", raiz->dado);
//     percorrerEmOrdem(raiz->dir);
//   }
// }

// // Função para percorrer a árvore em pré-ordem
// void percorrerPreOrdem(struct NoAVL *raiz) {
//   if (raiz != NULL) {
//     printf("%d ", raiz->dado);
//     percorrerEmOrdem(raiz->esq);
//     percorrerEmOrdem(raiz->dir);
//   }
// }

// // Função para percorrer a árvore em pós-ordem
// void percorrerPosOrdem(struct NoAVL *raiz) {
//   if (raiz != NULL)
//   {
//     percorrerEmOrdem(raiz->esq);
//     percorrerEmOrdem(raiz->dir);
//     printf("%d ", raiz->dado);
//   }
// }

// void imprimeNo(int c, int b) {
//   int i;
//   for (i = 0; i < b; i++) {
//     printf("   ");
//   }
//   printf("%i\n", c);
// }

// // Função para exibir a árvore no formato esquerda-raiz-direita
// void mostraArvore(struct NoAVL *a, int b) {
//   if (a != NULL) {
//     // Chama a função recursivamente para percorrer a subárvore direita
//     mostraArvore(a->dir, b + 1);
//     // Imprime o nó atual com um espaçamento proporcional à sua profundidade
//     imprimeNo(a->dado, b);
//     // Chama a função recursivamente para percorrer a subárvore esquerda
//     mostraArvore(a->esq, b + 1);
//   }
// }

// // Função para calcular a altura de uma árvore AVL
// int alturaTree(struct NoAVL *no) {
//   if (no == NULL) {
//     return -1;
//   }

//   // Calcula a altura da subárvore esquerda e direita
//   int altura_esquerda = alturaTree(no->esq) + 1;
//   int altura_direita = alturaTree(no->dir) + 1;

//   // Retorna a maior altura entre a subárvore esquerda e direita, somada à
//   // altura do nó atual
//   if (1 + ((altura_esquerda > altura_direita))) {
//     return altura_esquerda;
//   } else {
//     return altura_direita;
//   }
// }

// // Buscar elemento na árvore
// struct NoAVL *buscarNo(struct NoAVL *raiz, int valor) {
//   if (raiz == NULL || raiz->dado == valor)
//     return raiz;

//   if (valor < raiz->dado)
//     return buscarNo(raiz->esq, valor);
//   else
//     return buscarNo(raiz->dir, valor);
// }

// int main() {
//     int op = -1, valor;
//     struct NoAVL *raiz = NULL;
//     while (op != 0) {
//       printf("\n\n------- Menu ---------------\n\n");
//       printf("- 1 --- Adiciona Elemento(no)\n");
//       printf("- 2 --- Excluir Elemento(no)\n");
//       printf("- 3 --- Automatico\n");
//       printf("- 0 --- Sair\n\n");
//       printf("- Opção --> ");
//       scanf("%d", &op);

//       switch (op) {
//       case 1:
//         printf("\n\n--- Adiciona Elemento(no)\n");
//         printf("\nDigite o valor do no ->");
//         scanf("%d", &valor);
//         raiz = adicionaNo(raiz, valor);
//         mostraArvore(raiz, 3);
//         break;

//       case 2:
//         printf("\n\n--- Excluir Elemento(no)\n");
//         printf("\nDigite o valor do no ->");
//         scanf("%d", &valor);
//         raiz = excluir(raiz, valor);
//         mostraArvore(raiz, 3);
//         break;

//       case 3:
//         printf("\n\n--- Automatico\n");
//         // Inserindo elementos na árvore AVL
//         raiz = adicionaNo(raiz, 30);
//         raiz = adicionaNo(raiz, 24);
//         raiz = adicionaNo(raiz, 20);
//         raiz = adicionaNo(raiz, 35);
//         raiz = adicionaNo(raiz, 27);
//         raiz = adicionaNo(raiz, 33);
//         raiz = adicionaNo(raiz, 38);
//         raiz = adicionaNo(raiz, 25);
//         raiz = adicionaNo(raiz, 22);
//         raiz = adicionaNo(raiz, 34);
//         raiz = adicionaNo(raiz, 40);
//         raiz = adicionaNo(raiz, 29);
//         mostraArvore(raiz, 3);

//         printf("\nLetra A - Insere 31 ---------------------------\n");
//         raiz = adicionaNo(raiz, 31);
//         mostraArvore(raiz, 3);

//         printf("\nLetra B - Insere 15 ---------------------------\n");
//         raiz = adicionaNo(raiz, 15);
//         mostraArvore(raiz, 3);

//         printf("\nLetra C - Insere 23 ----------------------------\n");
//         raiz = adicionaNo(raiz, 23);
//         mostraArvore(raiz, 3);

//         printf("\nLetra D - Exclui 24 ---------------------------\n");
//         raiz = excluir(raiz, 24);
//         mostraArvore(raiz, 3);

//         printf("\nLetra E - Exclui 35 ---------------------------\n");
//         raiz = excluir(raiz, 35);
//         mostraArvore(raiz, 3);

//         printf("\nLetra F - Inserir 24 ---------------------------\n");
//         raiz = adicionaNo(raiz, 24);
//         mostraArvore(raiz, 3);

//         printf("\nLetra G - Exclui 27 ---------------------------\n");
//         raiz = excluir(raiz, 27);
//         mostraArvore(raiz, 3);

//         printf("\nLetra H - Inserir 32 ---------------------------\n");
//         raiz = adicionaNo(raiz, 32);
//         mostraArvore(raiz, 3);

//         printf("\nLetra I - Exclui 30 ---------------------------\n");
//         raiz = excluir(raiz, 30);
//         mostraArvore(raiz, 3);

//         printf("\nLetra J - Inserir 21 ---------------------------\n");
//         raiz = adicionaNo(raiz, 21);
//         mostraArvore(raiz, 3);
//         break;

//       case 0:
//         op = 0;
//         printf("\nSistema finalizado com sucesso!\n");
//         break;

//       default:
//         printf("Digite uma opcao valida\n");
//       }
//     }
//   return 0;
// }

// --------------------------------------

// // Kimberly Scaldaferro Colodeti
// #include <stdio.h>
// #include <stdlib.h>
// // quando coloca o typedef nao precisa coloca o struct no resto
// typedef struct {
//   int dado;
//   struct NoArvore *esq;
//   struct NoArvore *dir;
// } NoArvore;

// NoArvore *criarNo(int dado) {
//   // alocar memoria
//   NoArvore *novoNo = (NoArvore *)malloc(sizeof(NoArvore));
//   // verifica se alocou na memoria
//   if (novoNo == NULL) {
//     printf("Erro: Falha ao alocar memória para o novo nó.\n");
//     exit(-1);
//   }

//   novoNo->dado = dado;
//   novoNo->esq = NULL;
//   novoNo->dir = NULL;
//   return novoNo;
// }

// NoArvore *adicionaElemento(NoArvore *raiz, int dado) {
//   // Não tem nem um no na arvore
//   if (raiz == NULL) {
//     raiz = criarNo(dado);
//   } else {
//     if (dado <= raiz->dado) {
//       raiz->esq = adicionaElemento(raiz->esq, dado);
//     } else {
//       raiz->dir = adicionaElemento(raiz->dir, dado);
//     }
//   }
//   return raiz;
// }

// // Achar o no folha
// NoArvore *encontrarMinimo(NoArvore *raiz) {
//   NoArvore *atual = raiz;
//   while (atual->esq != NULL) {
//     atual = atual->esq;
//   }
//   return atual;
// }

// // excluir um no
// NoArvore *excluirElemento(NoArvore *raiz, int valor) {
//   if (raiz == NULL) {
//     return raiz;
//   }

//   if (valor < raiz->dado) {
//     raiz->esq = excluirElemento(raiz->esq, valor);
//   } else if (valor > raiz->dado) {
//     raiz->dir = excluirElemento(raiz->dir, valor);
//   } else {
//     // Caso 1: Nó folha ou nó com apenas um filho
//     if (raiz->esq == NULL) {
//       NoArvore *temp = raiz->dir;
//       free(raiz);
//       return temp;
//     } else if (raiz->dir == NULL) {
//       NoArvore *temp = raiz->esq;
//       free(raiz);
//       return temp;
//     }
//     // Caso 2: Nó com dois filhos, encontra o sucessor in-order (menor valor
//     na
//     // subárvore direita)
//     NoArvore *temp = encontrarMinimo(raiz->dir);
//     raiz->dado = temp->dado;
//     raiz->dir = excluirElemento(raiz->dir, temp->dado);
//   }
//   return raiz;
// }

// void posOrdem(NoArvore *raiz) {
//   // ESQ,DIR,RAIZ
//   if (raiz != NULL) {
//     posOrdem(raiz->esq);
//     posOrdem(raiz->dir);
//     printf(" %d |", raiz->dado);
//   }
//   return;
// }

// void preOrdem(NoArvore *raiz) {
//   // RAIZ,ESQ,DIR
//   if (raiz != NULL) {
//     printf(" %d |", raiz->dado);
//     posOrdem(raiz->esq);
//     posOrdem(raiz->dir);
//   }
//   return;
// }

// void inOrdem(NoArvore *raiz) {
//   // ESQ,RAIZ,DIR
//   if (raiz != NULL) {
//     posOrdem(raiz->esq);
//     printf(" %d |", raiz->dado);
//     posOrdem(raiz->dir);
//   }
//   return;
// }

// // Função auxiliar para imprimir um caractere precedido por uma quantidade
// // específica de espaços
// void imprimeNo(int dado, int valor) {
//   int i;
//   for (i = 0; i < valor; i++)
//     printf("   ");
//   printf("%i\n", dado);
// }

// // Função para exibir a árvore no formato esquerda-raiz-direita segundo
// // Sedgewick
// void mostraArvore(NoArvore *raiz, int valor) {
//   if (raiz == NULL) {
//     return;
//   }
//   mostraArvore(raiz->dir, valor + 1);
//   imprimeNo(raiz->dado, valor); // Convertendo para caractere para imprimir
//   mostraArvore(raiz->esq, valor + 1);
// }

// int main(void) {
//   int op = -1, valor;
//   struct NoArvore *raiz = NULL;
//   while (op != 0) {
//     printf("\n\n------- Menu ---------------\n\n");
//     printf("- 1 --- Adiciona Elemento(no)\n");
//     printf("- 2 --- Excluir Elemento(no)\n");
//     printf("- 3 --- Imprimir Arvore\n");
//     printf("- 4 --- Imprimir Pos-Ordem\n");
//     printf("- 5 --- Imprimir In-Ordem\n");
//     printf("- 6 --- Imprimir Pre-Ordem\n");
//     printf("- 7 --- \n");
//     printf("- 0 --- Sair\n\n");
//     printf("- Opção --> ");
//     scanf("%d", &op);

//     switch (op) {
//     case 1:
//       printf("\n\n--- Adiciona Elemento(no)\n");
//       // printf("\nDigite o valor do no ->");
//       // scanf("%d", &valor);
//       // adicionaElemento(raiz, valor);
//       // Inserindo elementos na árvore
//       raiz = adicionaElemento(raiz, 1);
//       raiz = adicionaElemento(raiz, 2);
//       raiz = adicionaElemento(raiz, 3);
//       raiz = adicionaElemento(raiz, 4);
//       raiz = adicionaElemento(raiz, 5);
//       raiz = adicionaElemento(raiz, 6);
//       raiz = adicionaElemento(raiz, 7);
//       raiz = adicionaElemento(raiz, 8);
//       raiz = adicionaElemento(raiz, 9);
//       raiz = adicionaElemento(raiz, 10);

//       mostraArvore(raiz, 3);
//       break;

//     case 2:
//       printf("\n\n--- Excluir Elemento(no)\n");
//       printf("\nDigite o valor do no ->");
//       scanf("%d", &valor);
//       excluirElemento(raiz, valor);
//       break;

//     case 3:
//       printf("\n\n--- Imprimir Arvore\n");
//       printf("\nDigite o valor do no ->");
//       scanf("%d", &valor);
//       mostraArvore(raiz, valor);
//       break;

//     case 4:
//       printf("\n\n--- Imprimir Pos-Ordem\n\n");
//       posOrdem(raiz);
//       break;

//     case 5:
//       printf("\n\n--- Imprimir In-Ordem\n\n");
//       inOrdem(raiz);
//       break;

//     case 6:
//       printf("\n\n--- Imprimir Pre-Ordem\n\n");
//       preOrdem(raiz);
//       break;

//     case 7:
//       printf("\n\n--- \n\n");

//       break;

//     case 0:
//       op = 0;
//       printf("\nSistema finalizado com sucesso!\n");
//       break;

//     default:
//       printf("Digite uma opcao valida\n");
//     }
//   }
//   return 0;
// }