@echo off


IF NOT EXIST .\build mkdir .\build
pushd .\build
pushd build
pwd
cl -Zi w:\beep\main.cpp
popd