#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <semaphore.h>
#include <math.h>
#define N 7
#define Speed 5
struct Poziz{
int x,y, name;
};
int ostan[4][2]={{8,5},{8,70},{14,5},{14,70}};

sem_t Stati[9],Smen[N];
int iterator[4];
struct Poziz taxi[4];
struct Poziz *men;
void add(int n){
    sem_post(&Stati[n]);
    men[n].name =97 + rand()%25;
    iterator[n]++;
    printf("\033[%d;%dH%c",ostan[n][0],ostan[n][1]+iterator[n],men[n].name);
    sem_wait(&Stati[n]);
}
void deletee(int n){
    sem_post(&Stati[n]);
    men[n].name = ' ';
    iterator[n]--;
    printf("\033[%d;%dH%c",ostan[n][0],ostan[n][1]+iterator[n],men[n].name);
    sem_wait(&Stati[n]);
}
void ostanovki(){

    printf("\033[%d;%dH*****",8,5);
    printf("\033[%d;%dH*****",14,5);
    printf("\033[%d;%dH*****",8,70);
    printf("\033[%d;%dH*****",14,70);
}
void Creat(){
int i ;
    for(i=0;i<70;i+=2){
         printf("\033[%d;%dH--",9,5+i);
         printf("\033[%d;%dH- ",11,5+i);
         printf("\033[%d;%dH--",13,5+i);
    }
    ostanovki();
}
void *Taxi(int in){
int k = (int)in;
int  i , x,o;
x = rand()%100;
i = rand()%70;
if (x<50) {x =0; o=1;}
else {x =2; o=3;}
   for(;;){
   if (x==0){
   for (;i<70;i++)
    {
        printf("\033[%d;%dHТ",10+x,5+i);
        usleep(100000);
        printf("\033[%d;%dH ",10+x,5+i);
    }
    i = 70; x = 2;
    usleep(3000000);
    deletee(o);
    }
    else{
       for (;i>0;i--)
    {
        printf("\033[%d;%dHТ",10+x,5+i);
        usleep(100000);
        printf("\033[%d;%dH ",10+x,5+i);
    }
    i = 0; x =0;
    usleep(3000000);
    deletee(o);
    }
}
}

void *Men(int in){
    int k = (int)in;
    for(;;){
    int u = rand()%100;
    if(u<5){
        add(k);
    }
    sem_post(&Smen[k]);
    usleep(1000000);
    }
    //rand()%
}

void Writer(){
    int i;
    for(;;){
        for (i=0;i<5;i++){
          //  printf("\033[%d;%dH&", taxi[i].x);
        }
    }
}
int main(){
int i;
    pthread_t cd[101];
    setbuf(stdout,NULL);
    Creat();
    men = (struct Poziz*)malloc(N * sizeof(struct Poziz));
      for(i=0;i<N;i++)
        {
            pthread_create( &cd[i], NULL, Men, (void*)i);
            sem_init(&Smen[i],0,3);
        }
     //    pthread_create( &cd[N+6], NULL, Writer, (void*)i);
      for(i=0;i<5;i++)
        {
         pthread_create( &cd[N+i], NULL, Taxi, (void*)i);
        }
            getchar();
}
