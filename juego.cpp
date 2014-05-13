#include "juego.h"
#include <fstream>

using namespace std;

void jugadores(string &player1, string &player2){
    cout<<"Ahorcado para MS-DOS: (No usar sin licencia)"<<endl;
    cout<<"============================================"<<endl;
    cout<<endl;
    //Funcion extra: Puntaje
    cout<<"Sistema de puntaje:"<<endl;
    cout<<"Cada letra acertada suma 10 puntos, cada letra erronea resta 5 puntos."<<endl;
    cout<<"Arriesgar la palabra da 50 puntos, en caso de arriesgar mal, resta 100 puntos."<<endl;
    cout<<endl;
    //Funcion extra: Puntaje
    cout<<"Ingrese el nombre del jugador 1: ";
    cin>>player1;
    cout<<"Ingrese el nombre del jugador 2: ";
    cin>>player2;
    cout<<endl;
}

string lower_palabra(string &palabra){ //Paso las palabras a minusculas
    for(unsigned int i=0; i<palabra.length(); i++){
        palabra[i]=tolower(palabra[i]);
    }
    return palabra;
}

void palabra_chances(string player1, string player2, string &palabra, int *p, int &chances){
    cout<<"Es tu turno "<<player1<<endl;

    //Subraya el nombre
    for(unsigned int i=0; i<player1.length(); i++){
        cout<<"=";
    }
    cout<<"============"<<endl<<endl;
    //Subraya el nombre

    cout<<"Ingrese una palabra: ";
    cin>>palabra;
    palabra=lower_palabra(palabra); //Me aseguro que la palabra quede escrita en minusculas
    *p= palabra.length(); //Guardo un vector del tamanio de la palabra
    cout<<"Ingrese las chances que tendra "<<player2<<" para adivinarla: ";
    cin>>chances;
    cout<<endl;
}

void inicializar_vector(int *p, char vec_palabra[]){ //Inicializo el vector con guiones
    cout<<"Ahorcado: ";
    for(int i=0; i<*p; i++){
        vec_palabra[i]='_';
        cout<<vec_palabra[i]<<" "; //Le muestro al jugador la palabra oculta
    }
    cout<<endl<<endl;
}

void estado_juego(int *p, char vec_palabra[]){ //Estado actual del juego
    cout<<endl;
    cout<<"Ahorcado: ";
    for(int i=0; i<*p; i++){
        cout<<vec_palabra[i]<<" ";
    }
    cout<<endl<<endl;
}

int comparar_letra(char letra, string palabra, int *p, char vec_palabra[]){
    int aciertos;
    aciertos=0;

    //Comparo la letra ingresada con la cada letra de la palabra elegida
    for(int i=0; i<*p; i++){
        if (letra==palabra[i]){
            vec_palabra[i]=letra; //Si la letra coincide la guardo en su posicion correspondiente
            aciertos++;
        }
    }
    return aciertos;
}

int comparar_palabra(char vec_palabra[], int *p){ //Veo si el juego termino
    int i;
    int finjuego;
    i=0;
    finjuego=1;

    while((i<*p) and (finjuego==1)){
        if (vec_palabra[i]=='_'){
            finjuego=0;
        }
        i++;
    }
    return finjuego;
}

void guardar_letra(char letra, char vec_abc[], int abc){ //Guarda la letra ingresada en un vector
    bool grabada;
    int i;
    grabada=false;
    i=0;

    while((i<abc) and (grabada==false)){
        //Busco un lugar vacio y la guardo, con la seguridad de que no va a estar repetida
        // ya que la comparacion se hizo en el procedimiento anterior.
        if (vec_abc[i]==' '){
            vec_abc[i]=letra;
            grabada=true;
        }
        i++;
    }
}

//No deja que el usuario ingrese dos veces la misma letra
bool letra_usada(char vec_palabra[], int *p, char letra, char vec_abc[], int abc){
    bool encontrada;
    encontrada=false;

    for(int i=0; i<*p; i++){
        if (vec_abc[i]==letra){
            encontrada=true;
        }
    }
    if (encontrada==false){
        guardar_letra(letra, vec_abc, abc);
    }
    return encontrada;
}

void crear_abc(char vec_abc[], int abc){ //Inicializo el vector abc donde se guardaran las letras ingresadas.
    for(int i=0; i<abc; i++){
        vec_abc[i]=' ';
    }
}

bool arriesgar(string palabra_letra, string palabra, int &puntaje_p){
    const int arriesgar_bien= 50;
    const int arriesgar_mal= 100;
    bool resultado;

    //Me aseguro antes que la palabra arriesgada este en minusculas
    palabra_letra=lower_palabra(palabra_letra);

    if (palabra_letra==palabra){
        cout<<"Muy bien! Adivinaste la palabra '"<<palabra<<"' de forma arriesgada!"<<endl<<endl;
        puntaje_p=puntaje_p + arriesgar_bien;
        resultado=true;
    }
    else{
        cout<<"Perdiste, la palabra correcta era: "<<palabra<<endl<<endl;
        puntaje_p=puntaje_p - arriesgar_mal;
        resultado=false;
    }
    return resultado;
}

