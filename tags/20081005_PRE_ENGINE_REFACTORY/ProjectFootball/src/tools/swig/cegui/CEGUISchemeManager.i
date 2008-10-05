%{
#include <CEGUISchemeManager.h>
%}

%template(_SchemeManagerSingleton) CEGUI::Singleton<CEGUI::SchemeManager>;

%ignore CEGUI::SchemeManager::getIterator;

%include /usr/include/CEGUI/CEGUISchemeManager.h
