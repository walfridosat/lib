void backtrack(vector<ll>& nums, vector<bool>& used, vector<ll>& current, vector<vector<ll>>& result) {
    if (current.size() == nums.size()) {
        result.push_back(current);
        return;
    }

    for (int i = 0; i < nums.size(); ++i) {
        if (!used[i]) {
            used[i] = true;
            current.push_back(nums[i]);

            backtrack(nums, used, current, result);

            current.pop_back();
            used[i] = false;
        }
    }
}

vector<vector<ll>> generatePermutations(vector<ll>& nums) {
    vector<vector<ll>> result;
    vector<ll> current;
    vector<bool> used(nums.size(), false);
    backtrack(nums, used, current, result);
    return result;
}