#include <cstdlib>
#include <stdio.h>

#include "igvInterfaz.h"

// Aplicación del patrón de diseño Singleton
igvInterfaz *igvInterfaz::_instancia = nullptr;

// Métodos públicos ----------------------------------------

/**
 * Método para acceder al objeto único de la clase, en aplicación del patrón de
 * diseño Singleton
 * @return Una referencia al objeto único de la clase
 */
igvInterfaz &igvInterfaz::getInstancia() {
    if (!_instancia) {
        _instancia = new igvInterfaz;
    }

    return *_instancia;
}

/**
 * Crea el mundo que se visualiza en la ventana
 */
void igvInterfaz::crear_mundo() {  // inicia la cámara
    _instancia->camara.set(IGV_PARALELA, {6.0, 4.0, 8}, {0, 0, 0}, {0, 1.0, 0}, -1 * 5, 1 * 5, -1 * 5, 1 * 5, -1 * 3,
                           200);
}

/**
 * Inicializa todos los parámetros para crear una ventana de visualización
 * @param argc Número de parámetros por línea de comandos al ejecutar la
 *             aplicación
 * @param argv Parámetros por línea de comandos al ejecutar la aplicación
 * @param _ancho_ventana Ancho inicial de la ventana de visualización
 * @param _alto_ventana Alto inicial de la ventana de visualización
 * @param _pos_X Coordenada X de la posición inicial de la ventana de
 *               visualización
 * @param _pos_Y Coordenada Y de la posición inicial de la ventana de
 *               visualización
 * @param _titulo Título de la ventana de visualización
 * @pre Se asume que todos los parámetros tienen valores válidos
 * @post Cambia el alto y ancho de ventana almacenado en el objeto
 */
void
igvInterfaz::configura_entorno(int argc, char **argv, int _ancho_ventana, int _alto_ventana, int _pos_X, int _pos_Y,
                               std::string _titulo) {  // inicialización de las variables de la interfaz
    ancho_ventana = _ancho_ventana;
    alto_ventana = _alto_ventana;

    // inicialización de la ventana de visualización
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(_ancho_ventana, _alto_ventana);
    glutInitWindowPosition(_pos_X, _pos_Y);
    glutCreateWindow(_titulo.c_str());

    glEnable(GL_DEPTH_TEST); // activa el ocultamiento de superficies por z-buffer
    glClearColor(1.0, 1.0, 1.0, 0.0); // establece el color de fondo de la ventana

    glEnable(GL_LIGHTING); // activa la iluminacion de la escena
    glEnable(GL_NORMALIZE); // normaliza los vectores normales para calculo iluminacion

    crear_mundo(); // crea el mundo a visualizar en la ventana
}

/**
 * Método para visualizar la escena y esperar a eventos sobre la interfaz
 */
void igvInterfaz::inicia_bucle_visualizacion() {
    glutMainLoop(); // inicia el bucle de visualización de GLUT
}

/**
 * Método para control de eventos del teclado
 * @param key Código de la tecla pulsada
 * @param x Coordenada X de la posición del cursor del ratón en el momento del
 *          evento de teclado
 * @param y Coordenada Y de la posición del cursor del ratón en el momento del
 *          evento de teclado
 * @pre Se asume que todos los parámetros tienen valores válidos
 * @post Los atributos de la clase pueden cambiar, dependiendo de la tecla pulsada
 */
