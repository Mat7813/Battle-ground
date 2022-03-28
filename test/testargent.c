#include <stdio.h>
#include <stdlib.h>


int min_puissance(int n[], int nb, int j){
  for(int i=0;nb>i;i++){
    if(nb<10){
      n[i]=nb;
      printf("%d\n", n[i]);
      return 1;
    }
    else if(nb==10){
      n[i]=0;
      printf("%d\n", n[i]);
      n[i+1]=1;
      printf("%d\n", n[i+1]);
      return 1;
    }
    n[i]=nb%10;
    printf("%d\n", n[i]);
    nb/=10;
  }
}

void main(){
  int nb[10], n;
  scanf("%d", &n);
  min_puissance(nb, n, 0);
  printf("12%10=%d\n",12%10);
}
