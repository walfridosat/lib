// Soma de prefixo 2D - retangulo em O(1)

vector<vector<ll>> ps2d(vector<vector<ll>>& palao){
    ll n=palao.size();
    ll m=palao[0].size();
    vector<vector<ll>>prefix(n, vector<ll>(m,0));
    for(int i = 0; i<n; i++){
        for(int j = 0; j<m; j++){
            prefix[i][j]=palao[i][j];
            if(i>0) prefix[i][j]+= prefix[i-1][j];
            if(j>0) prefix[i][j]+= prefix[i][j-1];
            if(i>0 && j>0) prefix[i][j] -=prefix[i-1][j-1];
        }
    }
    return prefix;
}

ll ps2d_query(vector<vector<ll>>& prefix, ll x1, ll y1, ll x2, ll y2) {
    ll sum = prefix[x2][y2];
    if (x1 > 0) sum -= prefix[x1 - 1][y2];
    if (y1 > 0) sum -= prefix[x2][y1 - 1];
    if (x1 > 0 && y1 > 0) sum += prefix[x1 - 1][y1 - 1];
    return sum;
}
/*LATEX_DESC_BEGIN***************************
-> **Soma de Prefixo 2D**
prefix[i][j] = soma do retangulo [0..i] x [0..j]; devolve a soma de qualquer
retangulo inclusivo em O(1). Coordenadas 0-based e inclusivas.

Complexidade: O(n*m) para construir, O(1) por consulta, O(n*m) memoria.
Uso:
  auto p = ps2d(a);
  ll s = ps2d_query(p, x1, y1, x2, y2);  // [x1..x2] x [y1..y2]

* Sobre o codigo:
  prefix[i][j] = a[i][j] + cima + esquerda - diagonal. A consulta usa quatro
  prefixos: total menos as faixas de cima e esquerda, somando a diagonal de
  volta.

* Problemas e reducoes:
  + Soma de submatriz inclusiva com quatro prefixos.
  + Contar pontos/peso em retangulo estatico.
  + Diferenca 2D: aplicar updates de retangulo e reconstruir com prefixo.
  + Coordenadas grandes: comprima antes de montar a matriz.

Cuidados: matriz nao vazia. Estrutura estatica; para updates use BIT 2D.
Catalogo: Estruturas de dados e queries.
Digitacao: 21 linhas | facil. Atalho: ok.
*****************************LATEX_DESC_END*/