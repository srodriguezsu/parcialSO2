#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define _POSIX_C_SOURCE 200809L

int cont = 0;
int tamanoPagina = 4096;

int decimalABinario(int n) {
    int binary = 0, base = 1;
    while (n > 0) {
        binary += (n % 2) * base;
        n /= 2;
        base *= 10;
    }
    return binary;
}


int binarioAlDecimal(int numero){
    char str[12];
    
}


void anadirTLB(int *tlb, int x) {


    for (int i = 0; i<5; i++) {

            if (x == *(tlb+(5*i))) {

                int * inicio = tlb;
                int * final = tlb+25;
                printf("TLB desde: %p hasta %p\n", inicio, final);
                printf("HIT \n");
                printf("Pagina: %d\n", *(tlb+(i*5) + 1));
                printf("Desplazamiento: %d\n", *(tlb+(i*5) + 2));
                printf("Pagina en Binario: %d\n", *(tlb+(i*5) + 3));
                printf("Desplazamiento en Binario: %d\n", *(tlb+(i*5) + 4));
                printf("Politica de reemplazo: 0x0\n");
                return;
            }

         }

    if (cont == 5) {
        

        for (int i = 0; i <= 20; i++) {
            *(tlb+i) = *(tlb+i+5); 
        }
        
         int a = floor(x / tamanoPagina);
         int b = x % tamanoPagina;
         int c = decimalABinario(a);
         int d = decimalABinario(b);

         *(tlb+20) = x;
         *(tlb+21) = a; //Pagina
         *(tlb+22) = b; // Desplazamiento
         *(tlb+23) = c; // Pagina en binario
         *(tlb+24) = d; // Desplazamiento en binario
         

         int * inicio = tlb;
         int * final = tlb+25;
         printf("TLB desde: %p hasta %p\n", inicio, final);
         printf("MISS \n"); 
         printf("Pagina: %d\n", *(tlb+21));
         printf("Desplazamiento: %d\n", *(tlb+22));
         printf("Pagina en Binario: %d\n", *(tlb+23));
         printf("Desplazamiento en Binario: %d\n", *(tlb+24));

         int *reemplazo = tlb+20;
         printf("Politica de reemplazo %p\n", &reemplazo);


    }

    else if (cont<5) {

        int a = floor(x / tamanoPagina);
        int b = x % tamanoPagina;
        int c = decimalABinario(a);
        int d = decimalABinario(b);

        *(tlb+(cont*5)) = x; //Direccion
        *(tlb+(cont*5) + 1) = a; // Pagina
        *(tlb+(cont*5) + 2) = b; // Desplazamiento
        *(tlb+(cont*5) + 3) = c; // Pagina en binario
        *(tlb+(cont*5) + 4) = d; // Desplazamiento en binario

        printf("MISS \n"); 
        int * inicio = tlb;
        int * final = tlb+25;
        printf("TLB desde: %p hasta %p\n", inicio, final);
        printf("Pagina: %d\n", *(tlb+(cont*5) + 1));
        printf("Desplazamiento: %d\n", *(tlb+(cont*5) + 2));
        printf("Pagina en Binario: %d\n", *(tlb+(cont*5) + 3));
        printf("Desplazamiento en Binario: %d\n", *(tlb+(cont*5) + 4));
        printf("Politica de reemplazo: 0x0\n");

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
        printf("Elapsed time: %.9f seconds\n", elapsed);

        
        printf("\nIngrese su direccion virtual: ");
        scanf("%s", &input);      
        //sebas es un gilipollas 
    }
    free(tlb);
}