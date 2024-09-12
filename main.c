#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define _POSIX_C_SOURCE 200809L

int cont = 0;
int tamanoPagina = 4096;

void printEntradaTlb(int *tlb, int posicion, int isHit, int isReplaced) {
    int * inicio = tlb;
    int * final = tlb+25;
    
    
    printf("TLB desde: %p hasta %p\n", inicio, final);
    if (isHit > 0)
    {
        printf("TLB Hit\n");
    } else{
        printf("TLB Miss\n");
    }
    printf("Pagina: %d\n", *(tlb+(posicion*5) + 1));
    printf("Desplazamiento: %d\n", *(tlb+(posicion*5) + 2));

    char *string_ptr = (char*)tlb + posicion * 5 + (3*sizeof(int));
    printf("Desplazamiento en Binario: %s\n", string_ptr);
    // printf("Pagina en Binario: %s\n", (char*) *(tlb+(posicion*5) + 3));
    // printf("Desplazamiento en Binario: %d\n", *(tlb+(posicion*5) + 4));
    if (isReplaced > 0)
    {
        int *reemplazo = tlb+(posicion*5);
        printf("Politica de reemplazo %p\n", &reemplazo);
    }
    else{
        printf("Politica de reemplazo 0x0\n");
    }
    
    return;
}
void guardarEntradaTlb(int* tlb, int posicion, int direccion){
    int a = floor(direccion / tamanoPagina);
    int b = direccion % tamanoPagina;
    // char* c = decimalABinario(a);
    // char* d = decimalABinario(b);
    
    char binario[21];
    decimalABinario(b, binario);
    
    *(tlb+(posicion*5)) = direccion; //Direccion
    *(tlb+(posicion*5) + 1) = a; // Pagina
    *(tlb+(posicion*5) + 2) = b; // Desplazamiento

    char *string_ptr = (char*)tlb + posicion * 5 + (3*sizeof(int));

    snprintf(string_ptr, 21, binario);
    // *(tlb+(posicion*5) + 3) = (char*) binario; // Pagina en binario
    // *(tlb+(posicion*5) + 24) = d; // Desplazamiento en binario
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
    for (int i = 0; i<5; i++) {
            if (direccion == *(tlb+(5*i))) {
                // si la encuentra, la imprime
                printEntradaTlb(tlb, i, 1, 0);
                return;
            }
         }
    // si la cola esta llena 
    if (cont == 5) {
        // Mover todos los elementos para sobre escribir el primero
        for (int i = 0; i <= 20; i++) {
            *(tlb+i) = *(tlb+i+5); 
        }
        // guardar la direccion al final de la cola
        guardarEntradaTlb(tlb, 4, direccion);
        printEntradaTlb(tlb, 4, 0, 1);
    }

    else if (cont<5) {
        // si la cola no esta llena, añade al final
        guardarEntradaTlb(tlb, cont, direccion);
        printEntradaTlb(tlb, cont, 0, 0);
        cont++;
        return;
    }
}


int main () {
    char input[1000];
    printf("Ingrese su direccion virtual: ");
    scanf("%s", &input);
    
    int *tlb =  malloc(285); 
    

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