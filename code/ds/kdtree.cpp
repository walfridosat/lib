// K-d tree 2D - vizinho mais proximo e contagem
struct KD {
	struct P { ll x, y; int id; };
	vector<P> a; // a eh reordenado: no de [l,r) esta em m=(l+r)/2
	vector<array<ll,4>> box; // bounding box (x1,y1,x2,y2) da subarvore em m
	KD(const vector<pair<ll,ll>>& pts) {
		for (int i = 0; i < (int)pts.size(); i++) a.push_back({pts[i].first, pts[i].second, i});
		box.assign(a.size(), {});
		build(0, a.size(), 0);
	}
	void build(int l, int r, int ax) {
		if (l >= r) return;
		int m = (l + r) / 2;
		nth_element(a.begin() + l, a.begin() + m, a.begin() + r, [&](const P& p, const P& q) {
			return ax ? p.y < q.y : p.x < q.x; });
		build(l, m, ax ^ 1); build(m + 1, r, ax ^ 1);
		box[m] = {a[m].x, a[m].y, a[m].x, a[m].y};
		auto mrg = [&](int c) { // junta a caixa do filho c
			box[m][0] = min(box[m][0], box[c][0]); box[m][1] = min(box[m][1], box[c][1]);
			box[m][2] = max(box[m][2], box[c][2]); box[m][3] = max(box[m][3], box[c][3]);
		};
		if (l < m) mrg((l + m) / 2);
		if (m + 1 < r) mrg((m + 1 + r) / 2);
	}
	int cnt(int l, int r, ll x1, ll y1, ll x2, ll y2) {
		if (l >= r) return 0;
		int m = (l + r) / 2; auto& b = box[m];
		if (b[2] < x1 || b[0] > x2 || b[3] < y1 || b[1] > y2) return 0; // disjunto
		if (x1 <= b[0] && b[2] <= x2 && y1 <= b[1] && b[3] <= y2) return r - l; // contido
		int s = (a[m].x >= x1 && a[m].x <= x2 && a[m].y >= y1 && a[m].y <= y2);
		return s + cnt(l, m, x1, y1, x2, y2) + cnt(m + 1, r, x1, y1, x2, y2);
	}
	int count(ll x1, ll y1, ll x2, ll y2) { return cnt(0, a.size(), x1, y1, x2, y2); }
	pair<ll,int> best;
	ll bdist(const array<ll,4>& b, ll x, ll y) { // dist^2 do ponto ate a caixa
		ll dx = max({b[0] - x, 0LL, x - b[2]}), dy = max({b[1] - y, 0LL, y - b[3]});
		return dx * dx + dy * dy;
	}
	void nn(int l, int r, ll x, ll y, bool skip) {
		if (l >= r) return;
		int m = (l + r) / 2;
		if (bdist(box[m], x, y) >= best.first) return; // poda
		ll dx = a[m].x - x, dy = a[m].y - y, d = dx * dx + dy * dy;
		if (!(skip && d == 0) && d < best.first) best = {d, a[m].id};
		// visita primeiro o lado mais promissor (menor dist a caixa)
		int lm = (l + m) / 2, rm = (m + 1 + r) / 2;
		ll dl = l < m ? bdist(box[lm], x, y) : LLONG_MAX, dr = m + 1 < r ? bdist(box[rm], x, y) : LLONG_MAX;
		if (dl <= dr) { nn(l, m, x, y, skip); nn(m + 1, r, x, y, skip); }
		else { nn(m + 1, r, x, y, skip); nn(l, m, x, y, skip); }
	}
	pair<ll,int> nearest(ll x, ll y, bool skip_same = false) {
		best = {LLONG_MAX, -1};
		nn(0, a.size(), x, y, skip_same);
		return best;
	}
};
/*LATEX_DESC_BEGIN***************************
-> **K-d tree 2D**
Arvore balanceada alternando eixos (mediana por nth_element). nearest acha
o ponto mais proximo (dist^2) e count conta pontos em retangulo.

Complexidade: build O(n log n); count O(sqrt n); nearest O(log n) medio,
  O(n) pior caso.
Uso:
  KD kd(vector<pair<ll,ll>> pts);
  kd.count(x1, y1, x2, y2)   // retangulo fechado
  auto [d2, idx] = kd.nearest(x, y, skip_same=false);
  // idx = indice em pts originais; skip_same ignora distancia 0

* Sobre o codigo:
  build escolhe a mediana alternando x/y e guarda a bounding box de cada
  subarvore. count poda caixas disjuntas e devolve r-l quando contida.
  nn poda pela distancia a caixa e visita primeiro o lado mais promissor.

* Problemas e reducoes:
  + Vizinho mais proximo em 2D.
  + Contagem de pontos em retangulo.
  + k pontos mais proximos (com heap).
  + Pontos nao muito adversariais com n ~ 1e5.

Cuidados: dist^2 em ll (coords ate ~1e9 -> 2e18 ok). nearest em kd vazio
  devolve {LLONG_MAX,-1}. Sem insercao dinamica (use Bentley-Saxe se
  precisar).
Catalogo: Estruturas de dados.
Digitacao: 55 linhas | dificil.
*****************************LATEX_DESC_END*/
