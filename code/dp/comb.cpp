ll fact[MAXN], invFact[MAXN];
 
void precompute() {
    fact[0] = invFact[0] = 1;
    for (int i = 1; i < MAXN; i++) {
        fact[i] = (fact[i - 1] * i) % M;
        invFact[i] = modExp(fact[i], M - 2, M);
    }
}

ll binomial(ll n, ll k) {
    if (k > n || k < 0) return 0;
    return fact[n] * invFact[k] % M * invFact[n - k] % M;
}