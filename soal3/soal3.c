#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>


pthread_t tid[3]; //inisialisasi array untuk menampung thread dalam kasus ini ada 2 thread

//fungsi untuk fitur cetak semua status terkini
void allstatus (int a, int i) {
	printf("Agmal WakeUp_Status = %d \nIraj Spirit_Status = %d\n", a, i);
	return NULL;
}
//fungsi ayo bangun untuk menambah value dari wakeup_status
int ayobangun(int a) {
	a+=15;
	return a;
}
//fungsi ayo tidur untuk mengurangi value dari spirit_status
int ayotidur(int i) {
	i-=20;
	return i;
}
//untuk mevalidasi counter dari setiap kali fungsi ayobangun dipanggil
void* valid1(int *ct1)
{
	while(1)
    {
        if(*ct1 ==3)
        {
            printf("Iraj ayo tidur tidak dapat digunakan dalam 10 detik\n"); //error message
            sleep(10); 
            *ct1 = 0; //mengembalikan counter dari fungsi ayobangun ke 0
        }
    }
	return NULL;
}
//untuk mevalidasi counter dari setiap kali fungsi ayotidur dipanggil
void* valid2(int *ct2)
{
	while(1)
    {
        if(*ct2 ==3)
        {
            printf("Agmal ayo bangun tidak dapat digunakan dalam 10 detik\n");
            sleep(10);
            *ct2 = 0; //mengembalikan counter dari fungsi ayotidur ke 0
        }
    }
	return NULL;
}

int main(void) {
	//inisialisasi status awal dan counter
	int count1=0;
	int count2=0;	
	int wu_sA = 0;
	int s_sI = 100;
	
	int* ct1 = &count1;
	int* ct2 = &count2;
		//create thread
		pthread_create(&(tid[0]),NULL,&valid1,(int*)ct1);	
		pthread_create(&(tid[1]),NULL,&valid2,(int*)ct2);
		
	while(1) {
		int opsi;
		printf("------ Agmal & Iraj Simulator -------\n");
		printf("Pilih Menu: \n");
		printf("1. Show All Status\n");
		printf("2. Agmal Ayo Bangun\n");
		printf("3. Iraj Ayo Tidur\n");
		scanf("%d", &opsi); //menerima inputan
		//printf("%d\n",  count1);
		//printf("%d\n",  count2);
		
		if (opsi==1) { //jika 1, maka jalankan fungsi allstatus
			allstatus(wu_sA, s_sI);
		}
		else if (opsi==2 && count2 != 3) { //jika 2 dan counter dari ayotidur!=3 maka jalankan ayobangun dan increment counter dari ayobangun
			wu_sA = ayobangun(wu_sA);
			count1++; 
		}
		else if (opsi==3 && count1 != 3) { //jika 2 dan counter dari ayotidur!=3 maka jalankan ayobangun dan increment counter dari ayobangun
			s_sI = ayotidur(s_sI);
			count2++;
		}
	
	if (wu_sA > 99) { //mencetak status final
		printf("Agmal Terbangun,mereka bangun pagi dan berolahraga\n");
		break;
	}
	else if (s_sI < 1) { //mencetak status final
		printf("Iraj ikut tidur, dan bangun kesiangan bersama Agmal\n");
		break;
	}  
	}
	return 0;	
}
