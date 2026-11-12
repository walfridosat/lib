// LGV - caminhos disjuntos em vertices
// Requer: code/combinatorics/binom_mod.cpp (cole antes, init_comb).
ll lgv_det(vector<vector<ll>> a) {
    int n = a.size(); ll d = 1;
    for (auto& r : a) for (auto& x : r) x = ((x % MOD) + MOD) % MOD;
    for (int c = 0; c < n; c++) {
        int pv = -1;
        for (int i = c; i < n; i++) if (a[i][c]) { pv = i; break; }
        if (pv < 0) return 0;
        if (pv != c) { swap(a[pv], a[c]); d = (MOD - d) % MOD; }
        d = d * a[c][c] % MOD;
        ll iv = pw(a[c][c], MOD - 2);
        for (int i = c + 1; i < n; i++) if (a[i][c]) {
            ll f = a[i][c] * iv % MOD;
            for (int j = c; j < n; j++) a[i][j] = ((a[i][j] - f * a[c][j]) % MOD + MOD) % MOD;
        }
    }
    return d;
}
ll lgv_grid(const vector<pair<ll,ll>>& A, const vector<pair<ll,ll>>& B) {
    int k = A.size();
    vector<vector<ll>> M(k, vector<ll>(k));
    for (int i = 0; i < k; i++) for (int j = 0; j < k; j++) {
        ll dx = B[j].first - A[i].first, dy = B[j].second - A[i].second;
        M[i][j] = (dx < 0 || dy < 0) ? 0 : C(dx + dy, dx);
    }
    return lgv_det(M);
}
/*LATEX_DESC_BEGIN***************************
-> **LGV - caminhos disjuntos em vertices**
Determinante de uma matriz de caminhos conta familias de caminhos disjuntos em vertices.

Complexidade: O(k^3 + k^2) consultas de binomial.
Uso:
  ll d = lgv_det(M);                  // matriz k x k mod p
  ll g = lgv_grid(A, B);              // A, B = vector<pair<ll,ll>>

* Sobre o codigo:
  lgv_det faz Gauss mod p com troca de linhas (sinal). lgv_grid monta
  M[i][j] = C(dx+dy, dx) quando o destino esta a direita e acima, e chama
  lgv_det. O determinante soma com sinal as familias de caminhos.

* Problemas e reducoes:
  + k caminhos disjuntos em vertices em um DAG -> lgv_det.
  + Caminhos monotonos disjuntos em grid -> lgv_grid.
  + Ladrilhos de losangos / particoes planas -> LGV.
  + Contar familias com origens e destinos compativeis -> lgv_grid.
  + Provar que so a permutacao identidade pode ser disjunta -> determinante.

Cuidados: so vale se toda familia disjunta induz a permutacao identidade
  (origens e destinos compativeis, ex. anti-diagonal ordenada); senao o
  determinante inclui sinais de outras permutacoes. Disjuntos em vertices.
Catalogo: Combinatoria.
Digitacao: 26 linhas | facil. Atalho: lgv_det e igual a det_mod de matrix_tree.cpp.
*****************************LATEX_DESC_END*/
