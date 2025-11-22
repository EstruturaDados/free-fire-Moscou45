#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// DEFINE AS GLOBAIS 

#define MAX_INTENS 10

  
typedef struct {

    char adcionar [30];
    char remover;
    int  listar;

}Componente;

// ================================

// Pausa

// ================================

void pausar() {

    printf("\nPressione ENTER para continuar...");

    getchar(); getchar();

}


