#ifndef __IGVESCENA3D
#define __IGVESCENA3D

#if defined(__APPLE__) && defined(__MACH__)
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else

#include <GL/glut.h>

#endif // defined(__APPLE__) && defined(__MACH__)

#include <cmath>

/**
 * Partes del modelo
 */
enum parte {
    basex   ///< Identifica la base del modelo
    , cuerpoinferior   ///< Identifica el cuerpo inferior del modelo
    , cuerposuperior   ///< Identifica el cuerpo superior del modelo
    , brazo   ///< Identifica el brazo del modelo
};

/**
 * Los objetos de esta clase representan escenas 3D para su visualización
 */
class igvEscena3D {
private:
    // Atributos
    // TODO: Apartado C: añadir quí los atributos para el control de los grados de libertad del modelo

    int angCabeza;
    int angPiernaI;
    int angPiernaD;
    int angBrazoI;
    int angBrazoD;
    float anguloColumna = 0.0;
    float profundidadCable = 1;
    float largoCable = 2;

    // Otros atributos
    bool ejes = true;   ///< Indica si hay que dibujar los ejes coordenados o no

public:

    // Constructores por defecto y destructor
    igvEscena3D();

    ~igvEscena3D();

    // método con las llamadas OpenGL para visualizar la escena
    void visualizar();

    // TODO: Apartado B: Métodos para visualizar cada parte del modelo

    void base();

    void pierna();

    void cuerpo();

    void cabeza();

    void mano();

    void visualizarPiernaIzq();

    void visualizarPiernaDer();

    void visualizarCuerpo();

    void visualizarBrazoIzq();

    void visualizarBrazoDer();

    void visualizarCabeza();

    void visualizarMunneco();

    // TODO: Apartado C: añadir aquí los métodos para modificar los grados de libertad del modelo

    void rotarCabeza(int ang);

    void rotarPiernaD(int ang);

    void rotarPiernaI(int ang);

    void rotarBrazoD(int ang);

    void rotarBrazoI(int ang);

    int getAngCabeza() const;

    void setAngCabeza(int angCabeza);

    int getAngPiernaD() const;

    void setAngPiernaD(int angPiernaD);

    int getAngPiernaI() const;

    void setAngPiernaI(int angPiernaI);

    int getAngBrazoI() const;

    void setAngBrazoI(int angBrazoI);

    int getAngBrazoD() const;

    void setAngBrazoD(int angBrazoD);

    bool get_ejes();

    void set_ejes(bool _ejes);

    void visualizarBase();

    void visualizarCuadrado();

    void pintar_ejes();

    void generarBases();

    void visualizarEstructura(int num);

    void visualizarBaseGrua();

    void visualizarColumna(const float *punto_partida, const float *centro_anterior);

    void visualizarBrazo(const float *punto_partida, const float *centro_anterior);

    void visualizarCable(const float punto_partida[3], const float centro_anterior[3]);

    void rotateY(const float *point, float angle, float *result);

    void rotar_izquierda(double scale);

    void reducir_altura_cable();

    void aumentar_altura_cable();

    void reducir_profundidad_cable();

    void aumentar_profundidad_cable();

    void rotar_derecha();

    void rotar_izquierda();

    void aumentar_altura_cable(double scale);

    void reducir_altura_cable(double scale);

    void reducir_profundidad_cable(double scale);

    void aumentar_profundidad_cable(double scale);

    void rotar_derecha(double scale);
};

#endif   // __IGVESCENA3D
