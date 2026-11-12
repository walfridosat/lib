// Hash anti-hack - splitmix64 com semente aleatoria
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
struct CH {
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15ULL;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9ULL;
        x = (x ^ (x >> 27)) * 0x94d049bb133111ebULL;
        return x ^ (x >> 31);
    }
    size_t operator()(uint64_t x) const {
        static const uint64_t R = chrono::steady_clock::now().time_since_epoch().count(); // semente por execucao
        return splitmix64(x + R);
    }
};
struct CHP {
    size_t operator()(const pair<ll, ll>& p) const {
        return CH()(CH()(p.first) ^ ((uint64_t)p.second * 0x9e3779b97f4a7c15ULL));
    }
};
/*LATEX_DESC_BEGIN***************************
-> **Hash Anti-Hack**
splitmix64 com semente aleatoria para unordered_map, unordered_set e gp_hash_table.

Complexidade: O(1) esperado por operacao
Uso:
  unordered_map<ll, int, CH> m;
  gp_hash_table<ll, int, CH> g;   // m.reserve(1<<20) acelera
  // chave pair<ll,ll>: use CHP

* Sobre o codigo:
  CH::operator() soma uma semente por execucao e aplica splitmix64.
  CHP combina as duas metades do pair com o mesmo multiplicador.

* Problemas e reducoes:
  + Evitar hacks de unordered_map em Codeforces: use CH.

Cuidados: se so precisa de contagem, sort + busca binaria costuma ser mais seguro.
Catalogo: Aleatorizacao (Anti-hack, Hash de unordered_map)
Digitacao: 19 linhas | facil.
*****************************LATEX_DESC_END*/
