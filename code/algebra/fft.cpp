// FFT complexa (double) e convolucao mod arbitrario
typedef complex<double> Cd;
void fft(vector<Cd>& a) {
    int n = a.size(), L = 31 - __builtin_clz(n);
    static vector<complex<long double>> R(2, 1);
    static vector<Cd> rt(2, 1); // rt[k+j] = e^(i*pi*j/k)
    for (static int k = 2; k < n; k *= 2) {
        R.resize(n); rt.resize(n);
        auto x = polar(1.0L, acosl(-1) / k);
        for (int i = k; i < 2 * k; i++) rt[i] = R[i] = i & 1 ? R[i / 2] * x : R[i / 2];
    }
    vector<int> rev(n);
    for (int i = 0; i < n; i++) rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
    for (int i = 0; i < n; i++) if (i < rev[i]) swap(a[i], a[rev[i]]);
    for (int k = 1; k < n; k *= 2)
        for (int i = 0; i < n; i += 2 * k)
            for (int j = 0; j < k; j++) {
                Cd z = rt[j + k] * a[i + j + k];
                a[i + j + k] = a[i + j] - z;
                a[i + j] += z;
            }
}
vector<double> conv(const vector<double>& a, const vector<double>& b) {
    if (a.empty() || b.empty()) return {};
    vector<double> res(a.size() + b.size() - 1);
    int L = 32 - __builtin_clz(res.size()), n = 1 << L;
    vector<Cd> in(n), out(n);
    copy(a.begin(), a.end(), in.begin());
    for (size_t i = 0; i < b.size(); i++) in[i].imag(b[i]); // a na parte real, b na imaginaria
    fft(in);
    for (Cd& x : in) x *= x;
    for (int i = 0; i < n; i++) out[i] = in[-i & (n - 1)] - conj(in[i]);
    fft(out);
    for (size_t i = 0; i < res.size(); i++) res[i] = imag(out[i]) / (4 * n);
    return res;
}
vector<ll> convMod(const vector<ll>& a, const vector<ll>& b, ll M) {
    if (a.empty() || b.empty()) return {};
    vector<ll> res(a.size() + b.size() - 1);
    int B = 32 - __builtin_clz(res.size()), n = 1 << B, cut = int(sqrt((double)M));
    vector<Cd> L(n), R(n), outs(n), outl(n);
    for (size_t i = 0; i < a.size(); i++) L[i] = Cd((int)(a[i] / cut), (int)(a[i] % cut));
    for (size_t i = 0; i < b.size(); i++) R[i] = Cd((int)(b[i] / cut), (int)(b[i] % cut));
    fft(L); fft(R);
    for (int i = 0; i < n; i++) {
        int j = -i & (n - 1);
        outl[j] = (L[i] + conj(L[j])) * R[i] / (2.0 * n);
        outs[j] = (L[i] - conj(L[j])) * R[i] / (2.0 * n) / Cd(0, 1);
    }
    fft(outl); fft(outs);
    for (size_t i = 0; i < res.size(); i++) {
        ll av = ll(real(outl[i]) + .5), cv = ll(imag(outs[i]) + .5);
        ll bv = ll(imag(outl[i]) + .5) + ll(real(outs[i]) + .5);
        res[i] = ((av % M * cut + bv) % M * cut + cv) % M;
    }
    return res;
}
/*LATEX_DESC_BEGIN***************************
-> **FFT complexa e convolucao mod arbitrario**
conv(a,b) convolui vetores de double; convMod(a,b,M) convolui mod M qualquer
(M < 2^31) quebrando cada coeficiente em duas metades de ~15 bits.

Complexidade: O(n log n); convMod usa 4 FFTs.
Uso:
  vector<double> c = conv(a, b);
  vector<ll> d = convMod(a, b, 1000000007);   // 0-based, tamanho |a|+|b|-1

* Sobre o codigo:
  fft e iterativa com bit-reversal e tabela de raizes. conv coloca a na parte
  real e b na imaginaria e extrai o produto com uma FFT. convMod separa a[i]
  em a[i]/cut e a[i]%cut, faz as transformadas e recombina as quatro partes
  (low/low, low/high, high/low, high/high).

* Problemas e reducoes:
  + Soma de pares a_i + b_j = s.
  + Casamento de strings com curinga (wildcard).
  + Convolucao mod 1e9+7 quando nao se quer 3 NTTs.

Cuidados: conv em double so e exato se n*(maior coef)^2 <~ 1e14; arredonde com
  llround. convMod: coeficientes em [0, M); raizes calculadas em long double.
  Para modulo arbitrario com mais garantia use conv_mod.cpp.
Catalogo: Algebra, polinomios e FFT (Precisao da FFT / Modulo arbitrario).
Digitacao: 56 linhas | dificil.
*****************************LATEX_DESC_END*/
