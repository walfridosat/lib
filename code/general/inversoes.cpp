// Contagem de inversoes (merge sort e BIT) e pares com condicao
//
// O que faz: numero de pares i<j com a[i] > a[j]; troca minima de adjacentes para transformar A em B.
// Quando usar: "swaps adjacentes minimos", "contar pares i<j com condicao".
//              Catalogo > Arrays e guloso (Contar pares i<j, Minimo de trocas adjacentes de A para B)
// Complexidade: O(n log n)
// Uso: ll inv = countInv(a);   (nao altera a)   minAdjSwaps(A, B) -> -1 se nao sao multiconjuntos iguais.
// Cuidados: inversoes estritas (a[i] > a[j]); para nao estritas troque > por >= no merge. Resultado ate n^2/2: ll.
ll mergeCount(vector<ll>& a, vector<ll>& tmp, int l, int r) {   // ordena a[l, r)
    if (r - l < 2) return 0;
    int m = (l + r) / 2;
    ll c = mergeCount(a, tmp, l, m) + mergeCount(a, tmp, m, r);
    int i = l, j = m, k = l;
    while (i < m || j < r) {
        if (j == r || (i < m && a[i] <= a[j])) tmp[k++] = a[i++];
        else { c += m - i; tmp[k++] = a[j++]; }   // a[j] menor que todos os restantes da esquerda
    }
    copy(tmp.begin() + l, tmp.begin() + r, a.begin() + l);
    return c;
}
ll countInv(vector<ll> a) {
    vector<ll> tmp(a.size());
    return mergeCount(a, tmp, 0, a.size());
}
// Minimo de trocas adjacentes para A virar B: mapeia a k-esima ocorrencia de cada valor de A para a k-esima de B
ll minAdjSwaps(const vector<ll>& A, const vector<ll>& B) {
    int n = A.size(); if ((int)B.size() != n) return -1;
    map<ll, vector<int>> pos;
    for (int i = n - 1; i >= 0; i--) pos[B[i]].push_back(i);   // pop_back da a menor posicao primeiro
    vector<ll> p(n);
    for (int i = 0; i < n; i++) {
        auto it = pos.find(A[i]);
        if (it == pos.end() || it->second.empty()) return -1;
        p[i] = it->second.back(); it->second.pop_back();
    }
    return countInv(p);
}
