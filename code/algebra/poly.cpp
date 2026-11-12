// Polinomios e series formais mod 998244353 (inv, ln, exp, sqrt, pow, divmod, multipoint, interpolacao)
//
// O que faz: operacoes de series formais por Newton, divisao de polinomios, avaliacao em
//   varios pontos, interpolacao rapida, shift de Taylor, produto de muitos polinomios,
//   numeros de Bernoulli.
// Quando usar: "[x^n] de F(G(x))", knapsack de contagem via exp/ln, particoes, Euler transform,
//   avaliar P em ~1e5 pontos, x^N mod f(x)
//   (Catalogo > Algebra, polinomios e FFT: Inverso de serie, ln/exp/sqrt/potencia, Divisao,
//   Multipoint, Interpolacao rapida, Taylor shift, Produto de muitos polinomios).
// Complexidade: inv/ln/exp/sqrt/pow O(n log n) (exp com constante grande); divmod O(n log n);
//   multipoint e interpolacao O(n log^2 n).
// Uso: P = vector<int> com coef. 0-based (P[i] = coef de x^i). Todas as funcoes "mod x^n" recebem n
//   e devolvem vetor de tamanho n.
//   inv(a,n) ln(a,n) exp(a,n) sqrt(a,n) pw_poly(a,k,n) divmod(a,b,q,r) multipoint(f,xs)
//   interpolate(xs,ys) taylor_shift(a,c) prod_all(vetor de polinomios) bernoulli(n)
// Cuidados: inv exige a[0]!=0; ln exige a[0]==1; exp exige a[0]==0; sqrt exige a[0]==1
//   (se a[0] e outro quadrado perfeito, escale; senao Tonelli-Shanks). pw_poly aceita k ate 1e18
//   e qualquer a (fatora x^t e a0^k usando k mod (MOD-1)). divmod exige b com lider != 0.
//   Entradas em [0, MOD). Tamanho maximo 2^23.
typedef vector<int> P;
const int MOD = 998244353, G = 3;
ll pw(ll b, ll e) {
    ll r = 1; b %= MOD; if (b < 0) b += MOD;
    for (; e; e >>= 1, b = b * b % MOD) if (e & 1) r = r * b % MOD;
    return r;
}
void ntt(P& a, bool inv) {
    int n = a.size();
    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1) j ^= bit;
        j ^= bit;
        if (i < j) swap(a[i], a[j]);
    }
    for (int len = 2; len <= n; len <<= 1) {
        ll w = pw(G, (MOD - 1) / len);
        if (inv) w = pw(w, MOD - 2);
        int h = len / 2;
        P ws(h); ws[0] = 1;
        for (int k = 1; k < h; k++) ws[k] = (ll)ws[k - 1] * w % MOD;
        for (int i = 0; i < n; i += len)
            for (int j = 0; j < h; j++) {
                int u = a[i + j], v = (ll)a[i + j + h] * ws[j] % MOD;
                a[i + j] = u + v >= MOD ? u + v - MOD : u + v;
                a[i + j + h] = u - v < 0 ? u - v + MOD : u - v;
            }
    }
    if (inv) { ll ni = pw(n, MOD - 2); for (auto& x : a) x = x * ni % MOD; }
}
P mul(P a, P b) {
    if (a.empty() || b.empty()) return {};
    int need = a.size() + b.size() - 1;
    if (min(a.size(), b.size()) <= 16) {
        P c(need, 0);
        for (size_t i = 0; i < a.size(); i++)
            for (size_t j = 0; j < b.size(); j++)
                c[i + j] = (c[i + j] + (ll)a[i] * b[j]) % MOD;
        return c;
    }
    int n = 1;
    while (n < need) n <<= 1;
    a.resize(n); b.resize(n);
    ntt(a, false); ntt(b, false);
    for (int i = 0; i < n; i++) a[i] = (ll)a[i] * b[i] % MOD;
    ntt(a, true);
    a.resize(need);
    return a;
}
P cut(P a, int n) { a.resize(n); return a; } // trunca / completa com zeros
P add(P a, const P& b) {
    if (a.size() < b.size()) a.resize(b.size());
    for (size_t i = 0; i < b.size(); i++) a[i] = (a[i] + b[i]) % MOD;
    return a;
}
P sub(P a, const P& b) {
    if (a.size() < b.size()) a.resize(b.size());
    for (size_t i = 0; i < b.size(); i++) a[i] = (a[i] - b[i] + MOD) % MOD;
    return a;
}
void trim(P& a) { while (!a.empty() && a.back() == 0) a.pop_back(); }
P deriv(const P& a) {
    if (a.size() <= 1) return {};
    P r(a.size() - 1);
    for (size_t i = 1; i < a.size(); i++) r[i - 1] = (ll)a[i] * i % MOD;
    return r;
}
P integ(const P& a) { // integral com constante 0
    P r(a.size() + 1, 0), iv(a.size() + 2, 1);
    for (size_t i = 2; i < iv.size(); i++) iv[i] = (ll)(MOD - MOD / i) * iv[MOD % i] % MOD; // inversos lineares
    for (size_t i = 0; i < a.size(); i++) r[i + 1] = (ll)a[i] * iv[i + 1] % MOD;
    return r;
}
P inv(const P& a, int n) { // 1/a mod x^n (Newton: b <- b(2 - ab))
    P b = {(int)pw(a[0], MOD - 2)};
    for (int m = 1; m < n; m <<= 1) {
        P t = mul(cut(a, 2 * m), b);
        t.resize(2 * m);
        for (auto& x : t) x = x ? MOD - x : 0;
        t[0] = (t[0] + 2) % MOD;
        b = mul(b, t);
        b.resize(2 * m);
    }
    b.resize(n);
    return b;
}
P ln(const P& a, int n) { // a[0] == 1
    P r = integ(mul(deriv(a), inv(a, n)));
    r.resize(n);
    return r;
}
P exp(const P& a, int n) { // a[0] == 0 (Newton: b <- b(1 - ln b + a))
    P b = {1};
    for (int m = 1; m < n; m <<= 1) {
        P t = sub(cut(a, 2 * m), ln(b, 2 * m));
        t[0] = (t[0] + 1) % MOD;
        b = mul(b, t);
        b.resize(2 * m);
    }
    b.resize(n);
    return b;
}
P sqrt_poly(const P& a, int n) { // a[0] == 1 (Newton: b <- (b + a/b)/2)
    P b = {1};
    ll i2 = (MOD + 1) / 2;
    for (int m = 1; m < n; m <<= 1) {
        P t = mul(cut(a, 2 * m), inv(b, 2 * m));
        t.resize(2 * m);
        b.resize(2 * m);
        for (int i = 0; i < 2 * m; i++) b[i] = (b[i] + t[i]) * i2 % MOD;
    }
    b.resize(n);
    return b;
}
P pw_poly(const P& a, ll k, int n) { // a^k mod x^n, k <= 1e18
    int t = 0;
    while (t < (int)a.size() && a[t] == 0) t++;
    if (t == (int)a.size()) return k == 0 ? cut({1}, n) : P(n, 0);
    if ((__int128)t * k >= n) return P(n, 0);
    int sh = t * k; // a = x^t * c * (1 + ...)
    ll c = a[t], ci = pw(c, MOD - 2);
    P b(a.begin() + t, a.end());
    for (auto& x : b) x = x * ci % MOD;
    P l = ln(cut(b, n - sh), n - sh);
    for (auto& x : l) x = x * (k % MOD) % MOD; // k mod p para o expoente da serie
    P e = exp(l, n - sh);
    ll f = pw(c, k % (MOD - 1)); // c^k usa k mod (p-1)
    P r(n, 0);
    for (int i = 0; i < n - sh; i++) r[i + sh] = e[i] * f % MOD;
    return r;
}
void divmod(P a, P b, P& q, P& r) { // a = q*b + r, grau r < grau b
    trim(a); trim(b);
    int n = a.size(), m = b.size();
    if (n < m) { q.clear(); r = a; return; }
    P ra(a.rbegin(), a.rend()), rb(b.rbegin(), b.rend());
    q = mul(cut(ra, n - m + 1), inv(rb, n - m + 1));
    q.resize(n - m + 1);
    reverse(q.begin(), q.end());
    r = sub(a, mul(q, b));
    r.resize(m - 1);
    trim(r);
}
// ---- multipoint e interpolacao (arvore de produtos) ----
vector<P> tr;
void build(int v, int l, int r, const P& xs) { // tr[v] = prod (x - xs[i]), i em [l,r)
    if (r - l == 1) { tr[v] = {(int)((MOD - xs[l]) % MOD), 1}; return; }
    int m = (l + r) / 2;
    build(2 * v, l, m, xs); build(2 * v + 1, m, r, xs);
    tr[v] = mul(tr[2 * v], tr[2 * v + 1]);
}
void evalrec(int v, int l, int r, const P& f, P& res) { // f ja reduzido mod tr[v]
    if (r - l == 1) { res[l] = f.empty() ? 0 : f[0]; return; }
    int m = (l + r) / 2;
    P q, rr;
    divmod(f, tr[2 * v], q, rr); evalrec(2 * v, l, m, rr, res);
    divmod(f, tr[2 * v + 1], q, rr); evalrec(2 * v + 1, m, r, rr, res);
}
P multipoint(const P& f, const P& xs) { // [f(xs[0]), f(xs[1]), ...]
    int n = xs.size();
    if (n == 0) return {};
    tr.assign(4 * n, P());
    build(1, 0, n, xs);
    P q, r, res(n);
    divmod(f, tr[1], q, r);
    evalrec(1, 0, n, r, res);
    return res;
}
P combine(int v, int l, int r, const P& c) { // sum c_i * prod_{j!=i}(x - x_j)
    if (r - l == 1) return {c[l]};
    int m = (l + r) / 2;
    return add(mul(combine(2 * v, l, m, c), tr[2 * v + 1]), mul(combine(2 * v + 1, m, r, c), tr[2 * v]));
}
P interpolate(const P& xs, const P& ys) { // polinomio de grau < n passando por (xs[i], ys[i]); xs distintos
    int n = xs.size();
    if (n == 0) return {};
    tr.assign(4 * n, P());
    build(1, 0, n, xs);
    P d = deriv(tr[1]), dv(n), c(n), q, r;
    divmod(d, tr[1], q, r); // d tem grau n-1 < n, nao muda
    evalrec(1, 0, n, d, dv);
    for (int i = 0; i < n; i++) c[i] = (ll)ys[i] * pw(dv[i], MOD - 2) % MOD;
    P res = combine(1, 0, n, c);
    res.resize(n);
    return res;
}
P taylor_shift(const P& a, ll c) { // retorna b com b(x) = a(x + c)
    int n = a.size();
    vector<ll> f(n + 1, 1), fi(n + 1);
    for (int i = 1; i <= n; i++) f[i] = f[i - 1] * i % MOD;
    fi[n] = pw(f[n], MOD - 2);
    for (int i = n; i > 0; i--) fi[i - 1] = fi[i] * i % MOD;
    P A(n), B(n);
    ll cp = 1; c %= MOD; if (c < 0) c += MOD;
    for (int i = 0; i < n; i++) {
        A[n - 1 - i] = a[i] * f[i] % MOD;      // a_i * i! invertido
        B[i] = cp * fi[i] % MOD; cp = cp * c % MOD; // c^i / i!
    }
    P C = mul(A, B);
    P res(n);
    for (int j = 0; j < n; j++) res[j] = C[n - 1 - j] * fi[j] % MOD;
    return res;
}
P prod_all(vector<P> v) { // produto de varios polinomios por D&C (pares do mesmo tamanho)
    if (v.empty()) return {1};
    while (v.size() > 1) {
        vector<P> w;
        for (size_t i = 0; i + 1 < v.size(); i += 2) w.push_back(mul(v[i], v[i + 1]));
        if (v.size() & 1) w.push_back(v.back());
        v = w;
    }
    return v[0];
}
P bernoulli(int n) { // B_0..B_n (B_1 = -1/2), via x / (e^x - 1)
    vector<ll> f(n + 2, 1);
    for (int i = 1; i <= n + 1; i++) f[i] = f[i - 1] * i % MOD;
    P a(n + 1); // (e^x - 1)/x = sum x^i/(i+1)!
    ll fi = pw(f[n + 1], MOD - 2);
    vector<ll> ifac(n + 2); ifac[n + 1] = fi;
    for (int i = n + 1; i > 0; i--) ifac[i - 1] = ifac[i] * i % MOD;
    for (int i = 0; i <= n; i++) a[i] = ifac[i + 1];
    P b = inv(a, n + 1);
    for (int i = 0; i <= n; i++) b[i] = b[i] * f[i] % MOD; // B_i = i! * [x^i]
    return b;
}
