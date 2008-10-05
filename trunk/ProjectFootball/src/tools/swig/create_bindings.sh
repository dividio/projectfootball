#!/bin/sh
swig -c++ -lua -Wall -module PF PF.i
mv *.cxx ../../bindings