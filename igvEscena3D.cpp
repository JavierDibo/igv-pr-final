#include <cstdlib>
#include <stdio.h>

#include "igvEscena3D.h"

// Métodos constructores

/**
 * Constructor por defecto
 */
igvEscena3D::igvEscena3D ()
{  // TODO: Apartado C: inicializar los atributos para el control de los grados de libertad del modelo
    angCabeza = 0;
    angPiernaD = 0;
    angPiernaI = 0;
    angBrazoD = 0;
    angBrazoI = 0;
}

/**
 * Destructor
 */
igvEscena3D::~igvEscena3D ()
{
}

/**
 * Método para pintar los ejes coordenados llamando a funciones de OpenGL
 */
void igvEscena3D::pintar_ejes()
{	GLfloat rojo[] = { 1,0,0,1.0 };
   GLfloat verde[] = { 0, 1, 0, 1.0 };
   GLfloat azul[] = { 0, 0, 1, 1.0 };

   glMaterialfv ( GL_FRONT, GL_EMISSION, rojo );
   glBegin ( GL_LINES );
   glVertex3f ( 1000, 0, 0 );
   glVertex3f ( -1000, 0, 0 );
   glEnd ();

   glMaterialfv ( GL_FRONT, GL_EMISSION, verde );
   glBegin ( GL_LINES );
   glVertex3f ( 0, 1000, 0 );
   glVertex3f ( 0, -1000, 0 );
   glEnd ();

   glMaterialfv ( GL_FRONT, GL_EMISSION, azul );
   glBegin ( GL_LINES );
   glVertex3f ( 0, 0, 1000 );
   glVertex3f ( 0, 0, -1000 );
   glEnd ();
}

// Métodos públicos

// TODO: Apartado B: Métodos para visualizar cada parte del modelo

void igvEscena3D::base() {
    glutSolidCube(1);
}

void igvEscena3D::pierna() {
    GLUquadricObj* cilindro;
    cilindro = gluNewQuadric();
    gluQuadricDrawStyle(cilindro, GLU_LINE);
    gluCylinder(cilindro, 0.2, 0.18, 2, 100, 100);
    gluDeleteQuadric(cilindro);
}

void igvEscena3D::cuerpo() {
    GLUquadricObj* cono;
    cono = gluNewQuadric();
    gluQuadricDrawStyle(cono, GLU_SILHOUETTE);
    gluCylinder(cono, 0.18, 1, 2.5, 1500, 1500);
    gluDeleteQuadric(cono);
}

void igvEscena3D::cabeza() {
    glutSolidSphere(0.8, 100, 100);
}

void igvEscena3D::mano() {
    glutSolidSphere(0.2, 100, 100);
}

//PARA APLICAR LOS GRADOS DE LIBERTAD A LAS PARTES DEL CUERPO TENGO QUE HACER DISTINTO METODOS
//DE VISUALIZACION PARA CADA PARTE TIPO: visualizarCabeza(), visualizarPiernaIzq()...
void igvEscena3D::visualizarPiernaIzq() {
    glPushMatrix();
        rotarPiernaI(angPiernaI);
        glPushMatrix();
            glTranslatef(-0.5, -2, 0);
            glScalef(0.5, 0.2, 1);
            base();
        glPopMatrix();
        glPushMatrix();
            glTranslatef(-0.5, 0.1, -0.2);
            glRotatef(90, 1, 0, 0);
            pierna();
        glPopMatrix();
    glPopMatrix();
}

void igvEscena3D::visualizarPiernaDer() {
    glPushMatrix();
        rotarPiernaD(angPiernaD);
        glPushMatrix();
            glTranslatef(0.5, -2, 0);
            glScalef(0.5, 0.2, 1);
            base();
        glPopMatrix();
        glPushMatrix();
            glTranslatef(0.5, 0.1, -0.2);
            glRotatef(90, 1, 0, 0);
            pierna();
        glPopMatrix();
    glPopMatrix();
}

void igvEscena3D::visualizarCuerpo() {
    glPushMatrix();
        glTranslatef(0, 2.5, 0);
        glRotatef(90, 1, 0, 0);
        cuerpo();
    glPopMatrix();
}

void igvEscena3D::visualizarBrazoIzq() {
    glPushMatrix();
        rotarBrazoI(angBrazoI);
        glPushMatrix();
            glTranslatef(-1.75, 0.5, 0.2);
            mano();
        glPopMatrix();
        glPushMatrix();
            glTranslatef(-0.2, 2, 0);
            glRotatef(-45, 0, 0, 1);
            glRotatef(90, 1, 0, 0);
            pierna();
        glPopMatrix();
    glPopMatrix();
}

