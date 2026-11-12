// Burnside - colares, pulseiras e strings primitivas
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
// pulseiras: (colares + reflexoes)/2
ll bracelets(ll n, ll k) {
    ll refl;
    if (n & 1) refl = bpw(k, (n + 1) / 2);
    else refl = (bpw(k, n / 2) + bpw(k, n / 2 + 1)) % BMOD * ((BMOD + 1) / 2) % BMOD;
    return (necklaces(n, k) + refl) % BMOD * ((BMOD + 1) / 2) % BMOD;
}
// strings sem periodo proprio: sum mu(n/d) k^d
ll primitive_strings(ll n, ll k) {
    ll s = 0;
    for (ll d : divisors_(n)) s = (s + mobius_(n / d) * bpw(k, d) % BMOD + BMOD) % BMOD;
    return s;
}
// palavras de Lyndon = colares primitivos
ll lyndon_count(ll n, ll k) { return primitive_strings(n, k) * bpw(n, BMOD - 2) % BMOD; }
// grid n x n com rotacoes de 90 graus
ll grid_rot4(ll n, ll k) {
    ll c1 = n * n, c180 = (n * n + 1) / 2;      // ciclos da identidade e da rotacao de 180
    ll c90 = (n * n - (n & 1)) / 4 + (n & 1);   // ciclos da rotacao de 90 (e 270)
    ll s = bpw(k, c1) + bpw(k, c180) + 2 * bpw(k, c90);
    return s % BMOD * bpw(4, BMOD - 2) % BMOD;
}
// Burnside: orbitas = media de k^ciclos
ll burnside_group(const vector<vector<int>>& G, ll k) {
    ll s = 0;
    for (auto& g : G) {
        int n = g.size(), c = 0; vector<char> vis(n, 0);
        for (int i = 0; i < n; i++) if (!vis[i]) { c++; for (int j = i; !vis[j]; j = g[j]) vis[j] = 1; }
        s = (s + bpw(k, c)) % BMOD;
    }
    return s * bpw(G.size(), BMOD - 2) % BMOD;
}
/*LATEX_DESC_BEGIN***************************
-> **Burnside, colares e strings primitivas**
Conta orbitas por Burnside, colares/pulseiras com k cores, strings primitivas e palavras de Lyndon.

Complexidade: necklaces O(d(n) log); burnside_group O(|G| n).
Uso:
  ll nc = necklaces(n, k), br = bracelets(n, k);
  ll ps = primitive_strings(n, k), ly = lyndon_count(n, k);
  ll gr = grid_rot4(n, k);
  ll bo = burnside_group(group, k);   // group = vector<vector<int>>

* Sobre o codigo:
  necklaces soma phi(d) * k^(n/d) sobre d | n e divide por n. bracelets junta
  as reflexoes (n impar: k^((n+1)/2); n par: (k^(n/2)+k^(n/2+1))/2).
  primitive_strings usa Mobius; lyndon_count divide por n. burnside_group
  conta ciclos de cada permutacao e faz a media de k^ciclos.

* Problemas e reducoes:
  + Colares de n contas com k cores (rotacao) -> necklaces.
  + Pulseiras (rotacao + reflexao) -> bracelets.
  + Strings de periodo exatamente n -> primitive_strings.
  + Palavras de Lyndon de tamanho n -> lyndon_count.
  + Colorir grid n x n com rotacoes de 90 graus -> grid_rot4.
  + Orbitas de um grupo de permutacoes qualquer -> burnside_group.
  + Coloracoes com numero fixo de cores (Polya/indice de ciclos) -> burnside_group.

Cuidados: mod primo BMOD = 998244353 e n < BMOD; k pode ser grande (reduzido
  mod); para mod nao primo calcule a soma inteira antes de dividir por n.
Catalogo: Combinatoria.
Digitacao: 43 linhas | media. Atalho: phi_/mobius_/divisors_ duplicam divisores.cpp.
*****************************LATEX_DESC_END*/
