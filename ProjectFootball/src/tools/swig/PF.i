%module PF
%{
#define SWIG_init_user SWIG_init_user_PF
%}

%include PF/DAO.i
%include PF/CLog.i
%include PF/States.i
%include PF/Sim.i
%include PF/Bullet.i