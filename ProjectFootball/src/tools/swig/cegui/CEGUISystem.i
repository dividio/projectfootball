%{
#include <CEGUISystem.h>
%}

%template(_SystemSingleton) CEGUI::Singleton<CEGUI::System>;

%ignore CEGUI::System::~System;
%ignore CEGUI::System::operator=;

%include /usr/include/CEGUI/CEGUISystem.h