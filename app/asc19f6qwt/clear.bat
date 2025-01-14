@echo off



@del *.Debug
@del *.Release
@del *.user
@del *.stash
@del *.rc

@del cmake_install.cmake
@del Makefile
@del CMakeCache.txt
@rd ascemqwt_autogen /s /q
@rd bin /s /q
@rd build /s /q
@rd debug /s /q
@rd release /s /q
@rd release /s /q
@rd CMakeFiles /s /q

@rd ../build-ascemqwt-Desktop_Qt_5_15_2_MinGW_32_bit-Debug /s /q


@copy %CD%+"bin/release/windows/ascemqwt.exe" %CD%+"../../dist/ascemqwt.exe"

@rd bin /s /q
