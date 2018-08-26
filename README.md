-----------------------
Project Football README
-----------------------

Index:

1- Software License
2- Dependencies
3- Compiling
4- Configure options
5- More information




-------------------------
1- Software License
-------------------------

+ Project Football source code is under GPL 2 License (see Source-License.txt). Souce code in src/bullet
is under Zlib license (see Bullet-License.txt).

+ Project Football data files, art, and sound, are under 
Creative Commons Attribution-ShareAlike 3.0 license (see Data-License.txt).


-----------------------------
2- Dependencies
-----------------------------

To play Project Football you need de following libraries and dependencies:

- Ogre   1.7.x
- Cegui  0.7.5
- OIS    1.3.x
- Sqlite 3
- SDL_mixer 1.2
- Lua 5.1
- Boost FileSystem >= 1.38
- Boost Thread >= 1.38

In Debian/Ubuntu you can install all the dependencies to compile and run with the following command:
sudo aptitude install build-essential libogre-dev libceguiogre-dev libcegui-mk2-dev libois-dev libboost-filesystem-dev libboost-thread-dev libsqlite3-dev liblua5.1-0-dev libsdl-mixer1.2-dev swig

--------------------------------
3- Compiling
--------------------------------

- Run cmake to compile the project.

- To play Project Football, run the following command:
./ProjectFootball


-----------------------------
4- Configuration options
-----------------------------

Project Football options are in "data/ProjectFootball.ini" file.

These are the principal options:

[General]
  FailSafeMode = [true | false]               // Switches failsafe video mode

[GUI]
  Skin = [ArridiDesign]            // Switches application skin
  XMLParser = [XercesParser | TinyXMLParser]  // Parser XML for CEGUI

[Video]
  RenderSystem = OpenGL Rendering Subsystem   // Render system for Ogre
  VSync = [true | false]                      // Vertical synchronization
  RTTPreferredMode = [FBO | PBuffer | Copy]   // Render to texture mode


-------------------
5- More information
-------------------

Visit Ikaro Games web site to know the latest news about Project Football:

http://www.ikarogames.com/projectfootball/
