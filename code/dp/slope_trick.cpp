// Slope trick
//
// O que faz: mantem uma funcao convexa linear por partes f(x) com dois heaps (pontos de quebra a esquerda L e a direita R)
//   e o valor minimo. Operacoes: somar max(0,x-a), max(0,a-x), |x-a|, prefix min, suffix min, shift (janela).
// Quando usar: Catalogo > DP > "Slope trick: reconhecer", "Slope trick com translacao".
//   dp[i][x] = min_y dp[i-1][y] + |x-a_i| com restricao em y-x; "tornar array nao-decrescente com custo |a_i-b_i|".
// Complexidade: O(log n) por operacao.
// Uso: SlopeTrick st; para cada i: st.prefix_min(); st.add_abs(a[i]);  st.minf = custo minimo
//   (nao-decrescente). Para |x_i - x_{i-1}| <= d: st.shift(-d, d); st.add_abs(a[i]).
// Cuidados: minf e o minimo global de f. f inicial = 0 (constante). topL vazio = -INF, topR vazio = +INF.
//   Offsets addl/addr guardam shifts lazy. Para custo c*|x-a| com c grande, insira c copias (ou heap com contagem).
struct SlopeTrick {
    const ll INF = (ll)4e18;
    ll minf = 0, addl = 0, addr = 0;
    priority_queue<ll> L;                                   // max-heap: quebras da parte decrescente
    priority_queue<ll, vector<ll>, greater<ll>> R;          // min-heap: quebras da parte crescente
    ll topL(){ return L.empty() ? -INF : L.top() + addl; }
    ll topR(){ return R.empty() ?  INF : R.top() + addr; }
    void pushL(ll x){ L.push(x - addl); }
    void pushR(ll x){ R.push(x - addr); }
    ll popL(){ ll x = topL(); L.pop(); return x; }
    ll popR(){ ll x = topR(); R.pop(); return x; }
    void add_x_minus_a(ll a){                               // f += max(0, x-a)
        minf += max(0LL, topL() - a);
        pushL(a); pushR(popL());
    }
    void add_a_minus_x(ll a){                               // f += max(0, a-x)
        minf += max(0LL, a - topR());
        pushR(a); pushL(popR());
    }
    void add_abs(ll a){ add_x_minus_a(a); add_a_minus_x(a); }
    void prefix_min(){ R = decltype(R)(); addr = 0; }       // g(x) = min_{y<=x} f(y)
    void suffix_min(){ L = decltype(L)(); addl = 0; }       // g(x) = min_{y>=x} f(y)
    void shift(ll a, ll b){ addl += a; addr += b; }         // g(x) = min_{x-b<=y<=x-a} f(y), a<=b
};
