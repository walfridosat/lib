// Uniao de retangulos - area e perimetro

struct CovTree {  // cobertura (contagem) e comprimento coberto
  int n;
  vector<ll> ys;
  vector<int> cnt;
  vector<ll> cov;
  void init(vector<ll> y) {
    ys = y;
    n = ys.size() - 1;
    cnt.assign(4 * max(n, 1), 0);
    cov.assign(4 * max(n, 1), 0);
  }
  void upd(int o, int l, int r, int a, int b, int v) {  // elementares [l,r)
    if (b <= l || r <= a) return;
    if (a <= l && r <= b) cnt[o] += v;
    else {
      int m = (l + r) / 2;
      upd(2 * o, l, m, a, b, v);
      upd(2 * o + 1, m, r, a, b, v);
    }
    if (cnt[o] > 0) cov[o] = ys[r] - ys[l];
    else cov[o] = (r - l == 1) ? 0 : cov[2 * o] + cov[2 * o + 1];
  }
};

// varre em x: area e soma de |delta cobertura|
ll sweepRect(const vector<array<ll, 4>> &r, ll &per) {
  vector<ll> ys;
  for (auto &a : r) ys.push_back(a[1]), ys.push_back(a[3]);
  sort(ys.begin(), ys.end());
  ys.erase(unique(ys.begin(), ys.end()), ys.end());
  CovTree T;
  T.init(ys);
  // eventos (x, tipo, y1, y2); abre antes de fecha
  vector<array<ll, 4>> ev;
  for (auto &a : r) {
    ev.push_back({a[0], 0, a[1], a[3]});  // 0 = abre (+1)
    ev.push_back({a[2], 1, a[1], a[3]});  // 1 = fecha (-1)
  }
  sort(ev.begin(), ev.end());
  ll area = 0, lastX = 0, prev = 0;
  per = 0;
  for (size_t i = 0; i < ev.size(); i++) {
    ll x = ev[i][0];
    if (i) area += T.cov[1] * (x - lastX);
    int a = lower_bound(ys.begin(), ys.end(), ev[i][2]) - ys.begin();
    int b = lower_bound(ys.begin(), ys.end(), ev[i][3]) - ys.begin();
    T.upd(1, 0, T.n, a, b, ev[i][1] == 0 ? 1 : -1);
    lastX = x;
    if (i + 1 < ev.size() && ev[i + 1][0] == x) continue;  // mede variacao apos eventos do mesmo x
    per += llabs(T.cov[1] - prev);
    prev = T.cov[1];
  }
  return area;
}

ll unionArea(const vector<array<ll, 4>> &r) {
  if (r.empty()) return 0;
  ll per;
  return sweepRect(r, per);
}

ll unionPerimeter(const vector<array<ll, 4>> &r) {
  if (r.empty()) return 0;
  ll p1, p2;
  sweepRect(r, p1);
  vector<array<ll, 4>> t;  // troca x<->y
  for (auto &a : r) t.push_back({a[1], a[0], a[3], a[2]});
  sweepRect(t, p2);
  return p1 + p2;
}

/*LATEX_DESC_BEGIN***************************
-> **Uniao de retangulos - area e perimetro**
Area e perimetro da uniao de retangulos alinhados aos eixos. Retangulo [x1,x2) x [y1,y2),
com x1 < x2 e y1 < y2.

Complexidade: O(n log n)
Uso:
  vector<array<ll,4>> r;   // {x1, y1, x2, y2}
  ll a = unionArea(r);
  ll p = unionPerimeter(r);

* Sobre o codigo:
  CovTree e uma segtree sobre y comprimido que guarda cnt (cobertura) e cov (comprimento
  coberto). sweepRect varre x, acumula area = cov[1] * dx e perimetro = |variacao de cov|.
  A abertura (tipo 0) vem antes do fechamento no mesmo x; a variacao so e medida depois de
  todos os eventos daquele x. unionPerimeter repete o sweep com os eixos trocados.

* Problemas e reducoes:
  + Area da uniao de retangulos alinhados aos eixos.
  + Perimetro da uniao de retangulos.
  + Cobertura de comprimento por intervalos (a segtree serve de base).
  + Area total coberta em uma faixa/grade retangular.

Cuidados: coordenadas compactadas internamente. Area em ll (cuidado com estouro em muitas
  sobreposicoes). Retangulos degenerados (x1 == x2 ou y1 == y2) nao sao tratados. Eventos no
  mesmo x precisam ser todos processados antes de medir a variacao.
Catalogo: Geometria; Estruturas.
Digitacao: 67 linhas | dificil. Atalho: CovTree.upd e recursiva; a mesma segtree pode ser
  escrita iterativa para encurtar.
*****************************LATEX_DESC_END*/
