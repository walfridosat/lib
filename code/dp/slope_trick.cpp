// Slope trick - funcao convexa com dois heaps
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
/*LATEX_DESC_BEGIN***************************
-> **Slope trick**
Mantem uma funcao convexa linear por partes f(x) com dois heaps (quebras a
esquerda L e a direita R) e o valor minimo minf.

Complexidade: O(log n) por operacao.
Uso:
  SlopeTrick st;
  for (int i = 0; i < n; i++) { st.prefix_min(); st.add_abs(a[i]); }
  ll custo = st.minf;   // tornar o array nao-decrescente com custo |a_i - b_i|
  // janela: st.shift(-d, d); st.add_abs(a[i]);

* Sobre o codigo:
  add_x_minus_a(a) soma max(0, x-a), add_a_minus_x(a) soma max(0, a-x) e
  add_abs(a) soma |x-a|. minf acompanha o minimo global. prefix_min/suffix_min
  descartam um dos heaps; shift guarda translacoes lazy em addl/addr.

* Problemas e reducoes:
  + Tornar um array nao-decrescente com custo |a_i - b_i|.
  + DP com |x - a_i| por passo e restricao em y-x.
  + Aproximar pontos por uma funcao convexa minimizando soma de |.|.
  + Janela de deslocamento por passo (shift).

Cuidados: minf e o minimo global de f; f inicial = 0. topL vazio = -INF e
  topR vazio = +INF. Offsets addl/addr sao lazy. Para custo c*|x-a| com c
  grande, insira c copias ou use heap com contagem.
Catalogo: DP > Slope trick.
Digitacao: 24 linhas | media.
*****************************LATEX_DESC_END*/
