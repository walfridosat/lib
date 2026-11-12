// Subset sum com bitset e multiplicidades
//
// O que faz: dado multiconjunto de pesos, diz quais somas 0..W sao alcancaveis.
//   ss_bitset: binary splitting + bitset (O(W/64) por pacote). ss_count: O(nW) sem log (usa used[] minimo).
// Quando usar: Catalogo > DP > "Subset sum com bitset", "Mochila limitada so de viabilidade", "Mochila de raiz (pesos distintos)".
//   Se soma total S: ha ate sqrt(2S) pesos distintos, agrupe iguais e use isso: S*sqrt(S)/64.
// Complexidade: ss_bitset O(sum_i log c_i * W/64); ss_count O(n_distintos * W).
// Uso: bitset<SSW> r = ss_bitset(pesos); r[x] = x alcancavel. ss_count(W, w, c) retorna vector<char> alcancavel[0..W].
//   w[i] peso distinto, c[i] quantidade. Para pesos "um bem grande" ver code/dp/subsetsum.cpp (Pisinger).
// Cuidados: SSW deve ser > soma maxima de interesse. Bits acima de SSW sao descartados (shift), ok para "<= W".
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
