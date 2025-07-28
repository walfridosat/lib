#include <bits/stdc++.h>
using namespace std;
mt19937 rng(time(0));
int l = 1;
int r = 1e5;
vector<int> random_a(int n){
    uniform_int_distribution<int>dist(l,r);
    vector<int>a(n);
    for(int& x : a)x=dist(rng);
    return a;
}
vector<int> random_perm(int n){
    vector<int>a(n);
    iota(a.begin(),a.end(),0);
    shuffle(a.begin(),a.end(),rng);
    return a;
}
