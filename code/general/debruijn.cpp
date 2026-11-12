// Sequencia de de Bruijn
//
// O que faz: string ciclica de tamanho k^n contendo toda string de tamanho n sobre alfabeto {0..k-1} exatamente uma vez.
// Quando usar: cofres/PINs, "menor string contendo todas as mascaras". Catalogo > Construtivos (de Bruijn)
// Complexidade: O(k^n)
// Uso: vector<int> s = deBruijn(k, n);  ciclico; para string linear: s + primeiros n-1 elementos (tamanho k^n + n - 1).
// Cuidados: o algoritmo e a concatenacao de palavras de Lyndon (FKM). Para n=1 devolve 0..k-1.
vector<int> deBruijn(int k, int n) {
    vector<int> a(k * n, 0), seq;
    function<void(int, int)> db = [&](int t, int p) {
        if (t > n) { if (n % p == 0) for (int i = 1; i <= p; i++) seq.push_back(a[i]); }
        else {
            a[t] = a[t - p]; db(t + 1, p);
            for (int j = a[t - p] + 1; j < k; j++) a[t] = j, db(t + 1, t);
        }
    };
    db(1, 1);
    return seq;
}
