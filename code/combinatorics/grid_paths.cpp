// Caminhos em grid: obstaculos, faixa 0<=y<=h (reflexao alternada)
//
// O que faz: (1) # caminhos (direita/cima) de (0,0) a (X,Y) evitando k pontos
//   proibidos, via f(i)=paths(start,i)-sum_{j antes de i} f(j)*paths(j,i);
//   (2) # passeios +-1 de n passos de a ate b que ficam em [0,h] (sem sair).
// Quando usar: "Catalogo > Combinatoria" (Caminhos em grid com obstaculos;
//   Faixa 0<=y<=h; Reflexao). Para h pequeno a DP O(n*h) tambem serve.
// Complexidade: (1) O(k^2) apos init; (2) O(n/h) termos.
// Requer: code/combinatorics/binom_mod.cpp (cole antes).
// Uso: precisa de binom_mod.cpp (C, init_comb) colado antes.
//   grid_obstacles(X,Y,bad) com bad = vector<pair<ll,ll>> de (x,y).
//   strip_walks(n,a,b,h).
// Cuidados: x,y ate o tamanho do fatorial (X+Y <= N). Obstaculo na origem ou
//   no destino e tratado corretamente (resposta 0 se a origem for proibida).
ll paths(ll x1, ll y1, ll x2, ll y2) {
    if (x2 < x1 || y2 < y1) return 0;
    return C(x2 - x1 + y2 - y1, x2 - x1);
}
ll grid_obstacles(ll X, ll Y, vector<pair<ll,ll>> bad) {
    sort(bad.begin(), bad.end());                 // ordem topologica: (x,y) lexicografico
    bad.push_back({X, Y});                        // destino vira o ultimo "ponto"
    int k = bad.size();
    vector<ll> f(k);
    for (int i = 0; i < k; i++) {
        f[i] = paths(0, 0, bad[i].first, bad[i].second);
        for (int j = 0; j < i; j++)
            f[i] = (f[i] - f[j] * paths(bad[j].first, bad[j].second, bad[i].first, bad[i].second)) % MOD;
        f[i] = (f[i] + MOD) % MOD;
    }
    // se (X,Y) tambem era proibido ele aparece duas vezes; o ultimo f ja desconta o anterior
    for (int i = 0; i + 1 < k; i++) if (bad[i] == make_pair(X, Y)) return 0;
    return f[k-1];
}
// Passeios +-1 de n passos, de a ate b, sempre dentro de [0,h]. Barreiras em -1 e h+1;
// periodo da reflexao w=2(h+2); soma alternada sobre imagens de b.
ll strip_walks(ll n, ll a, ll b, ll h) {
    if (a < 0 || a > h || b < 0 || b > h) return 0;
    ll w = 2 * (h + 2), r = 0;
    auto N = [&](ll x) -> ll { // # passeios livres de a ate x em n passos
        ll d = x - a;
        if (((n + d) & 1) || d > n || d < -n) return 0;
        return C(n, (n + d) / 2);
    };
    for (ll k = -(n / w) - 2; k <= n / w + 2; k++) {
        r += N(b + k * w) - N(-2 - b + k * w); // imagem refletida em -1 entra com sinal -
        r %= MOD;
    }
    return (r % MOD + MOD) % MOD;
}
