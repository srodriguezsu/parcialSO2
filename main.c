#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define _POSIX_C_SOURCE 200809L

int cont = 0;
const int tamanoPagina = 4096;
const int tamanoEntrada = 24;
const int cantidadEntradas = 5;

void printEntradaTlb(int *tlb, int posicion, int isHit, int isReplaced) {

    int *posicionPtr = tlb+(posicion*tamanoEntrada);

    int * inicio = tlb;
    int * final = tlb+(tamanoEntrada*cantidadEntradas);
    
    
    printf("TLB desde: %p hasta %p\n", inicio, final);
    if (isHit > 0)
    {
        printf("TLB Hit\n");
    } else{
        printf("TLB Miss\n");
    }
    printf("Pagina: %d\n", *(posicionPtr + 1));
    printf("Desplazamiento: %d\n", *(posicionPtr + 2));

    char *pagBiPtr = (char*)posicionPtr + (3*sizeof(int));
    char *desBiPtr = (char*)posicionPtr + (3*sizeof(int)) + 21;
    printf("Pagina en Binario: %s\n", pagBiPtr);
    printf("Desplazamiento en Binario: %s\n", desBiPtr);
    if (isReplaced > 0)
    {
        int *reemplazo = tlb+(posicion*tamanoEntrada);
        printf("Politica de reemplazo %p\n", &reemplazo);
    }
    else{
        printf("Politica de reemplazo 0x0\n");
    }
    
    return;
}
void guardarEntradaTlb(int* tlb, int posicion, int direccion){

    int *posicionPtr = tlb+(posicion*tamanoEntrada);


    int pagina = floor(direccion / tamanoPagina);
    int desplazamiento = direccion % tamanoPagina;
    char paginaBinario[20];
    char desplazamientoBinario[20];

    decimalABinario(pagina, paginaBinario);
    decimalABinario(desplazamiento, desplazamientoBinario);

    *(posicionPtr) = direccion; 
    *(posicionPtr + 1) = pagina; 
    *(posicionPtr + 2) = desplazamiento; 

    char *pagBiPtr = (char*)posicionPtr + (3*sizeof(int));
    char *desBiPtr = (char*)posicionPtr + (3*sizeof(int)) + 21;

    snprintf(pagBiPtr, 21, paginaBinario);
    snprintf(desBiPtr, 21, desplazamientoBinario);
    return;
}

void decimalABinario(int n, char* binaryString) {
    for (int i = 19; i >= 0; i--) {
        int bit = (n >> i) & 1;
        binaryString[19 - i] = bit ? '1' : '0'; // Store '1' or '0'
    }
    binaryString[20] = '\0'; // Null-terminate the string
}

int binarioAlDecimal(int numero){
    char str[12];
    
}


void anadirTLB(int *tlb, int direccion) {
    // Buscar direccion en el tlb
    for (int i = 0; i<cantidadEntradas; i++) {
            if (direccion == *(tlb+(tamanoEntrada*i))) {
                // si la encuentra, la imprime
                printEntradaTlb(tlb, i, 1, 0); // tlb, posicion a imprimir, isHit, !isReplaced
                return;
            }
         }
    // si la cola esta llena 
    if (cont == cantidadEntradas) {
        // Mover todos los elementos para sobre escribir el primero
        for (int i = 0; i <= 20; i++) {
            *(tlb+i) = *(tlb+i+tamanoEntrada); 
        }
        // guardar la direccion al final de la cola
        guardarEntradaTlb(tlb, 4, direccion); 
        printEntradaTlb(tlb, 4, 0, 1);  // tlb, posicion a imprimir, !isHit, isReplaced
    }

    else if (cont<cantidadEntradas) {
        // si la cola no esta llena, añade al final
        guardarEntradaTlb(tlb, cont, direccion);
        printEntradaTlb(tlb, cont, 0, 0);  // tlb, posicion a imprimir, !isHit, !isReplaced
        cont++;
        return;
    }
}


int main () {
    char input[1000];
    printf("Ingrese su direccion virtual: ");
    scanf("%s", &input);
    
    int *tlb =  malloc(tamanoEntrada * cantidadEntradas); 
    

    while (strcmp(input, "s") != 0) {

        struct timespec tiempoInicial, tiempoFinal, diferencia;
        long seconds, nanoseconds;
        double elapsed;
        clock_gettime(CLOCK_REALTIME, &tiempoInicial);

        int direccion = atoi(input);
        
        anadirTLB(tlb, direccion);
        
        clock_gettime(CLOCK_REALTIME, &tiempoFinal);


        seconds = tiempoFinal.tv_sec - tiempoInicial.tv_sec;
        nanoseconds = tiempoFinal.tv_nsec - tiempoInicial.tv_nsec;

        if (nanoseconds < 0) {
            seconds -= 1;
            nanoseconds += 1000000000;
        }

        // Calculate the total elapsed time in seconds as a double
        elapsed = seconds + nanoseconds*1e-9;

        // Print the elapsed time
        printf("Tiempo: %.9f segundos\n", elapsed);

        
        printf("\nIngrese su direccion virtual: ");
        scanf("%s", &input);      
        
    }
    free(tlb);
    printf("\nGood bye!\n");
}