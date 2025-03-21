void knapsack(vector<ll>&palao, vector<ll>&ryei){
    //palao = peso
    //ryei = valor
    ll n=palao.size();
    ll w = 0; //peso que vc quer
    FORI(n){
        cin>>palao[i];
        cin>>ryei[i];
    }

    vector<ll> dp(w+1, 0); // dp em w
    FORI(n) {
        for (ll j = w; j >= palao[i]; j--) {
            dp[j] = max(dp[j], dp[j - palao[i]] + ryei[i]);
        }
    }
}