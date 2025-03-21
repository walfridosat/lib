ll lis(vector<ll> &palao) {
    vector<ll>tfg;
    for(auto x : palao){
        auto it = lower_bound(all(tfg), x);
        if (it == tfg.end()) tfg.pb(x);
        else *it = x;
    }
    return tfg.size();
}
