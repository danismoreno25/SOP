/**************************************************************
    Pontificia Universidad Javeriana
  Autor: J. Corredor
  Fecha: Febrero 2024
  Materia: Sistemas Operativos
  Tema: Taller de Evaluación de Rendimiento
  Fichero: fuente de multiplicación de matrices NxN por hilos.
  Objetivo: Evaluar el tiempo de ejecución del 
          algoritmo clásico de multiplicación de matrices.
      Se implementa con la Biblioteca POSIX Pthreads
****************************************************************/

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include "mm_clasico.h"

#define DATA_SIZE (1024*1024*64*3) 

pthread_mutex_t MM_mutex;  // Declara un mutex para la sincronización de hilos
static double MEM_CHUNK[DATA_SIZE];  // Declara un array estático de doubles
double *mA, *mB, *mC;  // Declara punteros a double para las matrices A, B y C

struct parametros{  // Define una estructura para los parámetros de los hilos
  int nH;
  int idH;
  int N;
};

struct timeval start, stop;  // Declara dos estructuras para medir el tiempo

void llenar_matriz(int SZ){ 
  srand48(time(NULL));  // Inicializa la semilla del generador de números aleatorios  for(int i = 0; i < SZ*SZ; i++){
     mA[i] = 1.1*i;  // Llena la matriz A con valores determinados
    mB[i] = 2.2*i;  // Llena la matriz B con valores determinados
    mC[i] = 0;  // Inicializa la matriz C a cero
  }
}

void print_matrix(int sz, double *matriz){  // Función para imprimir una matriz
  if(sz < 12){  
    for(int i = 0; i < sz*sz; i++){  
      if(i%sz==0) printf("\n");  // Imprime una nueva línea al inicio de cada fila
      printf(" %.3f ", matriz[i]);  // Imprime el elemento de la matriz
    }
    printf("\n>-------------------->\n");  
  }
}

void inicial_tiempo(){  // Función para iniciar la medición del tiempo
  gettimeofday(&start, NULL);  // Obtiene el tiempo actual y lo guarda en "start"
}

void final_tiempo(){  // Función para finalizar la medición del tiempo
  gettimeofday(&stop, NULL);  // Obtiene el tiempo actual y lo guarda en "stop"
  stop.tv_sec -= start.tv_sec;  // Calcula la diferencia de tiempo
  printf("\n:-> %9.0f µs\n", (double) (stop.tv_sec*1000000 + stop.tv_usec));  // Imprime el tiempo transcurrido en microsegundos
}

void *mult_thread(void *variables){  // Función que ejecutan los hilos
  struct parametros *data = (struct parametros *)variables;  // Convierte el argumento a la estructura de parámetros

  int idH = data->idH;  // Obtiene el ID del hilo
  int nH  = data->nH;  // Obtiene el número total de hilos
  int N   = data->N;  // Obtiene el tamaño de las matrices
  int ini = (N/nH)*idH; 
  int fin = (N/nH)*(idH+1);  

  for (int i = ini; i < fin; i++){  
    for (int j = 0; j < N; j++){  
      double *pA, *pB, sumaTemp = 0.0;  // Declara dos punteros y una variable para la suma
      pA = mA + (i*N);  
      pB = mB + j;  
      for (int k = 0; k < N; k++, pA++, pB+=N){  
        sumaTemp += (*pA * *pB);  // Multiplica los elementos y suma al acumulador
      }
      mC[i*N+j] = sumaTemp;  
    }
  }

  pthread_mutex_lock (&MM_mutex);  // Bloquea el mutex
  pthread_mutex_unlock (&MM_mutex);  // Desbloquea el mutex
  pthread_exit(NULL);  // Termina el hilo
}




















