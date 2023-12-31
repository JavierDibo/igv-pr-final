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
        _instancia = new igvInterfaz();
    }

    return *_instancia;
}

igvInterfaz::igvInterfaz() {
    menuSelection = escena.EscenaA;
    escena.setCamara(&camara);
}

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

    create_menu();

    glEnable(GL_DEPTH_TEST); // activa el ocultamiento de superficies por z-buffer
    glClearColor(1.0, 1.0, 1.0, 0.0); // establece el color de fondo de la ventana

    glEnable(GL_LIGHTING); // activa la iluminacion de la escena
    glEnable(GL_NORMALIZE); // normaliza los vectores normales para calculo iluminacion

    crear_mundo(); // crea el mundo a renderEscenaA en la ventana
}                                                                                                                /**
 * Crea un men� asociado al bot�n derecho del rat�n
 */
void igvInterfaz::create_menu() {
    int menu_id = glutCreateMenu(menuHandle);
    glutAddMenuEntry(_instancia->escena.Nombre_EscenaA, _instancia->escena.EscenaA);
    glutAddMenuEntry(_instancia->escena.Nombre_EscenaB, _instancia->escena.EscenaB);
    glutAddMenuEntry(_instancia->escena.Nombre_EscenaC, _instancia->escena.EscenaC);
    glutAddMenuEntry(_instancia->escena.Nombre_EscenaD, _instancia->escena.EscenaD);

    glutAttachMenu(GLUT_RIGHT_BUTTON);
}                                                                                                                   /**
 * M�todo para gestionar la selecci�n de opciones de men�
 * @param value Nueva opci�n seleccionada
 * @pre Se asume que el valor del par�metro es correcto
 * @post Se almacena en el objeto la opci�n seleccionada
 */
void igvInterfaz::menuHandle(int value) {
    _instancia->menuSelection = value;
    glutPostRedisplay(); // renew the content of the window
}


/**
 * Crea el mundo que se visualiza en la ventana
 */
void igvInterfaz::crear_mundo() {  // inicia la c�mara
    _instancia->camara.set(IGV_PARALELA, {5, 5, 0}, {0, 0, 0}, {0, 1.0, 0}, -1 * 5, 1 * 5, -1 * 5, 1 * 5, -1 * 3,
                           200);
}

/**
 * M�todo para renderEscenaA la escena y esperar a eventos sobre la interfaz
 */
void igvInterfaz::inicia_bucle_visualizacion() {
    glutMainLoop(); // inicia el bucle de visualizaci�n de GLUT
}

/**
 * Modifica la posici�n y color de la iluminaci�n en la escena.
 * Esta funci�n ajusta la posici�n y el color difuso de una luz (GL_LIGHT0) bas�ndose
 * en una variable interna 'pos_luz' que determina la configuraci�n actual de la luz.
 * La funci�n alterna entre diferentes configuraciones de luz, cambiando tanto la
 * posici�n como el color de la misma.
 *
 * Dentro de la funci�n, se utiliza una declaraci�n switch para modificar los valores
 * de posici�n y color difuso de la luz seg�n el valor de 'pos_luz'. Despu�s de ajustar
 * estos valores, se aplican a la luz mediante llamadas a glLightfv y se habilita la
 * iluminaci�n y GL_LIGHT0.
 *
 * @pre 'pos_luz' debe estar inicializado y dentro del rango de los casos definidos.
 * @post La posici�n y el color de GL_LIGHT0 se actualizan, y la iluminaci�n se activa.
 *       El valor de 'pos_luz' se incrementa para la pr�xima llamada.
 */
