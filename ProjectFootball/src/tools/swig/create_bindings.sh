#!/bin/sh
swig -c++ -lua -Wall -module PF PF.i
swig -c++ -lua -Wall -module CEGUI CEGUI.i
mv *.cxx ../../bindings