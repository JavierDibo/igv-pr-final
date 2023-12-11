#ifndef __IGVINTERFAZ
#define __IGVINTERFAZ

#if defined(__APPLE__) && defined(__MACH__)
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else

#include <GL/glut.h>

#endif   // defined(__APPLE__) && defined(__MACH__)

#include <string>
#include <iostream>
#include <vector>
#include "igvEscena3D.h"
#include "igvCamara.h"

#define NUM_POSICIONES_CAMARA 5

/**
 * Los objetos de esta clase encapsulan la interfaz y el estado de la aplicación
 */
class igvInterfaz {
private:
    // Atributos
    int ancho_ventana = 0; ///< Ancho de la ventana de visualización
    int alto_ventana = 0;  ///< Alto de la ventana de visualización

    igvEscena3D escena; ///< Escena que se visualiza en la ventana definida por igvInterfaz
    igvCamara camara; ///< Cámara que se utiliza para visualizar la escena

    // Aplicación del patrón de diseño Singleton
    static igvInterfaz *_instancia; ///< Dirección de memoria del objeto único de la clase
    /// Constructor por defecto
    igvInterfaz() = default;

    int cont = 1;

    int posicion_camara;

public:
    // Aplicación del patrón de diseño Singleton
    static igvInterfaz &getInstancia();
    // Constructores por defecto y destructor

    /// Destructor
    ~igvInterfaz() = default;

    // Métodos estáticos
    // callbacks de eventos
    static void keyboardFunc(unsigned char key, int x, int y); // método para control de eventos del teclado
    static void reshapeFunc(int w, int h); // método que define la camara de vision y el viewport
    // se llama automáticamente cuando se cambia el tamaño de la ventana
    static void displayFunc(); // método para visualizar la escena
    static void idleFunc(); // método para animar la escena

    // Métodos
    // crea el mundo que se visualiza en la ventana
    void crear_mundo();

    // inicializa todos los parámetros para crear una ventana de visualización
    void configura_entorno(int argc, char **argv // parámetros del main
            , int _ancho_ventana, int _alto_ventana // ancho y alto de la ventana de visualización
            , int _pos_X, int _pos_Y // posición inicial de la ventana de visualización
            , std::string _titulo // título de la ventana de visualización
    );

    void inicializa_callbacks(); // inicializa todos los callbacks
    void inicia_bucle_visualizacion(); // visualiza la escena y espera a eventos sobre la interfaz

    // métodos get_ y set_ de acceso a los atributos
    int get_ancho_ventana();

    int get_alto_ventana();

    void set_ancho_ventana(int _ancho_ventana);

    void set_alto_ventana(int _alto_ventana);

    int getCont() const;

    void setCont(int cont);

    void mover_camara();
};

#endif   // __IGVINTERFAZ
