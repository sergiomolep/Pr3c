#include <cstdlib>
#include <stdio.h>
#include <vector>
#include "igvInterfaz.h"

// Aplicación del patrón de diseño Singleton
igvInterfaz *igvInterfaz::_instancia = nullptr;

// Métodos públicos ----------------------------------------

/**
 * Método para acceder al objeto único de la clase, en aplicación del patrón de
 * diseño Singleton
 * @return Una referencia al objeto único de la clase
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
{  // inicia la cámara
   _instancia->camara.set ( IGV_PERSPECTIVA, { 10.0, 4.0, 10.0 }, { 0, 0, 0 }, { 0, 1.0, 0 }, 60, 4.0 / 3.0, 1, 100 );
}

/**
 * Inicializa todos los parámetros para crear una ventana de visualización
 * @param argc Número de parámetros por línea de comandos al ejecutar la
 *             aplicación
 * @param argv Parámetros por línea de comandos al ejecutar la aplicación
 * @param _ancho_ventana Ancho inicial de la ventana de visualización
 * @param _alto_ventana Alto inicial de la ventana de visualización
 * @param _pos_X Coordenada X de la posición inicial de la ventana de
 *               visualización
 * @param _pos_Y Coordenada Y de la posición inicial de la ventana de
 *               visualización
 * @param _titulo Título de la ventana de visualización
 * @pre Se asume que todos los parámetros tienen valores válidos
 * @post Cambia el alto y ancho de ventana almacenado en el objeto
 */
void
igvInterfaz::configura_entorno ( int argc, char **argv, int _ancho_ventana, int _alto_ventana, int _pos_X, int _pos_Y,
                                 std::string _titulo )
{  // inicialización de las variables de la interfaz
   ancho_ventana = _ancho_ventana;
   alto_ventana = _alto_ventana;

   // inicialización de la ventana de visualización
   glutInit ( &argc, argv );
   glutInitDisplayMode ( GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH );
   glutInitWindowSize ( _ancho_ventana, _alto_ventana );
   glutInitWindowPosition ( _pos_X, _pos_Y );
   glutCreateWindow ( _titulo.c_str () );

   glEnable ( GL_DEPTH_TEST ); // activa el ocultamiento de superficies por z-buffer
   glClearColor ( 1.0, 1.0, 1.0, 0.0 ); // establece el color de fondo de la ventana

   glEnable ( GL_LIGHTING ); // activa la iluminación de la escena
   glEnable ( GL_NORMALIZE ); // normaliza los vectores normales para calculo iluminacion

   crear_mundo (); // crea el mundo a visualizar en la ventana
}

/**
 * Método para visualizar la escena y esperar a eventos sobre la interfaz
 */
void igvInterfaz::inicia_bucle_visualizacion ()
{  glutMainLoop (); // inicia el bucle de visualización de GLUT
}

/**
 * Método para control de eventos del teclado
 * @param key Código de la tecla pulsada
 * @param x Coordenada X de la posición del cursor del ratón en el momento del
 *          evento de teclado
 * @param y Coordenada Y de la posición del cursor del ratón en el momento del
 *          evento de teclado
 * @pre Se asume que todos los parámetros tienen valores válidos
 * @post Los atributos de la clase pueden cambiar, dependiendo de la tecla pulsada
 */
void igvInterfaz::keyboardFunc ( unsigned char key, int x, int y )
{  switch ( key )
   {  case 'e': // activa/desactiva la visualización de los ejes
         _instancia->escena.set_ejes ( !_instancia->escena.get_ejes () );
         break;
      case 27: // tecla de escape para SALIR
         exit ( 1 );
         break;
   }
   glutPostRedisplay (); // renueva el contenido de la ventana de visión
}

/**
 * Método que define la cámara de visión y el viewport. Se llama automáticamente
 * cuando se cambia el tamaño de la ventana.
 * @param w Nuevo ancho de la ventana
 * @param h Nuevo alto de la ventana
 * @pre Se asume que todos los parámetros tienen valores válidos
 */
void igvInterfaz::reshapeFunc ( int w, int h )
{  // dimensiona el viewport al nuevo ancho y alto de la ventana
   // guardamos valores nuevos de la ventana de visualizacion
   _instancia->set_ancho_ventana ( w );
   _instancia->set_alto_ventana ( h );

   // establece los parámetros de la cámara y de la proyección
   _instancia->camara.aplicar ();
}

/**
 * Método para visualizar la escena
 */
