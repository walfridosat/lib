// Geracao de todos os subconjuntos (por mascara)
//
// O que faz: subsets(nums) devolve os 2^n subconjuntos de nums (cada um como vetor).
// Quando usar: Catalogo > Construtivos e interativos (brute force pequeno); n <= 20.
//            Para DP de mascara use o laco direto sem materializar os vetores.
// Complexidade: O(2^n * n) tempo e O(2^n * n) memoria.
// Uso: auto ss = subsets(a); (a e copiado; a ordem dos elementos e preservada)
// Cuidados: n >= 31 estoura 1<<n e a memoria; para n grande conte/itere sob demanda.
vector<vector<ll>> subsets(vector<ll>& nums) {
    ll n = nums.size();
    vector<vector<ll>> subsets;
    
    ll totalSubsets = 1 << n; 
    
    for (ll mask = 0; mask < totalSubsets; ++mask) {
        vector<ll> subset;
        for (int i = 0; i < n; ++i) {
            if (mask & (1 << i)) {
                subset.push_back(nums[i]);
            }
        }
        subsets.push_back(subset);
    }
    
    return subsets;
}