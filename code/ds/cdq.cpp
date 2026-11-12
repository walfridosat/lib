// CDQ (divide e conquista offline) - template com BIT: dominancia 3D / DP 2D
//
// O que faz: exemplo completo de CDQ: res[i] = val[i] + max(res[j]) para
//   j < i (indice = dimensao 1), x_j < x_i, y_j < y_i (LIS 3D ponderado).
//   Dimensao 1 = ordem do indice, ordena por x (dim 2) em cada passo e usa
//   BIT em y (dim 3). Adapte "contribui" para contagem/soma (troque max por +).
// Quando usar: "Catalogo > Estruturas de dados" (CDQ para DP online e para
//   updates/queries no tempo): dominancia 3D, LIS ponderado 2D, CHT nao
//   monotonico, updates+queries de ponto/retangulo offline.
// Complexidade: O(n log^2 n).
// Uso: vector<CDQP> p(n) com x, y (y comprimido em 1..CDQY-1), val; res=0;
//   cdq(p, 0, n); resultado em p[i].res.
// Cuidados: CDQ de DP: resolve(l,m), contribui esq->dir, resolve(m,r) NESSA
//   ordem (dp depende do resultado final da esquerda). Para query apos update
//   na mesma coordenada, ordene com desempate (update antes de query). A BIT
//   deve ser DESFEITA apos cada contribuicao (limpa so os pontos tocados).
//   Para contagem de dominancia (sem DP) a ordem das chamadas recursivas eh
//   livre. Pontos com mesmo indice-tempo nao existem (indice eh unico).
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
