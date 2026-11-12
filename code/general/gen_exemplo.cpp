// Gerador de testes - caso aleatorio pela seed (stress)
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
/*LATEX_DESC_BEGIN***************************
-> **Gerador de Testes (exemplo)**
Gera um caso aleatorio pequeno determinado pela seed em argv[1], para stress test.

Complexidade: O(n)
Uso:
  ./gen SEED > in.txt   // arquivo standalone com include e main proprios

* Sobre o codigo:
  n e V sao pequenos para aparecerem muitos empates e casos de borda.
  Ha linhas comentadas para gerar arvore aleatoria ou permutacao.

* Problemas e reducoes:
  + Stress test: combine com brute force e stress.sh/stress.bat.

Cuidados: mantenha n e valores pequenos (n <= 8, v <= 5); varie parametros pela seed.
Catalogo: Quando nada funciona (Gerador de testes)
Digitacao: 13 linhas | facil.
*****************************LATEX_DESC_END*/
