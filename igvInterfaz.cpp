#include <cstdlib>
#include <stdio.h>
#include <vector>
#include "igvInterfaz.h"

// Aplicaci�n del patr�n de dise�o Singleton
igvInterfaz *igvInterfaz::_instancia = nullptr;

// M�todos p�blicos ----------------------------------------

/**
 * M�todo para acceder al objeto �nico de la clase, en aplicaci�n del patr�n de
 * dise�o Singleton
 * @return Una referencia al objeto �nico de la clase
 */
igvInterfaz &igvInterfaz::getInstancia ()
{  if ( !_instancia )
   {  _instancia = new igvInterfaz;
   }

   return *_instancia;
}

/**
 * Crea el mundo que se visualiza en la ventana
 */
void igvInterfaz::crear_mundo ()
{  // inicia la c�mara
   _instancia->camara.set ( IGV_PERSPECTIVA, { 10.0, 4.0, 10.0 }, { 0, 0, 0 }, { 0, 1.0, 0 }, 60, 4.0 / 3.0, 1, 100 );
}

/**
 * Inicializa todos los par�metros para crear una ventana de visualizaci�n
 * @param argc N�mero de par�metros por l�nea de comandos al ejecutar la
 *             aplicaci�n
 * @param argv Par�metros por l�nea de comandos al ejecutar la aplicaci�n
 * @param _ancho_ventana Ancho inicial de la ventana de visualizaci�n
 * @param _alto_ventana Alto inicial de la ventana de visualizaci�n
 * @param _pos_X Coordenada X de la posici�n inicial de la ventana de
 *               visualizaci�n
 * @param _pos_Y Coordenada Y de la posici�n inicial de la ventana de
 *               visualizaci�n
 * @param _titulo T�tulo de la ventana de visualizaci�n
 * @pre Se asume que todos los par�metros tienen valores v�lidos
 * @post Cambia el alto y ancho de ventana almacenado en el objeto
 */
void
igvInterfaz::configura_entorno ( int argc, char **argv, int _ancho_ventana, int _alto_ventana, int _pos_X, int _pos_Y,
                                 std::string _titulo )
{  // inicializaci�n de las variables de la interfaz
   ancho_ventana = _ancho_ventana;
   alto_ventana = _alto_ventana;

   // inicializaci�n de la ventana de visualizaci�n
   glutInit ( &argc, argv );
   glutInitDisplayMode ( GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH );
   glutInitWindowSize ( _ancho_ventana, _alto_ventana );
   glutInitWindowPosition ( _pos_X, _pos_Y );
   glutCreateWindow ( _titulo.c_str () );

   glEnable ( GL_DEPTH_TEST ); // activa el ocultamiento de superficies por z-buffer
   glClearColor ( 1.0, 1.0, 1.0, 0.0 ); // establece el color de fondo de la ventana

   glEnable ( GL_LIGHTING ); // activa la iluminaci�n de la escena
   glEnable ( GL_NORMALIZE ); // normaliza los vectores normales para calculo iluminacion

   crear_mundo (); // crea el mundo a visualizar en la ventana
}

/**
 * M�todo para visualizar la escena y esperar a eventos sobre la interfaz
 */
void igvInterfaz::inicia_bucle_visualizacion ()
{  glutMainLoop (); // inicia el bucle de visualizaci�n de GLUT
}

/**
 * M�todo para control de eventos del teclado
 * @param key C�digo de la tecla pulsada
 * @param x Coordenada X de la posici�n del cursor del rat�n en el momento del
 *          evento de teclado
 * @param y Coordenada Y de la posici�n del cursor del rat�n en el momento del
 *          evento de teclado
 * @pre Se asume que todos los par�metros tienen valores v�lidos
 * @post Los atributos de la clase pueden cambiar, dependiendo de la tecla pulsada
 */
void igvInterfaz::keyboardFunc ( unsigned char key, int x, int y )
{  switch ( key )
   {  case 'e': // activa/desactiva la visualizaci�n de los ejes
         _instancia->escena.set_ejes ( !_instancia->escena.get_ejes () );
         break;
      case 27: // tecla de escape para SALIR
         exit ( 1 );
         break;
   }
   glutPostRedisplay (); // renueva el contenido de la ventana de visi�n
}

/**
 * M�todo que define la c�mara de visi�n y el viewport. Se llama autom�ticamente
 * cuando se cambia el tama�o de la ventana.
 * @param w Nuevo ancho de la ventana
 * @param h Nuevo alto de la ventana
 * @pre Se asume que todos los par�metros tienen valores v�lidos
 */
void igvInterfaz::reshapeFunc ( int w, int h )
{  // dimensiona el viewport al nuevo ancho y alto de la ventana
   // guardamos valores nuevos de la ventana de visualizacion
   _instancia->set_ancho_ventana ( w );
   _instancia->set_alto_ventana ( h );

   // establece los par�metros de la c�mara y de la proyecci�n
   _instancia->camara.aplicar ();
}

/**
 * M�todo para visualizar la escena
 */
