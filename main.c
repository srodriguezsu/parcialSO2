#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define _POSIX_C_SOURCE 200809L


void decimalABinario(int numero) {
    int bits = sizeof(int) * 8;  // Número de bits en un entero
    int i;

    // Iterar a través de todos los bits del número
    for (i = bits - 1; i >= 0; i--) {
        // Usar el operador AND para obtener el bit más a la derecha
        int bit = (numero >> i) & 1;
        printf("%d", bit);
    }
    printf("\n");  // Salto de línea al final
}

int binarioAlDecimal(int numero){
    char str[12];
    
}





int main () {
    char input[1000];
    printf("Ingrese su direccion virtual: ");
    scanf("%s", &input);
    int tamanoPagina = 4096;
    while (strcmp(input, "s") != 0) {

        struct timespec tiempoInicial, tiempoFinal, diferencia;
        long seconds, nanoseconds;
        double elapsed;
        clock_gettime(CLOCK_REALTIME, &tiempoInicial);

        int direccion = atoi(input);

        int numeroPagina = floor(direccion / tamanoPagina);
        
        int desplazamiento = direccion % tamanoPagina;
        int desplazamientoBinario = 

        printf("Pagina: %d\n", numeroPagina);

        printf("Desplazamiento: %d\n", desplazamiento);

        printf("Pagina en binario: ");
        decimalABinario(numeroPagina);
        
        printf("Desplazamiento en binario: ");
        decimalABinario(desplazamiento);
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