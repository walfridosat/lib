// Elemento majoritario - Boyer-Moore, > n/k e aleatorizado
ll majority(const vector<ll>& a) {
    ll cand = 0; int cnt = 0;
    for (ll x : a) { if (cnt == 0) cand = x, cnt = 1; else cnt += (x == cand) ? 1 : -1; }
    return count(a.begin(), a.end(), cand) * 2 > (ll)a.size() ? cand : -1;
}
vector<ll> heavyHitters(const vector<ll>& a, int k) {
    map<ll, int> c;
    for (ll x : a) {
        c[x]++;
        if ((int)c.size() >= k) {     // remove 1 de cada um dos k valores distintos
            for (auto it = c.begin(); it != c.end();) { if (--it->second == 0) it = c.erase(it); else ++it; }
        }
    }
    vector<ll> res;
    for (auto& [v, _] : c) if ((ll)count(a.begin(), a.end(), v) * k > (ll)a.size()) res.push_back(v);
    return res;
}
ll majorityRandom(const vector<ll>& a, int iter = 30) {
    static mt19937_64 rg(chrono::steady_clock::now().time_since_epoch().count());
    for (int t = 0; t < iter; t++) {
        ll x = a[rg() % a.size()];
        if (count(a.begin(), a.end(), x) * 2 > (ll)a.size()) return x;
    }
    return -1;
}
/*LATEX_DESC_BEGIN***************************
-> **Elemento Majoritario**
Candidatos com frequencia > n/k em O(k) de memoria; versao aleatoria para >= metade.

Complexidade: O(n k); O(iter * n) na aleatoria
Uso:
  ll m = majority(a);                 // -1 se nao ha > n/2
  vector<ll> h = heavyHitters(a, k);  // freq > n/k
  ll r = majorityRandom(a, 30);

* Sobre o codigo:
  majority cancela pares diferentes (Boyer-Moore) e confirma em segunda passada.
  heavyHitters mantem no maximo k contadores e remove 1 de cada quando enche.
  majorityRandom sorteia candidatos e confirma por contagem.

* Problemas e reducoes:
  + Elemento que aparece mais de n/2 vezes: majority.
  + Elementos com frequencia > n/k: heavyHitters.
  + gcd/valor compartilhado por muitos: majorityRandom.

Cuidados: SEMPRE confirme o candidato com segunda passada (aqui ja confirmamos);
  valores tratados como int/ll.
Catalogo: Arrays e guloso (Boyer-Moore), Aleatorizacao (Elemento frequente)
Digitacao: 25 linhas | facil.
*****************************LATEX_DESC_END*/
