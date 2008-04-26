%module CEGUI

%{
#include <CEGUI.h>
#include <CEGUIExceptions.h>

using namespace CEGUI;
%}

%include std_pair.i

%include /usr/include/CEGUI/CEGUIConfig.h
%include /usr/include/CEGUI/CEGUIBase.h

#define CEGUIBASE_API
#define OPENGL_GUIRENDERER_API

// Templates
%template(_FloatFloatPair) std::pair<float, float>;

//%include cegui/elements/CEGUIPushButton.i
//%include cegui/elements/CEGUIButtonBase.i

%include cegui/CEGUISingleton.i
%include cegui/CEGUIEventArgs.i
%include cegui/CEGUIInputEvent.i
//%include cegui/CEGUISchemeManager.i
//%include cegui/CEGUIScheme.i
//%include cegui/CEGUIString.i
