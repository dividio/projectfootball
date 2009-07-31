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

To play Project Football you need de following libraries:

- Ogre   1.6.x
- Cegui  0.6.x
- OIS    1.2.x
- Sqlite 3
- SDL_mixer 1.2
- Lua 5.1
- Boost FileSystem >= 1.35

--------------------------------
3- Compiling
--------------------------------

- To compile, run this script:
sh build.sh

- To play Project Football, run the followig command:
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
  VSync = [true | false]                      // Vertical syncronization
  RTTPreferredMode = [FBO | PBuffer | Copy]   // Render to texture mode


-------------------
5- More information
-------------------

Visit Ikaro Games web site to know the latest news about Project Football:

http://www.ikarogames.com/projectfootball/

