// dijkstra
//
// 
// 
// 
// 
// 

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