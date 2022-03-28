
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main(){
  char argent[15][6];
  for(int j=0;j<15;j++){
    for(int f=0;f<6;f++)argent[j][f]=0;
  }
  int nb=95261;
  int nb2=nb;
  int puiss=1;
  int i;
  for(i=0;nb2>10;i++){
    nb=nb2;
  for(puiss=1;nb>10;){
    nb/=10;
    puiss*=10;
  }
  switch(nb){
  case 0:strcpy(argent[i], "0.png");break;
  case 1:strcpy(argent[i], "1.png");break;
  case 2:strcpy(argent[i], "2.png");break;
  case 3:strcpy(argent[i], "3.png");break;
  case 4:strcpy(argent[i], "4.png");break;
  case 5:strcpy(argent[i], "5.png");break;
  case 6:strcpy(argent[i], "6.png");break;
  case 7:strcpy(argent[i], "7.png");break;
  case 8:strcpy(argent[i], "8.png");break;
  case 9:strcpy(argent[i], "9.png");break;
  default:printf("erreur nb =%d\n", nb);break;
  }
  nb*=puiss;
  nb2-=nb;
  }
  switch(nb2){
  case 0:strcpy(argent[i], "0.png");break;
  case 1:strcpy(argent[i], "1.png");break;
  case 2:strcpy(argent[i], "2.png");break;
  case 3:strcpy(argent[i], "3.png");break;
  case 4:strcpy(argent[i], "4.png");break;
  case 5:strcpy(argent[i], "5.png");break;
  case 6:strcpy(argent[i], "6.png");break;
  case 7:strcpy(argent[i], "7.png");break;
  case 8:strcpy(argent[i], "8.png");break;
  case 9:strcpy(argent[i], "9.png");break;
  default:break;
}
//  for(i=0;strcmp(argent[i], "0");i++){
    for(int j=0;j<15;j++){
      printf("%s\n", argent[j]);
    }
  //}
//  printf("%d\n", nb2);
//  printf("%d, %d", nb, puiss);
}
