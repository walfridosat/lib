// Macro de debug e timer
//
// O que faz: dbg(x, y, ...) imprime nome e valor em cerr (so com -DLOCAL); timer para heuristicas.
// Quando usar: depuracao local; heuristicas com limite de tempo. Catalogo > Quando nada funciona, Aleatorizacao (Tempo como parametro)
// Complexidade: -
// Uso: dbg(a, b); dbg(vector); double t = elapsed();   compile local com g++ -DLOCAL
// Cuidados: sem LOCAL a macro vira vazia (pode deixar no submit). Suporta pair e containers (nao string-in-container aninhado).
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
