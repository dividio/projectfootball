/* typemap */
%typemap(in, checkfn="lua_islightuserdata") CLASS_P
%{
    $1 = ($type)lua_touserdata(L, $input);
%}

/* helper macro */
/* add inline function:
   SomeClass *SomeClass_p_ctor(SomeClass *pclass)
{return pclass;} */
%define ADD_CLASS_P_CTOR(class_name)
%apply CLASS_P {class_name *};
%inline %{
    class_name *class_name##_p_ctor(class_name
*pclass) {
        return pclass;
    }
%}
%clear class_name *;
%enddef