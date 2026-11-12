// Ciclos de permutacao - potencia, paridade, trocas, posto de gasolina
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
// move ao inicio/fim; parados = bloco consecutivo
int minMovesToSort(const vector<int>& p) {
    int n = p.size(); vector<int> pos(n); for (int i = 0; i < n; i++) pos[p[i]] = i;
    int best = 1, cur = 1;
    for (int v = 1; v < n; v++) { cur = pos[v] > pos[v - 1] ? cur + 1 : 1; best = max(best, cur); }
    return n - best;
}
// saldo = gain - cost; comeca apos o minimo do prefixo
int gasStart(const vector<ll>& gain, const vector<ll>& cost) {
    int n = gain.size(); ll s = 0, mn = 0; int arg = 0;
    for (int i = 0; i < n; i++) {
        s += gain[i] - cost[i];
        if (s < mn) mn = s, arg = i + 1;
    }
    if (s < 0) return -1;
    return arg % n;
}
/*LATEX_DESC_BEGIN***************************
-> **Ciclos de Permutacao**
Decompoe p em ciclos; p^k em O(n); min swaps; paridade; inversa; mover ao inicio/fim;
posto de gasolina circular. p 0-based (p[i] = para onde i vai).

Complexidade: O(n)
Uso:
  auto cs = cycles(p); vector<int> q = permPow(p, k);  // k ate 1e18
  int s = minSwaps(p), par = parity(p);
  vector<int> inv = invPerm(p);
  int mv = minMovesToSort(p);
  int g = gasStart(gain, cost);  // -1 se impossivel

* Sobre o codigo:
  permPow anda k % m passos dentro de cada ciclo.
  minSwaps = n - numero de ciclos; parity = minSwaps & 1.
  minMovesToSort = n - maior bloco consecutivo em ordem de posicao.
  gasStart acha o inicio apos o minimo do saldo prefixado.

* Problemas e reducoes:
  + Minimo de swaps arbitrarias para ordenar: minSwaps (adjacentes = inversoes).
  + Aplicar a mesma permutacao k vezes: permPow.
  + Mover elemento para o inicio/fim para ordenar: minMovesToSort.
  + Posto de gasolina circular: gasStart.

Cuidados: swaps adjacentes sao inversoes (veja inversoes.cpp), nao ciclos.
Catalogo: Arrays e guloso (Permutacao e um conjunto de ciclos, Potencia de permutacao, Mover elemento para o inicio, Circular com guloso)
Digitacao: 36 linhas | media.
*****************************LATEX_DESC_END*/
