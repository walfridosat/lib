// Geracao de permutacoes (backtracking)
//
// O que faz: generatePermutations(nums) devolve todas as permutacoes dos n elementos,
//            na ordem lexicografica dos indices (O(n! * n)).
// Quando usar: Catalogo > Construtivos e interativos (brute force pequeno); n <= 8-9.
//            Para a proxima permutacao use next_permutation; para contar, use formulas.
// Complexidade: O(n! * n) tempo e O(n! * n) memoria (todas guardadas).
// Uso: auto ps = generatePermutations(a); (a e copiado; duplicates geram repeticoes)
// Cuidados: nao trata elementos repetidos (deduplique com set ou exija distintos);
//            para n grande apenas conte/itere sob demanda em vez de guardar tudo.
void backtrack(vector<ll>& nums, vector<bool>& used, vector<ll>& current, vector<vector<ll>>& result) {
    if (current.size() == nums.size()) {
        result.push_back(current);
        return;
    }

    int n = nums.size();
    for (int i = 0; i < n; ++i) {
        if (!used[i]) {
            used[i] = true;
            current.push_back(nums[i]);

            backtrack(nums, used, current, result);

            current.pop_back();
            used[i] = false;
        }
    }
}

vector<vector<ll>> generatePermutations(vector<ll>& nums) {
    vector<vector<ll>> result;
    vector<ll> current;
    vector<bool> used(nums.size(), false);
    backtrack(nums, used, current, result);
    return result;
}