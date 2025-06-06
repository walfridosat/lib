void dp_frog(vector<ll>& palao){
    ll MAXV=LLONG_MAX;
    ll n = palao.size();
    ll k = 2; //opçoes pulo
    vector<ll>dp(MAXN,MAXV+1);
    dp[0]=0;
    for(int i = 1; i < n; i++){
        for(int j = 1; j<=k; j++){
            if(i-j>=0){
                dp[i]=min(dp[i],dp[i-j] + abs(palao[i] - palao[i-j]));
            }
        }
    }
}