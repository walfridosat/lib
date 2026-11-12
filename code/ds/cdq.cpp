// CDQ - divide e conquista offline (dominancia 3D / DP)
struct CDQP { int x, y; ll val, res; };
const int CDQY = 100005; // maior y + 1
ll cdq_bit[CDQY];
void cdq_upd(int i, ll v) { for (; i < CDQY; i += i & -i) cdq_bit[i] = max(cdq_bit[i], v); }
ll cdq_qry(int i) { ll r = 0; for (; i > 0; i -= i & -i) r = max(r, cdq_bit[i]); return r; }
void cdq_clr(int i) { for (; i < CDQY; i += i & -i) cdq_bit[i] = 0; }
void cdq(vector<CDQP>& p, int l, int r) { // processa [l, r) na ordem do indice
	if (r - l == 1) { p[l].res = max(p[l].res, p[l].val); return; }
	int m = (l + r) / 2;
	cdq(p, l, m);
	vector<int> A, B;
	for (int i = l; i < m; i++) A.push_back(i);
	for (int i = m; i < r; i++) B.push_back(i);
	auto cx = [&](int a, int b) { return p[a].x < p[b].x; };
	sort(A.begin(), A.end(), cx); sort(B.begin(), B.end(), cx);
	size_t k = 0;
	for (int b : B) {
		// insere da esquerda os com x estritamente menor
		while (k < A.size() && p[A[k]].x < p[b].x) { cdq_upd(p[A[k]].y, p[A[k]].res); k++; }
		p[b].res = max(p[b].res, p[b].val + cdq_qry(p[b].y - 1)); // y estrito
	}
	for (size_t i = 0; i < k; i++) cdq_clr(p[A[i]].y);
	cdq(p, m, r);
}
/*LATEX_DESC_BEGIN***************************
-> **CDQ (divide e conquista offline)**
Exemplo de CDQ: res[i] = val[i] + max(res[j]) para j < i, x_j < x_i,
y_j < y_i (LIS 3D ponderado). Dimensao 1 = indice, 2 = x, 3 = BIT em y.

Complexidade: O(n log^2 n).
Uso:
  vector<CDQP> p(n);  // p[i] = {x, y (1..CDQY-1), val, 0}
  cdq(p, 0, n);
  // resultado em p[i].res
  Adapte "contribui" para contagem/soma (troque max por +).

* Sobre o codigo:
  Divide por indice; resolve a esquerda, contribui esq->dir ordenando por
  x com BIT em y, e resolve a direita. A BIT e desfeita nos pontos tocados.

* Problemas e reducoes:
  + LIS 3D ponderado / dominancia 3D.
  + Contar pontos dominados em 3D.
  + dp[i] = max(dp[j]) + val com x_j<x_i e y_j<y_i.
  + Updates + queries offline no tempo (CDQ no lugar da segtree no tempo).
  + DP com transicao tipo CHT fora de ordem (CDQ optimization).

Cuidados: no DP a ordem e resolve(l,m), contribui esq->dir, resolve(m,r).
  Para query apos update na mesma coordenada ordene com desempate (update
  antes de query). Desfaca a BIT apos cada contribuicao. Pontos com mesmo
  indice-tempo nao existem. Para contagem pura a ordem recursiva e livre.
Catalogo: Estruturas de dados.
Digitacao: 24 linhas | dificil.
*****************************LATEX_DESC_END*/
