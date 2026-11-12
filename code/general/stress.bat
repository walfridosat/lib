@echo off
rem Stress test (Windows cmd). Uso: stress.bat [N]   (precisa de sol.cpp brute.cpp gen.cpp na pasta)
rem Catalogo > Quando nada funciona (Gerador de testes). gen recebe a seed em argv[1].
set N=%1
if "%N%"=="" set N=1000
g++ -std=c++17 -O2 -o sol.exe sol.cpp || exit /b 1
g++ -std=c++17 -O2 -o brute.exe brute.cpp || exit /b 1
g++ -std=c++17 -O2 -o gen.exe gen.cpp || exit /b 1
for /l %%i in (1,1,%N%) do (
    gen.exe %%i > in.txt
    sol.exe < in.txt > out_sol.txt
    brute.exe < in.txt > out_brute.txt
    fc out_sol.txt out_brute.txt > nul || (echo DIFERENTE na seed %%i & type in.txt & exit /b 1)
)
echo OK %N% casos