void igvInterfaz::mover_luces() {

    GLfloat light_position[4] = {1.0, 1.0, 1.0, 1.0};
    GLfloat light_diffuse[4] = {1.0, 1.0, 1.0, 1.0};
    GLfloat light_ambient[4] = {1.0, 1.0, 1.0, 1.0};
    GLfloat light_specular[4] = {1.0, 1.0, 1.0, 1.0};

    // Cambia el color de la luz seg�n la habitaci�n
    switch (pos_luz) {
        case 1:
            std::cout << "1 ";
            light_diffuse[0] = 0.0; // Rojo
            light_diffuse[1] = 1.0; // Verde
            light_diffuse[2] = 1.0; // Azul
            light_position[0] = 0;
            light_position[1] = 0;
            light_position[2] = 0;
            break;
        case 2:
            std::cout << "2 ";
            light_diffuse[0] = 1.0;
            light_diffuse[1] = 0.0;
            light_diffuse[2] = 0.0;
            light_position[0] = 5;
            light_position[1] = -5;
            light_position[2] = 0;
            break;
        case 3:
            std::cout << "3 ";
            light_diffuse[0] = 1.0;
            light_diffuse[1] = 1.0;
            light_diffuse[2] = 0.0;
            light_position[0] = 30;
            light_position[1] = 5;
            light_position[2] = 5;
            break;
        case 4: // Verde claro
            std::cout << "4 ";
            light_diffuse[0] = 1.0;
            light_diffuse[1] = 0.0;
            light_diffuse[2] = 1.0;
            light_position[0] = 0;
            light_position[1] = 5;
            light_position[2] = 0;
            break;
        default:
            std::cout << "def ";
            light_diffuse[0] = 1.0;
            light_diffuse[1] = 1.0;
            light_diffuse[2] = 1.0;
            light_position[0] = 5;
            light_position[1] = 5;
            light_position[2] = 5;
            break;
    }

    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    _instancia->pos_luz = (_instancia->pos_luz + 1) % NUM_POSICIONES_LUZ;
}

/**
 * Cambia la posici�n de la c�mara y actualiza su configuraci�n.
 * Esta funci�n modifica la posici�n actual de la c�mara bas�ndose en el valor de
 * 'posicion_camara' de la instancia. La posici�n de la c�mara se actualiza y se
 * recalculan los par�metros de la misma seg�n su tipo actual (paralela, frustum o
 * perspectiva).
 *
 * Primero, la funci�n incrementa y ajusta el valor de 'posicion_camara' y calcula
 * una nueva posici�n para la c�mara. Luego, obtiene el tipo actual de la c�mara y
 * ajusta sus par�metros manteniendo el tipo de proyecci�n actual. Finalmente, aplica
 * los cambios a la c�mara.
 *
 * @pre 'posicion_camara' debe estar inicializada y debe ser un valor v�lido dentro
 *      del rango de posiciones definidas por NUM_POSICIONES_CAMARA.
 * @post La c�mara se mueve a una nueva posici�n y se actualizan sus par�metros
 *       seg�n el tipo de proyecci�n que tenga actualmente.
 */
void igvInterfaz::mover_camara() {
    double num;
    _instancia->posicion_camara = (_instancia->posicion_camara + 1) % NUM_POSICIONES_CAMARA;
    num = _instancia->posicion_camara * 3;

    igvPunto3D P0 = {5, 5, 0 + num};
    igvPunto3D r = {0, 0, 0 + num};
    igvPunto3D V = {0, 1, 0};

    // Obtener el tipo actual de la c�mara
    tipoCamara tipoActual = _instancia->camara.getTipo();

    // Configurar la c�mara manteniendo el tipo actual
    if (tipoActual == IGV_PARALELA || tipoActual == IGV_FRUSTUM) {
        // Mantener los par�metros de proyecci�n actuales
        double xwmin, xwmax, ywmin, ywmax, znear, zfar;
        _instancia->camara.getProyeccionParalelaFrustum(xwmin, xwmax, ywmin, ywmax, znear, zfar);
        _instancia->camara.set(tipoActual, P0, r, V, xwmin, xwmax, ywmin, ywmax, znear, zfar);
    } else if (tipoActual == IGV_PERSPECTIVA) {
        // Mantener los par�metros de proyecci�n actuales para perspectiva
        double angulo, raspecto, znear, zfar;
        _instancia->camara.getProyeccionPerspectiva(angulo, raspecto, znear, zfar);
        _instancia->camara.set(tipoActual, P0, r, V, angulo, raspecto, znear, zfar);
    }

    // Aplicar los cambios
    _instancia->camara.aplicar();
}

void igvInterfaz::camara_D() {
    if (_instancia->menuSelection == 4) {
        _instancia->camara.set(IGV_FRUSTUM, {-5, 5, -5}, {3, 3, 3}, {0, 1.0, 0}, -5, 5, -5, 5, 2, 200);
    }
}

