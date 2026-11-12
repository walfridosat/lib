// Burnside, colares, pulseiras, strings primitivas
//
// O que faz: (1) Burnside generico: dado um grupo de permutacoes (lista de
//   todos os elementos), #orbitas = media de k^{ciclos}; (2) colares (rotacao)
//   e pulseiras (rotacao+reflexao) com k cores; (3) colares primitivos
//   (Lyndon) e strings sem periodo proprio por Mobius; (4) grid n x n com
//   rotacoes de 90 graus.
// Quando usar: "Catalogo > Combinatoria" (Burnside; Burnside em grid; Strings
//   primitivas e Lyndon; contagem por simetria). Cores com contagem fixa: indice de ciclos (Polya) + GF.
// Complexidade: necklaces O(d(n) * log); burnside_group O(|G| * n).
// Uso: necklaces(n,k), bracelets(n,k), lyndon_count(n,k), primitive_strings(n,k),
//   grid_rot4(n,k), burnside_group(group,k) com group = vector<vector<int>> (cada
//   elemento e uma permutacao de 0..n-1).
// Cuidados: mod primo MOD (998244353) e n < MOD. k pode ser ate ~1e18 (reduzido mod).
//   Para mod nao primo, calcule a soma inteira antes de dividir por n.
const ll BMOD = 998244353;
ll bpw(ll b, ll e) { ll r = 1; b %= BMOD; if (b < 0) b += BMOD; for (; e > 0; e >>= 1, b = b * b % BMOD) if (e & 1) r = r * b % BMOD; return r; }
ll phi_(ll n) { ll r = n; for (ll p = 2; p * p <= n; p++) if (n % p == 0) { while (n % p == 0) n /= p; r -= r / p; } if (n > 1) r -= r / n; return r; }
int mobius_(ll n) { int r = 1; for (ll p = 2; p * p <= n; p++) if (n % p == 0) { n /= p; if (n % p == 0) return 0; r = -r; } if (n > 1) r = -r; return r; }
vector<ll> divisors_(ll n) { vector<ll> d; for (ll i = 1; i * i <= n; i++) if (n % i == 0) { d.push_back(i); if (i != n / i) d.push_back(n / i); } return d; }
// colares: (1/n) sum_{d|n} phi(d) k^{n/d}
ll necklaces(ll n, ll k) {
    ll s = 0;
    for (ll d : divisors_(n)) s = (s + phi_(d) % BMOD * bpw(k, n / d)) % BMOD;
    return s * bpw(n, BMOD - 2) % BMOD;
}
// pulseiras: (necklaces + reflexoes)/2; reflexoes: n impar: k^{(n+1)/2}; n par: (k^{n/2}+k^{n/2+1})/2
ll bracelets(ll n, ll k) {
    ll refl;
    if (n & 1) refl = bpw(k, (n + 1) / 2);
    else refl = (bpw(k, n / 2) + bpw(k, n / 2 + 1)) % BMOD * ((BMOD + 1) / 2) % BMOD;
    return (necklaces(n, k) + refl) % BMOD * ((BMOD + 1) / 2) % BMOD;
}
// strings de comprimento n sem periodo proprio: sum_{d|n} mu(n/d) k^d
ll primitive_strings(ll n, ll k) {
    ll s = 0;
    for (ll d : divisors_(n)) s = (s + mobius_(n / d) * bpw(k, d) % BMOD + BMOD) % BMOD;
    return s;
}
// palavras de Lyndon = colares primitivos
ll lyndon_count(ll n, ll k) { return primitive_strings(n, k) * bpw(n, BMOD - 2) % BMOD; }
// grid n x n, k cores, grupo das rotacoes de 90 (identidade, 90, 180, 270)
ll grid_rot4(ll n, ll k) {
    ll c1 = n * n, c180 = (n * n + 1) / 2;      // ciclos da identidade e da rotacao de 180
    ll c90 = (n * n - (n & 1)) / 4 + (n & 1);   // ciclos da rotacao de 90 (e 270)
    ll s = bpw(k, c1) + bpw(k, c180) + 2 * bpw(k, c90);
    return s % BMOD * bpw(4, BMOD - 2) % BMOD;
}
// Burnside generico: #orbitas = (1/|G|) sum_g k^{ciclos(g)}
ll burnside_group(const vector<vector<int>>& G, ll k) {
    ll s = 0;
    for (auto& g : G) {
        int n = g.size(), c = 0; vector<char> vis(n, 0);
        for (int i = 0; i < n; i++) if (!vis[i]) { c++; for (int j = i; !vis[j]; j = g[j]) vis[j] = 1; }
        s = (s + bpw(k, c)) % BMOD;
    }
    return s * bpw(G.size(), BMOD - 2) % BMOD;
}
