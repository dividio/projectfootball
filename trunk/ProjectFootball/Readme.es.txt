-----------------------
Project Football README
-----------------------

Indice:

1- Licencia del software
2- Dependencias
3- Instrucciones de compilación
4- Opciones de configuración
5- Más información




-------------------------
1- Licencia del software
-------------------------

+ El código fuente de este software se distribuye bajo la licencia GPL
versión 2 (ver Source-License.txt), excepto el código fuente incluido en el directório src/bullet,
el cual se distribuye bajo la licencia Zlib (ver Bullet-License.txt).

+ Los ficheros de datos, arte, y sonido, se distribuyen balo la licencia 
Creative Commons Attribution-ShareAlike 3.0 (ver Data-License.txt).


-----------------------------
2- Dependencias
-----------------------------

Para ejecutar Project Football es necesario tener las siguientes librerías y sus dependencias:

- Ogre   1.6.x
- Cegui  = 0.6.2
- OIS    1.2.x
- Sqlite 3
- SDL_mixer 1.2
- Lua 5.1
- Boost FileSystem >= 1.38
- Boost Thread >= 1.38

En Debian/Ubuntu puedes instalar todas las dependencias para compilar y ejecutar con el siguiente comando:
sudo aptitude install build-essential libogre-dev libceguiogre-dev libcegui-mk2-dev libois-dev libboost-filesystem-dev libboost-thread-dev libsqlite3-dev liblua5.1-0-dev libsdl-mixer1.2-dev swig


--------------------------------
3- Instrucciones de compilación
--------------------------------

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
  Skin = [ArridiDesign]            // Nos indica el Skin a utilizar
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

http://www.ikarogames.com/projectfootball/

