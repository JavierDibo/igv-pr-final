#include <cstdlib>
#include <stdio.h>

#include "igvEscena3D.h"

// Métodos constructores

/**
 * Constructor por defecto
 */
igvEscena3D::igvEscena3D() {  // TODO: Apartado C: inicializar los atributos para el control de los grados de libertad del modelo
    angCabeza = 0;
    angPiernaD = 0;
    angPiernaI = 0;
    angBrazoD = 0;
    angBrazoI = 0;
}

/**
 * Destructor
 */
igvEscena3D::~igvEscena3D() {
}

/**
 * Método para pintar los ejes coordenados llamando a funciones de OpenGL
 */
void igvEscena3D::pintar_ejes() {
    GLfloat rojo[] = {1, 0, 0, 1.0};
    GLfloat verde[] = {0, 1, 0, 1.0};
    GLfloat azul[] = {0, 0, 1, 1.0};

    glMaterialfv(GL_FRONT, GL_EMISSION, rojo);
    glBegin(GL_LINES);
    glVertex3f(1000, 0, 0);
    glVertex3f(-1000, 0, 0);
    glEnd();

    glMaterialfv(GL_FRONT, GL_EMISSION, verde);
    glBegin(GL_LINES);
    glVertex3f(0, 1000, 0);
    glVertex3f(0, -1000, 0);
    glEnd();

    glMaterialfv(GL_FRONT, GL_EMISSION, azul);
    glBegin(GL_LINES);
    glVertex3f(0, 0, 1000);
    glVertex3f(0, 0, -1000);
    glEnd();
}

// Métodos públicos

// TODO: Apartado B: Métodos para visualizar cada parte del modelo

void igvEscena3D::base() {
    glutSolidCube(1);
}

void igvEscena3D::pierna() {
    GLUquadricObj *cilindro;
    cilindro = gluNewQuadric();
    gluQuadricDrawStyle(cilindro, GLU_LINE);
    gluCylinder(cilindro, 0.2, 0.18, 2, 100, 100);
    gluDeleteQuadric(cilindro);
}

