#include <stdio.h>
#include <math.h>

#include "igvPunto3D.h"

// Constructores
/**
 * Constructor parametrizado
 * @param x Coordenada X del punto/vector
 * @param y Coordenada Y del punto/vector
 * @param z Coordenada Z del punto/vector
 * @post Las coordenadas del nuevo punto/vector serán las que se pasan como parámetro
 */
igvPunto3D::igvPunto3D(const double &x, const double &y, const double &z) :
        c{x, y, z} {}

/**
 * Constructor de copia
 * @param p Punto/vector del que se copian las coordenadas
 * @post Las coordenadas del nuevo punto/vector serán iguales a las del original
 */
igvPunto3D::igvPunto3D(const igvPunto3D &p) : c{p.c[X], p.c[Y], p.c[Z]} {}

/**
 * Operador de asignación
 * @param p Punto/vector del que se copian las coordenadas
 * @return El propio punto/vector modificado
 * @post Las coordenadas del punto/vector pasan a ser las mismas del original
 */
igvPunto3D &igvPunto3D::operator=(const igvPunto3D &p) {
    c[X] = p.c[X];
    c[Y] = p.c[Y];
    c[Z] = p.c[Z];
    return *this;
}

/**
 * Operador de igualdad
 * @param p Punto/vector con el que se compara
 * @retval true Si el punto/vector es igual al que se pasa como parámetro, con
 *         una tolerancia dada por IGV_EPSILON
 */
bool igvPunto3D::operator==(const igvPunto3D &p) {
    return ((fabs(c[X] - p[X]) < IGV_EPSILON)
            && (fabs(c[Y] - p[Y]) < IGV_EPSILON)
            && (fabs(c[Z] - p[Z]) < IGV_EPSILON)
    );
}

/**
 * Operador distinto
 * @param p Punto/vector con el que se compara
 * @retval true Si el punto/vector es distinto al que se pasa como parámetro, con
 *         una tolerancia dada por IGV_EPSILON
 */
bool igvPunto3D::operator!=(const igvPunto3D &p) {
    return ((fabs(c[X] - p[X]) >= IGV_EPSILON)
            || (fabs(c[Y] - p[Y]) >= IGV_EPSILON)
            || (fabs(c[Z] - p[Z]) >= IGV_EPSILON)
    );
}

/**
 * Asignación de las tres coordenadas del punto/vector
 * @param x Valor para la coordenada X
 * @param y Valor para la coordenada Y
 * @param z Valor para la coordenada Z
 * @post Las coordenadas del punto/vector cambian a las que se pasan como
 *       parámetro
 */
void igvPunto3D::set(const double &x, const double &y, const double &z) {
    c[X] = x;
    c[Y] = y;
    c[Z] = z;
}

