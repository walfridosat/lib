// Mochila limitada - fila monotona e binary splitting
vector<ll> knap_deque(int W, const vector<int>& w, const vector<ll>& v, const vector<ll>& c){
    vector<ll> dp(W+1, 0), nd(W+1);
    int n = w.size();
    vector<pair<int,ll>> dq(W+2);                           // (indice t, valor dp[r+t*w]-t*v)
    for(int i = 0; i < n; i++){
        ll cnt = min<ll>(c[i], W / w[i]);
        for(int r = 0; r < w[i] && r <= W; r++){
            int h = 0, t = 0;                               // deque dq[h..t)
            for(int k = 0; r + (ll)k * w[i] <= W; k++){
                ll val = dp[r + k * w[i]] - (ll)k * v[i];
                while(t > h && dq[t-1].second <= val) t--;  // mantem valores decrescentes
                dq[t++] = {k, val};
                while(dq[h].first < k - cnt) h++;           // janela de tamanho cnt+1
                nd[r + k * w[i]] = dq[h].second + (ll)k * v[i];
            }
        }
        dp = nd;
    }
    return dp;
}
vector<ll> knap_split(int W, const vector<int>& w, const vector<ll>& v, const vector<ll>& c){
    vector<ll> dp(W+1, 0);
    int n = w.size();
    for(int i = 0; i < n; i++){
        ll rest = min<ll>(c[i], W / w[i]);
        for(ll p = 1; rest > 0; p <<= 1){                   // pacotes 1,2,4,...,resto
            ll q = min(p, rest); rest -= q;
            ll ww = q * w[i], vv = q * v[i];
            for(int x = W; x >= ww; x--) dp[x] = max(dp[x], dp[x-ww] + vv);   // 0/1: W decrescente
        }
    }
    return dp;
}
/*LATEX_DESC_BEGIN***************************
-> **Mochila limitada (bounded knapsack)**
Maximiza valor com itens (peso w_i, valor v_i, quantidade c_i), capacidade W.
knap_deque: O(nW) com deque por residuo. knap_split: O(nW log c) por binary
splitting. Devolve dp[0..W], dp[x] = melhor valor com peso total <= x.

Complexidade: knap_deque O(n*W); knap_split O(W * sum log c_i).
Uso:
  vector<ll> dp = knap_deque(W, w, v, c);
  vector<ll> dp2 = knap_split(W, w, v, c);

* Sobre o codigo:
  knap_deque percorre cada residuo r mod w[i] e mantem uma janela deslizante de
  cnt+1 candidatos com deque monotona de valores dp[r+k*w]-k*v. knap_split
  quebra c em pacotes 1,2,4,... e resolve como 0/1.

* Problemas e reducoes:
  + Mochila com quantidade limitada de cada item.
  + Troco minimo/maximo com numero limitado de moedas.
  + Contagem de formas com multiplicidades (troque max por soma).

Cuidados: na 0/1, o laco de W e decrescente. Valores negativos de v nao sao
  tratados. c_i enorme: o codigo ja limita em W/w[i]. Para peso exato,
  inicialize dp[x>0] = -INF.
Catalogo: DP > Mochila limitada (binary splitting / fila monotona).
Digitacao: 33 linhas | media. Atalho: knap_split e mais curto; use-o se log c
  for aceitavel, deixando knap_deque so quando O(nW) for necessario.
*****************************LATEX_DESC_END*/