void letras_usadas(int abc, char vec_abc[]){ //Muestra las letras utilizadas
    cout<<"Letras utilizadas: ";
    for(int i=0; i<abc; i++){
        cout<<" "<<vec_abc[i]<<" ";
    }
    cout<<endl;
}

void comparar_puntajes(int puntaje_p1, int puntaje_p2, string player1, string player2){
    cout<<"Resultados oficiales:"<<endl;
    cout<<"====================="<<endl<<endl;
    if (puntaje_p1>puntaje_p2){
        cout<<"El ganador es "<<player1<<" con "<<puntaje_p1<<" puntos, frente a "<<puntaje_p2<<" puntos de "<<player2<<endl;
    }
    else if (puntaje_p1<puntaje_p2){
        cout<<"El ganador es "<<player2<<" con "<<puntaje_p2<<" puntos, frente a "<<puntaje_p1<<" puntos de "<<player1<<endl;
    }
    else if (puntaje_p1==puntaje_p2){
        cout<<"Cada jugador obtuvo "<<puntaje_p1<<". Esto ha sido un empate!"<<endl;
    }
}

int puntaje(int aciertos, int &puntaje_p){
    const int aumento=10;
    const int descuento=5;

    if ((aciertos)!=0){
        puntaje_p=puntaje_p +(aciertos*aumento); //Suma el puntaje anterior mas los aciertos
    }
    else if ((aciertos)==0){
        puntaje_p=(puntaje_p - descuento);
    }
    return puntaje_p;
}

int juego(string player1, string player2, string palabra, int chances, int *p, char vec_palabra[]){
    const int abc=26; //26 letras del abecedario
    bool resultado;
    int intentos=0;
    int aciertos=0;
    int finjuego=1;
    char letra;
    string palabra_letra;
    int puntaje_p=0;
    char vec_abc[abc];

    crear_abc(vec_abc, abc); //Crea vector abecedario
    ofstream historial("resultados.txt", ios::app); //Abro el archivo de texto para escritura

    //Subraya el nombre
    cout<<"Es tu turno "<<player2<<endl;
    for(unsigned int i=0; i<player2.length(); i++){
        cout<<"=";
    }
    cout<<"============"<<endl<<endl;
    //Subraya el nombre

    inicializar_vector(p, vec_palabra); //Muestro el estado del juego inicializando el vector
    while ((intentos<chances) and (finjuego==1)){
        cout<<"Ingrese una letra o arriesgue la palabra: ";
        cin>>palabra_letra;
        if (palabra_letra.length()==palabra.length()){ //Solo entra si las palabras tienen el mismo tamaño
            resultado=arriesgar(palabra_letra, palabra, puntaje_p);
            if (resultado==true){
                historial<<player2<<" arriesgo y adivino la palabra "<<palabra<<" de "<<player1<<'\n';
            }
            else if (resultado==false){
                historial<<player2<<" arriesgo y no adivino la palabra "<<palabra<<" de "<<player1<<'\n';
            }
            finjuego=0;
        }
        else{
            letra=palabra_letra[0]; //Guardo el primer caracter en un char
            letra=tolower(letra); //Me aseguro que el usuario no ingrese mayusculas

            if (letra_usada(vec_palabra, p, letra, vec_abc, abc)==true){
                cout<<"La letra ya fue utilizada! Ingresa una distinta."<<endl;
                letras_usadas(abc, vec_abc);
            }
            else{
                letras_usadas(abc, vec_abc);
                aciertos= comparar_letra(letra, palabra, p, vec_palabra);
                //Funcion extra: Puntaje
                puntaje_p= puntaje(aciertos, puntaje_p);
                cout<<"Puntaje actual: "<<puntaje_p<<endl;
                //Funcion extra: Puntaje
                if (aciertos!=0){
                    cout<<"Bien! La letra elegida se encontro "<<aciertos<<" vez/veces."<<endl;
                    if (comparar_palabra(vec_palabra,p)==1){ //Se comprueba que aun queden lugares sin adivinar
                        cout<<endl;
                        cout<<"Fin del juego, adivinaste la palabra :)"<<endl;
                        historial<<player2<<" adivino la palabra "<<palabra<<" de "<<player1<<" en "<<intentos<<" de "<<chances<<" chances."<<'\n';
                        finjuego=0;
                    }
                }
                else {
                    cout<<"La letra "<<letra<<" no se encuentra en la palabra."<<endl;
                    intentos++; //Incremento los intentos ya que no encontro la letra.
                    cout<<"Te quedan "<<chances-intentos<<" de "<<chances<<" chances."<<endl;
                }
                aciertos=0;
                estado_juego(p, vec_palabra); //Muestro el estado del juego cada vez que el usuario ingresa una palabra

                if (chances-intentos==0){
                    cout<<"Perdiste, la palabra era: "<<palabra<<endl<<endl;
                    historial<<player2<<" no adivino la palabra "<<palabra<<" de "<<player1<<" en menos de "<<chances<<" chances."<<'\n';
                }
            }
        }
    }
    return puntaje_p;
}

void intercambio(string &player1, string &player2){ //Intercambio los jugadores para la segunda partida
    string aux=player1;
    player1=player2;
    player2=aux;
}

