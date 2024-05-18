#include <unistd.h>          
#include <stdlib.h>          
#include <time.h>            
#include <sys/time.h>        
#include "mm_clasico.c"      

int main(int argc, char *argv[]){  
  if (argc < 2){                    // Verifica si se ingresaron suficientes argumentos.
    printf("Ingreso de argumentos \n $./ejecutable tamMatriz numHilos\n"); 
    return -1;                     
  }
    int SZ = atoi(argv[1]);         // Convierte el primer argumento en el tamaño de la matriz.
    int n_threads = atoi(argv[2]);   // Convierte el segundo argumento en el número de hilos.

    pthread_t p[n_threads];          // Declara un arreglo de identificadores de hilo.
    pthread_attr_t atrMM;            // Declara una estructura de atributos de hilo.

  mA = MEM_CHUNK;                    // Asigna una dirección de memoria a la matriz mA.
  mB = mA + SZ*SZ;                   // Calcula la dirección de memoria de la matriz mB.
  mC = mB + SZ*SZ;                   // Calcula la dirección de memoria de la matriz mC.

  llenar_matriz(SZ);                 // Llama a la función para llenar las matrices con valores aleatorios.
  print_matrix(SZ, mA);              // Imprime la matriz mA.
  print_matrix(SZ, mB);              // Imprime la matriz mB.

  inicial_tiempo();                  // Inicia el temporizador para medir el tiempo de ejecución.
  pthread_mutex_init(&MM_mutex, NULL); // Inicializa el mutex para la exclusión mutua.
  pthread_attr_init(&atrMM);         // Inicializa los atributos de hilo.
  pthread_attr_setdetachstate(&atrMM, PTHREAD_CREATE_JOINABLE); // Establece los atributos para permitir que los hilos sean "joinable".

    for (int j=0; j<n_threads; j++){ 
    struct parametros *datos = (struct parametros *) malloc(sizeof(struct parametros)); // Reserva memoria para la estructura de datos de los hilos.
    datos->idH = j;                  // Asigna el ID del hilo.
    datos->nH  = n_threads;          // Asigna el número total de hilos.
    datos->N   = SZ;                  // Asigna el tamaño de la matriz.
        pthread_create(&p[j],&atrMM,mult_thread,(void *)datos); // Crea un nuevo hilo con los datos proporcionados.
  }

    for (int j=0; j<n_threads; j++)  
        pthread_join(p[j],NULL);      // Espera a que un hilo específico termine su ejecución.

  final_tiempo();                    // Detiene el temporizador y muestra el tiempo de ejecución.
  
  print_matrix(SZ, mC);              // Imprime la matriz resultante de la multiplicación.

  pthread_attr_destroy(&atrMM);      // Destruye los atributos del hilo.
  pthread_mutex_destroy(&MM_mutex);  // Destruye el mutex.
  pthread_exit (NULL);                // Sale del hilo principal.
}