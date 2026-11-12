// Caminhos em grid - obstaculos e faixa [0,h]
// Requer: code/combinatorics/binom_mod.cpp (cole antes).
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
    // destino repetido: ja descontado
    for (int i = 0; i + 1 < k; i++) if (bad[i] == make_pair(X, Y)) return 0;
    return f[k-1];
}
// dentro de [0,h]; reflexao com periodo 2(h+2)
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
/*LATEX_DESC_BEGIN***************************
-> **Caminhos em grid com obstaculos e faixa**
Caminhos monotonos evitando pontos proibidos e passeios +-1 presos em [0,h].

Complexidade: (1) O(k^2) apos init; (2) O(n/h) termos.
Uso:
  ll g = grid_obstacles(X, Y, bad);    // bad = vector<pair<ll,ll>>
  ll w = strip_walks(n, a, b, h);

* Sobre o codigo:
  grid_obstacles ordena os pontos (inclusive o destino) e calcula
  f[i] = caminhos(0, i) - sum_{j<i} f[j]*caminhos(j, i). strip_walks soma
  imagens refletidas de b em uma reta com periodo 2(h+2), com sinal alternado.

* Problemas e reducoes:
  + Caminhos de (0,0) a (X,Y) evitando k pontos -> grid_obstacles.
  + Caminhos que nao passam por uma casa proibida -> grid_obstacles.
  + Passeio +-1 de n passos de a ate b sem sair de [0,h] -> strip_walks.
  + Caminhos com barreiras absorventes em -1 e h+1 -> strip_walks.
  + Contar caminhos monotonos em um retangulo -> C(dx+dy, dx).
  + Caminhos que passam por um ponto obrigatorio -> produto de dois caminhos.

Cuidados: x,y ate o tamanho do fatorial (X+Y <= N); obstaculo na origem ou
  no destino e tratado (resposta 0 se a origem for proibida).
Catalogo: Combinatoria.
Digitacao: 34 linhas | media. Atalho: paths() e so uma chamada de C; pode ser inline.
*****************************LATEX_DESC_END*/
