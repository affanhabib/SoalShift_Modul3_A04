#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#define PORT 8080
  
int main(int argc, char const *argv[]) {
    struct sockaddr_in address;
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    //atribut string yang dibutuhkan
    char *tambah = "tambah"; 
    char *beli = "beli";
    char *ipjual = "127.0.0.1";
    char *ipbeli = "127.0.0.2";
    char buffer[1024] = {0};
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }
    //definisi dan implementasi dari shared memory
    key_t key = 1234;
        int *stok;

        int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
        value = shmat(shmid, NULL, 0);
        shmdt(stok);
        shmctl(shmid, IPC_RMID, NULL);
  	//
    memset(&serv_addr, '0', sizeof(serv_addr));
  
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
      
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }
    //jika client terhubung dengan server penjual
	if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)>0) {
    	char *n;
		while (1) {
			gets(n); //mendapatkan inputan dari client
		if (strcmp(n,tambah)) { //validasi perintah
    		*stok++; //increment stok
    		valread = read( sock , buffer, 1024); //menyimak outputan dari server
    		printf("%s", buffer); //print outputan
		}
    }
    //jika client terhubung dengan server pembeli
    if(inet_pton(AF_INET, "127.0.0.2", &serv_addr.sin_addr)>0) {
    	char *n;
		while (*stok > 0) { //mengecek ketersediaan stok
			gets(n); //mengambil inputan
		if (strcmp(n,beli)) { //validasi perintah
    		*stok--; //decrement stok
		}
		valread = read( sock , buffer, 1024); //menyimak outputan dari server
		printf("%s", buffer); //print outputan
    }
    return 0;
}
