#include <math.h>
#include <stdio.h>
#include <algorithm>

#include "igvCamara.h"

// M�todos constructores

/**
 * Constructor parametrizado
 * @param _tipo Tipo de c�mara (IGV_PARALELA, IGV_FRUSTUM o IGV_PERSPECTIVA)
 * @param _P0 Posici�n de la c�mara (punto de visi�n)
 * @param _r Punto al que mira la c�mara (punto de referencia)
 * @param _V Vector que indica la vertical
 * @pre Se asume que todos los par�metros tienen valores v�lidos
 * @post Los atributos de la nueva c�mara ser�n iguales a los par�metros que se
 *       le pasan
 */
igvCamara::igvCamara(tipoCamara _tipo, igvPunto3D _P0, igvPunto3D _r, igvPunto3D _V) : P0(_P0), r(_r), V(_V),
                                                                                       tipo(_tipo) {}

// M�todos p�blicos
/**
 * Define la posici�n de la c�mara
 * @param _P0 Posici�n de la c�mara (punto de visi�n)
 * @param _r Punto al que mira la c�mara (punto de referencia)
 * @param _V Vector que indica la vertical
 * @pre Se asume que todos los par�metros tienen valores v�lidos
 * @post Los atributos de la c�mara cambian a los valores pasados como par�metro
 */
void igvCamara::set(igvPunto3D _P0, igvPunto3D _r, igvPunto3D _V) {
    P0 = _P0;
    r = _r;
    V = _V;
}

/**
 * Define una c�mara de tipo paralela o frustum
 * @param _tipo Tipo de la c�mara (IGV_PARALELA o IGV_FRUSTUM)
 * @param _P0 Posici�n de la c�mara
 * @param _r Punto al que mira la c�mara
 * @param _V Vector que indica la vertical
 * @param _xwmin Coordenada X m�nima del frustum
 * @param _xwmax Coordenada X m�xima del frustum
 * @param _ywmin Coordenada Y m�nima del frustum
 * @param _ywmax Coordenada Y m�xima del frustum
 * @param _znear Distancia de la c�mara al plano Z near
 * @param _zfar Distancia de la c�mara al plano Z far
 * @pre Se asume que todos los par�metros tienen valores v�lidos
 * @post Los atributos de la c�mara cambian a los valores pasados como par�metro
 */
void igvCamara::set(tipoCamara _tipo, igvPunto3D _P0, igvPunto3D _r, igvPunto3D _V, double _xwmin, double _xwmax,
                    double _ywmin, double _ywmax, double _znear, double _zfar) {
    tipo = _tipo;

    P0 = _P0;
    r = _r;
    V = _V;

    xwmin = _xwmin;
    xwmax = _xwmax;
    ywmin = _ywmin;
    ywmax = _ywmax;
    znear = _znear;
    zfar = _zfar;
}

/**
 * Define una c�mara de tipo perspectiva
 * @param _tipo Tipo de la c�mara (IGV_PERSPECTIVA)
 * @param _P0 Posici�n de la c�mara
 * @param _r Punto al que mira la c�mara
 * @param _V Vector que indica la vertical
 * @param _angulo �ngulo de apertura
 * @param _raspecto Raz�n de aspecto
 * @param _znear Distancia de la c�mara al plano Z near
 * @param _zfar Distancia de la c�mara al plano Z far
 * @pre Se asume que todos los par�metros tienen valores v�lidos
 * @post Los atributos de la c�mara cambian a los valores que se pasan como
 *       par�metros
 */
void igvCamara::set(tipoCamara _tipo, igvPunto3D _P0, igvPunto3D _r, igvPunto3D _V, double _angulo, double _raspecto,
                    double _znear, double _zfar) {
    tipo = _tipo;

    P0 = _P0;
    r = _r;
    V = _V;

    angulo = _angulo;
    raspecto = _raspecto;
    znear = _znear;
    zfar = _zfar;
}

/**
 * Aplica a los objetos de la escena la transformaci�n de visi�n y la
 * transformaci�n de proyecci�n asociadas a los par�metros de la c�mara
 */
