#ifndef __IGVCAMARA
#define __IGVCAMARA

#if defined(__APPLE__) && defined(__MACH__)
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else

#include <GL/glut.h>

#endif   // defined(__APPLE__) && defined(__MACH__)

#include "igvPunto3D.h"

#include <cmath>

/**
 * Vistas de cámara
 */
enum poscam {
    panoramica   ///< Vista desde un punto arbitrario
    , planta   ///< Vista de planta (cámara en el eje Y)
    , perfil   ///< Vista de perfil (cámara en el eje X)
    , alzado   ///< Vista de alzado (cámara en el eje Z)
};

/**
 * Etiquetas para los diferentes tipos de cámara
 */
enum tipoCamara {
    IGV_PARALELA   ///< Proyección paralela
    , IGV_FRUSTUM   ///< Proyección en perspectiva usando OpenGL
    , IGV_PERSPECTIVA   ///< Proyección en perspectiva usando GLU
};

/**
 * Los objetos de esta clase representan cámaras de visualización en la aplicación
 */
class igvCamara {
private:

    const double DEG_TO_RAD = M_PI / 180.0;
    // atributos
    poscam vis = panoramica;      ///< Posición de la cámara

    tipoCamara tipo = IGV_PARALELA;
public:
    tipoCamara getTipo() const;

private:
    ///< Tipo de la cámara

    // ventana de visión: parámetros proyección paralela y frustum
    GLdouble xwmin = -5    ///< Coordenada X mínima del frustum/proyección paralela
    , xwmax = 5   ///< Coordenada X máxima del frustum/proyección paralela
    , ywmin = -5   ///< Coordenada Y mínima del frustum/proyección paralela
    , ywmax = 5   ///< Coordenada Y máxima del frustum/proyección paralela
    ;

    // ventana de visión: parámetros proyección perspectiva
    GLdouble angulo = 60   ///< Ángulo de apertura (proyección perspectiva)
    , raspecto = 1   ///< Razón de aspecto (proyección perspectiva)
    ;

    // distancias de planos cercano y lejano
    GLdouble znear = 3    ///< Distancia de la cámara al plano Z near
    , zfar = 200 ///< Distancia de la cámara al plano Z far
    ;

    // punto de visión
    igvPunto3D P0 = {0, 4, 8};   ///< Posición de la cámara

    // punto de referencia de visión
    igvPunto3D r = {0, 0, 0};   ///< Punto al que mira la cámara

    // vector arriba
    igvPunto3D V = {0, 1, 0};   ///< Vector que indica la vertical

public:
    // Constructores por defecto y destructor
    /// Constructor por defecto
    igvCamara() = default;

    /// Destructor
    ~igvCamara() = default;

    // Otros constructores
    igvCamara(tipoCamara _tipo, igvPunto3D _P0, igvPunto3D _r, igvPunto3D _V);

    // Métodos
    // define la posición de la cámara
    void set(igvPunto3D _P0, igvPunto3D _r, igvPunto3D _V);

    // define una cámara de tipo paralela o frustum
    void
    set(tipoCamara _tipo, igvPunto3D _P0, igvPunto3D _r, igvPunto3D _V, double _xwmin, double _xwmax, double _ywmin,
        double _ywmax, double _znear, double _zfar);

    // define una cámara de tipo perspectiva
    void
    set(tipoCamara _tipo, igvPunto3D _P0, igvPunto3D _r, igvPunto3D _V, double _angulo, double _raspecto, double _znear,
        double _zfar);

    void aplicar(); // aplica a los objetos de la escena la transformación
    // de visión y la transformación de proyección
    // asociadas a los parámetros de la cámara
    void zoom(double factor); // realiza un zoom sobre la cámara

    const igvPunto3D &getP0() const;

    const igvPunto3D &getR() const;

    const igvPunto3D &getV() const;

    // Método para alternar entre los diferentes tipos de cámara
    void cambiar_tipo_camara();

    void
    getProyeccionParalelaFrustum(GLdouble &_xwmin, GLdouble &_xwmax, GLdouble &_ywmin, GLdouble &_ywmax,
                                 GLdouble &_znear,
                                 GLdouble &_zfar) const;

    void getProyeccionPerspectiva(GLdouble &_angulo, GLdouble &_raspecto, GLdouble &_znear, GLdouble &_zfar) const;
};

#endif   // __IGVCAMARA

