@echo off

pushd ..
Vendor\Binaries\Premake\Windows\premake5.exe --CC=gcc  gmake2
popd
pause