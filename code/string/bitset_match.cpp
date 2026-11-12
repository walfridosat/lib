// Matching e LCS com bitset
//
// O que faz: (1) ocorrencias de p em t por bitset (util quando ha variacoes tipo
//   "casa com classe de chars" ou varios deslocamentos); (2) LCS de duas strings em O(nm/w).
// Quando usar: Catalogo > Strings ("LCS com bitset", "Padrao em texto" com bitset).
// Complexidade: match O(|p|*|t|/w); lcs O(|t|*|s|/w).
// Uso: bit_match(t, p) -> vector<int> posicoes iniciais (0-based) de p em t. (|t| <= BN)
//   lcs_bits(s, t) -> tamanho do LCS de s e t.
// Cuidados: BN e o tamanho do bitset do match; ajuste ao limite. Para casar '?' em p,
//   pule o caractere (nao faz AND) no match. lcs_bits nao usa bitset fixo: aloca
//   palavras de 64 bits do tamanho de s e faz a soma com carry manualmente.
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
// LCS bit-paralelo (Hyyrö): V = (V + (V & M[c])) | (V & ~M[c]); resposta = zeros de V.
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
