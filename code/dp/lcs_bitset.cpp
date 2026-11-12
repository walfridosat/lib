// LCS bitset (Hyyro / Allison-Dix)
int lcs_bitset(const string& a, const string& b){
    int n = a.size(), W = (n + 63) / 64;
    vector<vector<unsigned long long>> M(256, vector<unsigned long long>(W, 0));   // M[c] = posicoes de c em a
    for(int i = 0; i < n; i++) M[(unsigned char)a[i]][i >> 6] |= 1ULL << (i & 63);
    vector<unsigned long long> V(W, ~0ULL);
    for(unsigned char ch : b){
        const auto& m = M[ch];
        unsigned long long carry = 0;
        for(int w = 0; w < W; w++){
            unsigned long long v = V[w], u = v & m[w];
            unsigned long long s1 = v + u;
            unsigned long long c1 = s1 < v;                 // carry do v+u
            unsigned long long s2 = s1 + carry;
            unsigned long long c2 = s2 < s1;                // carry do + carry de entrada
            carry = c1 | c2;
            V[w] = s2 | (v & ~u);                           // V' = (V+U) | (V & ~U)
        }
    }
    int zeros = 0;
    for(int i = 0; i < n; i++) zeros += !(V[i >> 6] >> (i & 63) & 1);
    return zeros;
}
/*LATEX_DESC_BEGIN***************************
-> **LCS com bitset (Hyyro / Allison-Dix)**
Comprimento da LCS de a e b em O(|a||b|/64), com palavras de 64 bits e carry.

Complexidade: O(|b| * |a| / 64) tempo, O(256 * |a|/64) memoria.
Uso:
  int l = lcs_bitset(a, b);   // qualquer alfabeto de 256 chars

* Sobre o codigo:
  M[c] tem bit i ligado se a[i] == c. V comeca com todos os bits 1. Para cada
  caractere ch de b, calcula-se U = V & M[ch] e V' = (V+U) | (V & ~U) com carry
  propagado palavra a palavra. A LCS e o numero de zeros nos |a| primeiros bits.

* Problemas e reducoes:
  + LCS de strings de ate ~1e5 com O(n^2/64).
  + Comparar sequencias grandes sem alocar matriz.

Cuidados: V comeca com todos os bits 1; bits acima de |a| sao mascarados no
  fim pela contagem. Para reconstrucao use Hirschberg (code/dp/hirschberg.cpp),
  nao este.
Catalogo: DP > LCS bitset.
Digitacao: 22 linhas | media.
*****************************LATEX_DESC_END*/
