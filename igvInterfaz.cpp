#include <cstdlib>
#include <stdio.h>
#include <random>

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

void igvInterfaz::mover_luz() {
    _instancia->posicion_luz = (_instancia->posicion_luz + 1) % NUM_POSICIONES_CAMARA;
}


void igvInterfaz::keyboardFunc(unsigned char key, int x, int y) {

    switch (key) {
        case 'r':
            _instancia->mover_camara();
            break;
        case 'l':
            _instancia->mover_luz();
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
    _instancia->escena.visualizar(_instancia->posicion_luz);

    // refresca la ventana
    glutSwapBuffers();
}

enum EstadoAnimacion {
    ROTANDO_IZQUIERDA,
    ROTANDO_DERECHA,
    SUBIR,
    BAJAR,
    LEJOS,
    CERCA
};

static EstadoAnimacion estado_actual = ROTANDO_IZQUIERDA;
static int ultimo_tiempo = 0;
static float tiempo_pasado_en_estado = 0.0f;
static std::mt19937 random(1234);
static std::uniform_real_distribution<float> tiempo(0.0f, 5.0f);
static float tiempo_random = tiempo(random);
/**
 * M�todo para animar la escena
 */
void igvInterfaz::idleFunc() {
    int tiempo_actual = glutGet(GLUT_ELAPSED_TIME);
    int delta_tiempo = tiempo_actual - ultimo_tiempo;

    // Convert delta time to seconds for easier calculations
    tiempo_pasado_en_estado += delta_tiempo / 1000.0f;


    switch (estado_actual) {
        case ROTANDO_IZQUIERDA:
            if (tiempo_pasado_en_estado <= tiempo_random) {
                _instancia->escena.rotar_izquierda(delta_tiempo / 5000.0f);
            } else {
                estado_actual = CERCA;
                tiempo_pasado_en_estado = 0.0f;
                tiempo_random = tiempo(random);
            }
            break;

        case CERCA:
            if (tiempo_pasado_en_estado <= tiempo_random) {
                _instancia->escena.reducir_profundidad_cable(delta_tiempo / 3000.0f);
            } else {
                estado_actual = SUBIR;
                tiempo_pasado_en_estado = 0.0f;
                tiempo_random = tiempo(random);
            }
            break;

        case SUBIR:
            if (tiempo_pasado_en_estado <= 2.0f) {
                _instancia->escena.aumentar_altura_cable(delta_tiempo / 2000.0f);
            } else {
                estado_actual = ROTANDO_DERECHA;
                tiempo_pasado_en_estado = 0.0f;
            }
            break;
        case ROTANDO_DERECHA:
            if (tiempo_pasado_en_estado <= tiempo_random) {
                _instancia->escena.rotar_derecha(delta_tiempo / 5000.0f);
            } else {
                estado_actual = LEJOS;
                tiempo_pasado_en_estado = 0.0f;
                tiempo_random = tiempo(random);
            }
            break;
        case LEJOS:
            if (tiempo_pasado_en_estado <= tiempo_random) {
                _instancia->escena.aumentar_profundidad_cable(delta_tiempo / 3000.0f);
            } else {
                estado_actual = BAJAR;
                tiempo_pasado_en_estado = 0.0f;
                tiempo_random = tiempo(random);
            }
            break;
        case BAJAR:
            if (tiempo_pasado_en_estado <= 2.0f) {
                _instancia->escena.reducir_altura_cable(delta_tiempo / 2000.0f);
            } else {
                estado_actual = ROTANDO_IZQUIERDA;
                tiempo_pasado_en_estado = 0.0f;
            }
            break;
    }

    ultimo_tiempo = tiempo_actual;
    glutPostRedisplay();
}

void igvEscena3D::rotar_izquierda(double scale) {
    anguloColumna -= ANGULO_MAX * scale;
}

void igvEscena3D::rotar_derecha(double scale) {
    anguloColumna += ANGULO_MAX * scale;
}

void igvEscena3D::aumentar_profundidad_cable(double scale) {
    if ( (profundidadCable + PROFUNDIDAD_MAX * scale) >= PROFUNDIDAD_MAX)
        return;

    profundidadCable += PROFUNDIDAD_MAX * scale;
}

void igvEscena3D::reducir_profundidad_cable(double scale) {
    if (profundidadCable - PROFUNDIDAD_MAX * scale < 0.3)
        return;

    profundidadCable -= PROFUNDIDAD_MAX * scale;
}

void igvEscena3D::aumentar_altura_cable(double scale) {
    if ( (largoCable + ALTURA_MAX * scale) > ALTURA_MAX)
        return;

    largoCable += ALTURA_MAX * scale;
}

void igvEscena3D::reducir_altura_cable(double scale) {
    if ( (largoCable - ALTURA_MAX * scale) < 0.5)
        return;

    largoCable -= ALTURA_MAX * scale;
}

void igvEscena3D::rotar_izquierda() {
    anguloColumna -= 5;
}

void igvEscena3D::rotar_derecha() {
    anguloColumna += 5;
}

void igvEscena3D::aumentar_profundidad_cable() {
    if (profundidadCable + 0.2 >= 3.5)
        return;

    profundidadCable += 0.2;
}

void igvEscena3D::reducir_profundidad_cable() {
    if (profundidadCable - 0.2 <= 0)
        return;

    profundidadCable -= 0.2;
}

void igvEscena3D::aumentar_altura_cable() {
    if (largoCable + 0.2 > 3.5)
        return;

    largoCable += 0.2;
}

void igvEscena3D::reducir_altura_cable() {
    if (largoCable - 0.2 < 0)
        return;

    largoCable -= 0.2;
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
