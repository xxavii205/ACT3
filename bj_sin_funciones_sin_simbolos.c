#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TOTAL_CARTAS 52
#define VALORES_CARTA 13
#define MAX_MANO 10

char *valores[] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};
char *palos[] = {"Corazones", "Diamantes", "Picas", "Treboles"};

struct carta {
    char *valor;
    char *palo;
    int valorNumerico;
};

struct carta mazo[TOTAL_CARTAS];
struct carta manoJugador[MAX_MANO];
int numCartasJugador = 0;
int sumaJugador = 0;
char eleccion;

int main() {

    for (int i = 0; i < TOTAL_CARTAS; i++) {
        mazo[i].valor = valores[i % VALORES_CARTA];
        mazo[i].palo = palos[i / VALORES_CARTA];
        mazo[i].valorNumerico = (i % VALORES_CARTA) + 2;
        if (mazo[i].valorNumerico > 10) mazo[i].valorNumerico = 10;
        if (i % VALORES_CARTA == VALORES_CARTA - 1) mazo[i].valorNumerico = 11;
    }


    srand(time(NULL));
    for (int i = 0; i < TOTAL_CARTAS; i++) {
        int j = rand() % TOTAL_CARTAS;
        struct carta temp = mazo[i];
        mazo[i] = mazo[j];
        mazo[j] = temp;
    }

    printf("Bienvenido al Blackjack!\n");


    manoJugador[numCartasJugador++] = mazo[0];
    manoJugador[numCartasJugador++] = mazo[1];


    sumaJugador = 0;
    for (int i = 0; i < numCartasJugador; i++) {
        sumaJugador += manoJugador[i].valorNumerico;
    }


    for (int i = 0; i < numCartasJugador; i++) {
        printf("  %s de %s\n", manoJugador[i].valor, manoJugador[i].palo);
    }
    printf("Suma total: %d\n", sumaJugador);


    while (sumaJugador < 21) {
        printf("Quieres otra carta? (s/n): ");
        scanf(" %c", &eleccion);

        if (eleccion == 's' || eleccion == 'S') {
            manoJugador[numCartasJugador] = mazo[numCartasJugador + 1];
            numCartasJugador++;
            sumaJugador = 0;
            for (int i = 0; i < numCartasJugador; i++) {
                sumaJugador += manoJugador[i].valorNumerico;
            }

            for (int i = 0; i < numCartasJugador; i++) {
                printf("  %s de %s\n", manoJugador[i].valor, manoJugador[i].palo);
            }
            printf("Suma total: %d\n", sumaJugador);
        } else {
            break;
        }
    }

    if (sumaJugador == 21) {
        printf("Blackjack! Has ganado.\n");
    } else if (sumaJugador > 21) {
        printf("Te has pasado. Fin del juego.\n");
    } else {
        printf("Te has plantado con %d. Fin del juego.\n", sumaJugador);
    }

    return 0;
}
