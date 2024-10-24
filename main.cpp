#include <iostream>
#include <map>
#include <tuple>
#include <vector>

using namespace std;

// Funciones para imprimir la cinta y la posición de la cabeza de lectura/escritura
void imprimir_menu(string);
void imprimir_seguimiento(int);
void ejecutar_maquina(string, map<pair<string, char>, tuple<string, char, char>>, string, string);

int main() {
    // Parámetros de la máquina de Turing
    // Faltan los alfabetos
    //que revisar que la maquina no se salga de la cinta
    string texto = "pollo";  // Cadena de entrada
    string estado_inicial = "q0";
    string estado_final = "qf";
    char blanco = '_';  // Representa la palabra vacía

    // Función de transición (estado actual, símbolo leído) -> (nuevo estado, nuevo símbolo, dirección)
    // La dirección puede ser 'L' (izquierda) o 'R' (derecha) para la palabra pollo
    // Debemos crear la nuestra
    map<pair<string, char>, tuple<string, char, char>> transiciones;
    transiciones[{"q0", 'p'}] = {"q1", 'P', 'R'};
    transiciones[{"q1", 'o'}] = {"q2", 'O', 'R'};
    transiciones[{"q2", 'l'}] = {"q3", 'L', 'R'};
    transiciones[{"q3", 'l'}] = {"q4", 'L', 'R'};
    transiciones[{"q4", 'o'}] = {"qf", 'O', 'R'};

    // Ejecutar la máquina de Turing
    ejecutar_maquina(texto, transiciones, estado_inicial, estado_final);

    return 0;
}

void imprimir_menu(string texto){
    cout << string(texto.length() * 5 + 3, '-') << endl;
    for (char caracter : texto){
        cout << "| " << caracter << " |";
    }
    cout<<endl;
}

void imprimir_seguimiento(int ubicacion){
    cout << string(ubicacion * 5 +1, ' ') << "/\\ " << endl;
}

void ejecutar_maquina(string cinta, map<pair<string, char>, tuple<string, char, char>> transiciones, string estado_inicial, string estado_final) {
    string estado_actual = estado_inicial;
    int posicion = 0;
    while (estado_actual != estado_final) {
        // Imprimir el estado actual de la cinta y la posición de la cabeza
        imprimir_menu(cinta);
        imprimir_seguimiento(posicion);

        char simbolo_actual = cinta[posicion];

        cout<<estado_actual<<endl;
        // Obtener la transición correspondiente (nuevo estado, nuevo símbolo, dirección)
        auto transicion = transiciones[{estado_actual, simbolo_actual}];
        string nuevo_estado = get<0>(transicion);
        char nuevo_simbolo = get<1>(transicion);
        char direccion = get<2>(transicion);

        // Actualizar la cinta con el nuevo símbolo estado actual y se mueve derecha o izquierda
        cinta[posicion] = nuevo_simbolo;

        estado_actual = nuevo_estado;

        if (direccion == 'R') {
            posicion++;
        } else if (direccion == 'L') {
            posicion--;
        }

        //Simula el avance paso a paso
        cout << "Presione enter para continuar..." << endl;
        cin.ignore();
    }

    cout << "La maquina ha terminado en el estado final: " << estado_final << endl;
    imprimir_menu(cinta);
    imprimir_seguimiento(posicion);
}