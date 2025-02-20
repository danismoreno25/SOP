#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include "mm_transpuesta.c"

int main(int argc, char *argv[]){
	if (argc < 2){
		printf("Ingreso de argumentos \n $./ejecutable tamMatriz numHilos\n");
		return -1;
	}
    int SZ = atoi(argv[1]);
    int n_threads = atoi(argv[2]);

    pthread_t p[n_threads];
    pthread_attr_t atrMM;

	mA = MEM_CHUNK;
	mB = mA + SZ*SZ;
	mC = mB + SZ*SZ;

	llenar_matriz(SZ);
	print_matrix(SZ, mA);
	print_matrix(SZ, mB);

	inicial_tiempo();
	pthread_mutex_init(&MM_mutex, NULL);
	pthread_attr_init(&atrMM);
	pthread_attr_setdetachstate(&atrMM, PTHREAD_CREATE_JOINABLE);

    for (int j=0; j<n_threads; j++){
		struct parametros *datos = (struct parametros *) malloc(sizeof(struct parametros)); 
		datos->idH = j;
		datos->nH  = n_threads;
		datos->N   = SZ;
        pthread_create(&p[j],&atrMM,mult_thread,(void *)datos);
	}

    for (int j=0; j<n_threads; j++)
        pthread_join(p[j],NULL);
	final_tiempo();
	
	print_matrix(SZ, mC);

	pthread_attr_destroy(&atrMM);
	pthread_mutex_destroy(&MM_mutex);
	pthread_exit (NULL);
}
