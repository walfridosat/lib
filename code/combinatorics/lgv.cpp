// Lindstrom-Gessel-Viennot (caminhos disjuntos em vertices)
//
// O que faz: dado e[i][j] = # caminhos de a_i ate b_j em um DAG, devolve
//   det(e) = (# familias de caminhos disjuntos em vertices com permutacao identidade)
//   - ... (com sinais das permutacoes). Se so a identidade pode ser disjunta, e
//   exatamente o numero de familias. Versao pronta para grid (direita/cima).
// Quando usar: "Catalogo > Combinatoria" (LGV; ladrilhos de losangos, particoes planas)
//   e "Repetidas": k caminhos que nao se tocam em grid.
// Complexidade: O(k^3 + k^2) consultas de binomial.
// Uso: lgv_det(M) det mod p de matriz k x k (vetor<vector<ll>>).
//   lgv_grid(A, B): A[i]=(x,y) origens, B[j]=(x,y) destinos, passos (x+1) ou (y+1);
//   precisa de C(n,k) de binom_mod.cpp (cole antes, init_comb).
// Requer: code/combinatorics/binom_mod.cpp (cole antes, init_comb).
// Cuidados: so valido se TODA familia disjunta induz a permutacao identidade (origens
//   e destinos "compativeis": ex. origens ao longo de uma anti-diagonal ordenadas
//   de forma monotona). Caso contrario o determinante inclui sinais de outras
//   permutacoes. Dois caminhos disjuntos em VERTICES (nao so em arestas).
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
