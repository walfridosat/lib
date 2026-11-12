// Hash 2D de submatrizes (mod 2^61-1)
typedef unsigned long long ull;
const ull H2M = (1ULL << 61) - 1;
ull h2mul(ull a, ull b) {
	__uint128_t t = (__uint128_t)a * b;
	ull r = (ull)(t & H2M) + (ull)(t >> 61);
	return r >= H2M ? r - H2M : r;
}
ull h2add(ull a, ull b) { a += b; return a >= H2M ? a - H2M : a; }
ull h2sub(ull a, ull b) { return a >= b ? a - b : a + H2M - b; }
struct Hash2D {
	int n, m;
	ull B1, B2;
	vector<ull> p1, p2;
	vector<vector<ull>> h;
	Hash2D(const vector<string>& a) {
		mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
		B1 = rng() % (H2M - 1000) + 500; B2 = rng() % (H2M - 1000) + 500;
		n = a.size(); m = n ? a[0].size() : 0;
		p1.assign(n + 1, 1); p2.assign(m + 1, 1);
		for (int i = 0; i < n; i++) p1[i + 1] = h2mul(p1[i], B1);
		for (int j = 0; j < m; j++) p2[j + 1] = h2mul(p2[j], B2);
		h.assign(n + 1, vector<ull>(m + 1, 0));
		// h[i][j] = soma a[x][y] * B1^(i-1-x) * B2^(j-1-y)  (incl-excl)
		for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) {
			ull v = h2add(h2mul(h[i - 1][j], B1), h2mul(h[i][j - 1], B2));
			v = h2sub(v, h2mul(h[i - 1][j - 1], h2mul(B1, B2)));
			h[i][j] = h2add(v, (unsigned char)a[i - 1][j - 1] + 1);
		}
	}
	ull get(int x1, int y1, int x2, int y2) { // [x1,x2) x [y1,y2)
		ull r = h[x2][y2];
		r = h2sub(r, h2mul(h[x1][y2], p1[x2 - x1]));
		r = h2sub(r, h2mul(h[x2][y1], p2[y2 - y1]));
		r = h2add(r, h2mul(h[x1][y1], h2mul(p1[x2 - x1], p2[y2 - y1])));
		return r;
	}
};
/*LATEX_DESC_BEGIN***************************
-> **Hash 2D de submatrizes (mod 2^61-1)**
Hash de qualquer submatriz em O(1); permite achar padrao 2D, submatrizes
iguais de tamanho fixo (set de hashes), simetrias etc. 0-indexed.

Complexidade: build O(nm); get O(1).
Uso:
  Hash2D H(vector<string> v);
  ull h = H.get(x1, y1, x2, y2); // linhas [x1,x2), colunas [y1,y2)
  Duas submatrizes de mesmo tamanho sao iguais sse os hashes sao iguais.

* Sobre o codigo:
  h[i][j] e a soma a[x][y] * B1^(i-1-x) * B2^(j-1-y) (prefixo 2D com
  inclusao-exclusao). p1/p2 guardam as potencias de B1/B2; get desfaz as
  quatro bordas. Aritmetica em mod 2^61-1 com __uint128_t.

* Problemas e reducoes:
  + Hash de submatriz: H.get(x1, y1, x2, y2).
  + Busca de padrao 2D: hashes de janelas do mesmo tamanho.
  + Submatrizes iguais de tamanho fixo: set de hashes.
  + Simetrias/translacoes de tabuleiro: compare hashes de regioes.
  + Verificar repeticao de blocos: hashes de cada bloco.

Cuidados: usa duas bases aleatorias (uma por eixo). Compare so submatrizes
  do mesmo tamanho. 0-indexed. n = 0 e tratado (m = 0).
Catalogo: Strings (hash 2D).
Digitacao: 37 linhas | media. Atalho: ok.
*****************************LATEX_DESC_END*/
