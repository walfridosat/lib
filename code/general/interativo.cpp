// Template interativo + buscas binarias interativas + interator local
//
// O que faz: funcao de query com flush, busca binaria por query (valor ate 1e18 em ~60 queries),
//            min e max em ceil(3n/2)-2 comparacoes; esqueleto de interator para teste local.
// Quando usar: problemas interativos. Catalogo > Construtivos e interativos (Busca binaria interativa, Flush e protocolo)
// Complexidade: log N queries / 3n/2 comparacoes
// Uso: ll ask(ll x) manda "? x", da flush e le a resposta (se vier -1, exit(0) imediatamente).
//      bsearchInteractive(lo, hi, pred): menor x em [lo, hi] com pred(x) verdadeiro (pred monotono; pred faz a query).
//      minMaxCompare(n, less): indices do min e do max usando less(i, j) (query "a[i] < a[j]?").
// Cuidados: SEMPRE flush apos cada saida. O template define endl como '\n' (sem flush),
//           entao use '\n' << flush ou cout.flush(); nao misture cin/scanf sem sync;
//           conte queries localmente; em erro do juiz (-1) termine na hora. Teste com interator local (abaixo).
ll ask(ll x) {
    cout << "? " << x << '\n' << flush;
    ll r; cin >> r;
    if (r == -1) exit(0);
    return r;
}
void answer(ll x) { cout << "! " << x << '\n' << flush; }
template<class P> ll bsearchInteractive(ll lo, ll hi, P pred) {
    while (lo < hi) {
        ll mid = lo + (hi - lo) / 2;
        if (pred(mid)) hi = mid; else lo = mid + 1;
    }
    return lo;
}
// pareia elementos: compara o par (1 query), depois menor com menores e maior com maiores
template<class L> pair<int, int> minMaxCompare(int n, L less) {
    int mn = -1, mx = -1;
    for (int i = 0; i + 1 < n; i += 2) {
        int a = i, b = i + 1; if (less(b, a)) swap(a, b);      // a <= b
        if (mn == -1) { mn = a; mx = b; continue; }
        if (less(a, mn)) mn = a;
        if (less(mx, b)) mx = b;
    }
    if (n % 2) {
        int c = n - 1;
        if (mn == -1) mn = mx = c;
        else { if (less(c, mn)) mn = c; if (less(mx, c)) mx = c; }
    }
    return {mn, mx};
}
/* Interator local para testes (arquivo separado inter.cpp). Ligue com pipe de dois sentidos ou use:
     mkfifo f1 f2; ./inter < f1 > f2 & ./sol < f2 > f1
   (Windows: use um driver em python com subprocess). Esqueleto:
   #include <bits/stdc++.h>
   int main(int argc, char** argv) {
       long long secret = atoll(argv[1]); int q = 0;
       std::string c; long long x;
       while (std::cin >> c) {
           if (c == "?") { std::cin >> x; q++; std::cout << (x >= secret) << std::endl; if (q > 60) return 1; }
           else { std::cin >> x; std::cerr << (x == secret ? "OK " : "WA ") << q << " queries\n"; return x != secret; }
       }
   }
*/
