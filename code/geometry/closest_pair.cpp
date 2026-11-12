// Par de pontos mais proximo - sweep com set

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

/*LATEX_DESC_BEGIN***************************
-> **Par de pontos mais proximo - sweep com set**
Menor distancia^2 entre dois pontos e os indices. Pontos repetidos dao distancia 0.
Indices 0-based, posicoes no vetor original.

Complexidade: O(n log n)
Uso:
  vector<pair<ll,ll>> pts;
  auto r = closestPair(pts);   // r = {dist2, {i, j}}, n >= 2

* Sobre o codigo:
  Ordena por x. Mantem um set (y, indice) com os pontos de x >= x_i - d. Remove da janela
  quem ja nao pode melhorar (dx^2 >= best) e compara com os candidatos de y em [y-d, y+d].
  d e uma aproximacao inteira do raio atual (ceil(sqrt(best))).

* Problemas e reducoes:
  + Par de pontos mais proximo: closestPair direto.
  + Existe par a distancia < D? Compare o dist2 devolvido com D^2.
  + Detectar pontos duplicados/colisao: dist2 == 0.
  + Reduzir para O(n log n) o teste de todos os pares.

Cuidados: dist2 em ll; coords ate ~1e9 dao dist2 ate ~8e18, perto do limite de ll. Para
  coords maiores use __int128. n >= 2.
Catalogo: Geometria.
Digitacao: 29 linhas | media. Atalho: recalcular d (ceil sqrt) so quando best diminui, em
  vez de a cada iteracao.
*****************************LATEX_DESC_END*/
