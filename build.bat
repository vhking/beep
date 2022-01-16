@echo off


IF NOT EXIST ..\build mkdir ..\build
pushd ..\build
pushd build
pwd
cl -Zi C:\Users\gamer\Documents\GitHub\beep\beep\main.cpp
popd