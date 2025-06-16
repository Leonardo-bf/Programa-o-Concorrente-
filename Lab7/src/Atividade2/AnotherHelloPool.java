package Atividade2;/* Disciplina: Programacao Concorrente */
/* Prof.: Silvana Rossetto */
/* Laboratório: 11 */
/* Codigo: Exemplo de uso de um pool de threads oferecido por Java */
/* -------------------------------------------------------------------*/

import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.atomic.AtomicInteger;

// classe runnable
class Worker implements Runnable {
  private final AtomicInteger contador;

  // construtor
  Worker(AtomicInteger contador) {
    this.contador = contador;
  }

  // método executado pela thread
  public void run() {
    // simula um trabalho e incrementa o contador compartilhado
    contador.incrementAndGet(); // incrementa com segurança
  }
}

// classe principal
public class AnotherHelloPool {
  private static final int NTHREADS = 10;
  private static final int WORKERS = 50;

  public static void main(String[] args) {
    ExecutorService executor = Executors.newFixedThreadPool(NTHREADS);

    // variável compartilhada entre threads
    AtomicInteger contador = new AtomicInteger(0);

    // dispara a execução dos workers
    for (int i = 0; i < WORKERS; i++) {
      executor.execute(new Worker(contador));
    }

    // encerra o pool e aguarda término das tarefas
    executor.shutdown();
    while (!executor.isTerminated()) {}

    // exibe o valor final da variável compartilhada
    System.out.println("Valor final do contador: " + contador.get());
    System.out.println("Terminou");
  }
}
