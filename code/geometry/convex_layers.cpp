// Camadas convexas (onion peeling) e frente de Pareto

typedef pair<ll, ll> pll;
ll crs(pll a, pll b, pll c) {
  return (b.first - a.first) * (c.second - a.second) - (b.second - a.second) * (c.first - a.first);
}

vector<int> convexLayers(const vector<pll> &pts) {
  int n = pts.size();
  vector<int> layer(n, -1), rest(n);
  iota(rest.begin(), rest.end(), 0);
  for (int L = 0; !rest.empty(); L++) {
    sort(rest.begin(), rest.end(), [&](int a, int b) { return pts[a] < pts[b]; });
    vector<int> h;  // hull mantendo colineares (pop so se cross < 0)
    int m = rest.size();
    if (m <= 2) {
      for (int i : rest) layer[i] = L;
      break;
    }
    vector<int> hh(2 * m);
    int k = 0;
    for (int t = 0; t < m; t++) {
      while (k >= 2 && crs(pts[hh[k - 2]], pts[hh[k - 1]], pts[rest[t]]) < 0) k--;
      hh[k++] = rest[t];
    }
    for (int t = m - 2, lo = k + 1; t >= 0; t--) {
      while (k >= lo && crs(pts[hh[k - 2]], pts[hh[k - 1]], pts[rest[t]]) < 0) k--;
      hh[k++] = rest[t];
    }
    for (int i = 0; i < k; i++) layer[hh[i]] = L;
    vector<int> nr;
    for (int i : rest) if (layer[i] < 0) nr.push_back(i);
    rest = nr;
  }
  return layer;
}

// frente de Pareto (maximizar x e y)
vector<int> pareto(const vector<pll> &p) {
  int n = p.size();
  vector<int> id(n), r;
  iota(id.begin(), id.end(), 0);
  sort(id.begin(), id.end(), [&](int a, int b) { return p[a] != p[b] ? p[a] > p[b] : a < b; });
  ll bestY = LLONG_MIN;
  for (int i : id) {  // x decrescente; fica se y >= maior y visto
    if (p[i].second >= bestY) {
      // descarta dominado de mesmo y com x maior
      bool dom = false;
      if (!r.empty() && p[r.back()].second == p[i].second && p[r.back()].first > p[i].first) dom = true;
      if (!dom) r.push_back(i);
      bestY = max(bestY, p[i].second);
    }
  }
  return r;
}

/*LATEX_DESC_BEGIN***************************
-> **Camadas convexas (onion peeling) e frente de Pareto**
layer[i] = camada do ponto i (0 = fecho externo), obtida removendo o hull e repetindo.
pareto devolve os indices nao dominados (maximizar x e y). Indices 0-based.

Complexidade: layers ~O(n^2 log n) no pior caso (versao simples); pareto O(n log n)
Uso:
  vector<pair<ll,ll>> pts;
  vector<int> L = convexLayers(pts);  // camada de cada ponto
  vector<int> fr = pareto(pts);       // indices da frente de Pareto

* Sobre o codigo:
  convexLayers ordena o conjunto restante e monta o hull com colineares (pop so com cross < 0),
  marca os vertices e repete com o resto. pareto ordena por x decrescente e mantem quem tem
  y >= maior y ja visto, desempatando por x para descartar dominados.

* Problemas e reducoes:
  + Convex layers / onion peeling: quantas camadas de hull um conjunto tem.
  + Frente de Pareto 2D (maximizar x e y): pareto.
  + Pontos nao dominados em dois criterios.
  + Profundidade convexa de cada ponto.

Cuidados: pontos colineares na borda ficam na MESMA camada (mantidos no hull). Duplicatas
  entram na mesma camada do original. Cross em ll; coords ~1e9 dao ate 4e18, perto do limite.
Catalogo: Geometria.
Digitacao: 51 linhas | dificil. Atalho: as duas cadeias do hull repetem o mesmo while;
  extrair um helper de cadeia (inferior/superior) usado por convexLayers.
*****************************LATEX_DESC_END*/
