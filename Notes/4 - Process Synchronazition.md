# 4 - Sincronização de Processos

### Formação e interrupção de processos via linguagem C:

```c++
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int main () {
    printf("PID = %d\n", getpid());             // system call
    char * args[] = {"Hello", "World", NULL};
    execv("./another", args);                   // system call -> replace the entire process
    printf("This line will never be printed!");    
    return 0;
}
```

Os processos podem ser interrompidos a qualquer momento (execução concorrente), tornando a sequência de processos ativos não deterministica. Exemplo: incremento e decremento de contadores (*race condition*).

### Critical Section

Zona crítica é qualquer pedaço de código que, usando a share-memory, modifica algum ficheiro, ou variável, ou memória. Por exemplo, com incremento e decremento de contadores (secção crítica). Solução: <br>

- `Mutual Exclusion`: se um processo está a executar a secção crítica, então mais nenhum está a executar ao mesmo tempo;

- `Progress`: um processo que terá de aceder à secção crítica de outro processo, tem prioridade em relação ao outros;

- `Bounded Waiting`: Existe um limite do número de vezes que um processo é ultrapassado. Um processo não pode ser permanentemente ultrapassado por outros que usem os tópicos anteriores;

#### O Kernel pode ter duas atitudes: 

1. `Preemptive` – permite entrada na zona crítica quando está em kernel mode;
2. `Non-preemptive` – executa até sair do kernel model ou até voluntariamente. Geralmente sem neEssentially free of race conditions in kernel mode

## Peterson's Solution

Solução que serve para dois processos concorrentes:

```c++
/* i só entra na secção crítica se j não estiver ativo ou turn = i*/
bool flag[2];
int turn;
do {
    flag[i] = true; // o i fica preparado para entrar na secção crítica
    turn = j;
    while (flag[j] && turn == j); // critial section, espera ativa
    flag[i] = false;
} while (true);
```

Só entra na zona crítica um dos dois processos, a *mutual exclusion* é assegurada, e o outro processo está em espera ativa.

### Instruções de harware atómicas

Quando a instrução não tem qualquer interrupção. Ou testa a zona de memória e define o seu valor ou troca o conteúdo das duas zonas de memória (*control word*).

## Solução usando test_and_set

Solução atómica (só um dos processos é que consegue mudar o target alocado na memória).

```c++
/**
 * Informa o que está na memória e muda para o valor para true
 * Instrução do processador -> instrução atómica
 */
bool test_and_set (bool *target) {

    bool returnValue = *target;
    *target = true;
    return returnValue;
}

do {
    while (test_and_set(&lock)); // critial section com espera ativa
    lock = 0; // tempo restante
} while (true);

/**
 * Informa o que está na memória e muda para um novo valor
 * Instrução do processador
 **/
int compare_and_swap (int *value, int expected, int newValue) {
    int temp = *value;
    if (*value == expected) *value = newValue;
    return temp;
}

do {
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

A exclusão múltipla só é usada para casos onde a secção crítica é pequena (por exemplo, não realizam operações I/O de ficheiros), ou seja, a espera ativa dos outros processos não representa um grande número de ciclos de relógio gastos. <br>
Em casos maiores, é necessário usar o `aquire()` para receber receber a secção crítica fechada e `release()` para libertá-la.

```c++
void aquire() {
    while (!available); // espera até que outro processo saia da secção crítica
    available = false;
}

void release() {
    available = true;
}

do {
    aquire();
    /* Secção crítica */
    release();
    /* Outras funções sem usar a secção crítica */
} while (true);
```

### Semaphore 

Formas mais sofisticadas de colocar processos à espera. Um semáforo que só contenha dois valores (0, 1) torna-se binário (*binary semaphores* != *counting semaphores*) e semelhante aos exemplos anteriores -> continua a existir espera ativa. <br>
As operações da implementação `wait()` e `signal` têm de ser atómicas.

#### Implementação com espera ativa

```c++
wait (semaphore *S) {
    while (S <= 0);
    S--;
}

