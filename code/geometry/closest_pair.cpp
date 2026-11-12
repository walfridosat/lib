// Par de pontos mais proximo (sweep + set)
//
// O que faz: menor distancia^2 entre dois pontos (e os indices). Pontos repetidos => 0.
// Quando usar: Catalogo > Geometria ("pares mais proximos"); tambem checar "algum par a dist < d".
// Complexidade: O(n log n).
// Uso: vector<pair<ll,ll>> pts; auto r = closestPair(pts); r = {dist2, {i, j}}.  n >= 2.
// Cuidados: dist2 em ll (coords ate ~1e9 => dist2 ate 8e18 cabe no limite; cuidado acima).
//   Indices sao posicoes no vetor original.

pair<ll, pair<int, int>> closestPair(const vector<pair<ll, ll>> &pts) {
  int n = pts.size();
  vector<int> id(n);
  iota(id.begin(), id.end(), 0);
  sort(id.begin(), id.end(), [&](int a, int b) { return pts[a] < pts[b]; });
  ll best = LLONG_MAX;
  pair<int, int> bp = {-1, -1};
  set<pair<ll, int>> s;  // (y, indice) dos pontos na janela x - d <= x_i
  int left = 0;
  for (int k = 0; k < n; k++) {
    int i = id[k];
    ll d = best == LLONG_MAX ? (ll)4e9 : (ll)ceill(sqrtl((long double)best));
    // tira da janela quem ja nao pode melhorar (dx^2 >= best)
    while (left < k && (pts[i].first - pts[id[left]].first) * (pts[i].first - pts[id[left]].first) >= best) {
      s.erase({pts[id[left]].second, id[left]});
      left++;
    }
    // candidatos com y em [y - d, y + d]
    auto it = s.lower_bound({pts[i].second - d, -1});
    for (; it != s.end() && it->first <= pts[i].second + d; ++it) {
      int j = it->second;
      ll dx = pts[i].first - pts[j].first, dy = pts[i].second - pts[j].second;
      ll c = dx * dx + dy * dy;
      if (c < best) best = c, bp = {j, i};
    }
    s.insert({pts[i].second, i});
  }
  return {best, bp};
}
