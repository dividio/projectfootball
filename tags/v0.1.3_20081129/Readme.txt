-----------------------
Project Football README
-----------------------

Indice:

1- Licencia del software
2- Dependencias de ejecución
3- Instrucciones de compilación
4- Opciones de configuración
5- Más información




-------------------------
1- Licencia del software
-------------------------

+ El código fuente de este software se distribuye bajo la licencia GPL
versión 2, excepto el código fuente incluido en el directório src/bullet,
el cual se distribuye bajo la licencia Zlib.

+ El contenido de la licencia GPL 2 puede consultarse en el fichero COPYRIGHT.txt

+ El contenido de licencia Zlib para la librería Bullet en el directorio src/bullet, se encuentra
en el fichero BulletLicense.txt


-----------------------------
2- Dependencias de ejecución
-----------------------------

Para ejecutar Project Football es necesario tener las siguientes librerías:

- Ogre 1.4.3 (libogre14)
- Cegui 0.5.0 (libcegui-mk2-1)
- OIS (libois1)
- Sqlite 3 (libsqlite3-0)
- SDL_mixer (libsdl-mixer1.2)
- Lua 5.1 (liblua5.1-0)

Entre paréntesis está el nombre del paquete que es necesario instalar en Debian y Ubuntu.

Según algunas pruebas realizadas en distintos sistemas, parece que en determinadas
distribuciones hace falta instalar algún paquete adicional. A continuación podéis encontrar
los casos especiales conocidos.

+ Debian Unstable:
- Instalar las librerías arriba indicadas.
- Instalar el paquete libceguiogre14 para probar el binario y libceguiogre-dev para poder
compilar el código fuente.

+ Ubuntu 7.10:
- Instalar las librerías arriba indicadas.
- Instalar el paquete libcegui-mk2-dev


--------------------------------
3- Instrucciones de compilación
--------------------------------

- En sistemas Debian y Ubuntu hay que instalar primero los siguientes paquetes:

libogre-dev libcegui-mk2-dev libois-dev libsqlite3-dev
libsdl-mixer1.2-dev liblua5.1-0-dev

- En Debian Unstable hay que añadir también libceguiogre-dev

- Para compilar, ejecutar desde el directorio ProjectFootball el siguiente comando:
sh build.sh

- Para ejecutar Project Football, ejecutar el comando:
./ProjectFootball


-----------------------------
4- Opciones de configuración
-----------------------------

Project Football cuenta con varias opciones de configuración, con el objetivo de
adaptarse lo mejor posible a la máquina del usuario, y se almacenan en
el fichero "data/ProjectFootball.ini". Pasemos a ver algunas de ellas:

[General]
  FailSafeMode = [true | false]               // Nos indica si se ha iniciado el
                                              // "modo seguro de video"

[GUI]
  Skin = [DefaultSkin | CleanSkin]            // Nos indica el Skin a utilizar
  XMLParser = [XercesParser | TinyXMLParser]  // Parser de XML a utilizar por CEGUI

[Video]
  RenderSystem = OpenGL Rendering Subsystem   // Sistema de Render a utilizar
  VSync = [true | false]                      // Activación de la sincronización vertical
  RTTPreferredMode = [FBO | PBuffer | Copy]   // Modo de renderizado a textura

La opción RTT Preferred Mode puede provocar problemas en determinados sistemas. La
opción por defecto es "FBO", si se encuentran problemas al arrancar la aplicación
se pueden probar los modos "PBuffer" o "Copy", siendo este último el modo más lento
pero que debería funcionar en más sistemas.


-------------------
5- Más información
-------------------

Visita la web de Ikaro Games para conocer las últimas novedades sobre Project Football:

http://www.ikarogames.com

