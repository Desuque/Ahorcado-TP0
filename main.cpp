#include <iostream>
#include <fstream>
#include <string>
#include "juego.h"

using namespace std;

int main (){
    int puntaje_p1, puntaje_p2;
    string player1;
    string player2;
    int chances;
    string palabra;
    char continuar;
    int* p; // Declaro variable puntero entero
    p= new int; //Reservo memoria en el heap
    *p= 0; //Guardo un 0 en el heap
    char vec_palabra[*p]; //Genero un vector de char

    do {
        //Comienzo primera partida
        jugadores(player1, player2);
        palabra_chances(player1, player2, palabra, p, chances);
        puntaje_p2= juego(player1, player2, palabra, chances, p, vec_palabra);

        //Comienzo segunda partida
        intercambio(player1, player2);
        palabra_chances(player1, player2, palabra, p, chances);
        puntaje_p1= juego(player1, player2, palabra, chances, p, vec_palabra);

        //Funcion extra: Puntaje
        comparar_puntajes(puntaje_p1, puntaje_p2, player2, player1);

        //Desea seguir jugando?
        cout<<endl;
        cout<<"Desea jugar una nueva partida? (S/N): ";
        cin>>continuar;
        cout<<endl<<endl;

    } while (continuar=='s');

    delete p; //Libero la memoria
    return 0;
}
