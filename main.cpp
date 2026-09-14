#include <iostream>
#include <vector>
#include <termios.h>
#include <unistd.h>

const int FILAS = 20;
const int COLUMNAS = 20;

// Función para leer un carácter de la terminal sin esperar Enter (Modo Canónico Off)
char obtenerTecla() {
    char c = 0;
    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    if (read(STDIN_FILENO, &c, 1) < 0) c = 0;

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return c;
}
// Limpia la pantalla de la consola
void limpiarPantalla() {
    std::cout << "\033[H\033[J";
}

int main() {
    // Posición inicial del personaje
    int posX = 1;
    int posY = 1;

    bool ejecutando = true;

    while (ejecutando) {
        limpiarPantalla();

        // Dibujar el mapa y el personaje
        for (int i = 0; i < FILAS; ++i) {
            for (int j = 0; j < COLUMNAS; ++j) {
                // Dibujar bordes del mapa
                if (i == 0 || i == FILAS - 1 || j == 0 || j == COLUMNAS-1) {
                    std::cout << "\033[1;34m█ \033[0m"; // Pared Azul
                } else if (i == posY && j == posX) {
                    std::cout << "\033[1;32mඞ \033[0m"; // Personaje Verde ('P')
                } else {
                    std::cout << "\033[1;30m· \033[0m"; // Suelo Gris ('·')
                }
            }
            std::cout << "\n";
        }

        std::cout << "\nUsa las FLECHAS del teclado para moverte. Presiona 'q' para salir.\n";

        // Captura de teclas de dirección (secuencias ANSI ESC [ A/B/C/D)
        char c = obtenerTecla();
        if (c == 'q' || c == 'Q') {
            ejecutando = false;
        } else if (c == '\033') { // Inicio de secuencia de escape
            obtenerTecla(); // Consume '['
            switch (obtenerTecla()) {
                case 'A': // Arriba
                    if (posY > 1) posY--;
                    break;
                case 'B': // Abajo
                    if (posY < FILAS - 2) posY++;
                    break;
                case 'C': // Derecha
                    if (posX < COLUMNAS - 2) posX++;
                    break;
                case 'D': // Izquierda
                    if (posX > 1) posX--;
                    break;
            }
        }
    }

    limpiarPantalla();
    std::cout << "¡Juego terminado!\n";
    return 0;
}