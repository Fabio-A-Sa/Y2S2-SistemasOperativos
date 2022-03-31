# 4 - Sincronização de Processos

Os processos podem ser interrompidos a qualquer momento (execução concorrente), tornando a sequ~encia de processos ativos não deterministica. Exemplo: incremento e decremento de contadores (*race condition*).

### Critical Section

Por exemplo, com incremento e decremento de contadores (secção crítica). Solução: <br>

- `Mutual Exclusion`: se um processo está a executar a secção crítica, então mais nenhum está a executar ao mesmo tempo;

- `Progress`: um processo que terá de aceder à secção crítica de outro processo, tem prioridade em relação ao outros;

- `Bounded Waiting`: um processo não pode ser permanentemente ultrapassado por outros que usem o tópico anterior;


1. Preemptive – permite entrada na zona crítica quando está em kernel mode;
2. Non-preemptive – executa até sair do kernel model ou até voluntariamente. Geralmente sem neEssentially free of race conditions in kernel mode

## Peterson's Solution

Solução que serve para dois processos concorrentes:

```c++
bool flag[2];
do {
    flag[i] = true;
    turn = j;
    while (flag[j] && turn == j); // critial section, espera ativa
    flag[i] = false;
} while (true);
```

Só entra na zona crítica um dos dois processos, a *mutual exclusion* é assegurada, e o outro processo está em espera ativa.

## Solução usando test_and_set

Solução atómica (só um dos processos é que consegue mudar o target alocado na memória).

```c++
/**
 * Informa o que está na memória e muda para o valor para true
 * Instrução do processador
 */
bool test_and_set (bool *target) {

    bool returnValue = *target;
    *target = true;
    return returnValue;
}

/**
 * Informa o que está na memória e muda para um novo valor
 * Instrução do processador
 */
int compare_and_swap (int *value, int expected, int newValue) {
    int temp = *value;
    if (*value == expected) *value = newValue;
    return temp;
}

do {
    while (test_and_set(&lock)); // critial section com espera ativa
    while (compare_and_swap(&lock, 0, 1)) // critical section com espera ativa
    lock = 0; // tempo restante
} while (true);
```

Outra solução, com *bounded waiting* e *mutual exclusion* e para n processos:

```c++
global bool waiting[n-1];
do {
    
    waiting[i] = true;
    key = true;
    while (waiting[i] && key) 
      key = test_and_set(&lock);

    waiting[i] = false; 
    /* critical section */ 

    j = (i + 1) % n; 
    while ((j != i) && !waiting[j]) 
        j = (j + 1) % n; 
    if (j == i) 
        lock = false; 
    else 
        waiting[j] = false; 
    /* remainder section */ 

} while (true);
```

Cada processo i que sai da exclusão múltipla, vai escolher um outro processo j que está a competir para entrar (waiting[j] == true). Se i == j, significa que já procurou todos os processos e nenhum está à espera de lugar (não há concorrência). Nesse caso, lock = false, pelo que o sistema fica aberto a novas *threads*.

## Mutex locks

A exclusão múltipla só é usada para casos onde a secção crítica é pequena (por exemplo, não realizam operações I/O de ficheiros), ou seja, a espera ativa dos outros processos não representa um grande número de ciclos de relógio gastos.

### Semaphore

Formas mais sofisticadas de colocar processos à espera. Um semáforo que só contenha dois valores (0, 1) torna-se binário (*binary semaphores* != *counting semaphores*) e semelhante aos exemplos anteriores -> continua a existir espera ativa.

#### Implementação sem espera ativa

```c++
list<semaphore> all = {};
wait (semaphore *S) {
    S->value--;
    if (S->value < 0) {
        all.push_back(S);
        block();
    }
}

signal(semaphore *S) {
    S->value++;
    if (S->value <= 0) {
        semaphore P = all.pop(); // considerando ordenação da lista por prioridade
        wakeup(P);
    }
}
```

Sempre que há locks em *threads*, todos devem pegar nos recursos pela mesma ordem (inibe a possibilidade da maior espera ativa).

### Problemas de sincronização

#### 1. Bounded buffer Problem

Tem de existir zonas livres para albergar os processos e garantir que os processos não se sobreponham. Características de produtor-consumidor (push() e pop() concorrentes, read() e write() concorrentes, por exemplo).

#### 2. Readers-Writers Problem

Os escritores podem ler e escrever e os leitores só podem ler.