@echo off

set source=%cd%\main.cpp

pushd build


cl %source% /link user32.lib

popd

copy build\main.exe main.exe