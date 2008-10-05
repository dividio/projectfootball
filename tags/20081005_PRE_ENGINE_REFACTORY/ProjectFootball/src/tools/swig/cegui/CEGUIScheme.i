%{
#include <CEGUIScheme.h>
%}

%cegui_attribute(Scheme, const CEGUI::String &, Name, getName);
%cegui_attribute(Scheme, bool, ResourcesLoaded, resourcesLoaded);

%include /usr/include/CEGUI/CEGUIScheme.h