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
    // Cinta con 50 espacios vacíos ('B')
    string cinta(50, 'B');

    // Alfabeto de la máquina (incluye el símbolo de blanco 'B')
    vector<char> alfabeto_maquina = {'p', 'o', 'l', 'P', 'O', 'L', 'B'};
    set<char> alfabeto_maquina_set(alfabeto_maquina.begin(), alfabeto_maquina.end());

    // Solicitar al usuario que ingrese la cadena de entrada carácter por carácter
    string texto = "";
    char input;
    int posicion = 0;

    cout << "Introduce la cadena de entrada caracter por caracter. Presiona Enter despues de cada letra." << endl;
    while (true) {
        cout << "Introduce la letra en la posicion " << posicion + 1 << " (para finalizar introduce '_'): ";
        cin >> input;

        if (input == '_') {
            break;
        }

        // Verificar si el carácter está en el alfabeto de la máquina
        if (alfabeto_maquina_set.find(input) == alfabeto_maquina_set.end()) {
            cout << "Error: El caracter '" << input << "' no es valido." << endl;
            continue;
        }

        // Agregar el carácter ingresado a la cinta
        cinta[posicion] = input;

        // Mostrar la cinta después de cada cambio
        imprimir_menu(cinta);
        imprimir_seguimiento(posicion);

        // Avanzar la posición en la cinta
        posicion++;
    }

    // Establecer los parámetros de la máquina de Turing
    string estado_inicial = "q0";
    string estado_final = "qf";
    char blanco = 'B';  // Representa el espacio vacío

    // Función de transición (estado actual, símbolo leído) -> (nuevo estado, nuevo símbolo, dirección)
    map<pair<string, char>, tuple<string, char, char>> transiciones;
    transiciones[{"q0", 'p'}] = {"q1", 'P', 'R'};
    transiciones[{"q1", 'o'}] = {"q2", 'O', 'R'};
    transiciones[{"q2", 'l'}] = {"q3", 'L', 'R'};
    transiciones[{"q3", 'l'}] = {"q4", 'L', 'R'};
    transiciones[{"q4", 'o'}] = {"qf", 'O', 'R'};

    // Ejecutar la máquina de Turing
    ejecutar_maquina(cinta, transiciones, estado_inicial, estado_final, alfabeto_maquina_set, blanco);

    return 0;
}

void imprimir_menu(string cinta) {
    cout << string(cinta.length() * 5 + 3, '-') << endl;
    for (char caracter : cinta) {
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
        // Verificar que la posición no se salga de la cinta
        if (posicion < 0 || posicion >= cinta.length()) {
            cout << "Error: La cabeza de lectura/escritura se ha salido de la cinta." << endl;
            return;
        }

        // Imprimir el estado actual de la cinta y la posición de la cabeza
        imprimir_menu(cinta);
        imprimir_seguimiento(posicion);

        char simbolo_actual = cinta[posicion];

        // Verificar que el símbolo actual esté en el alfabeto de la máquina
        if (alfabeto_maquina.find(simbolo_actual) == alfabeto_maquina.end()) {
            cout << "Error: Simbolo '" << simbolo_actual << "' no está en el alfabeto de la máquina." << endl;
            return;
        }

        cout << "Estado actual: " << estado_actual << endl;

        // Verificar si hay una transición válida
        if (transiciones.find({estado_actual, simbolo_actual}) == transiciones.end()) {
            cout << "Error: No hay transición definida para el par (" << estado_actual << ", " << simbolo_actual << ")." << endl;
            cout << "La máquina se detendrá." << endl;
            exit(1);  // Finaliza el programa abruptamente para simular el Halt
        }

        // Obtener la transición correspondiente (nuevo estado, nuevo símbolo, dirección)
        auto transicion = transiciones[{estado_actual, simbolo_actual}];
        string nuevo_estado = get<0>(transicion);
        char nuevo_simbolo = get<1>(transicion);
        char direccion = get<2>(transicion);

        // Actualizar la cinta con el nuevo símbolo y el estado actual
        cinta[posicion] = nuevo_simbolo;
        estado_actual = nuevo_estado;

        // Mover la cabeza de lectura/escritura
        if (direccion == 'R') {
            posicion++;
            // Expandir la cinta si es necesario
            if (posicion >= cinta.length()) {
                cinta += blanco;  
            }
        } else if (direccion == 'L') {
            posicion--;
            // Expandir la cinta si se mueve fuera de bounds a la izquierda
            if (posicion < 0) {
                cinta = blanco + cinta;  
                posicion = 0;  
            }
        }

        // Simula el avance paso a paso cuando haya terminado de imprimir la cinta
        cout << "Presione enter para continuar..." << endl;
        cin.ignore();
        cin.get();  // Espera a que el usuario presione enter
    }

    cout << "La maquina ha terminado en el estado final: " << estado_final << endl;
    imprimir_menu(cinta);
    imprimir_seguimiento(posicion);
}