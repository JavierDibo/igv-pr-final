#include <cstdlib>
#include <stdio.h>
#include <random>

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

igvInterfaz::igvInterfaz() : menuSelection(escena.EscenaA) {}

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

    create_menu();

    glEnable(GL_DEPTH_TEST); // activa el ocultamiento de superficies por z-buffer
    glClearColor(1.0, 1.0, 1.0, 0.0); // establece el color de fondo de la ventana

    glEnable(GL_LIGHTING); // activa la iluminacion de la escena
    glEnable(GL_NORMALIZE); // normaliza los vectores normales para calculo iluminacion

    crear_mundo(); // crea el mundo a renderEscenaA en la ventana
}                                                                                                                /**
 * Crea un menú asociado al botón derecho del ratón
 */
void igvInterfaz::create_menu() {
    int menu_id = glutCreateMenu(menuHandle);
    glutAddMenuEntry(_instancia->escena.Nombre_EscenaA, _instancia->escena.EscenaA);
    glutAddMenuEntry(_instancia->escena.Nombre_EscenaB, _instancia->escena.EscenaB);
    glutAddMenuEntry(_instancia->escena.Nombre_EscenaC, _instancia->escena.EscenaC);

    glutAttachMenu(GLUT_RIGHT_BUTTON);
}                                                                                                                   /**
 * Método para gestionar la selección de opciones de menú
 * @param value Nueva opción seleccionada
 * @pre Se asume que el valor del parámetro es correcto
 * @post Se almacena en el objeto la opción seleccionada
 */
void igvInterfaz::menuHandle(int value) {
    _instancia->menuSelection = value;
    glutPostRedisplay(); // renew the content of the window
}


/**
 * Crea el mundo que se visualiza en la ventana
 */
void igvInterfaz::crear_mundo() {  // inicia la cámara
    _instancia->camara.set(IGV_PARALELA, {5, 5, 0}, {0, 0, 0}, {0, 1.0, 0}, -1 * 5, 1 * 5, -1 * 5, 1 * 5, -1 * 3,
                           200);
}

/**
 * Método para renderEscenaA la escena y esperar a eventos sobre la interfaz
 */
void igvInterfaz::inicia_bucle_visualizacion() {
    glutMainLoop(); // inicia el bucle de visualización de GLUT
}

void igvInterfaz::mover_luces() {

    GLfloat light_position[4] = {1.0, 1.0, 1.0, 1.0};
    GLfloat light_diffuse[4] =  {1.0, 1.0, 1.0, 1.0};
    GLfloat light_ambient[4] = {1.0, 1.0, 1.0, 1.0};
    GLfloat light_specular[4] = {1.0, 1.0, 1.0, 1.0};

    // Cambia el color de la luz según la habitación
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

void igvInterfaz::mover_camara() {
    double num;
    _instancia->posicion_camara = (_instancia->posicion_camara + 1) % NUM_POSICIONES_CAMARA;
    num = _instancia->posicion_camara * 3;

    igvPunto3D P0 = {5, 5, 0 + num};
    igvPunto3D r = {0, 0, 0 + num};
    igvPunto3D V = {0, 1, 0};

    // Obtener el tipo actual de la cámara
    tipoCamara tipoActual = _instancia->camara.getTipo();

    // Configurar la cámara manteniendo el tipo actual
    if (tipoActual == IGV_PARALELA || tipoActual == IGV_FRUSTUM) {
        // Mantener los parámetros de proyección actuales
        double xwmin, xwmax, ywmin, ywmax, znear, zfar;
        _instancia->camara.getProyeccionParalelaFrustum(xwmin, xwmax, ywmin, ywmax, znear, zfar);
        _instancia->camara.set(tipoActual, P0, r, V, xwmin, xwmax, ywmin, ywmax, znear, zfar);
    } else if (tipoActual == IGV_PERSPECTIVA) {
        // Mantener los parámetros de proyección actuales para perspectiva
        double angulo, raspecto, znear, zfar;
        _instancia->camara.getProyeccionPerspectiva(angulo, raspecto, znear, zfar);
        _instancia->camara.set(tipoActual, P0, r, V, angulo, raspecto, znear, zfar);
    }

    // Aplicar los cambios
    _instancia->camara.aplicar();
}

void igvInterfaz::mover_luz(int num_pasos) {
    GLfloat **luz = _instancia->escena.luz_principal;

    double distancia = 5;
    double delta = distancia / num_pasos;

    for (int i = 0; i < num_pasos; ++i) {
        *luz[0] = *luz[0] + delta;
        // *luz[1] = *luz[1] + delta;
        // *luz[2] = *luz[2] + delta;
        Sleep(50);
    }
}

void igvInterfaz::keyboardFunc(unsigned char key, int x, int y) {

    switch (key) {
        case 'r':
            _instancia->mover_camara();
            break;
        case 'l':
            _instancia->mover_luces();
            break;
        case 'k':
            _instancia->camara.cambiar_tipo_camara();
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
    printf("Posicion: %d\n", _instancia->posicion_camara);
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
 * Método para renderEscenaA la escena
 */
void igvInterfaz::displayFunc() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // borra la ventana y el z-buffer
    // se establece el viewport
    glViewport(0, 0, _instancia->get_ancho_ventana(), _instancia->get_alto_ventana());

    // aplica las transformaciones en función de los parámetros de la cámara
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
 * Método para animar la escena
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