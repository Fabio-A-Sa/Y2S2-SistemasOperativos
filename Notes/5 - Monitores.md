# 5 - Monitores

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