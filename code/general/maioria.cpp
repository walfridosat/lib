// Elemento majoritario: Boyer-Moore, > n/k, e versao aleatorizada
//
// O que faz: acha candidatos a elemento com frequencia > n/k em O(1)·k de memoria; versao aleatoria para "aparece em >= metade".
// Quando usar: "elemento > n/2", "gcd de pelo menos metade", "resposta compartilhada por muitos".
//              Catalogo > Arrays e guloso (Boyer-Moore), Aleatorizacao (Elemento frequente)
// Complexidade: O(n k) / O(iter * n)
// Uso: majority(a) -> valor ou -1 se nao ha (> n/2). heavyHitters(a, k) -> valores com freq > n/k.
//      majorityRandom(a, iter=30): sorteia candidatos (acerta c.p. >= 1/2 por tentativa se existe).
// Cuidados: SEMPRE confirmar o candidato com segunda passada (aqui ja confirmamos); valores usados como int/ll.
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
