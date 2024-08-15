## Exercício 1: Soma de Elementos
Dado o seguinte algoritmo, determine a complexidade em termos de Big O:
```c
int soma(int vetor[], int n) { // 1
    int soma = 0; // 1
    for (int i = 0; i < n; i++) { // n+1
        soma += vetor[i]; // n
    } //--
    return soma; // 1
} //--
```
Qual é a complexidade desse algoritmo? Aceitavel
O(n)
## Exercício 2: Multiplicação de Matrizes
Considere o algoritmo abaixo para multiplicar duas matrizes:
```c
void multiplica_matrizes(int A[][n], int B[][n], int C[][n], int n) { // 1
    for (int i = 0; i < n; i++) { // n+1
        for (int j = 0; j < n; j++) { // (n+1)²
            C[i][j] = 0; // n²
            for (int k = 0; k < n; k++) {  // (n+1)³
                C[i][j] += A[i][k] * B[k][j];  // n³
            } //--
        }  //--
    }  //--
}  //--
```
Qual é a complexidade desse algoritmo em termos de n?
O(n³)
## Exercício 3: Busca Binária
Analise a complexidade do seguinte algoritmo de busca binária:
```c
int busca_binaria(int vetor[], int n, int x) { // 1
    int inicio = 0, fim = n - 1; // 1
    while (inicio <= fim) { // n
        int meio = inicio + (fim - inicio) / 2; // log n      
        if (vetor[meio] == x) // n
            return meio; // n
        if (vetor[meio] < x) // n
            inicio = meio + 1; // n
        else // n
            fim = meio - 1; // n
    } // --
    return -1; // 1
} // --

```
Qual é a complexidade do algoritmo de busca binária?
O(log(n))
## Exercício 4: Verificação de Número Primo
Dado o algoritmo abaixo que verifica se um número é primo, determine a complexidade:
```c
int eh_primo(int n) {  // 1
    if (n <= 1) // 1
        return 0; // 1
    for (int i = 2; i * i <= n; i++) { // sqrt(n)+1
        if (n % i == 0) // sqrt(n)
            return 0; // sqrt(n)
    } // --
    return 1; // 1
} // --
```
Qual é a complexidade do algoritmo para verificar se um número é primo?
O(sqrt(n)) 
## Exercício 5: Ordenação por Inserção
Analise a complexidade do algoritmo de ordenação por inserção abaixo:
```c
void insertion_sort(int vetor[], int n) { //1
    for (int i = 1; i < n; i++) { //n+1
        int chave = vetor[i]; //n
        int j = i - 1; //n
        while (j >= 0 && vetor[j] > chave) { //(n+1)²
            vetor[j + 1] = vetor[j]; //n²
            j--; //n²
        } //--
        vetor[j + 1] = chave; //n
    } //--
} //--
```
Qual é a complexidade do pior caso para o algoritmo de ordenação por inserção?
O(n²)
## Exercício 6: Fibonacci Recursivo
Considere o seguinte algoritmo recursivo para calcular o n-ésimo número de Fibonacci:
```c
int fibonacci(int n) { //1
    if (n <= 1) //1
        return n; //1
    return fibonacci(n-1) + fibonacci(n-2); //n*n=n²
} //--
```
Qual é a complexidade do algoritmo recursivo para calcular o n-ésimo número de Fibonacci?
O(n²)
 
## Exercício 7: Soma Recursiva dos Números de 1 a N
Analise a complexidade do algoritmo recursivo abaixo:
```c
int soma_recursiva(int n) { //1
    if (n == 1) //1
        return 1; //1
    return n + soma_recursiva(n - 1); //n
} //--
```
Qual é a complexidade do algoritmo para somar recursivamente os números de 1 a N?
O(n)
## Exercício 8: Quick Sort
Dado o seguinte algoritmo de Quick Sort, determine sua complexidade no melhor, pior e caso médio:
```c
void quick_sort(int vetor[], int baixo, int alto) { //1
    if (baixo < alto) { //1
        int pi = particiona(vetor, baixo, alto); //n
        quick_sort(vetor, baixo, pi - 1); //log n
        quick_sort(vetor, pi + 1, alto);  //log n
    } //--
} //--
```
Qual é a complexidade do Quick Sort nos três casos (melhor, pior e caso médio)?
Pior caso -> O(n²) | 

Melhor e Médio caso -> O(n log(n))
# Exercício 9: Contagem de Dígitos
Analise a complexidade do seguinte algoritmo que conta o número de dígitos de um número inteiro:
```c
int conta_digitos(int n) { //1
    int contagem = 0; //1
    while (n != 0) {  //n
        n = n / 10;   //log n
        contagem++;   //n
    } //--
    return contagem; //1
} //--
```
Qual é a complexidade desse algoritmo para contar o número de dígitos?
O(log n /10)
## Exercício 10: Merge Sort
Considere o seguinte algoritmo de Merge Sort:
```c
void merge_sort(int vetor[], int l, int r) { //1
    if (l < r) {                             //n
        int m = l + (r - l) / 2;             //log n
        merge_sort(vetor, l, m);             //n
        merge_sort(vetor, m + 1, r);         //n
        merge(vetor, l, m, r);               //n
    }                                        //--
}                                            //--
```
Qual é a complexidade do algoritmo de Merge Sort?
O(n log n)

Esses exercícios cobrem uma variedade de algoritmos e ajudam a entender a aplicação da notação Big O em diferentes cenários.
