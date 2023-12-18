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
#define NUM_POSICIONES_LUZ 4
#define PROFUNDIDAD_MAX 3
#define ALTURA_MAX 3.2
#define ANGULO_MAX 360

/**
 * Los objetos de esta clase encapsulan la interfaz y el estado de la aplicaci�n
 */
class igvInterfaz {
private:
    // Atributos
    int ancho_ventana = 0; ///< Ancho de la ventana de visualizaci�n
    int alto_ventana = 0;  ///< Alto de la ventana de visualizaci�n

    igvEscena3D escena; ///< Escena que se visualiza en la ventana definida por igvInterfaz
    igvCamara camara; ///< C�mara que se utiliza para renderEscenaA la escena

    // Aplicaci�n del patr�n de dise�o Singleton
    static igvInterfaz *_instancia; ///< Direcci�n de memoria del objeto �nico de la clase
    /// Constructor por defecto
    igvInterfaz();

    int menuSelection = 0; ///< �ltima opci�n de men� seleccionada                                                                                                       static void menuHandle(int value); // m�todo para gestionar la selecci�n de opciones de men�
    void create_menu(); // Creates a menu that is handled with the right button of the mouse.

    int cont = 1;

    int num_escena = 1;
    int posicion_camara = 0;
    int pos_luz = 0;

public:
    // Aplicaci�n del patr�n de dise�o Singleton
    static igvInterfaz &getInstancia();
    // Constructores por defecto y destructor

    /// Destructor
    ~igvInterfaz() = default;

    // M�todos est�ticos
    // callbacks de eventos
    static void keyboardFunc(unsigned char key, int x, int y); // m�todo para control de eventos del teclado
    static void reshapeFunc(int w, int h); // m�todo que define la camara de vision y el viewport
    // se llama autom�ticamente cuando se cambia el tama�o de la ventana
    static void displayFunc(); // m�todo para renderEscenaA la escena
    static void idleFunc(); // m�todo para animar la escena

    // M�todos
    // crea el mundo que se visualiza en la ventana
    void crear_mundo();

    // inicializa todos los par�metros para crear una ventana de visualizaci�n
    void configura_entorno(int argc, char **argv // par�metros del main
            , int _ancho_ventana, int _alto_ventana // ancho y alto de la ventana de visualizaci�n
            , int _pos_X, int _pos_Y // posici�n inicial de la ventana de visualizaci�n
            , std::string _titulo // t�tulo de la ventana de visualizaci�n
    );

    void inicializa_callbacks(); // inicializa todos los callbacks
    void inicia_bucle_visualizacion(); // visualiza la escena y espera a eventos sobre la interfaz

    // m�todos get_ y set_ de acceso a los atributos
    int get_ancho_ventana();

    int get_alto_ventana();

    void set_ancho_ventana(int _ancho_ventana);

    void set_alto_ventana(int _alto_ventana);

    int getCont() const;

    void setCont(int cont);

    void mover_camara();

    void mover_luz(int num_pasos);

    static void menuHandle(int value);

    void mover_luces();
};

#endif   // __IGVINTERFAZ
