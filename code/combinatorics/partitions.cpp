// Particoes de inteiros - pentagonais e DP
const ll PMOD = 998244353;
vector<ll> part_pentagonal(int N) {
    vector<ll> p(N + 1, 0); p[0] = 1;
    for (int n = 1; n <= N; n++) {
        ll s = 0;
        for (int k = 1; ; k++) {
            ll g1 = (ll)k * (3 * k - 1) / 2, g2 = (ll)k * (3 * k + 1) / 2; // pentagonais generalizados
            if (g1 > n) break;
            ll t = p[n - g1] + (g2 <= n ? p[n - g2] : 0);
            s += (k & 1) ? t : -t;
        }
        p[n] = ((s % PMOD) + PMOD) % PMOD;
    }
    return p;
}
// p(n,k) = p(n-1,k-1) + p(n-k,k)
vector<vector<ll>> part_exact_k(int N, int K) {
    vector<vector<ll>> t(K + 1, vector<ll>(N + 1, 0));
    t[0][0] = 1;
    for (int k = 1; k <= K; k++)
        for (int n = k; n <= N; n++) t[k][n] = (t[k-1][n-1] + t[k][n-k]) % PMOD;
    return t;
}
// q(n,k) = q(n-k,k) + q(n-k,k-1)
vector<ll> part_distinct(int N) {
    int K = 0; while ((ll)(K + 1) * (K + 2) / 2 <= N) K++; // k(k+1)/2 <= N
    vector<vector<ll>> q(K + 1, vector<ll>(N + 1, 0));
    q[0][0] = 1;
    vector<ll> res(N + 1, 0); res[0] = 1;
    for (int k = 1; k <= K; k++)
        for (int n = k; n <= N; n++) {
            q[k][n] = (q[k][n-k] + q[k-1][n-k]) % PMOD;
            res[n] = (res[n] + q[k][n]) % PMOD;
        }
    return res;
}
/*LATEX_DESC_BEGIN***************************
-> **Particoes de inteiros**
p(n) por pentagonais de Euler, particoes em exatamente k partes e em partes distintas.

Complexidade: part_pentagonal O(N sqrt N); part_exact_k O(N K); part_distinct O(N sqrt N).
Uso:
  vector<ll> p = part_pentagonal(N);      // p[0..N]
  vector<vector<ll>> t = part_exact_k(N, K);  // t[k][n]
  vector<ll> q = part_distinct(N);

* Sobre o codigo:
  part_pentagonal usa p(n) = sum (-1)^(k-1) (p(n-g1) + p(n-g2)) com os
  pentagonais generalizados. part_exact_k usa p(n,k) = p(n-1,k-1) + p(n-k,k).
  part_distinct usa q(n,k) = q(n-k,k) + q(n-k,k-1), com k <= sqrt(2n).

* Problemas e reducoes:
  + Numero de particoes de n -> part_pentagonal.
  + Particoes de n em exatamente k partes -> part_exact_k.
  + Particoes em partes distintas/impares -> part_distinct.
  + Particoes com partes de um conjunto S -> knapsack ilimitado.
  + Numero de composicoes de n (partes ordenadas) -> 2^(n-1).
  + Particoes em partes limitadas por k -> DP de part_exact_k.

Cuidados: mod arbitrario ok (nao usa inverso); memoria de part_exact_k e
  (K+1)*(N+1).
Catalogo: Combinatoria.
Digitacao: 36 linhas | facil. Atalho: part_exact_k e part_distinct compartilham a DP; unificar.
*****************************LATEX_DESC_END*/
