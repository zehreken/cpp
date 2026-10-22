@echo off
rem Build with Ninja, configuring build/ on first run. Ninja needs the MSVC
rem environment (INCLUDE/LIB), which the Visual Studio generator used to set up
rem implicitly. Extra args pass through, e.g.  build.cmd --target graph
setlocal
set "VSWHERE=%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe"
if not exist "%VSWHERE%" (
    echo ERROR: vswhere.exe not found - is Visual Studio installed?
    exit /b 1
)
for /f "usebackq tokens=*" %%i in (`"%VSWHERE%" -latest -products * -property installationPath`) do set "VSPATH=%%i"
if not defined VSPATH (
    echo ERROR: no Visual Studio installation found.
    exit /b 1
)
call "%VSPATH%\VC\Auxiliary\Build\vcvars64.bat" >nul
if errorlevel 1 exit /b 1
if not exist build\CMakeCache.txt (
    cmake -B build -G Ninja
    if errorlevel 1 exit /b 1
)
cmake --build build %*
