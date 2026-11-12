// Matching e LCS com bitset
const int BN = 100005;
vector<int> bit_match(const string& t, const string& p) {
	int n = t.size(), m = p.size();
	static bitset<BN> pos[256], res;
	for (int c = 0; c < 256; c++) pos[c].reset();
	for (int i = 0; i < n; i++) pos[(unsigned char)t[i]][i] = 1;
	res.set();
	for (int j = 0; j < m; j++) res &= pos[(unsigned char)p[j]] >> j; // bit i: t[i+j]==p[j]
	vector<int> r;
	for (int i = 0; i + m <= n; i++) if (res[i]) r.push_back(i);
	return r;
}
// LCS bit-paralelo (Hyyro): V = (V + (V & M[c])) | (V & ~M[c]); resposta = zeros de V.
int lcs_bits(const string& s, const string& t) {
	int n = s.size();
	if (n == 0 || t.empty()) return 0;
	int W = (n + 64) / 64; // palavras; sobra o bit de carry
	vector<vector<uint64_t>> M(256, vector<uint64_t>(W, 0));
	for (int i = 0; i < n; i++) M[(unsigned char)s[i]][i >> 6] |= 1ULL << (i & 63);
	vector<uint64_t> V(W, ~0ULL);
	if (n & 63) V[n >> 6] &= (1ULL << (n & 63)) - 1; // bits >= n ficam zero
	else V[n >> 6] = 0;                                // palavra do carry
	for (char ch : t) {
		const vector<uint64_t>& m = M[(unsigned char)ch];
		uint64_t carry = 0;
		for (int i = 0; i < W; i++) {
			uint64_t x = V[i] & m[i], keep = V[i] & ~m[i];
			uint64_t s1 = V[i] + x, c1 = s1 < V[i];
			uint64_t s2 = s1 + carry, c2 = s2 < s1;
			V[i] = s2 | keep;
			carry = c1 | c2;
		}
	}
	int zeros = 0;
	for (int i = 0; i < n; i++) zeros += !((V[i >> 6] >> (i & 63)) & 1);
	return zeros;
}
/*LATEX_DESC_BEGIN***************************
-> **Matching e LCS com bitset**
(1) Ocorrencias de p em t por bitset, util com classes de caracteres ou
varios deslocamentos; (2) LCS de duas strings em O(nm/w).

Complexidade: match O(|p| |t| / w); lcs O(|t| |s| / w).
Uso:
  vector<int> pos = bit_match(t, p); // posicoes iniciais 0-based (|t| <= BN)
  int l = lcs_bits(s, t);            // tamanho do LCS de s e t

* Sobre o codigo:
  bit_match monta pos[c] com as posicoes de c em t e faz res &= pos[p[j]] >> j;
  o bit i fica 1 quando t[i+j] == p[j] para todo j. lcs_bits usa o algoritmo
  de Hyyro: V = (V + (V & M[c])) | (V & ~M[c]) com carry manual entre
  palavras de 64 bits; a resposta e o numero de zeros.

* Problemas e reducoes:
  + Padrao em texto com bitset: bit_match devolve os inicios.
  + Casamento com '?' no padrao: pule o caractere (nao faz AND) no match.
  + LCS de duas strings: lcs_bits, O(nm/64).
  + Comparar muitas posicoes de uma vez: bit-paralelismo.
  + Maior subsequencia comum como base para diff.

Cuidados: BN e o tamanho do bitset do match; ajuste ao limite. lcs_bits nao
  usa bitset fixo: aloca palavras de 64 bits do tamanho de s. 0-indexed.
Catalogo: Strings (LCS com bitset, padrao em texto com bitset).
Digitacao: 37 linhas | media. Atalho: ok.
*****************************LATEX_DESC_END*/
