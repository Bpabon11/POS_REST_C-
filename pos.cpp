//PROYECTO FINAL - PROGRAMACION C++
// Nombre: POS_REST_C++
// Descripcion: Sistema de punto de venta para un restaurante
// Integrantes:MANUELA JARAMILLO, BREINER PABON, LAURA RAMIREZ 
// Fecha: 2025-05-01
// Version: 1.0 
// Licencia: GPL-3.0
// Este programa es software libre: usted puede redistribuirlo y/o modificarlo  
// bajo los términos de la Licencia Pública General de GNU, versión 3.
// Este programa se distribuye con la esperanza de que sea útil, pero SIN NINGUNA GARANTÍA;
// sin siquiera la garantía implícita de COMERCIABILIDAD o IDONEIDAD PARA UN PROPÓSITO PARTICULAR.
// Para más detalles, consulte la Licencia Pública General de GNU en <http://www.gnu.org/licenses/>.
// Este programa es un sistema de punto de venta para un restaurante.
// Permite a los usuarios seleccionar productos de un menú, calcular el total del pedido,
// y generar un archivo de texto con el pedido y un código de barras.
// El código está diseñado para ser fácil de entender y modificar.
// El programa utiliza funciones para organizar el código y mejorar la legibilidad.
// El menú incluye opciones como ensalada vegana, filete de pollo, pescado con camarones y sopa de tomate.
// El precio de cada opción está definido en el código.
// El programa guarda el pedido en un archivo de texto con un nombre único basado en un contador.
// El contador se almacena en un archivo separado y se incrementa cada vez que se realiza un pedido.
// El código de barras se genera a partir del número de pedido y se incluye en el archivo de texto.
// El programa utiliza bibliotecas estándar de C++ como iostream, fstream y string.
// El código está diseñado para ser fácil de entender y modificar.
// El programa utiliza un bucle do-while para permitir al usuario seleccionar múltiples opciones del menú.

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int total = 0;
string pedido = "";

// Función para guardar el pedido
void guardarpedido(int opcion) {
    if (opcion == 1) {
        pedido += "Ensalada vegana - $8000\n";
        total += 8000;
    } else if (opcion == 2) {
        pedido += "Filete de pollo - $35000\n";
        total += 35000;
    } else if (opcion == 3) {
        pedido += "Pescado con camarones - $40000\n";
        total += 40000;
    } else if (opcion == 4) {
        pedido += "Sopa de tomate - $25000\n";
        total += 25000;
    } else if (opcion != 0) {
        cout << "Opcion invalida.\n";
    }
}

// Función para obtener el número de pedido desde un archivo y actualizarlo
int obtenerNumeroPedido() {
    ifstream archivoLectura("contador.txt");
    int numero = 1;

    if (archivoLectura.is_open()) {
        archivoLectura >> numero;
        archivoLectura.close();
    }

    ofstream archivoEscritura("contador.txt");
    if (archivoEscritura.is_open()) {
        archivoEscritura << (numero + 1);
        archivoEscritura.close();
    }

    return numero;
}

// Función para generar un código de barras en formato ASCII
string generarCodigoBarras(int numeroPedido) {
    string codigoBarras = "|";
    string numero = to_string(numeroPedido);

    for (char c : numero) {
        codigoBarras += string(c - '0', '==') + "|";
    }

    return codigoBarras;
}

// Función principal
int main() {
    int opcion;

    do {
        cout << "\n--- MENU DEL RESTAURANTE ---\n";
        cout << "1. Ensalada vegana - $8000\n";
        cout << "2. Filete de pollo - $35000\n";
        cout << "3. Pescado con camarones - $40000\n";
        cout << "4. Sopa de tomate - $25000\n";
        cout << "0. Finalizar pedido\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        guardarpedido(opcion);
    } while (opcion != 0);

    cout << "\n--- PEDIDO REALIZADO ---\n";
    cout << pedido;
    cout << "Total a pagar: $" << total << endl;
    cout << "-Gracias por su compra-" << endl;

    // Obtener número de pedido e incrementar
    int numPedido = obtenerNumeroPedido();

    // Crear nombre de archivo
    string nombreArchivo = "pedido_" + to_string(numPedido) + ".txt";

    // Generar código de barras
    string codigoBarras = generarCodigoBarras(numPedido);

    // Guardar el pedido en archivo
    ofstream archivo(nombreArchivo);
    if (archivo.is_open()) {
        archivo << "--- PEDIDO REALIZADO ---\n";
        archivo << pedido;
        archivo << "Total a pagar: $" << total << "\n";
        archivo << "-Gracias por su compra-\n";
        archivo << "\n--- CODIGO DE BARRAS ---\n";
        archivo << codigoBarras << "\n";
        archivo.close();
        cout << "\nEl pedido se ha guardado en '" << nombreArchivo << "'.\n";
    } else {
        cout << "\nError al guardar el archivo.\n";
    }

    return 0;
}