void igvEscena3D::visualizarBrazoDer() {
    glPushMatrix();
        //rotarBrazoD(angBrazoD);
    glPushMatrix();
    glTranslatef(0.2, 2, 0);
    glRotatef(45, 0, 0, 1);
    glRotatef(90, 1, 0, 0);
    rotarBrazoD(angBrazoD);
    pierna();
    glPopMatrix();
        glPushMatrix();
            glTranslatef(1.75, 0.5, 0);
    rotarBrazoD(angBrazoD);
            mano();
        glPopMatrix();

    glPopMatrix();
}

void igvEscena3D::visualizarCabeza() {
    rotarCabeza(angCabeza);
    glPushMatrix();
        glTranslatef(0, 3.2, 0);
        //rotarCabeza(angCabeza);
        cabeza();
    glPopMatrix();
}

void igvEscena3D::visualizarModelo() {
    rotarCabeza(angCabeza);
    visualizarPiernaIzq();
    visualizarPiernaDer();
    visualizarCuerpo();
    visualizarBrazoIzq();
    visualizarBrazoDer();
    visualizarCabeza();
}

// TODO: Apartado C: añadir aquí los métodos para modificar los grados de libertad del modelo
void igvEscena3D::rotarCabeza(int ang) {
    glRotatef(ang, 0, 1, 0);
}

void igvEscena3D::rotarPiernaD(int ang) {
    glRotatef(ang, 1, 0, 0);
}

void igvEscena3D::rotarPiernaI(int ang) {
    glRotatef(ang, 1, 0, 0);
}

void igvEscena3D::rotarBrazoD(int ang) {
    glRotatef(ang, 1, 0, 0);
}

void igvEscena3D::rotarBrazoI(int ang) {
    glRotatef(ang, 1, 0, 0);
}

/**
 * Método con las llamadas OpenGL para visualizar la escena
 */
void igvEscena3D::visualizar ()
{  // crear luces
   GLfloat luz0[4] = { 5.0, 5.0, 5.0, 1 }; // luz puntual
   glLightfv ( GL_LIGHT0, GL_POSITION, luz0 ); // la luz se coloca aquí si permanece fija y no se mueve con la escena
   glEnable ( GL_LIGHT0 );

   // crear el modelo
   glPushMatrix (); // guarda la matriz de modelado

   // se pintan los ejes
   if ( ejes )
   { pintar_ejes (); }

   //glLightfv(GL_LIGHT0,GL_POSITION,luz0); // la luz se coloca aquí si se mueve junto con la escena (también habría que desactivar la de arriba).



   // TODO: Apartado B: aquí hay que añadir la visualización del árbol del modelo utilizando la pila de matrices de OpenGL
   //       se recomienda crear una método auxiliar que encapsule el código para la visualización
   //       del modelo, dejando aquí sólo la llamada a ese método, así como distintas funciones una para cada
   //       parte del modelo.
    visualizarModelo();


   glPopMatrix (); // restaura la matriz de modelado
}

/**
 * Método para consultar si hay que dibujar los ejes o no
 * @retval true Si hay que dibujar los ejes
 * @retval false Si no hay que dibujar los ejes
 */
bool igvEscena3D::get_ejes ()
{  return ejes;
}

/**
 * Método para activar o desactivar el dibujado de los _ejes
 * @param _ejes Indica si hay que dibujar los ejes (true) o no (false)
 * @post El estado del objeto cambia en lo que respecta al dibujado de ejes,
 *       de acuerdo al valor pasado como parámetro
 */
void igvEscena3D::set_ejes ( bool _ejes )
{  ejes = _ejes;
}

int igvEscena3D::getAngCabeza() const {
    return angCabeza;
}

void igvEscena3D::setAngCabeza(int angCabeza) {
    igvEscena3D::angCabeza = angCabeza;
}

int igvEscena3D::getAngPiernaD() const {
    return angPiernaD;
}

void igvEscena3D::setAngPiernaD(int angPiernaD) {
    igvEscena3D::angPiernaD = angPiernaD;
}

int igvEscena3D::getAngPiernaI() const {
    return angPiernaI;
}

void igvEscena3D::setAngPiernaI(int angPiernaI) {
    igvEscena3D::angPiernaI = angPiernaI;
}

int igvEscena3D::getAngBrazoI() const {
    return angBrazoI;
}

void igvEscena3D::setAngBrazoI(int angBrazoI) {
    igvEscena3D::angBrazoI = angBrazoI;
}

int igvEscena3D::getAngBrazoD() const {
    return angBrazoD;
}

void igvEscena3D::setAngBrazoD(int angBrazoD) {
    igvEscena3D::angBrazoD = angBrazoD;
}






