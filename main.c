#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define _POSIX_C_SOURCE 200809L

int cont = 0;
int tamanoPagina = 4096;

char* decimalABinario(int numero) {
    int bits = sizeof(int) * 8;  // Número de bits en un entero (32 bits)
    char* binario = (char*)malloc(bits + 1);  // Reservar memoria (+1 para el terminador nulo)
    
    if (binario == NULL) {
        return NULL;  // Si falla malloc, devolver NULL
    }

    // Iterar a través de todos los bits del número
    for (int i = bits - 1; i >= 0; i--) {
        int bit = (numero >> i) & 1;  // Obtener el bit más significativo
        binario[bits - 1 - i] = bit + '0';  // Convertir el bit a carácter '0' o '1'
    }
    
    binario[bits] = '\0';  // Agregar el terminador nulo al final
    return binario;
}

int binarioAlDecimal(int numero){
    char str[12];
    
}


void anadirTLB(int *tlb, int x) {


    for (int i = 0; i<5; i++) {

            if (x == *(tlb+(5*i))) {
                printf("HIT \n");
                return;
            }

         }

    if (cont == 5) {
        

        for (int i = 0; i <= 20; i++) {
            *(tlb+i) = *(tlb+i+5); 
        }

         *(tlb+20) = x;

    }

    else if (cont<5) {
        *(tlb+(cont*5)) = x;
        *(tlb+(cont*5) + 1) = floor(x / tamanoPagina);
        *(tlb+(cont*5) + 2) = x % tamanoPagina;
        *(tlb+(cont*5) + 3) = 

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
        

        printf("En el tlb esta: %d\n", *tlb);
        printf("En el tlb tambien esta: %d\n", *(tlb+5));
        printf("En el tlb tambien esta: %d\n", *(tlb+10));
        printf("En el tlb tambien esta: %d\n", *(tlb+15));
        printf("En el tlb tambien esta: %d\n", *(tlb+20));



        
        
        
        int desplazamientoBinario;

       // printf("Pagina: %d\n", numeroPagina);

        // printf("Desplazamiento: %d\n", desplazamiento);
        char* dec = decimalABinario(121);

        printf("Pagina en binario: %s\n", dec);
        
        
        printf("Desplazamiento en binario: ");
        // decimalABinario(desplazamiento);
        // printBinario(desplazamientoBinario);
         
        clock_gettime(CLOCK_REALTIME, &tiempoFinal);

        //printf("\nTiempo en mls %d \n", tiempoFinal - tiempoInicial);

        seconds = tiempoFinal.tv_sec - tiempoInicial.tv_sec;
        nanoseconds = tiempoFinal.tv_nsec - tiempoInicial.tv_nsec;

        if (nanoseconds < 0) {
            seconds -= 1;
            nanoseconds += 1000000000;
        }

        // Calculate the total elapsed time in seconds as a double
        elapsed = seconds + nanoseconds*1e-9;

        // Print the elapsed time
        printf("Elapsed time: %.9f seconds\n", elapsed);

        
        printf("\nIngrese su direccion virtual: ");
        scanf("%s", &input);      
        //sebas es un gilipollas 
    }
}