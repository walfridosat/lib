// Subset sum com bitset e multiplicidades
const int SSW = 100005;
bitset<SSW> ss_bitset(const vector<int>& pesos){
    map<int,int> cnt;
    for(int x : pesos) cnt[x]++;
    bitset<SSW> b; b[0] = 1;
    for(auto [w, c] : cnt){
        for(int p = 1; c > 0; p <<= 1){
            int q = min(p, c); c -= q;
            if((ll)q * w < SSW) b |= b << (q * w);          // pacote de q copias do peso w
        }
    }
    return b;
}
vector<char> ss_count(int W, const vector<int>& w, const vector<int>& c){
    vector<char> dp(W+1, 0); dp[0] = 1;
    vector<int> used(W+1);
    for(size_t i = 0; i < w.size(); i++){
        for(int x = 0; x <= W; x++){
            if(dp[x]) used[x] = 0;                          // ja alcancavel antes: 0 usos deste peso
            else if(x >= w[i] && dp[x-w[i]] && used[x-w[i]] < c[i]){
                dp[x] = 1; used[x] = used[x-w[i]] + 1;      // alcanca usando mais uma copia
            }
        }
    }
    return dp;
}
/*LATEX_DESC_BEGIN***************************
-> **Subset sum com bitset e multiplicidades**
Dado um multiconjunto de pesos, diz quais somas 0..W sao alcancaveis.
ss_bitset: binary splitting + bitset. ss_count: O(nW) com vetor used[] minimo.

Complexidade: ss_bitset O(sum log c_i * SSW/64); ss_count O(n_distintos * W).
Uso:
  bitset<SSW> r = ss_bitset(pesos);        // r[x] = x e alcancavel
  vector<char> ok = ss_count(W, w, c);     // w[i] peso, c[i] quantidade

* Sobre o codigo:
  ss_bitset agrupa pesos iguais e escreve cada quantidade c em pacotes 1,2,4,...;
  cada pacote vira um shift do bitset (0/1 sobre os pacotes). ss_count percorre as
  somas em ordem crescente e usa used[x] = minimo de copias do peso atual para x.

* Problemas e reducoes:
  + Mochila limitada so de viabilidade: basta saber se a soma e possivel.
  + Mochila de raiz (pesos distintos): ha ate sqrt(2S) pesos distintos.
  + Troco/particao com quantidade limitada de cada moeda.

Cuidados: SSW deve ser maior que a maior soma de interesse; bits acima de SSW
  sao descartados no shift (ok para "<= W"). Pesos positivos.
Catalogo: DP > Subset sum com bitset / mochila limitada.
Digitacao: 26 linhas | media. Atalho: se todas as quantidades sao 1, troque o
  laco de pacotes por b |= b << w.
*****************************LATEX_DESC_END*/
