#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

#define _POSIX_C_SOURCE 200809L

int cont = 0;
const int tamanoPagina = 4096;
const int tamanoEntrada = 24;
const int cantidadEntradas = 5;

void sliceString(char* originalString, char* newString, int start, int end) {
    for (int i = start; i <= end; i++){
        newString[i-start] = originalString[i];
    };
    newString[end-start+1] = '\0';
}

void decimalABinario(int n, int numBits, char* binaryString) {
    for (int i = numBits - 1; i >= 0; i--) {
        int bit = (n >> i) & 1;
        binaryString[numBits - 1 - i] = bit ? '1' : '0';
        
    }
    binaryString[numBits] = '\0';  // Terminar con un NULL
}

int binarioADecimal(const char* binaryString) {
    int leng = strlen(binaryString);
    int suma = 0;
    int potencia = leng-1;

    for (int i = 0; i < leng; i++) {
        
        if (binaryString[i] == '1') {
            suma += pow(2, potencia);
        }
        potencia--;
    }
    
    return suma;
}



void printEntradaTlb(int *tlb, int posicion, int isHit, int isReplaced) {

    int *posicionPtr = tlb+(posicion*tamanoEntrada);

    void *inicio = (void *)tlb;
    void *final = (void *)tlb + (tamanoEntrada * cantidadEntradas) - 1;

    
    
    printf("TLB desde %p hasta %p\n", inicio, final);
    if (isHit > 0)
    {
        printf("TLB Hit\n");
    } else{
        printf("TLB Miss\n");
    }
    printf("Página: %d\n", *(posicionPtr + 1));
    printf("Desplazamiento: %d\n", *(posicionPtr + 2));

    char *pagBiPtr = (char*)posicionPtr + (3*sizeof(int));
    char *desBiPtr = (char*)posicionPtr + (3*sizeof(int)) + 21;
    printf("Página en Binario: %s\n", pagBiPtr);
    printf("Desplazamiento en Binario: %s\n", desBiPtr);
    if (isReplaced > 0)
    {
        int *reemplazo = (void *) (tlb+(posicion*tamanoEntrada));
        printf("Política de reemplazo: %p\n", reemplazo);
    }
    else{
        printf("Política de reemplazo: 0x0\n");
    }
    
    return;
}
void guardarEntradaTlb(int* tlb, int posicion, int direccion){

    int *posicionPtr = tlb+(posicion*tamanoEntrada);

    // convertir direccion a binario
    char direccionBin[33];
    decimalABinario(direccion, 32, direccionBin);

    // variables para binario
    char pagBinario[21]; 
    char desplazamientoBinario[13];

    sliceString(direccionBin, pagBinario, 0, 19);
    sliceString(direccionBin, desplazamientoBinario, 20, 31);
    
    int pagina = binarioADecimal(pagBinario);
    int desplazamiento = binarioADecimal(desplazamientoBinario);
    
    *(posicionPtr) = direccion; 
    *(posicionPtr + 1) = binarioADecimal(pagBinario); 
    *(posicionPtr + 2) = binarioADecimal(desplazamientoBinario);

    char *pagBiPtr = (char*)posicionPtr + (3*sizeof(int));
    char *desBiPtr = (char*)posicionPtr + (3*sizeof(int)) + 21;
    
    snprintf(pagBiPtr, 21, "%s", pagBinario);
    snprintf(desBiPtr, 13, "%s", desplazamientoBinario);
    return;
}


void anadirTLB(int *tlb, int direccion) {

    // Buscar dirección en el tlb
    for (int i = 0; i<cantidadEntradas; i++) {
            if (direccion == *(tlb+(tamanoEntrada*i))) {
                // Si la encuentra, la imprime
                printEntradaTlb(tlb, i, 1, 0); // tlb, posición a imprimir, isHit, !isReplaced
                return;
            }
         }
    // Si la cola está llena 
    if (cont == cantidadEntradas) {
        // Mover todos los elementos para sobrescribir el primero
        for (int i = 0; i < tamanoEntrada*cantidadEntradas; i++) {
            *(tlb+i) = *(tlb+i+tamanoEntrada);
        }
        // Guardar la dirección al final de la cola
        guardarEntradaTlb(tlb, 4, direccion); 
        printEntradaTlb(tlb, 4, 0, 1);  // tlb, posición a imprimir, !isHit, isReplaced
    }

    else if (cont<cantidadEntradas) {
        // Si la cola no está llena, añade al final
        guardarEntradaTlb(tlb, cont, direccion);
        printEntradaTlb(tlb, cont, 0, 0);  // tlb, posición a imprimir, !isHit, !isReplaced
        cont++;
        return;
    }
}


int main () {
    char input[1000];
    printf("Ingrese dirección virtual: ");
    scanf("%s", input);
    
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

        // Calcula el tiempo total transcurrido en segundos como un double
        elapsed = seconds + nanoseconds*1e-9;

        // Imprime el tiempo transcurrido
        printf("Tiempo: %.9f segundos\n", elapsed);

        
        printf("\nIngrese dirección virtual: ");
        scanf("%s", input);      
        
    }
    // liberar recursos

    free(tlb);
    printf("\nGoodbye!\n");
}



// gcc -o traducir main.c -lm
