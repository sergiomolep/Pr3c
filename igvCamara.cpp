#include <math.h>
#include <stdio.h>

#include "igvCamara.h"

// Metodos constructores

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
igvCamara::igvCamara ( tipoCamara _tipo, igvPunto3D _P0, igvPunto3D _r
   , igvPunto3D _V ): P0 ( _P0 ), r ( _r ), V ( _V )
                      , tipo ( _tipo )
{ }

// M�todos p�blicos
/**
 * Define la posici�n de la c�mara
 * @param _P0 Posici�n de la c�mara (punto de visi�n)
 * @param _r Punto al que mira la c�mara (punto de referencia)
 * @param _V Vector que indica la vertical
 * @pre Se asume que todos los par�metros tienen valores v�lidos
 * @post Los atributos de la c�mara cambian a los valores pasados como par�metro
 */
void igvCamara::set ( igvPunto3D _P0, igvPunto3D _r, igvPunto3D _V )
{  P0 = _P0;
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
void igvCamara::set ( tipoCamara _tipo, igvPunto3D _P0, igvPunto3D _r
                      , igvPunto3D _V, double _xwmin, double _xwmax, double _ywmin
                      , double _ywmax, double _znear, double _zfar )
{  tipo = _tipo;

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
void igvCamara::set ( tipoCamara _tipo, igvPunto3D _P0, igvPunto3D _r
                      , igvPunto3D _V, double _angulo, double _raspecto
                      , double _znear, double _zfar )
{  tipo = _tipo;

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
void igvCamara::aplicar ()
{  glMatrixMode ( GL_PROJECTION );
   glLoadIdentity ();

   if ( tipo == IGV_PARALELA )
   {  glOrtho ( xwmin, xwmax, ywmin, ywmax, znear, zfar );
   }
   if ( tipo == IGV_FRUSTUM )
   {  glFrustum ( xwmin, xwmax, ywmin, ywmax, znear, zfar );
   }
   if ( tipo == IGV_PERSPECTIVA )
   {  gluPerspective ( angulo, raspecto, znear, zfar );
   }

   glMatrixMode ( GL_MODELVIEW );
   glLoadIdentity ();
   gluLookAt ( P0[X], P0[Y], P0[Z], r[X], r[Y], r[Z], V[X], V[Y], V[Z] );
}

/**
 * Cambia el tipo de la c�mara
 * @param t Nuevo tipo (valores v�lidos: IGV_PARALELA, IGV_FRUSTUM, IGV_PERSPECTIVA)
 * @pre Se asume que el par�metro tiene un valor v�lido
 * @post Cambia el tipo de la c�mara
 */
void igvCamara::set_vista ( tipoCamara t )
{  tipo = t;
}

/**
 * Consulta el tipo de la c�mara
 * @return El tipo de c�mara actualmente almacenado en el objeto
 */
tipoCamara igvCamara::get_vista ()
{  return tipo;
}

/**
 * Cambia el tipo de vista de la c�mara
 * @param x Nuevo tipo de vista (valores v�lidos: panoramica, planta, alzado,
 *        perfil)
 * @pre Se asume que el par�metro tiene un valor v�lido
 * @post Cambia el tipo de vista almacenado (no cambia la posici�n de la c�mara,
 *       ni el punto de referencia, ni el vector de vertical)
 */
void igvCamara::set_poscam ( poscam x )
{  vis = x;
}

/**
 * Consulta el tipo de vista de la c�mara
 * @return El tipo de vista almacenado en el objeto
 */
poscam igvCamara::get_poscam ()
{  return vis;
}
