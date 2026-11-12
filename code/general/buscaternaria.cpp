// Busca ternaria (minimo de funcao convexa/unimodal)
//
// O que faz: tern_double(l, r) acha o x que minimiza func em [l, r] (250 iteracoes);
//            tern_int(l, r) acha o inteiro minimo comparando vizinhos.
// Quando usar: Catalogo > Busca binaria e otimizacao (Busca ternaria). So vale se a
//            funcao for convexa/unimodal no intervalo; caso contrario use binaria na derivada.
// Complexidade: O(iteracoes) no double; O(log(range)) no inteiro.
// Uso: troque func(x) pela sua funcao; ld x = tern_double(l, r); ll i = tern_int(l, r).
// Cuidados: standalone (tem #include e func de exemplo); em empates no inteiro o
//            resultado pode ser qualquer minimizador; use long double para precisao.
#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define ld long double

ll func(ll x){
    return 2*x*x - 4*x + 2;
}

ld tern_double(ld l, ld r) {
    for(int it=250; it--;){
        ld m1 = l + (r-l)/3, m2 = r - (r-l)/3;
        ld f1 = func(m1), f2 = func(m2);
        if(f1 < f2) r = m2;
        else l = m1;
    }
    //retorna o x que minimiza a funcao
    return l;
}

ll tern_int(ll l, ll r){

    while(r-l>3){
        //ATENCAO
        int m1 = l + (r - l) / 3;
        int m2 = r - (r - l) / 3;

        if(func(m1)<func(m2)){
            r=m2;
        } else {
            l=m1;
        }
    }

    ll ans = LLONG_MAX;
    for (int i = l; i <= r; i++) {
        ans = min(ans, func(i));
    }

    //retorna o f(x) minimizado
    return ans;
} 
    
