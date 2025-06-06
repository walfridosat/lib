// Segtree lazy
//
// 
// 
// 
// 
// 

class SegTree {
    private:
        vector<ll> tree, lazy;
        ll n;
    
        void push(ll node, ll start, ll end) {
            if (lazy[node] != 0) {
                tree[node] += (end - start + 1) * lazy[node];
                if (start != end) {
                    lazy[2 * node] += lazy[node];
                    lazy[2 * node + 1] += lazy[node];
                }
                lazy[node] = 0;
            }
        }
    
        void build(const vector<ll>& arr, ll node, ll start, ll end) {
            if (start == end) {
                tree[node] = arr[start];
            } else {
                ll mid = (start + end) / 2;
                build(arr, 2 * node, start, mid);
                build(arr, 2 * node + 1, mid + 1, end);
                tree[node] = tree[2 * node] + tree[2 * node + 1];
            }
        }
    
        void updateRange(ll node, ll start, ll end, ll l, ll r, ll val) {
            push(node, start, end);
            if (r < start || end < l) return;
            if (l <= start && end <= r) {
                lazy[node] += val;
                push(node, start, end);
                return;
            }
            ll mid = (start + end) / 2;
            updateRange(2 * node, start, mid, l, r, val);
            updateRange(2 * node + 1, mid + 1, end, l, r, val);
            tree[node] = tree[2 * node] + tree[2 * node + 1];
        }
    
        ll query(ll node, ll start, ll end, ll l, ll r) {
            push(node, start, end);
            if (r < start || end < l) return 0;
            if (l <= start && end <= r) return tree[node];
            ll mid = (start + end) / 2;
            return query(2 * node, start, mid, l, r) + 
                   query(2 * node + 1, mid + 1, end, l, r);
        }
    
    public:
        SegTree(const vector<ll>& arr) {
            n = arr.size();
            tree.resize(4 * n, 0);
            lazy.resize(4 * n, 0);
            build(arr, 1, 0, n - 1);
        }
    
        void update(ll l, ll r, ll val) {
            updateRange(1, 0, n - 1, l, r, val);
        }
    
        ll query(ll l, ll r) {
            return query(1, 0, n - 1, l, r);
        }
    };