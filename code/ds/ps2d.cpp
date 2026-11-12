// Soma de prefixo 2D (prefix sum em matriz)
//
// O que faz: prefix[i][j] = soma do retangulo [0..i] x [0..j]; consulta de retangulo em O(1).
// Quando usar: Catalogo > Estruturas de dados e queries (Retangulo -> 4 prefixos + BIT).
// Complexidade: O(n*m) para construir, O(1) por consulta, O(n*m) memoria.
// Uso: auto p = ps2d(a); ps2d_query(p, x1, y1, x2, y2) com coordenadas inclusivas e 0-indexadas.
// Cuidados: matriz nao vazia; nao use se a matriz muda (para updates use BIT 2D).

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