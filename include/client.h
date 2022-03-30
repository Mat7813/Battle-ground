#ifndef __CLIENT_H_
#define __CLIENT_H_
#include <stdio.h>

void envoyer(int to_server_socket);
void quitter(int to_server_socket);
int main (  int argc, char** argv );
#endif