signal (semaphore *S) {
    S++;
}
```

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

Sempre que há locks em *threads*, todos devem pegar nos recursos pela mesma ordem (inibe a possibilidade da maior espera ativa). Noções importantes:

#### DeadLock

Quando dois ou mais processos estão continuamente à espera por um evento que só pode ser causado por um único processo à espera. Por exemplo o wait(Q) e wait(P) em dois processos: cada um está à espera do outro para poder continuar.

#### Starvation / Indefinite blocking

Um processo pode nunca ser removido da fila de semáforos em que está suspenso

#### Priority Invertion

Problema de agendamento em que o processo de prioridade mais baixa mantém o bloqueio necessário para o processo de prioridade mais alta. É resolvido com o protocolo de herança de prioridade.

### Problemas de sincronização

#### 1. Bounded buffer Problem

Tem de existir zonas livres para albergar os processos e garantir que os processos não se sobreponham. Características de produtor-consumidor (push() e pop() concorrentes, read() e write() concorrentes, por exemplo).

#### 2. Readers-Writers Problem

Os escritores podem ler e escrever e os leitores só podem ler. Sempre que existe pelo menos um escritor secção crítica, os leitores esperam que este acabe para entrar. Depois, podem entrar um ou vários leitores para a secção crítica. Quando todos terminarem, só um novo escritor pode ocupar o lugar.

#### 3. Dining-Philosophers Problem

Só permite que cada filósofo (processo) pegue nos dados (os dois pauzinhos) somente se os dois estiverem disponíveis ao mesmo tempo. Os filósofos de número ímpar pegam primeiro no pauzinho esquerdo e só depois o direito, os de número par pegam no pauzinho direito e só depois o esquero. Assim alguns ficam sempre à espera e outros ficam sempre com todos os dados que necessitam. <br>

# Monitores

Controlo de concorrência, ligada a OOP por encapsulamento de atributos privados (o status do monitor). Cada instância só tem um *thread* em cada método. Cada método pode ser sincronizado ou não, com exclusão múltipla.

```c++
monitor Buffer {

    int status[N];

    int take() { // exclusão múltipla em relação ao objecto todo
        // lock()
        // unlock()
        return x;
    }

    void put(int x) {
        // lock()
        // unlock()
    }
}
```

## Variáveis de condição - flags

São declaradas explicitamente ou implicitamento (mutex).

- `wait()` para adormecer e libertar a exclusão múltipla. Pode acontecer num método de um monitor sempre que não tiver dados para poder avançar. Exemplo: falta de variáveis, buffer vazio, buffer cheio... 

- `signal()` para enviar um sinal a possíveis threads que estejam em wait(), guardadas em filas, de forma a continuar com a exclusão múltipla.

```c++
monitor Semaphore {

    int v;
    condition notZero;

    acquire() {
        if (v == 0) // para melhor controlo sobre o código, usar while() e termos sempre que voltar
                    // a testar o predicado
            wait(notZero); // bloqueia e liberta a exclusão múltipla
        v = v - 1;
    }

    release() {
        v = v + 1;
        signal(notZero); // avisa que já não está a zero, o acquire() pode continuar
    }
}
```

`signalAll()`, acorda mais do que um processo no wait(), sempre que as condições o permitam (mais dados disponíveis e quantidade suficiente de threads à espera). Encontram-se nos monitores modernos, como em Java.

### Prioridades nos Monitores clássicos:
- W, os que estão parados no wait();
- S, os que fizeram signal(), pois estão em exclusão múltipla;
- E, os outros processos todos;

### Prioridades nos Monitores modernos:
- S, continua o processo que faz signal();
- E, W, continua os que estão parados no wait() ou novos processos;

#### Implementação do problema clássico de escritores e leitores

```c++
monitorRWLock { // E = W < S

    int readers = 0, writers = 0, wantWrite = 0; 
    condition OKread, OKwrite;

    readLock() { /* Se ainda existirem leitores ou alguém quer ler, então wait() */
        while (writers != 0 || wantWrite > 0) wait(OKread); 
        readers++;
        signal(OKread);
    }

    readUnlock() { /* Liberta um reader, se ficar a zero então podem escrever */
        readers--;
        if (readers == 0) signal(OKwrite); 
    }

    writeLock() { /* Passa de querer escrever para escritor, se não houver mais ninguém */
        wantWrite++;
        while (writers != 0 || readers != 0) wait(OKwrite); 
        wantWrite--; 
        writers++;
    }

    writeUnlock() { /* Acaba a escrita, sinaliza que podem entrar ou vários leitores ou um escritor */
        writers--; 
        signal(OKread); 
        signal(OKwrite);
    } 
}
```