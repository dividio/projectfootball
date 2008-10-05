%{
#include <CEGUIString.h>
%}

namespace CEGUI
{
    class String
    {
        String();
        String(const String &);

        virtual ~String();
    };
}