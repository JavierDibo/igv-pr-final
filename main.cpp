#include <cstdlib>

#include "igvInterfaz.h"

int main(int argc, char **argv) {

    // inicializa la ventana de visualización
    igvInterfaz::getInstancia().configura_entorno(argc, argv, 600, 600 // tamaño de la ventana
            , 100, 100 // posición de la ventana
            , "IGV. Proyecto Final." // título de la ventana
    );

    // establece las funciones callbacks para la gestión de los eventos
    igvInterfaz::getInstancia().inicializa_callbacks();

    // inicia el bucle de visualización de GLUT
    igvInterfaz::getInstancia().inicia_bucle_visualizacion();

    return (0);
}
