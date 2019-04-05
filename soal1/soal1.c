#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<tgmath.h>

// adalah fungsi untuk menghitung faktorial
void* faktorial(char *p) {
	int i, fact=1;
 		for (i = 2; i <= atoi(p); i++){
     			fact=fact*i;}
 				printf("Factorial of %s is %ld\n", p,fact);
 				return NULL;
 }
 
 // adalah fungsi untuk melakukan quick sort pada inputan yang dimasukkan
 int compare (const void *arg1, const void *arg2)
{
   return(strcmp(*(char **)arg1, *(char **)arg2));
}

int main (int argc, char * argv[]) {
	int i;
	argc--;
	argv++;
	// proses sorting inputan argv[]
	qsort((char *)argv, argc, sizeof(int), compare);
	for (i=0;i<argc;i++) {
		if (argv[i] != NULL) {
			//pembuatan thread sebanyak inputan i(argc)
		pthread_t tid[i];
		pthread_create(&(tid[i]),NULL,faktorial,(char *) argv[i]);
		pthread_join(tid[i],NULL);
	}
	}
	return 0;
}