void igvCamara::aplicar() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if (tipo == IGV_PARALELA) {
        glOrtho(xwmin, xwmax, ywmin, ywmax, znear, zfar);
    }
    if (tipo == IGV_FRUSTUM) {
        glFrustum(xwmin, xwmax, ywmin, ywmax, znear, zfar);
    }
    if (tipo == IGV_PERSPECTIVA) {
        gluPerspective(angulo, raspecto, znear, zfar);
    }

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(P0[X], P0[Y], P0[Z], r[X], r[Y], r[Z], V[X], V[Y], V[Z]);
}

/**
 * Realiza un zoom sobre la c�mara
 * @param factor Factor (en tanto por 100) que se aplica al zoom. Si el valor es
 *        positivo, se aumenta el zoom. Si es negativo, se reduce.
 * @pre Se asume que el par�metro tiene un valor v�lido
 */
void igvCamara::zoom(double factor) {
    double aux = (100 - factor / 2) / 100;
    // En los casos de c�mara paralela y c�mara generada con frustum, hay que
    // aplicar el factor de zoom a las coordenadas de ventana de visi�n
    xwmin *= aux;
    xwmax *= aux;
    ywmin *= aux;
    ywmax *= aux;

    // En el caso de la c�mara perspectiva GLU, basta con aplicar el factor de
    // zoom al �ngulo de visi�n
    aux = (100 - factor) / 100;
    angulo *= aux;
}

const igvPunto3D &igvCamara::getP0() const {
    return P0;
}

const igvPunto3D &igvCamara::getR() const {
    return r;
}

const igvPunto3D &igvCamara::getV() const {
    return V;
}

/**
 * Cambia el tipo de c�mara entre diferentes modos disponibles.
 * Esta funci�n alterna la c�mara entre los modos paralela, frustum y perspectiva,
 * ajustando los par�metros necesarios para cada modo.
 *
 * La funci�n utiliza una declaraci�n switch para cambiar el tipo de c�mara basado
 * en su estado actual. Cada caso ajusta el tipo de c�mara y llama a la funci�n 'set'
 * con par�metros espec�ficos para cada tipo de c�mara. Al final, se llama a 'aplicar'
 * para implementar los cambios.
 *
 * @pre Se asume que el tipo de c�mara actual est� correctamente establecido en uno de los
 *      modos conocidos (IGV_PARALELA, IGV_FRUSTUM, o IGV_PERSPECTIVA).
 * @post La c�mara cambia a un tipo diferente, con los par�metros ajustados para ese tipo.
 */
void igvCamara::cambiar_tipo_camara() {
    switch (tipo) {
        case IGV_PARALELA:
            tipo = IGV_FRUSTUM;
            set(tipo, P0, r, V, -5, 5, -5, 5, 2, 200); // Valores para frustum
            break;
        case IGV_FRUSTUM:
            tipo = IGV_PERSPECTIVA;
            set(tipo, P0, r, V, 45, 16.0/9.0, 1, 1000); // Valores para perspectiva
            break;
        case IGV_PERSPECTIVA:
            tipo = IGV_PARALELA;
            set(tipo, P0, r, V, -10, 10, -10, 10, 1, 100); // Valores para paralela
            break;
        default:
            tipo = IGV_PARALELA;
            set(tipo, P0, r, V, -10, 10, -10, 10, 1, 100); // Valores predeterminados para paralela
            break;
    }

    aplicar(); // Aplicar los cambios
}

tipoCamara igvCamara::getTipo() const {
    return tipo;
}

void igvCamara::getProyeccionParalelaFrustum(GLdouble& _xwmin, GLdouble& _xwmax, GLdouble& _ywmin, GLdouble& _ywmax, GLdouble& _znear, GLdouble& _zfar) const {
    _xwmin = xwmin;
    _xwmax = xwmax;
    _ywmin = ywmin;
    _ywmax = ywmax;
    _znear = znear;
    _zfar = zfar;
}

void igvCamara::getProyeccionPerspectiva(GLdouble& _angulo, GLdouble& _raspecto, GLdouble& _znear, GLdouble& _zfar) const {
    _angulo = angulo;
    _raspecto = raspecto;
    _znear = znear;
    _zfar = zfar;
}