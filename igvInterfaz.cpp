#include <cstdlib>
#include <stdio.h>

#include "igvInterfaz.h"

// Aplicaci�n del patr�n de dise�o Singleton
igvInterfaz *igvInterfaz::_instancia = nullptr;

// M�todos p�blicos ----------------------------------------

/**
 * M�todo para acceder al objeto �nico de la clase, en aplicaci�n del patr�n de
 * dise�o Singleton
 * @return Una referencia al objeto �nico de la clase
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
void igvInterfaz::crear_mundo() {  // inicia la c�mara
    _instancia->camara.set(IGV_PARALELA, {5, 5, 0}, {0, 0, 0}, {0, 1.0, 0}, -1 * 5, 1 * 5, -1 * 5, 1 * 5, -1 * 3,
                           200);
}

/**
 * Inicializa todos los par�metros para crear una ventana de visualizaci�n
 * @param argc N�mero de par�metros por l�nea de comandos al ejecutar la
 *             aplicaci�n
 * @param argv Par�metros por l�nea de comandos al ejecutar la aplicaci�n
 * @param _ancho_ventana Ancho inicial de la ventana de visualizaci�n
 * @param _alto_ventana Alto inicial de la ventana de visualizaci�n
 * @param _pos_X Coordenada X de la posici�n inicial de la ventana de
 *               visualizaci�n
 * @param _pos_Y Coordenada Y de la posici�n inicial de la ventana de
 *               visualizaci�n
 * @param _titulo T�tulo de la ventana de visualizaci�n
 * @pre Se asume que todos los par�metros tienen valores v�lidos
 * @post Cambia el alto y ancho de ventana almacenado en el objeto
 */
void
igvInterfaz::configura_entorno(int argc, char **argv, int _ancho_ventana, int _alto_ventana, int _pos_X, int _pos_Y,
                               std::string _titulo) {  // inicializaci�n de las variables de la interfaz
    ancho_ventana = _ancho_ventana;
    alto_ventana = _alto_ventana;

    // inicializaci�n de la ventana de visualizaci�n
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
 * M�todo para visualizar la escena y esperar a eventos sobre la interfaz
 */
void igvInterfaz::inicia_bucle_visualizacion() {
    glutMainLoop(); // inicia el bucle de visualizaci�n de GLUT
}

void igvInterfaz::mover_camara() {
    int num;
    _instancia->posicion_camara = (_instancia->posicion_camara + 1) % NUM_POSICIONES_CAMARA;
    num = _instancia->posicion_camara * 3;

    igvPunto3D P0 = {5, 5, 0 + num};
    igvPunto3D r = {0, 0, 0 + num};
    igvPunto3D V = {0, 1, 0};

    _instancia->camara.set(IGV_PARALELA, P0, r, V, -1 * 5, 1 * 5, -1 * 5, 1 * 5, -1 * 3,
                           200);
}

void igvInterfaz::keyboardFunc(unsigned char key, int x, int y) {

    switch (key) {
        case 'r':
            _instancia->mover_camara();
            break;
        case 'z':
            _instancia->camara.zoom(-2);
            break;
        case 'Z':
            _instancia->camara.zoom(2);
            break;
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
    printf("Posicion: %d\n", _instancia->posicion_camara);
    glutPostRedisplay(); // renueva el contenido de la ventana de vision
}

/**
 * M�todo que define la c�mara de visi�n y el viewport. Se llama autom�ticamente
 * cuando se cambia el tama�o de la ventana.
 * @param w Nuevo ancho de la ventana
 * @param h Nuevo alto de la ventana
 * @pre Se asume que todos los par�metros tienen valores v�lidos
 */
void igvInterfaz::reshapeFunc(int w, int h) {  // dimensiona el viewport al nuevo ancho y alto de la ventana
    // guardamos valores nuevos de la ventana de visualizacion
    _instancia->set_ancho_ventana(w);
    _instancia->set_alto_ventana(h);

    // establece los par�metros de la c�mara y de la proyecci�n
    _instancia->camara.aplicar();
}

/**
 * M�todo para visualizar la escena
 */
void igvInterfaz::displayFunc() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // borra la ventana y el z-buffer
    // se establece el viewport
    glViewport(0, 0, _instancia->get_ancho_ventana(), _instancia->get_alto_ventana());


    // aplica las transformaciones en funci�n de los par�metros de la c�mara
    _instancia->camara.aplicar();
    // visualiza la escena
    _instancia->escena.visualizar();

    // refresca la ventana
    glutSwapBuffers();
}

/**
 * M�todo para animar la escena
 */
void
igvInterfaz::idleFunc() {  // TODO: Apartado D: incluir el c�digo para animar el modelo de la manera m�s realista posible
}

/**
 * M�todo para inicializar los callbacks GLUT
 */
void igvInterfaz::inicializa_callbacks() {
    glutKeyboardFunc(keyboardFunc);
    glutReshapeFunc(reshapeFunc);
    glutDisplayFunc(displayFunc);
    glutIdleFunc(idleFunc);
}

/**
 * M�todo para consultar el ancho de la ventana de visualizaci�n
 * @return El valor almacenado como ancho de la ventana de visualizaci�n
 */
int igvInterfaz::get_ancho_ventana() {
    return ancho_ventana;
}

/**
 * M�todo para consultar el alto de la ventana de visualizaci�n
 * @return El valor almacenado como alto de la ventana de visualizaci�n
 */
int igvInterfaz::get_alto_ventana() {
    return alto_ventana;
}

/**
 * M�todo para cambiar el ancho de la ventana de visualizaci�n
 * @param _ancho_ventana Nuevo valor para el ancho de la ventana de visualizaci�n
 * @pre Se asume que el par�metro tiene un valor v�lido
 * @post El ancho de ventana almacenado en la aplicaci�n cambia al nuevo valor
 */
void igvInterfaz::set_ancho_ventana(int _ancho_ventana) {
    ancho_ventana = _ancho_ventana;
}

/**
 * M�todo para cambiar el alto de la ventana de visualizaci�n
 * @param _alto_ventana Nuevo valor para el alto de la ventana de visualizaci�n
 * @pre Se asume que el par�metro tiene un valor v�lido
 * @post El alto de ventana almacenado en la aplicaci�n cambia al nuevo valor
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