void igvInterfaz::displayFunc ()
{  glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // borra la ventana y el z-buffer
   // se establece el viewport
   glViewport ( 0, 0, _instancia->get_ancho_ventana (), _instancia->get_alto_ventana () );

   // TODO: Apartado A: antes de aplicar las transformaciones de c�mara y proyecci�n hay que comprobar el modo para s�lo visualizar o seleccionar:
   if ( _instancia->modo == IGV_SELECCIONAR )
   {   // Apartado A: Para que funcione hay que dibujar la escena sin efectos, sin iluminaci�n, sin texturas ...
      glDisable ( GL_LIGHTING ); // desactiva la iluminaci�n de la escena
      glDisable ( GL_DITHER );

      glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
      glDisable ( GL_TEXTURE_2D );
      glDisable ( GL_CULL_FACE );

      // TODO: Apartado A: Reestablece los colores como no seleccionado


      // TODO: Apartado A: aplica la c�mara


      // TODO: Apartado A: visualiza las cajas cada una de un color


      // TODO: Apartado A: Obtener el color del pixel seleccionado

      // TODO: Apartado A: Comprobar el color del objeto que hay en el cursor mirando en la tabla de colores y asigna otro color al objeto seleccionado


      // TODO: Apartado A: Cambiar a modo de visualizaci�n de la escena


      // TODO: Apartado A: Habilitar de nuevo la iluminaci�n
      glEnable ( GL_LIGHTING );
   }
   else
   {   // aplica las transformaciones en funci�n de los par�metros de la c�mara
      _instancia->camara.aplicar ();
      // visualiza la escena
      _instancia->escena.visualizar ();

      // refresca la ventana
      glutSwapBuffers ();
   }
}

/**
 * M�todo para el control de los clics con el rat�n
 * @param boton Identifica el bot�n que se ha pulsado. Puede ser
 *        GLUT_LEFT_BUTTON, GLUT_MIDDLE_BUTTON o GLUT_RIGHT_BUTTON
 * @param estado Describe si el bot�n se ha pulsado (GLUT_DOWN) o soltado
 *        (GLUT_UP)
 * @param x Coordenada X del p�xel de la ventana donde se ha hecho clic
 * @param y Coordenada Y del p�xel de la ventana donde se ha hecho clic
 * @post Se actualiza el estado de la interfaz
 */
void igvInterfaz::mouseFunc ( GLint boton, GLint estado, GLint x, GLint y )
{   // TODO: Apartado A: comprobar que se ha pulsado el bot�n izquierdo

   /* TODO: Apartado A: guardar que el bot�n se ha presionado o se ha soltado.
      Si se ha pulsado hay que pasar a modo IGV_SELECCIONAR */

   // TODO: Apartado A: guardar el pixel pulsado

   // TODO: Apartado A: renovar el contenido de la ventana de vision

}

/**
 * M�todo para el control del desplazamiento del rat�n con un bot�n pulsado
 * @param x Coordenada X de la posici�n del cursor del rat�n en la ventana
 * @param y Coordenada Y de la posici�n del cursor del rat�n en la ventana
 * @post Se actualiza el estado de la interfaz
 */
void igvInterfaz::motionFunc ( GLint x, GLint y )
{  /* TODO: Apartado B: si el bot�n est� pulsado y hay alg�n objeto seleccionado,
      hay que comprobar el objeto seleccionado y la posici�n del rat�n y rotar
      el objeto seleccionado utilizando el desplazamiento entre la posici�n
      inicial y final del rat�n */

   // TODO: Apartado B: guardar la nueva posici�n del rat�n

   // TODO: Apartado B: renovar el contenido de la ventana de vision

}

/**
 * M�todo para inicializar los callbacks GLUT
 */
void igvInterfaz::inicializa_callbacks ()
{  glutKeyboardFunc ( keyboardFunc );
   glutReshapeFunc ( reshapeFunc );
   glutDisplayFunc ( displayFunc );

   glutMouseFunc ( mouseFunc );
   glutMotionFunc ( motionFunc );
}

/**
 * M�todo para consultar el ancho de la ventana de visualizaci�n
 * @return El valor almacenado como ancho de la ventana de visualizaci�n
 */
int igvInterfaz::get_ancho_ventana ()
{  return ancho_ventana;
}

/**
 * M�todo para consultar el alto de la ventana de visualizaci�n
 * @return El valor almacenado como alto de la ventana de visualizaci�n
 */
int igvInterfaz::get_alto_ventana ()
{  return alto_ventana;
}

/**
 * M�todo para cambiar el ancho de la ventana de visualizaci�n
 * @param _ancho_ventana Nuevo valor para el ancho de la ventana de visualizaci�n
 * @pre Se asume que el par�metro tiene un valor v�lido
 * @post El ancho de ventana almacenado en la aplicaci�n cambia al nuevo valor
 */
void igvInterfaz::set_ancho_ventana ( int _ancho_ventana )
{  ancho_ventana = _ancho_ventana;
}

/**
 * M�todo para cambiar el alto de la ventana de visualizaci�n
 * @param _alto_ventana Nuevo valor para el alto de la ventana de visualizaci�n
 * @pre Se asume que el par�metro tiene un valor v�lido
 * @post El alto de ventana almacenado en la aplicaci�n cambia al nuevo valor
 */
void igvInterfaz::set_alto_ventana ( int _alto_ventana )
{  alto_ventana = _alto_ventana;
}
