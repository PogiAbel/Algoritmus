#include <stdio.h>
#include <time.h>

int main(){
    srand(time(NULL));
    int size = 50;
    int szamok[size];
    clock_t start;
    for(int i=0;i<size;i++){
        szamok[i]=random();
        //printf("%d\n",szamok[i]);
        if(voltE(szamok[i],szamok,i)){
            szamok[i]=random();
        }
    }
    clock_t end;
    float secounds = (float)(end - start);
    printf("Eltelt ido:%f s",secounds);


    return 0;
}


int random(){
    int ran=rand();
    return ran;
}

int voltE(int szam,int tomb[],int hely){
    int eredm = 0;
for(int j=0;j<hely;j++){
    if(szam == tomb[j]){
       eredm = 1; 
       break;
    } 
}
return eredm;
}
