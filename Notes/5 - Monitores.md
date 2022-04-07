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

- `signal()` para enviar um sinal a possíveis threads que estejam em wait(), de forma a continuar com a exclusão múltipla.