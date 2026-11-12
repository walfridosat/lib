// Template interativo - query com flush, busca binaria, min/max
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
// pareia; menor com menores, maior com maiores
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
/*LATEX_DESC_BEGIN***************************
-> **Template Interativo**
Query com flush, busca binaria interativa (valor ate 1e18 em ~60 queries),
min e max em ceil(3n/2)-2 comparacoes, e esqueleto de interator local.

Complexidade: O(log N) queries; 3n/2 comparacoes
Uso:
  ll r = ask(x);              // manda "? x", flush, le a resposta (-1 -> exit)
  ll lo = bsearchInteractive(lo, hi, pred);
  auto [mn, mx] = minMaxCompare(n, less);
  answer(x);                  // manda "! x"

* Sobre o codigo:
  ask/answer fazem flush a cada saida; o pred de bsearch faz a query.
  minMaxCompare pareia elementos e compara menor com menores e maior com maiores.
  O comentario no fim tem um esqueleto de interator local para testar.

* Problemas e reducoes:
  + Achar valor secreto por comparacoes: bsearchInteractive.
  + Min e max com poucas comparacoes: minMaxCompare.

Cuidados: SEMPRE flush apos cada saida; o template define endl como '\n' (sem flush),
  entao use '\n' << flush ou cout.flush(); nao misture cin/scanf sem sync;
  conte queries; em erro do juiz (-1) termine na hora.
Catalogo: Construtivos e interativos (Busca binaria interativa, Flush e protocolo)
Digitacao: 43 linhas | media.
*****************************LATEX_DESC_END*/
