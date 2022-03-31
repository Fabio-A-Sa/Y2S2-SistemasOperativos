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
 * Informa o que está na memória e muda para true
 */
bool test_and_set (bool *target) {

    bool returnValue = *target;
    *target = true;
    return returnValue;
}

do {
    while (test_and_set(&lock)); // critial section
    lock = false; // tempo restante
} while (true);
```