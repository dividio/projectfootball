%{
#include <CEGUIEventArgs.h>
%}

%rename(Handled) CEGUI::EventArgs::handled;

%include /usr/include/CEGUI/CEGUIEventArgs.h