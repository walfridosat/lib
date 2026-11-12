// ColorUpdate: intervalos [l, r) disjuntos, cada um com uma cor v (ll)
// Pedaco = array<ll,3> {l, r, v}. Tudo semiaberto: o ponto r NAO entra.
// NAO junta vizinhos de mesma cor sozinho (use updMerge/join/normalize).
// Complexidade: O(log n) por operacao + tamanho do que e retornado/percorrido.
// Amortizado: cada upd cria <= 3 intervalos, cada um e apagado no maximo 1 vez.

struct ColorUpdate {
    typedef array<ll, 3> R;
    const ll NONE = LLONG_MIN;
    const R VOID = {NONE, NONE, NONE};
    map<ll, pair<ll, ll>> mp; // mp[l] = {r, v}

    // ===================== BASICOS =====================

    // Corta o intervalo que atravessa x em [l,x) e [x,r). Depois disso x e fronteira.
    void split(ll x) {
        auto it = mp.upper_bound(x);
        if (it == mp.begin()) return;
        --it;
        auto [r, v] = it->second;
        if (it->first < x && x < r) it->second.first = x, mp[x] = {r, v};
    }

    // Apaga [l, r). Retorna os pedacos apagados (recortados para dentro de [l, r)).
    vector<R> erase(ll l, ll r) {
        vector<R> ans;
        if (l >= r) return ans;
        split(l), split(r);
        auto a = mp.lower_bound(l), b = mp.lower_bound(r);
        for (auto it = a; it != b; ++it)
            ans.push_back({it->first, it->second.first, it->second.second});
        mp.erase(a, b);
        return ans;
    }

    // Pinta [l, r) com v. Retorna os pedacos antigos que foram sobrescritos.
    vector<R> upd(ll l, ll r, ll v) {
        auto ans = erase(l, r);
        if (l < r) mp[l] = {r, v};
        return ans;
    }

    // Intervalo inteiro {l, r, v} que contem x, ou VOID se x nao esta pintado.
    R getrange(ll x) {
        auto it = mp.upper_bound(x);
        if (it == mp.begin()) return VOID;
        --it;
        if (x >= it->second.first) return VOID;
        return {it->first, it->second.first, it->second.second};
    }

    // Cor de x, ou NONE se x nao esta pintado.
    ll get(ll x) { return getrange(x)[2]; }

    // Todos os intervalos, em ordem.
    vector<R> all() {
        vector<R> ans;
        for (auto &[l, p] : mp) ans.push_back({l, p.first, p.second});
        return ans;
    }

    // ===================== AVANCADOS =====================

    // Se o intervalo que termina em x e o que comeca em x encostam e tem a mesma
    // cor, funde os dois num so.
    void join(ll x) {
        auto it = mp.find(x);
        if (it == mp.end() || it == mp.begin()) return;
        auto p = prev(it);
        if (p->second.first == x && p->second.second == it->second.second)
            p->second.first = it->second.first, mp.erase(it);
    }

    // upd + funde com os vizinhos de mesma cor. Se so usar updMerge, cada trecho
    // maximo de mesma cor e sempre UM intervalo (getrange devolve a componente).
    vector<R> updMerge(ll l, ll r, ll v) {
        auto ans = upd(l, r, v);
        if (l < r) join(r), join(l);
        return ans;
    }

    // Funde todos os vizinhos de mesma cor. O(n).
    void normalize() {
        for (auto it = mp.begin(); it != mp.end() && next(it) != mp.end();) {
            auto nx = next(it);
            if (it->second.first == nx->first && it->second.second == nx->second.second)
                it->second.first = nx->second.first, mp.erase(nx);
            else ++it;
        }
    }

    // Pedacos que intersectam [l, r), recortados, SEM modificar a estrutura.
    vector<R> query(ll l, ll r) {
        vector<R> ans;
        if (l >= r) return ans;
        auto it = mp.upper_bound(l);
        if (it != mp.begin()) --it;
        for (; it != mp.end() && it->first < r; ++it) {
            ll a = max(l, it->first), b = min(r, it->second.first);
            if (a < b) ans.push_back({a, b, it->second.second});
        }
        return ans;
    }

    // Quantos pontos de [l, r) estao pintados (qualquer cor).
    ll covered(ll l, ll r) {
        ll s = 0;
        for (auto [a, b, v] : query(l, r)) s += b - a;
        return s;
    }

    // Quantos pontos de [l, r) tem cor c.
    ll countColor(ll l, ll r, ll c) {
        ll s = 0;
        for (auto [a, b, v] : query(l, r)) if (v == c) s += b - a;
        return s;
    }

    // Menor y >= x NAO pintado. O(k log n), k = numero de intervalos
    // encostados um no outro a partir de x.
    ll nextFree(ll x) {
        while (true) {
            R g = getrange(x);
            if (g[0] == NONE) return x;
            x = g[1];
        }
    }

    // Menor y >= x pintado, ou NONE se nao existe.
    ll nextPainted(ll x) {
        if (getrange(x)[0] != NONE) return x;
        auto it = mp.upper_bound(x);
        return it == mp.end() ? NONE : it->first;
    }

    // Maior y <= x pintado, ou NONE se nao existe.
    ll prevPainted(ll x) {
        auto it = mp.upper_bound(x);
        if (it == mp.begin()) return NONE;
        --it;
        return min(x, it->second.first - 1);
    }

    // Chama f(l, r, v) em cada pedaco dentro de [l, r), com v por REFERENCIA
    // (pode alterar a cor). Pontos nao pintados sao ignorados.
    template <class F> void forEach(ll l, ll r, F f) {
        if (l >= r) return;
        split(l), split(r);
        for (auto it = mp.lower_bound(l); it != mp.end() && it->first < r; ++it)
            f(it->first, it->second.first, it->second.second);
    }

    // Soma d na cor de todo pedaco pintado em [l, r).
    void add(ll l, ll r, ll d) {
        forEach(l, r, [&](ll, ll, ll &v) { v += d; });
    }

    // k-esimo menor valor (1-indexado, contando cada ponto) entre os pontos
    // pintados de [l, r). NONE se k > covered(l, r). O(m log m), m = pedacos.
    ll kth(ll l, ll r, ll k) {
        auto q = query(l, r);
        sort(q.begin(), q.end(), [](const R &a, const R &b) { return a[2] < b[2]; });
        for (auto [a, b, v] : q) {
            if (k <= b - a) return v;
            k -= b - a;
        }
        return NONE;
    }
};
