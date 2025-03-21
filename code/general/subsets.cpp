vector<vector<ll>> subsets(vector<ll>& nums) {
    ll n = nums.size();
    vector<vector<ll>> subsets;
    
    ll totalSubsets = 1 << n; 
    
    for (ll mask = 0; mask < totalSubsets; ++mask) {
        vector<ll> subset;
        for (int i = 0; i < n; ++i) {
            if (mask & (1 << i)) {
                subset.push_back(nums[i]);
            }
        }
        subsets.push_back(subset);
    }
    
    return subsets;
}