void igvInterfaz::displayFunc ()
{  glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // borra la ventana y el z-buffer
   // se establece el viewport
   glViewport ( 0, 0, _instancia->get_ancho_ventana (), _instancia->get_alto_ventana () );

   // TODO: Apartado A: antes de aplicar las transformaciones de cámara y proyección hay que comprobar el modo para sólo visualizar o seleccionar:
   if ( _instancia->modo == IGV_SELECCIONAR )
   {   // Apartado A: Para que funcione hay que dibujar la escena sin efectos, sin iluminación, sin texturas ...
      glDisable ( GL_LIGHTING ); // desactiva la iluminación de la escena
      glDisable ( GL_DITHER );

      glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
      glDisable ( GL_TEXTURE_2D );
      glDisable ( GL_CULL_FACE );

      // TODO: Apartado A: Reestablece los colores como no seleccionado


      // TODO: Apartado A: aplica la cámara


      // TODO: Apartado A: visualiza las cajas cada una de un color


      // TODO: Apartado A: Obtener el color del pixel seleccionado

      // TODO: Apartado A: Comprobar el color del objeto que hay en el cursor mirando en la tabla de colores y asigna otro color al objeto seleccionado


      // TODO: Apartado A: Cambiar a modo de visualización de la escena


      // TODO: Apartado A: Habilitar de nuevo la iluminación
      glEnable ( GL_LIGHTING );
   }
   else
   {   // aplica las transformaciones en función de los parámetros de la cámara
      _instancia->camara.aplicar ();
      // visualiza la escena
      _instancia->escena.visualizar ();

      // refresca la ventana
      glutSwapBuffers ();
   }
}

/**
 * Método para el control de los clics con el ratón
 * @param boton Identifica el botón que se ha pulsado. Puede ser
 *        GLUT_LEFT_BUTTON, GLUT_MIDDLE_BUTTON o GLUT_RIGHT_BUTTON
 * @param estado Describe si el botón se ha pulsado (GLUT_DOWN) o soltado
 *        (GLUT_UP)
 * @param x Coordenada X del píxel de la ventana donde se ha hecho clic
 * @param y Coordenada Y del píxel de la ventana donde se ha hecho clic
 * @post Se actualiza el estado de la interfaz
 */
void igvInterfaz::mouseFunc ( GLint boton, GLint estado, GLint x, GLint y )
{   // TODO: Apartado A: comprobar que se ha pulsado el botón izquierdo

   /* TODO: Apartado A: guardar que el botón se ha presionado o se ha soltado.
      Si se ha pulsado hay que pasar a modo IGV_SELECCIONAR */

   // TODO: Apartado A: guardar el pixel pulsado

   // TODO: Apartado A: renovar el contenido de la ventana de vision

}

/**
 * Método para el control del desplazamiento del ratón con un botón pulsado
 * @param x Coordenada X de la posición del cursor del ratón en la ventana
 * @param y Coordenada Y de la posición del cursor del ratón en la ventana
 * @post Se actualiza el estado de la interfaz
 */
void igvInterfaz::motionFunc ( GLint x, GLint y )
{  /* TODO: Apartado B: si el botón está pulsado y hay algún objeto seleccionado,
      hay que comprobar el objeto seleccionado y la posición del ratón y rotar
      el objeto seleccionado utilizando el desplazamiento entre la posición
      inicial y final del ratón */

   // TODO: Apartado B: guardar la nueva posición del ratón

   // TODO: Apartado B: renovar el contenido de la ventana de vision

}

/**
 * Método para inicializar los callbacks GLUT
 */
void igvInterfaz::inicializa_callbacks ()
{  glutKeyboardFunc ( keyboardFunc );
   glutReshapeFunc ( reshapeFunc );
   glutDisplayFunc ( displayFunc );

   glutMouseFunc ( mouseFunc );
   glutMotionFunc ( motionFunc );
}

/**
 * Método para consultar el ancho de la ventana de visualización
 * @return El valor almacenado como ancho de la ventana de visualización
 */
int igvInterfaz::get_ancho_ventana ()
{  return ancho_ventana;
}

/**
 * Método para consultar el alto de la ventana de visualización
 * @return El valor almacenado como alto de la ventana de visualización
 */
int igvInterfaz::get_alto_ventana ()
{  return alto_ventana;
}

/**
 * Método para cambiar el ancho de la ventana de visualización
 * @param _ancho_ventana Nuevo valor para el ancho de la ventana de visualización
 * @pre Se asume que el parámetro tiene un valor válido
 * @post El ancho de ventana almacenado en la aplicación cambia al nuevo valor
 */
void igvInterfaz::set_ancho_ventana ( int _ancho_ventana )
{  ancho_ventana = _ancho_ventana;
}

/**
 * Método para cambiar el alto de la ventana de visualización
 * @param _alto_ventana Nuevo valor para el alto de la ventana de visualización
 * @pre Se asume que el parámetro tiene un valor válido
 * @post El alto de ventana almacenado en la aplicación cambia al nuevo valor
 */
void igvInterfaz::set_alto_ventana ( int _alto_ventana )
{  alto_ventana = _alto_ventana;
}
