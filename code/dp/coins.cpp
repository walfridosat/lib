void dp_coins(vector<ll>& coins, ll target){
    vector<ll> dp(target + 1, MAXN+1);
    dp[0] = 0;

    for (ll i = 1; i <= target; i++) {
        for (auto c : coins) {
            if (i - c >= 0)
                dp[i] = min(dp[i], dp[i - c] + 1);
        }
    }

}