#include <iostream>

using namespace std;

void imprimir_menu(string);
void imprimir_seguimiento(int);

int main() {
    string texto = "pollo";
    //cout<<"ingrese frase: "<<endl;
    //cin>>texto;

    int posicion = 0;
    //imprimir maquina
    imprimir_menu(texto);
    imprimir_seguimiento(posicion);

    return 0;
}

void imprimir_menu(string texto){
    cout<<string(texto.length() *5 +3,'-')<<endl;
    int temp = 0;
    for (char caracter : texto){
        if(caracter == texto[0]){
            cout<<" | "<<caracter<<" |";
            temp++;
        }
        else if(temp == texto.length()){
            cout<<"| "<<caracter<<" |   ";
        }
        else{
            cout<<"| "<<caracter<<" |";
            temp++;
        }
    }
    cout<<endl;
}

void imprimir_seguimiento(int ubicacion){
    cout<<string(ubicacion * 5,' ');
    cout<<"  /\\ "<<endl;
}
