#ifndef __IGVPUNTO3D
#define __IGVPUNTO3D

#if defined(__APPLE__) && defined(__MACH__)
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else

#include <GL/glut.h>

#endif   // defined(__APPLE__) && defined(__MACH__)

#define IGV_EPSILON 0.000001 ///< Constante para comparaciones con 0

#ifndef __ENUM_XYZ
#define __ENUM_XYZ

/**
 * Etiquetas para las coordenadas del punto/vector
 */
enum Coordenadas {
    X   ///< Coordenada X
    , Y   ///< Coordenada Y
    , Z   ///< Coordenada Z
};
#endif   // __ENUM_XYZ

/**
 * Los objetos de esta clase representan puntos y vectores en 3D
 */
class igvPunto3D {
private:
    double c[3] = {0, 0, 0}; ///< Componentes x, y, z del punto o vector

public:
    // Constructores
    /// Constructor por defecto
    igvPunto3D() = default;

    igvPunto3D(const double &x, const double &y, const double &z);

    // Constructor de copia
    igvPunto3D(const igvPunto3D &p);

    // Operador de asignación
    igvPunto3D &operator=(const igvPunto3D &p);

    /// Destructor
    ~igvPunto3D() = default;

    // Operadores
    double &operator[](const unsigned char idx);

    double operator[](const unsigned char idx) const;

    bool operator==(const igvPunto3D &p);

    bool operator!=(const igvPunto3D &p);

    void set(const double &x, const double &y, const double &z);
};

/**
 * Acceso a una coordenada del punto/vector
 * @param idx Coordenada a la que se quiere acceder (0, 1 o 2)
 * @return La coordenada correspondiente
 * @pre Se asume que el valor del parámetro es correcto
 */
inline double &igvPunto3D::operator[](const unsigned char idx) {
    return c[idx];
}

/**
 * Acceso a una coordenada del punto/vector
 * @param idx Coordenada a la que se quiere acceder (0, 1 o 2)
 * @return La coordenada correspondiente
 * @pre Se asume que el valor del parámetro es correcto
 */
inline double igvPunto3D::operator[](const unsigned char idx) const {
    return c[idx];
}

#endif   // __IGVPUNTO3D

