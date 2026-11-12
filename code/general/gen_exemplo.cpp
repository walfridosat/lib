// Gerador de testes (exemplo para stress.sh / stress.bat)
//
// O que faz: gera um caso aleatorio pequeno determinado pela seed (argv[1]).
// Quando usar: junto com brute force. Catalogo > Quando nada funciona (Gerador de testes)
// Complexidade: O(n)
// Uso: ./gen SEED > in.txt   (arquivo standalone: tem include e main proprios; copie como gen.cpp)
// Cuidados: mantenha n e valores pequenos (n<=8, v<=5) para casos de borda aparecerem; varie parametros pela seed.
#include <bits/stdc++.h>
using namespace std;
int main(int argc, char** argv) {
    int seed = atoi(argv[1]);
    mt19937_64 rng(seed);
    auto R = [&](long long l, long long r) { return l + (long long)(rng() % (unsigned long long)(r - l + 1)); };
    int n = R(1, 8), V = R(1, 2) == 1 ? 3 : 20;   // alterna valores minusculos (muitos empates) e maiores
    printf("%d\n", n);
    for (int i = 0; i < n; i++) printf("%lld ", R(1, V));
    puts("");
    // arvore aleatoria:   for i in 2..n: printf("%lld %d\n", R(1,i-1), i);
    // permutacao: vector<int> p(n); iota(..); shuffle(p.begin(), p.end(), rng);
}