/**
 * Maneja las entradas del teclado para interactuar con la escena.
 * Esta funci�n responde a diversas teclas presionadas por el usuario, activando
 * diferentes funcionalidades como mover la c�mara, cambiar luces, ajustar la
 * perspectiva de la c�mara, aplicar zoom y otras interacciones.
 *
 * Cada tecla presionada ('t', 'r', 'l', 'k', 'z', 'Z', etc.) est� asociada con
 * una acci�n espec�fica. Por ejemplo, 't' cambia a una c�mara espec�fica, 'r' y 'l'
 * mueven la c�mara y las luces respectivamente, 'k' cambia el tipo de c�mara, y
 * 'z'/'Z' aplican zoom. Las teclas 'w', 'a', 's', 'd' ajustan la posici�n de la
 * escena, y 'e' activa o desactiva la visualizaci�n de los ejes. La tecla 'c'/'C'
 * ajusta el �ngulo de la cabeza, y 'p' controla el movimiento de las piernas.
 * La tecla de escape (27) se utiliza para salir del programa.
 *
 * @param key Tecla presionada.
 * @param x Posici�n horizontal del cursor en el momento de la pulsaci�n.
 * @param y Posici�n vertical del cursor en el momento de la pulsaci�n.
 * @post Dependiendo de la tecla presionada, se ejecutan diferentes acciones que
 *       afectan a la c�mara, las luces, la escena, o terminan el programa.
 */
void igvInterfaz::keyboardFunc(unsigned char key, int x, int y) {

    switch (key) {
        // Cuando se cambia a la vista 4 (escena final) se usa para establecer una camara que mire a los objetos
        case 't':
            _instancia->camara_D();
            break;
            // Mueve la camara hacia la derecha 5 veces de forma ciclica
        case 'r':
            _instancia->mover_camara();
            break;
            // Mueve una luz hacia la derecha 5 veces de forma ciclica
        case 'l':
            _instancia->mover_luces();
            break;
            // cambia la pespectiva de la camara
        case 'k':
            _instancia->camara.cambiar_tipo_camara();
            break;
            // zoom
        case 'z':
            _instancia->camara.zoom(-5);
            break;
        case 'Z':
            _instancia->camara.zoom(5);
            break;
        case 'e': // activa/desactiva la visualizacion de los ejes
            _instancia->escena.set_ejes(!_instancia->escena.get_ejes());
            break;
        case 27: // tecla de escape para SALIR
            exit(1);
            break;
        case 'c':
            _instancia->escena.setAngCabeza(_instancia->escena.getAngCabeza() + 3);
            break;
        case 'C':
            _instancia->escena.setAngCabeza(_instancia->escena.getAngCabeza() - 3);
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

                // _instancia->escena.setAngBrazoD(_instancia->escena.getAngBrazoD() - 1);
                // _instancia->escena.setAngBrazoI(_instancia->escena.getAngBrazoI() - 1);
            } else {
                _instancia->escena.setAngPiernaD(_instancia->escena.getAngPiernaD() + 1);
                _instancia->escena.setAngPiernaI(_instancia->escena.getAngPiernaI() - 1);

                // _instancia->escena.setAngBrazoD(_instancia->escena.getAngBrazoD() + 1);
                // _instancia->escena.setAngBrazoI(_instancia->escena.getAngBrazoI() + 1);
            }
        case 'd':
            _instancia->escena.setPos(_instancia->escena.getPos() - 0.2);
            break;
        case 'a':
            _instancia->escena.setPos(_instancia->escena.getPos() + 0.2);
            break;
        case 'w':
            _instancia->escena.setPos2(_instancia->escena.getPos2() - 0.2);
            break;
        case 's':
            _instancia->escena.setPos2(_instancia->escena.getPos2() + 0.2);
            break;
    }
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
 * M�todo para renderizar la escena
 */
void igvInterfaz::displayFunc() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // borra la ventana y el z-buffer
    // se establece el viewport
    glViewport(0, 0, _instancia->get_ancho_ventana(), _instancia->get_alto_ventana());

    // aplica las transformaciones en funci�n de los par�metros de la c�mara
    _instancia->camara.aplicar();
    // visualiza la escena
    _instancia->escena.visualizar(_instancia->menuSelection);

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
 * M�todo para animar la grua
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
    if ((profundidadCable + PROFUNDIDAD_MAX * scale) >= PROFUNDIDAD_MAX)
        return;

    profundidadCable += PROFUNDIDAD_MAX * scale;
}

void igvEscena3D::reducir_profundidad_cable(double scale) {
    if (profundidadCable - PROFUNDIDAD_MAX * scale < 0.3)
        return;

    profundidadCable -= PROFUNDIDAD_MAX * scale;
}

void igvEscena3D::aumentar_altura_cable(double scale) {
    if ((largoCable + ALTURA_MAX * scale) > ALTURA_MAX)
        return;

    largoCable += ALTURA_MAX * scale;
}

void igvEscena3D::reducir_altura_cable(double scale) {
    if ((largoCable - ALTURA_MAX * scale) < 0.5)
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