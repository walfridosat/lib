const int MOD = 998244353;
const int G = 3;
const int MAXCOEF = 1e6 + 1; // pra calcular mod x^n

void prep_roots(int n) {
    if ((int)roots.size() >= n) return;
    int len = __builtin_ctz(roots.size());
    roots.resize(n);
    while ((1 << len) < n) {
        int z = power(G, (MOD - 1) >> (len + 1));
        for (int i = 1 << (len - 1); i < (1 << len); i++) {
            roots[2 * i] = roots[i];
            roots[2 * i + 1] = 1LL * roots[i] * z % MOD;
        }
        len++;
    }
}


void ntt(vector<int> &a) {
    int n = a.size();
    
    if ((int)rev.size() != n) {
        int k = __builtin_ctz(n) - 1;
        rev.resize(n);
        for (int i = 0; i < n; i++) {
            rev[i] = rev[i >> 1] >> 1 | (i & 1) << k;
        }
    }
    
    for (int i = 0; i < n; i++) {
        if (i < rev[i]) swap(a[i], a[rev[i]]);
    }
    
    prep_roots(n);
    
    for (int k = 1; k < n; k *= 2) {
        for (int i = 0; i < n; i += 2 * k) {
            for (int j = 0; j < k; j++) {
                int z = 1LL * a[i + j + k] * roots[j + k] % MOD;
                a[i + j + k] = a[i + j] - z;
                if (a[i + j + k] < 0) a[i + j + k] += MOD; 
                a[i + j] = a[i + j] + z;
                if (a[i + j] >= MOD) a[i + j] -= MOD;  
            }
        }
    }
}

vector<int> convolution(vector<int> a, vector<int> b) {
    if (a.empty() || b.empty()) return {};
    
    int sz = a.size() + b.size() - 1;
    int n = 1;
    while (n < sz) n *= 2;
    
    a.resize(n);
    b.resize(n);
    
    ntt(a);
    ntt(b);
    
    for (int i = 0; i < n; ++i) {
        a[i] = 1LL * a[i] * b[i] % MOD;
    }
    
    ntt(a);
    reverse(a.begin() + 1, a.end()); 
 
    int inv_n = power(n, MOD - 2);
    for (int i = 0; i < n; ++i) {
        a[i] = 1LL * a[i] * inv_n % MOD;
    }
    
    a.resize(min(sz, MAXCOEF));
    return a;
}
