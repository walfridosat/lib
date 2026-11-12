// Permutacoes especiais - desarranjos, inversoes, zigzag
// Requer: code/combinatorics/binom_mod.cpp (cole antes).
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
// sem prefixo que seja permutacao de 1..j
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
// # perms com k inversoes (prefix sums)
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
// Euler zigzag via triangulo de Entringer
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
/*LATEX_DESC_BEGIN***************************
-> **Permutacoes especiais**
Desarranjos, pontos fixos, involucoes, indecomponiveis, tabela de inversoes e Euler zigzag.

Complexidade: derangements/involutions/indecomposable O(n) ou O(n^2); inversions O(n K).
Uso:
  vector<ll> D = derangements(N);
  ll fp = fixed_points(n, k, D);
  vector<ll> I = involutions(N), ind = indecomposable(N);
  vector<ll> inv = inversions_table(n, K);
  vector<ll> A = alternating(N);

* Sobre o codigo:
  D_n = (n-1)(D_{n-1}+D_{n-2}); I_n = I_{n-1}+(n-1)I_{n-2}.
  indecomposable subtrai as decomposicoes por prefixo. inversions_table usa
  prefix sums porque inserir i cria 0..i-1 inversoes. alternating usa o
  triangulo de Entringer.

* Problemas e reducoes:
  + Permutacoes sem ponto fixo -> derangements.
  + Permutacoes com exatamente k pontos fixos -> fixed_points.
  + Involucoes (ciclos de tamanho 1 ou 2) -> involutions.
  + Permutacoes indecomponiveis -> indecomposable.
  + Permutacoes com k inversoes -> inversions_table.
  + Permutacoes alternantes (up/down) -> alternating.
  + Numero de Euler zigzag -> alternating.

Cuidados: inversions_table devolve k = 0..K (K pode passar de n(n-1)/2;
  termos extras sao 0); fixed_points precisa de C e de D.
Catalogo: Combinatoria.
Digitacao: 49 linhas | media. Atalho: derangements/involutions/indecomposable repetem alocacao de vetor.
*****************************LATEX_DESC_END*/
