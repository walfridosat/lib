// Ciclos de permutacao, potencia, paridade, trocas minimas
//
// O que faz: decompoe permutacao em ciclos; p^k em O(n); minimo de trocas arbitrarias; paridade; inversa;
//            "mover para o inicio/fim para ordenar"; posto de gasolina circular.
// Quando usar: "swaps para ordenar", "aplicar operacao k vezes", "permutacao ciclica". Catalogo > Arrays e guloso
//              (Permutacao e um conjunto de ciclos, Potencia de permutacao, Mover elemento para o inicio, Circular com guloso)
// Complexidade: O(n)
// Uso: p 0-based (p[i] = para onde i vai). cycles(p) -> lista de ciclos; permPow(p, k) (k pode ser ate 1e18);
//      minSwaps(p) = n - #ciclos; parity(p) = (n - #ciclos) & 1 (1 = impar);
//      minMovesToSort(p) (so mover ao inicio OU fim, qualquer um): n - maior bloco de valores consecutivos em ordem de posicao;
//      gasStart(gain, cost) -> indice de partida para dar a volta ou -1.
// Cuidados: swaps adjacentes = inversoes (ver inversoes.cpp), nao ciclos.
vector<vector<int>> cycles(const vector<int>& p) {
    int n = p.size(); vector<bool> vis(n, false); vector<vector<int>> res;
    for (int i = 0; i < n; i++) if (!vis[i]) {
        vector<int> c; for (int j = i; !vis[j]; j = p[j]) vis[j] = true, c.push_back(j);
        res.push_back(c);
    }
    return res;
}
vector<int> permPow(const vector<int>& p, ll k) {
    vector<int> r(p.size());
    for (auto& c : cycles(p)) {
        int m = c.size(); ll s = k % m;
        for (int i = 0; i < m; i++) r[c[i]] = c[(i + s) % m];   // anda s passos no ciclo
    }
    return r;
}
int minSwaps(const vector<int>& p) { return p.size() - cycles(p).size(); }
int parity(const vector<int>& p) { return minSwaps(p) & 1; }
vector<int> invPerm(const vector<int>& p) { vector<int> q(p.size()); for (size_t i = 0; i < p.size(); i++) q[p[i]] = i; return q; }
// p e permutacao de 0..n-1 (valor em cada posicao). Operacao: tirar um elemento e coloca-lo no inicio ou no fim.
// Os que ficam parados formam um bloco de valores consecutivos v, v+1, ..., em ordem crescente de posicao.
int minMovesToSort(const vector<int>& p) {
    int n = p.size(); vector<int> pos(n); for (int i = 0; i < n; i++) pos[p[i]] = i;
    int best = 1, cur = 1;
    for (int v = 1; v < n; v++) { cur = pos[v] > pos[v - 1] ? cur + 1 : 1; best = max(best, cur); }
    return n - best;
}
// posto de gasolina circular: saldo[i] = gain[i] - cost[i]; comeca apos o minimo do prefixo
int gasStart(const vector<ll>& gain, const vector<ll>& cost) {
    int n = gain.size(); ll s = 0, mn = 0; int arg = 0;
    for (int i = 0; i < n; i++) {
        s += gain[i] - cost[i];
        if (s < mn) mn = s, arg = i + 1;
    }
    if (s < 0) return -1;
    return arg % n;
}
