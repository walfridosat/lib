// Particoes de inteiros (numeros pentagonais de Euler e DPs em sqrt)
//
// O que faz: p(0..N) por pentagonais; particoes em partes distintas; tabela
//   p(n,k) = particoes de n em exatamente k partes (k<=K) em O(N*K); particoes
//   de n em exatamente k partes DISTINTAS q(n,k) (k<=sqrt(2n)).
// Quando usar: "Catalogo > Combinatoria" (Composicoes e particoes; dualidades e DP sqrt;
//   p(n) por pentagonos de Euler). Particoes com partes em conjunto S: knapsack
//   ilimitado (dp[j]+=dp[j-s]).
// Complexidade: part_pentagonal O(N sqrt N); part_exact_k O(N*K); part_distinct O(N sqrt N).
// Uso: part_pentagonal(N) -> vetor p[0..N]. part_exact_k(N,K) -> t[k][n].
//   part_distinct(N) -> vetor com # particoes em partes distintas (= em partes impares).
// Cuidados: mod arbitrario ok (nao usa inverso). Memoria de part_exact_k (K+1)*(N+1).
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
// t[k][n] = # particoes de n em exatamente k partes: p(n,k)=p(n-1,k-1)+p(n-k,k)
vector<vector<ll>> part_exact_k(int N, int K) {
    vector<vector<ll>> t(K + 1, vector<ll>(N + 1, 0));
    t[0][0] = 1;
    for (int k = 1; k <= K; k++)
        for (int n = k; n <= N; n++) t[k][n] = (t[k-1][n-1] + t[k][n-k]) % PMOD;
    return t;
}
// # particoes de n em partes distintas, para n=0..N: q(n,k)=q(n-k,k)+q(n-k,k-1)
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
