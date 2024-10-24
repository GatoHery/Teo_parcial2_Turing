#include <iostream>
#include <map>
#include <tuple>
#include <vector>
#include <set>

using namespace std;

// Funciones para imprimir la cinta y la posición de la cabeza de lectura/escritura
void imprimir_menu(string);
void imprimir_seguimiento(int);
void ejecutar_maquina(string, map<pair<string, char>, tuple<string, char, char>>, string, string, set<char>, char);

int main() {
    // Params de la TM
    string texto = "pollo";  // Cadena de entrada
    string estado_inicial = "q0";
    string estado_final = "qf";
    char blanco = '_';  // palabra vacía

    // Alfabeto de la máquina (incluye la palabra vacia)
    set<char> alfabeto_maquina = {'p', 'o', 'l', 'P', 'O', 'L', blanco};

    // Función de transición (estado actual, símbolo leído) -> (nuevo estado, nuevo símbolo, dirección)
    map<pair<string, char>, tuple<string, char, char>> transiciones;
    transiciones[{"q0", 'p'}] = {"q1", 'P', 'R'};
    transiciones[{"q1", 'o'}] = {"q2", 'O', 'R'};
    transiciones[{"q2", 'l'}] = {"q3", 'L', 'R'};
    transiciones[{"q3", 'l'}] = {"q4", 'L', 'R'};
    transiciones[{"q4", 'o'}] = {"qf", 'O', 'R'};

    // Ejecutar la máquina de Turing
    ejecutar_maquina(texto, transiciones, estado_inicial, estado_final, alfabeto_maquina, blanco);

    return 0;
}

void imprimir_menu(string texto) {
    cout << string(texto.length() * 5 + 3, '-') << endl;
    for (char caracter : texto) {
        cout << "| " << caracter << " |";
    }
    cout << endl;
}

void imprimir_seguimiento(int ubicacion) {
    cout << string(ubicacion * 5 + 1, ' ') << "/\\ " << endl;
}

void ejecutar_maquina(string cinta, map<pair<string, char>, tuple<string, char, char>> transiciones, string estado_inicial, string estado_final, set<char> alfabeto_maquina, char blanco) {
    string estado_actual = estado_inicial;
    int posicion = 0;

    while (estado_actual != estado_final) {
        // Imprimir el estado actual de la cinta y la posición de la cabeza
        imprimir_menu(cinta);
        imprimir_seguimiento(posicion);

        char simbolo_actual = cinta[posicion];

        // Verificar que el símbolo actual se encuentre en el alfabeto de la TM
        if (alfabeto_maquina.find(simbolo_actual) == alfabeto_maquina.end()) {
            cout << "Error: Símbolo '" << simbolo_actual << "' no está en el alfabeto de la máquina." << endl;
            return;
        }

        cout << "Estado actual: " << estado_actual << endl;

        // Obtener la transicion (nuevo estado, nuevo símbolo, dirección)
        if (transiciones.find({estado_actual, simbolo_actual}) == transiciones.end()) {
            cout << "Error: No hay transición definida para el par (" << estado_actual << ", " << simbolo_actual << ")." << endl;
            return;
        }

        auto transicion = transiciones[{estado_actual, simbolo_actual}];
        string nuevo_estado = get<0>(transicion);
        char nuevo_simbolo = get<1>(transicion);
        char direccion = get<2>(transicion);

        // Actualizar la cinta con el nuevo simbolo y el estado actual
        cinta[posicion] = nuevo_simbolo;
        estado_actual = nuevo_estado;

        // Mover la cabeza de L/E
        if (direccion == 'R') {
            posicion++;
            // Expandir la cinta si es necesario
            if (posicion >= cinta.length()) {
                cinta += blanco;  // Agregar un vacio al final si se mueve fuera de bounds
            }
        } else if (direccion == 'L') {
            posicion--;
            // Expandir la cinta si se mueve fuera de bounds a la izq
            if (posicion < 0) {
                cinta = blanco + cinta;  // Agregar un vacio al inicio
                posicion = 0;  // Ajustar la pos. de la cabeza al nuevo inicio
            }
        }

        // Simula el avance paso a paso
        cout << "Presione enter para continuar..." << endl;
        cin.get();  // Espera a que el usuario presione enter
    }

    cout << "La máquina ha terminado en el estado final: " << estado_final << endl;
    imprimir_menu(cinta);
    imprimir_seguimiento(posicion);
}