// RNG para gerar testes e stress
//
// O que faz: random_a(n) gera n inteiros uniformes em [l, r]; random_perm(n) gera
//            uma permutacao aleatoria de 0..n-1; rng e mt19937 semeado com time(0).
// Quando usar: Catalogo > Aleatorizacao (stress test). Use no gerador, nunca na solucao.
// Complexidade: O(n) por vetor.
// Uso: ajuste os globais l, r; chame random_a(n) / random_perm(n).
// Cuidados: standalone (tem #include); para reprodutibilidade semeie com constante;
//            nao use em solucao que exige aleatorizacao verdadeira (juiz pode repetir seed).
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
