#include <iostream>
#ifndef JUEGO_H_INCLUDED
#define JUEGO_H_INCLUDED

using namespace std;

void jugadores(string &player1, string &player2);
string lower_palabra(string &palabra); //Paso las palabras a minusculas
void palabra_chances(string player1, string player2, string &palabra, int *p, int &chances);
void inicializar_vector(int *p, char vec_palabra[]); //Inicializo el vector con guiones
void estado_juego(int *p, char vec_palabra[]); //Estado actual del juego
int comparar_letra(char letra, string palabra, int *p, char vec_palabra[]);
int comparar_palabra(char vec_palabra[], int *p); //Veo si el juego termino
void guardar_letra(char letra, char vec_abc[], int abc); //Guarda la letra ingresada en un vector
bool letra_usada(char vec_palabra[], int *p, char letra, char vec_abc[], int abc);
void crear_abc(char vec_abc[], int abc); //Inicializo el vector abc donde se guardaran las letras ingresadas.
bool arriesgar(string palabra_letra, string palabra, int &puntaje_p);
void letras_usadas(int abc, char vec_abc[]); //Muestra las letras utilizadas
void comparar_puntajes(int puntaje_p1, int puntaje_p2, string player1, string player2);
int puntaje(int aciertos, int &puntaje_p);
int juego(string player1, string player2, string palabra, int chances, int *p, char vec_palabra[]);
void intercambio(string &player1, string &player2); //Intercambio los jugadores para la segunda partida

#endif // JUEGO_H_INCLUDED
