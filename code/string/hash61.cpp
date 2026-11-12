// Hash polinomial mod 2^61-1 (substring, LCP, palindromo)
typedef unsigned long long ull;
const ull HM = (1ULL << 61) - 1;
ull hmul(ull a, ull b) {
	__uint128_t t = (__uint128_t)a * b;
	ull r = (ull)(t & HM) + (ull)(t >> 61);
	return r >= HM ? r - HM : r;
}
mt19937_64 hrng(chrono::steady_clock::now().time_since_epoch().count());
const ull HB = uniform_int_distribution<ull>(1000, HM - 2)(hrng); // base aleatoria
vector<ull> hpw(1, 1); // potencias de HB, cresce sob demanda
void hgrow(int n) {
	while ((int)hpw.size() <= n) hpw.push_back(hmul(hpw.back(), HB));
}
ull hcat(ull hA, ull hB, int lenB) { // hash(A+B), hash = sum s[i]*B^(n-1-i)
	hgrow(lenB);
	ull r = hmul(hA, hpw[lenB]) + hB;
	return r >= HM ? r - HM : r;
}
struct Hash {
	int n; string s;
	vector<ull> h, hr; // h: prefixos; hr: prefixos do reverso
	Hash(const string& s_) : n(s_.size()), s(s_), h(n + 1), hr(n + 1) {
		hgrow(n);
		for (int i = 0; i < n; i++) {
			h[i + 1] = hmul(h[i], HB) + (unsigned char)s[i] + 1;
			if (h[i + 1] >= HM) h[i + 1] -= HM;
			hr[i + 1] = hmul(hr[i], HB) + (unsigned char)s[n - 1 - i] + 1;
			if (hr[i + 1] >= HM) hr[i + 1] -= HM;
		}
	}
	ull get(int l, int r) { // hash de s[l..r)
		ull x = h[r] + HM - hmul(h[l], hpw[r - l]);
		return x >= HM ? x - HM : x;
	}
	ull getrev(int l, int r) { // hash do reverso de s[l..r)
		int a = n - r, b = n - l; // posicoes no reverso
		ull x = hr[b] + HM - hmul(hr[a], hpw[b - a]);
		return x >= HM ? x - HM : x;
	}
	bool pal(int l, int r) { return get(l, r) == getrev(l, r); }
	int lcp(int i, Hash& o, int j) { // LCP de s[i..] com o.s[j..]
		int lo = 0, hi = min(n - i, o.n - j);
		while (lo < hi) {
			int m = (lo + hi + 1) / 2;
			if (get(i, i + m) == o.get(j, j + m)) lo = m; else hi = m - 1;
		}
		return lo;
	}
	int lcp(int i, int j) { return lcp(i, *this, j); }
	int cmp(int a, int b, int c, int d) { // compara s[a..b) com s[c..d)
		int l = lcp(a, c);
		int la = b - a, lb = d - c;
		if (l >= min(la, lb)) return la == lb ? 0 : (la < lb ? -1 : 1);
		return s[a + l] < s[c + l] ? -1 : 1;
	}
};
/*LATEX_DESC_BEGIN***************************
-> **Hash polinomial mod 2^61-1**
Hash de substring em O(1) com base aleatoria; compara substrings, acha LCP
de dois sufixos por busca binaria, testa palindromo de substring (hash direto
e do reverso) e combina hash de A+B.

Complexidade: build O(n); get O(1); lcp O(log n).
Uso:
  Hash h(s);
  h.get(l, r) -> hash de s[l..r) (0-based, r exclusivo);
  h.lcp(i, h2, j) -> LCP de s[i..] com h2.s[j..]; h.lcp(i, j) idem em s;
  h.cmp(a, b, c, d) -> compara s[a..b) com s[c..d) (-1, 0, 1);
  h.pal(l, r) -> s[l..r) e palindromo;
  hcat(hA, hB, lenB) -> hash de A+B.
  Todos os Hash compartilham a base global HB (comparaveis entre si).

* Sobre o codigo:
  h[] e o prefixo, hr[] o prefixo do reverso. get e getrev subtraem o prefixo
  deslocado; pal compara os dois. lcp faz busca binaria no tamanho do trecho
  igual. hmul faz multiplicacao mod 2^61-1 com __uint128_t.

* Problemas e reducoes:
  + Comparar substrings de strings iguais ou diferentes.
  + LCP de dois sufixos por busca binaria + hash.
  + Palindromo de substring: hash direto == hash do reverso.
  + Comparacao lexicografica de substrings (cmp).
  + Concatenar hashes: hcat para juntar duas partes.
  + Buscar padrao por hash e verificar colisoes.
  + Maior substring comum por binaria no tamanho + conjuntos de hashes.

Cuidados: nao use mod 2^64 (Thue-Morse quebra). Caracteres entram como
  valor do char + 1 (para '\0' nao ser zero). Hashes de strings de tamanhos
  diferentes so sao comparaveis se voce comparar tambem os tamanhos.
  0-indexed, intervalo [l, r).
Catalogo: Strings (comparar substrings, hash mod 2^61-1, hash de string e do
  reverso, comparacao lexicografica por hash).
Digitacao: 56 linhas | media. Atalho: ok.
*****************************LATEX_DESC_END*/