void igvInterfaz::keyboardFunc(unsigned char key, int x, int y) {
    switch (key) {
        // TODO: Apartado C: incluir aquí el cambio de la cámara para mostrar las vistas planta, perfil, alzado o perspectiva
        // TODO: Apartado C: incluir aquí la modificación de los grados de libertad del modelo pulsando las teclas correspondientes

        case 'e': // activa/desactiva la visualizacion de los ejes
            _instancia->escena.set_ejes(!_instancia->escena.get_ejes());
            break;
        case 27: // tecla de escape para SALIR
            exit(1);
            break;
        case 'c':
            _instancia->escena.setAngCabeza(_instancia->escena.getAngCabeza() + 1);
            break;
        case 'C':
            _instancia->escena.setAngCabeza(_instancia->escena.getAngCabeza() - 1);
            break;
        case 'p':
            if (_instancia->escena.getAngPiernaD() == 45 && _instancia->escena.getAngPiernaI() == -45
                || _instancia->escena.getAngPiernaD() == -45 && _instancia->escena.getAngPiernaI() == 45) {
                _instancia->setCont(_instancia->getCont() + 1);
                //_instancia->escena.setAngCabeza(_instancia->escena.getAngCabeza()+1);
            }
            if (_instancia->getCont() % 2 == 0) {
                _instancia->escena.setAngPiernaD(_instancia->escena.getAngPiernaD() - 1);
                _instancia->escena.setAngPiernaI(_instancia->escena.getAngPiernaI() + 1);

                _instancia->escena.setAngBrazoD(_instancia->escena.getAngBrazoD() - 1);
                _instancia->escena.setAngBrazoI(_instancia->escena.getAngBrazoI() - 1);
            } else {
                _instancia->escena.setAngPiernaD(_instancia->escena.getAngPiernaD() + 1);
                _instancia->escena.setAngPiernaI(_instancia->escena.getAngPiernaI() - 1);

                _instancia->escena.setAngBrazoD(_instancia->escena.getAngBrazoD() + 1);
                _instancia->escena.setAngBrazoI(_instancia->escena.getAngBrazoI() + 1);
            }


    }
    glutPostRedisplay(); // renueva el contenido de la ventana de vision
}

/**
 * Método que define la cámara de visión y el viewport. Se llama automáticamente
 * cuando se cambia el tamaño de la ventana.
 * @param w Nuevo ancho de la ventana
 * @param h Nuevo alto de la ventana
 * @pre Se asume que todos los parámetros tienen valores válidos
 */
void igvInterfaz::reshapeFunc(int w, int h) {  // dimensiona el viewport al nuevo ancho y alto de la ventana
    // guardamos valores nuevos de la ventana de visualizacion
    _instancia->set_ancho_ventana(w);
    _instancia->set_alto_ventana(h);

    // establece los parámetros de la cámara y de la proyección
    _instancia->camara.aplicar();
}

/**
 * Método para visualizar la escena
 */
void igvInterfaz::displayFunc() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // borra la ventana y el z-buffer
    // se establece el viewport
    glViewport(0, 0, _instancia->get_ancho_ventana(), _instancia->get_alto_ventana());


    // aplica las transformaciones en función de los parámetros de la cámara
    _instancia->camara.aplicar();
    // visualiza la escena
    _instancia->escena.visualizar();

    // refresca la ventana
    glutSwapBuffers();
}

/**
 * Método para animar la escena
 */
void
igvInterfaz::idleFunc() {  // TODO: Apartado D: incluir el código para animar el modelo de la manera más realista posible
}

/**
 * Método para inicializar los callbacks GLUT
 */
void igvInterfaz::inicializa_callbacks() {
    glutKeyboardFunc(keyboardFunc);
    glutReshapeFunc(reshapeFunc);
    glutDisplayFunc(displayFunc);
    glutIdleFunc(idleFunc);
}

/**
 * Método para consultar el ancho de la ventana de visualización
 * @return El valor almacenado como ancho de la ventana de visualización
 */
int igvInterfaz::get_ancho_ventana() {
    return ancho_ventana;
}

/**
 * Método para consultar el alto de la ventana de visualización
 * @return El valor almacenado como alto de la ventana de visualización
 */
int igvInterfaz::get_alto_ventana() {
    return alto_ventana;
}

/**
 * Método para cambiar el ancho de la ventana de visualización
 * @param _ancho_ventana Nuevo valor para el ancho de la ventana de visualización
 * @pre Se asume que el parámetro tiene un valor válido
 * @post El ancho de ventana almacenado en la aplicación cambia al nuevo valor
 */
void igvInterfaz::set_ancho_ventana(int _ancho_ventana) {
    ancho_ventana = _ancho_ventana;
}

/**
 * Método para cambiar el alto de la ventana de visualización
 * @param _alto_ventana Nuevo valor para el alto de la ventana de visualización
 * @pre Se asume que el parámetro tiene un valor válido
 * @post El alto de ventana almacenado en la aplicación cambia al nuevo valor
 */
void igvInterfaz::set_alto_ventana(int _alto_ventana) {
    alto_ventana = _alto_ventana;
}

int igvInterfaz::getCont() const {
    return cont;
}

void igvInterfaz::setCont(int cont) {
    igvInterfaz::cont = cont;
}
