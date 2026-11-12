#!/bin/bash
# Uso: bash stress.sh [N]  (N = 1000 se omitido)
# Requer sol.cpp, brute.cpp e gen.cpp na mesma pasta.
# Stress test (bash)
#
# O que faz: compila sol.cpp, brute.cpp e gen.cpp, roda N casos aleatorios e para no primeiro que diverge.
# Quando usar: WA sem causa aparente. Catalogo > Quando nada funciona (Gerador de testes, Stress test)
# Complexidade: -
# Uso: ./stress.sh [N=1000]   (gen recebe a seed como argv[1]; ver gen_exemplo.cpp)
# Cuidados: brute deve imprimir no mesmo formato; se ha varias respostas validas, escreva um checker.
#           Ao achar diferenca, o caso fica em in.txt (reduza n no gerador e rode de novo).
N=${1:-1000}
g++ -std=c++17 -O2 -o sol sol.cpp || exit 1
g++ -std=c++17 -O2 -o brute brute.cpp || exit 1
g++ -std=c++17 -O2 -o gen gen.cpp || exit 1
for ((i = 1; i <= N; i++)); do
    ./gen $i > in.txt
    ./sol < in.txt > out_sol.txt
    ./brute < in.txt > out_brute.txt
    if ! diff -q out_sol.txt out_brute.txt > /dev/null; then
        echo "DIFERENTE na seed $i"; cat in.txt; echo "--- sol"; cat out_sol.txt; echo "--- brute"; cat out_brute.txt
        exit 1
    fi
done
echo "OK $N casos"
