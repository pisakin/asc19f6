@echo off



@del *.Debug
@del *.Release
@del *.user
@del *.stash
@del *.rc
@del *.oven
@del *.ascgm
@del *.ascgbm
@del *.ascgmm
@del *.ascmu
@del *.ascvn
@del *.combivert

@del cmake_install.cmake
@del Makefile
@del CMakeCache.txt
@rd cascemtorque_autogen /s /q
@rd build /s /q
@rd debug /s /q
@rd release /s /q
@rd release /s /q
@rd CMakeFiles /s /q

@copy %CD%+"bin/release/windows/ascemtorque.exe" %CD%+"../../dist/ascemtorque.exe"

@rd bin /s /q
