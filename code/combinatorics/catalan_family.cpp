// Familia de Catalan e contagens de caminhos/selecoes classicas
//
// O que faz: Catalan, ballot (estrito e com empate), Narayana, Fuss-Catalan,
//   Motzkin, Delannoy, caminhos que tocam y=x+c (reflexao), prefixo >= -k,
//   escolher k sem vizinhos (linha e circulo, com folga d).
// Quando usar: "Catalogo > Combinatoria" (Bijecao, Reflexao e ballot, Catalan
//   disfarces e variantes, Escolher sem vizinhos, Cycle lemma / Fuss-Catalan).
// Complexidade: O(1) por consulta (Motzkin O(n), Delannoy O(min(m,n))).
// Requer: code/combinatorics/binom_mod.cpp (cole antes).
// Uso: precisa de fact/ifact/C (cole junto binom_mod.cpp, init_comb(N)).
//   catalan(n), ballot_strict(a,b), ballot_tie(a,b), narayana(n,k),
//   fuss(m,n) = # arvores m-arias com n nos, motzkin(n) (vetor 0..n),
//   delannoy(m,n), touch_line(n,m,c), prefix_ge(n,k),
//   nonadj_line(n,k), nonadj_circle(n,k), gap_pick(n,k,d).
// Cuidados: depende de binom_mod.cpp (nao repetido aqui). Indices fora dos
//   dominios devolvem 0. Catalan(n) = C(2n,n)/(n+1) = C(2n,n)-C(2n,n+1).
ll catalan(ll n) { return n < 0 ? 0 : (C(2 * n, n) - C(2 * n, n + 1) + MOD) % MOD; }
// A recebe a votos, B recebe b; A sempre estritamente a frente (a>b): (a-b)/(a+b) C(a+b,a)
ll ballot_strict(ll a, ll b) {
    if (a <= b) return 0;
    return (C(a + b, a) - C(a + b, a + 1) + MOD) % MOD; // equivale a (a-b)/(a+b)*C(a+b,a)
}
// A nunca atras (empates permitidos): (a-b+1)/(a+1) C(a+b,b)
ll ballot_tie(ll a, ll b) {
    if (a < b) return 0;
    return (C(a + b, b) - C(a + b, b - 1) + MOD) % MOD;
}
// Narayana: Dyck de 2n passos com k picos
ll narayana(ll n, ll k) {
    if (k < 1 || k > n) return 0;
    return C(n, k) * C(n, k - 1) % MOD * pw(n, MOD - 2) % MOD;
}
// Fuss-Catalan: arvores m-arias ordenadas com n nos = C(mn,n)/((m-1)n+1)
ll fuss(ll m, ll n) { return C(m * n, n) * pw((m - 1) * n + 1, MOD - 2) % MOD; }
// Motzkin M_0..M_n: (k+2)M_k = (2k+1)M_{k-1} + 3(k-1)M_{k-2}
vector<ll> motzkin(int n) {
    vector<ll> M(max(n + 1, 2)); M[0] = M[1] = 1;
    for (int k = 2; k <= n; k++)
        M[k] = ((2 * k + 1) * M[k-1] + 3LL * (k - 1) % MOD * M[k-2]) % MOD * pw(k + 2, MOD - 2) % MOD;
    return M;
}
// Delannoy: passos (1,0),(0,1),(1,1) de (0,0) a (m,n)
ll delannoy(ll m, ll n) {
    ll r = 0, p2 = 1;
    for (ll k = 0; k <= min(m, n); k++, p2 = p2 * 2 % MOD) r = (r + C(m, k) * C(n, k) % MOD * p2) % MOD;
    return r;
}
// Caminhos (passos direita/cima) (0,0)->(n,m) que TOCAM a reta y=x+c, c>0, quando
// o destino esta abaixo dela (m < n+c): reflete o destino -> C(n+m, n+c)
ll touch_line(ll n, ll m, ll c) {
    if (m >= n + c) return C(n + m, n); // destino na reta ou alem: todos tocam
    return C(n + m, n + c);
}
// Sequencias +-1 com n subidas e n descidas cujo minimo de prefixo >= -k: C(2n,n)-C(2n,n+k+1)
ll prefix_ge(ll n, ll k) { return (C(2 * n, n) - C(2 * n, n + k + 1) + MOD) % MOD; }
// Escolher k de n em linha sem dois adjacentes
ll nonadj_line(ll n, ll k) { return C(n - k + 1, k); }
// ... em circulo: n/(n-k) * C(n-k,k)
ll nonadj_circle(ll n, ll k) {
    if (k == 0) return 1;
    if (n - k <= 0 || n - k < k) return 0;
    return n % MOD * pw(n - k, MOD - 2) % MOD * C(n - k, k) % MOD;
}
// ... em linha com distancia >= d entre escolhidos (d=2 e nao adjacente)
ll gap_pick(ll n, ll k, ll d) { return k == 0 ? 1 : C(n - (k - 1) * (d - 1), k); }
