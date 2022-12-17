@echo off
call D:\KOD\KOD-2022\Debug\KOD-2022.exe -in:D:\KOD\KOD-2022\KOD-2022\example.txt -out:D:\KOD\Generation\Generation\Gen.asm
call D:\VS\VC\Auxiliary\Build\vcvarsall.bat x86
ml /c D:\KOD\Generation\Generation\Gen.asm
link /OPT:NOREF /OUT:Generation.exe /SUBSYSTEM:CONSOLE GenLib.lib Gen.obj stdafx.obj
call Generation.exe
pause