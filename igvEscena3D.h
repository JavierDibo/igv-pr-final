#ifndef __IGVESCENA3D
#define __IGVESCENA3D

#if defined(__APPLE__) && defined(__MACH__)
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else

#include <GL/glut.h>

#endif // defined(__APPLE__) && defined(__MACH__)

/**
 * Partes del modelo
 */
enum parte
{	basex   ///< Identifica la base del modelo
   , cuerpoinferior   ///< Identifica el cuerpo inferior del modelo
   , cuerposuperior   ///< Identifica el cuerpo superior del modelo
   , brazo   ///< Identifica el brazo del modelo
};

/**
 * Los objetos de esta clase representan escenas 3D para su visualizaci�n
 */
class igvEscena3D
{  private:
      // Atributos
	   // TODO: Apartado C: a�adir qu� los atributos para el control de los grados de libertad del modelo

      int angCabeza;
      int angPiernaI;
      int angPiernaD;
      int angBrazoI;
      int angBrazoD;

	   // Otros atributos
      bool ejes = true;   ///< Indica si hay que dibujar los ejes coordenados o no

   public:

      // Constructores por defecto y destructor
      igvEscena3D();
      ~igvEscena3D();

      // m�todo con las llamadas OpenGL para visualizar la escena
      void visualizar();

      // TODO: Apartado B: M�todos para visualizar cada parte del modelo

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
      void visualizarModelo();

      // TODO: Apartado C: a�adir aqu� los m�todos para modificar los grados de libertad del modelo

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


    bool get_ejes ();
      void set_ejes ( bool _ejes );

   private:
      void pintar_ejes ();

};

#endif   // __IGVESCENA3D