void igvEscena3D::cuerpo() {
    GLUquadricObj *cono;
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

void igvEscena3D::visualizarBase() {
    glPushMatrix(); // Guarda el estado actual de la matriz

    glScalef(1.0, 0.5, 1.0);

    glScalef(2.0, 2.0, 2.0);

    glutSolidCube(1.0);

    glPopMatrix();
}

void igvEscena3D::visualizarMunneco() {
    glPushMatrix();
    // glTranslatef(0,3,0);
    rotarCabeza(angCabeza);
    visualizarPiernaIzq();
    visualizarPiernaDer();
    visualizarCuerpo();
    visualizarBrazoIzq();
    visualizarBrazoDer();
    visualizarCabeza();
    glPopMatrix();
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

void igvEscena3D::visualizarCable(const float punto_partida[3], const float centro_anterior[3]) {
    float s1 = 0.05, s2 = largoCable, s3 = 0.05;
    float t1 = punto_partida[0], t2 = punto_partida[1] - 0.20f, t3 = punto_partida[2] - s3 / 2 - profundidadCable;

    glPushMatrix();

    glRotated(anguloColumna, 0.0, 1.0, 0.0);

    glTranslatef(t1, t2, t3);

    // Mover al centro y escalarlo
    glScalef(s1, -s2, s3);
    glTranslatef(0, 0.5, 0);

    // glutWireCube(1.0);
    glutSolidCube(1.0);

    glPopMatrix();

}

void igvEscena3D::rotateY(const float point[3], float angle, float result[3]) {
    float rad = angle * M_PI / 180.0; // Convertir el ?ngulo a radianes
    result[0] = cos(rad) * point[0] - sin(rad) * point[2];
    result[1] = point[1];
    result[2] = sin(rad) * point[0] + cos(rad) * point[2];
}

void igvEscena3D::visualizarBrazo(const float punto_partida[3], const float centro_anterior[3]) {

    float s1 = 0.40, s2 = 0.40, s3 = 5.00;
    float t1 = punto_partida[0], t2 = punto_partida[1], t3 = punto_partida[2] + s3 / 2 - 0.20f;

    glPushMatrix();

    glRotated(anguloColumna, 0.0, 1.0, 0.0);

    glTranslatef(t1, t2, t3);

    // Mover al centro y escalarlo
    glScalef(s1, s2, s3);
    glTranslatef(0, 0.5, 0);

    // glutWireCube(1.0);
    glutSolidCube(1.0);

    glPopMatrix();

    float centroX = centro_anterior[0] * s1 + t1;
    float centroY = (centro_anterior[0] + 0.5f) * s2 + t2;
    float centroZ = centro_anterior[0] * s3 + t3;

    float centro[3] = {centroX, centroY, centroZ};

    float centro_cara_superior_x = centroX;
    float centro_cara_superior_y = centroY;
    float centro_cara_superior_z = centroZ + s3 / 2;

    // Coordenadas del centro de la cara superior del cubo
    float centro_cara_superior[3] = {centro_cara_superior_x, centro_cara_superior_y, centro_cara_superior_z};

    visualizarCable(centro_cara_superior, centro);
}

void igvEscena3D::visualizarColumna(const float punto_partida[3], const float centro_anterior[3]) {

    float s1 = 0.40, s2 = 3.00, s3 = 0.40;
    float t1 = punto_partida[0], t2 = punto_partida[1], t3 = punto_partida[2];

    glPushMatrix();

    glRotated(anguloColumna, 0.0, 1.0, 0.0);

    glTranslatef(t1, t2, t3);

    // Mover al centro y escalarlo
    glScalef(s1, s2, s3);
    glTranslatef(0, 0.5, 0);

    // glutWireCube(1.0);
    glutSolidCube(1.0);

    glPopMatrix();

    float centro_rotado[3];
    rotateY(centro_anterior, anguloColumna, centro_rotado);

    float centroX = centro_rotado[0] * s1 + t1;
    float centroY = (centro_rotado[0] + 0.5f) * s2 + t2;
    float centroZ = centro_rotado[0] * s3 + t3;

    float centro[3] = {centroX, centroY, centroZ};

    float centro_cara_superior_x = centroX;
    float centro_cara_superior_y = centroY + s2 / 2;
    float centro_cara_superior_z = centroZ;

    // Coordenadas del centro de la cara superior del cubo
    float centro_cara_superior[3] = {centro_cara_superior_x, centro_cara_superior_y, centro_cara_superior_z};

    visualizarBrazo(centro_cara_superior, centro);
}

void igvEscena3D::visualizarBaseGrua() {

    float s1 = 1.00, s2 = 0.50, s3 = 1.00;
    float t1 = 0.00, t2 = s2 / 2, t3 = 0.00;

    glPushMatrix();

    glTranslatef(t1, t2, t3);
    glScalef(s1, s2, s3);

    glutSolidCube(1.0);

    glPopMatrix();

    float centroX = 0.0f * s1 + t1;
    float centroY = 0.0f * s2 + t2;
    float centroZ = 0.0f * s3 + t3;

    float centro[3] = {centroX, centroY, centroZ};

    float centro_cara_superior_x = centroX;
    float centro_cara_superior_y = centroY + s2 / 2;
    float centro_cara_superior_z = centroZ;

    // Coordenadas del centro de la cara superior del cubo
    float cara_superior[3] = {centro_cara_superior_x, centro_cara_superior_y, centro_cara_superior_z};

    visualizarColumna(cara_superior, centro);
}

void igvEscena3D::visualizarEstructura(int num) {
    GLfloat altura;
    if (num == 0) {
        altura = 2.5;
        glTranslatef(0, altura, 0);
        visualizarMunneco();
        glTranslatef(0, -altura, 0);
    }
    if (num == 1) {
        altura = 0.5;
        glTranslatef(0, altura, 0);
        visualizarBaseGrua();
        glTranslatef(0, -altura, 0);
    }
}

void igvEscena3D::generarBases() {

    for (int i = 0; i < 5; ++i) {
        glPushMatrix();
        glTranslatef(0, 0, 3 * i);
        glRotatef(27 * i, 0, 1, 0);
        visualizarBase();
        glPushMatrix();
        visualizarEstructura(i);
        glPopMatrix();
        glPopMatrix();
    }
}

void igvEscena3D::visualizar() {  // crear luces
    GLfloat luz0[4] = {5.0, 5.0, 5.0, 1}; // luz puntual
    glLightfv(GL_LIGHT0, GL_POSITION, luz0); // la luz se coloca aquí si permanece fija y no se mueve con la escena
    glEnable(GL_LIGHT0);

    // crear el modelo
    glPushMatrix(); // guarda la matriz de modelado

    // se pintan los ejes
    if (ejes) { pintar_ejes(); }

    //glLightfv(GL_LIGHT0,GL_POSITION,luz0); // la luz se coloca aquí si se mueve junto con la escena (también habría que desactivar la de arriba).

    generarBases();

    glPopMatrix(); // restaura la matriz de modelado
}

/**
 * Método para consultar si hay que dibujar los ejes o no
 * @retval true Si hay que dibujar los ejes
 * @retval false Si no hay que dibujar los ejes
 */
bool igvEscena3D::get_ejes() {
    return ejes;
}

/**
 * Método para activar o desactivar el dibujado de los _ejes
 * @param _ejes Indica si hay que dibujar los ejes (true) o no (false)
 * @post El estado del objeto cambia en lo que respecta al dibujado de ejes,
 *       de acuerdo al valor pasado como parámetro
 */
void igvEscena3D::set_ejes(bool _ejes) {
    ejes = _ejes;
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






