// Debug e timer - imprime nomes e valores com -DLOCAL
#ifdef LOCAL
template<class A, class B> ostream& operator<<(ostream& o, const pair<A, B>& p) { return o << "(" << p.first << "," << p.second << ")"; }
template<class T, class = typename enable_if<!is_same<T, string>::value, typename T::value_type>::type>
ostream& operator<<(ostream& o, const T& v) { o << "{"; bool f = 1; for (auto& x : v) { if (!f) o << ","; f = 0; o << x; } return o << "}"; }
void dbg_out() { cerr << endl; }
template<class H, class... T> void dbg_out(H h, T... t) { cerr << " " << h; dbg_out(t...); }
#define dbg(...) cerr << "[" << #__VA_ARGS__ << "]:", dbg_out(__VA_ARGS__)
#else
#define dbg(...)
#endif
// tempo desde o inicio do programa, em segundos
double elapsed() { return (double)clock() / CLOCKS_PER_SEC; }
/*LATEX_DESC_BEGIN***************************
-> **Debug e Timer** - dbg(x, ...) imprime nome e valor em cerr com -DLOCAL; elapsed() em segundos.
Complexidade: -
Uso: dbg(a, b); dbg(v); double t = elapsed();  // compile com g++ -DLOCAL
* Sobre o codigo: operator<< para pair/containers e dbg_out recursivo; sem LOCAL a macro e vazia.
* Problemas e reducoes: + depurar valores sem escrever prints; + medir tempo.
Cuidados: sem LOCAL a macro vira vazia; suporta pair e containers (nao string aninhada).
Catalogo: Quando nada funciona, Aleatorizacao (Tempo como parametro)
Digitacao: 12 linhas | facil.
*****************************LATEX_DESC_END*/
