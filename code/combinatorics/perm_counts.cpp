// Contagens de permutacoes especiais
//
// O que faz: desarranjos D_n, perms com exatamente k pontos fixos, involucoes,
//   permutacoes indecomponiveis, # perms com k inversoes (Mahoniano, tabela
//   O(n*K) com prefix sums), zigue-zague (Entringer/Euler), Catalan de padrao evitado fica em catalan_family.
// Quando usar: "Catalogo > Combinatoria" (Desarranjos e permutacoes especiais, Inversoes,
//   Permutacoes indecomponiveis, Zigue-zague). Eulerianos e Stirling 1a: stirling_bell.cpp.
// Complexidade: derange/involutions/indecomposable O(n) ou O(n^2); inversions O(n*K).
// Requer: code/combinatorics/binom_mod.cpp (cole antes).
// Uso: derangements(N) -> D[0..N]; fixed_points(n,k) (precisa binom_mod.cpp);
//   involutions(N); indecomposable(N); inversions_table(n,K) -> v[k] = # perms de n com k inversoes;
//   alternating(N) -> E[0..N] (up/down, 1,1,1,2,5,16,61...).
// Cuidados: inversions_table devolve k=0..K (K pode ser > n(n-1)/2, termos extras = 0).
vector<ll> derangements(int N) { // D_n = (n-1)(D_{n-1}+D_{n-2})
    vector<ll> D(max(N + 1, 2)); D[0] = 1; D[1] = 0;
    for (int n = 2; n <= N; n++) D[n] = (n - 1) * (D[n-1] + D[n-2]) % MOD;
    return D;
}
ll fixed_points(int n, int k, const vector<ll>& D) { return C(n, k) * D[n-k] % MOD; } // C(n,k) D_{n-k}
vector<ll> involutions(int N) { // I_n = I_{n-1}+(n-1)I_{n-2}
    vector<ll> I(max(N + 1, 2)); I[0] = I[1] = 1;
    for (int n = 2; n <= N; n++) I[n] = (I[n-1] + (n - 1) * I[n-2]) % MOD;
    return I;
}
// Indecomponiveis (nenhum prefixo e permutacao de 1..j para j<n): I(n)=n!-sum_{j<n} I(j)(n-j)!
vector<ll> indecomposable(int N) {
    vector<ll> I(N + 1), f(N + 1); f[0] = 1;
    for (int i = 1; i <= N; i++) f[i] = f[i-1] * i % MOD;
    for (int n = 1; n <= N; n++) {
        ll s = f[n];
        for (int j = 1; j < n; j++) s = (s - I[j] * f[n-j]) % MOD;
        I[n] = (s + MOD) % MOD;
    }
    return I;
}
// v[k] = # perms de n com k inversoes: inserir i adiciona 0..i-1 inversoes -> prefix sum
vector<ll> inversions_table(int n, int K) {
    vector<ll> dp(K + 1, 0), nd(K + 1);
    dp[0] = 1;
    for (int i = 1; i <= n; i++) {
        ll run = 0; // nd[k] = sum_{j=k-i+1..k} dp[j]
        for (int k = 0; k <= K; k++) {
            run += dp[k];
            if (k - i >= 0) run -= dp[k - i];
            run %= MOD; if (run < 0) run += MOD;
            nd[k] = run;
        }
        dp = nd;
    }
    return dp;
}
// Numeros alternantes (Euler zigzag) A_0..A_N via triangulo de Entringer (O(N^2))
vector<ll> alternating(int N) {
    vector<ll> A(N + 1), row = {1}, nr;
    A[0] = 1;
    for (int n = 1; n <= N; n++) {
        nr.assign(n + 1, 0);               // E(n,k)=E(n,k-1)+E(n-1,n-k)
        for (int k = 1; k <= n; k++) nr[k] = (nr[k-1] + row[n - k]) % MOD;
        row = nr; A[n] = row[n];
    }
    return A;
}
