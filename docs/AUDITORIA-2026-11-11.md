# Auditoria dos docs — 2026-11-11

Escopo: `docs/catalogo-completo.md` (2252 linhas), `docs/mapa-rapido.md`, `docs/PLANO_LIB.md` e estado real do repo.
Método: 20 subagentes em paralelo — 18 fatiaram o catálogo, 1 compilou o repo e conferiu o plano, 1 cruzou o mapa com o catálogo. Os achados de alta gravidade foram reconferidos por amostragem.
Legenda: **[ERRO]** fato/fórmula errada; **[GRAVE]** induz a solução errada em casos comuns; **[IMPRECISO]** falta hipótese/condição ou redação enganosa; **[FALTA]** lacuna.

> Aviso metodológico: os rótulos `*(adicionado em 2026-11-10 por agentes; revisado)*` **não são confiáveis**. O arquivo tem 23 marcadores e **nenhum** bloco marcado "não revisado", apesar do aviso da linha 3. Quase todas as seções auditadas têm erros dentro de blocos marcados "revisado".

## Status em 2026-11-11 (pós-correção)

- Catálogo: as 20 faixas foram corrigidas e remontadas; o arquivo mantém 2252 linhas. O aviso da linha 3 foi atualizado.
- Código: todos os `.cpp` compilam com o prelude derivado do template; os 9 arquivos de combinatória compilam com `binom_mod.cpp` incluído antes. Nenhuma falha na varredura final.
- `code/general/guloso_heap.cpp`: `stocks` agora soma as diferenças positivas adjacentes (a versão heap superconta); `[0,1,4,7] -> 7` e `[3,1,4,1,5,9] -> 11`.
- `code/string/bitset_match.cpp`: `lcs_bits` reescrito com palavras de 64 bits e carry; validado contra DP em 5000 casos aleatórios.
- `code/ds/sparse_min.cpp` reescrito e validado contra brute; `lis`, `coins`, `knapsack`, `frog` e `stocks` testados com casos conhecidos.
- `PLANO_LIB.md` §3 lista as correções aplicadas; §1 documenta exceções de programa completo; §2 documenta o include de `binom_mod.cpp`.
- `mapa-rapido.md`: referência quebrada removida, condições de LGV/BEST/planar/diferença em árvore corrigidas e técnicas ausentes adicionadas.
- `docs/catalogo-completo.md` foi substituído pela versão corrigida (2252 linhas, 23 seções, tabelas com `\|` escapado).
- `docs/lib-index.md` gerado: 206 trechos, com status de compilação/teste e a seção do catálogo de cada um.
- Correções adicionais no código: `ds/seg_t.cpp` (estava vazio; agora segtree iterativa), `ds/ps2d.cpp` (título errado), `string/trie.cpp` (`init()` automático), `dp/digitdp.cpp` (tabela `[171]`), `dp/subsetsum.cpp` (ordena `w`, validado com brute), `graph/dijkstra` renomeado para `.cpp`.
- Varredura final: 206 `.cpp` com prelude completo e mínimo, mais `binom_mod.cpp` nos 9 de combinatória — 0 falhas.

---

## 0. Resumo executivo

### 0.1 O que bloqueia o trabalho agora (plano/repo)

| # | Onde | Problema | Ação |
|---|---|---|---|
| 1 | `PLANO_LIB.md` §3 | 24 arquivos falham no prelude, mas só 14 são citados. Ficam de fora 10 antigos: `dp/coins`, `dp/comb`, `dp/frog`, `ds/sparse_min`, `graph/kruskal`, `math/sieve`, `string/hash`, `string/trie` (e `dp/lis`, `dp/knapsack` falham só com o prelude de 3 linhas). | Completar a seção 3 e rodar varredura de compilação completa antes dos lotes. |
| 2 | `PLANO_LIB.md` §1/§2 | O "prelude de 3 linhas" contradiz o `template.cpp` real (6 macros + `main`). Com o template real, `flow/gomory_hu.cpp` colide com `#define all` e `geometry/convexhull.cpp` com `#define pii`. | Adotar `template.cpp` sem `main` como prelude; remover/renomear `all`/`pii` ou proibi-los. |
| 3 | `PLANO_LIB.md` §3 | Correção sugerida para `bitset_match.cpp` (`D = ((D<<1)|1)&mask[c]`) é de shift-and de matching; o erro real é em `lcs_bits`, que usa soma de bitsets. `bit_match` compila e funciona. | Não reescrever `bit_match`; corrigir `lcs_bits` com soma inteira/custom bitset. |
| 4 | `PLANO_LIB.md` §3 | `annealing.cpp`: `nx` fora de escopo é cascata de `M_PI`; trocar só `M_PI` por `acos(-1.0)` já compila. `ntt.cpp` também usa `rev` não declarado; nota "OBSOLETO" não faz `ntt`/`convexhull` compilarem. | Corrigir a descrição; decidir se arquivos obsoletos precisam compilar. |
| 5 | `PLANO_LIB.md` §5 | Nenhum dos 71 nomes existe com nome exato, mas 9 itens já estão cobertos: `kth_ancestor`, `periodos`, `rotacao_minima`, `lcp_queries`, `knapsack_binario`, `phi_mu_sieve`, `multipoint`, `pick_lattice`, `point_in_convex`. | Executar os "Verifique" antes de implementar o lote. |
| 6 | Repo | `docs/lib-index.md` não existe; 4 novos têm `#include` (`ds/ordered_set`, `general/gen_exemplo`, `general/hash_anti`, `general/interativo`), 2 têm `main`; nenhum arquivo tem `// Requer:`. | Padronizar; gerar índice só no fim. |
| 7 | Catálogo/código | `code/general/guloso_heap.cpp:27-34` reproduz o bug do catálogo L431 (push duplo) — devolve 10 para `[0,1,4,7]` em vez de 7. | Corrigir os dois (feito: soma das diferenças positivas). |

### 0.2 Erros do catálogo com maior chance de custar WA/TLE

- **L42** fecho transitivo geral não é `n²/64` (é `n³/64`, ou `nm/64` em DAG esparso).
- **L431** guloso de venda com heap empurra `p` duas vezes e superconta.
- **L739 / L2014** fórmula de k-colorações por OR-convolução conta coberturas com sobreposição (K₂,k=3 dá 12, não 6).
- **L1484** poda por máximo não vale para update de `gcd` em segtree (use `lcm`/divisibilidade).
- **L1594** inserção de **segmento** no Li Chao é `O(log²)`, não `O(log)`.
- **L987** regra do MEX na trie está invertida.
- **L946** variância do coupon collector está errada.
- **L1920** rank da matriz de Tutte é `2ν`, não `ν`.
- **L2077** distância ponto-reta com sinal incompatível.
- **L2104** LP do jogo na direção errada (minimiza em vez de maximizar).
- **L1425 / L1424** partição de árvore por xor/tamanho com condições insuficientes.
- **L884** ballot pode ficar negativo (`a < b`); fórmula de tocar reta exige `m ≤ n+c`.
- **L917** BEST sem exigir grafo euleriano.
- **L1131 / L1160 / L1137** off-by-ones em SAM/suffix automaton.
- **L1302** Ramsey usa cota inferior como condição suficiente.
- **L1262** fluxo com limites inferiores reporta só o augmento.

Contagem aproximada: **~250 achados**, sendo **~45 [ERRO] + ~35 [GRAVE]** e o resto imprecisões/duplicatas.

---

## 1. `PLANO_LIB.md` × repo real

Repo é git, branch `catalogo` (idêntica a `main`, sem commits próprios): 29 `.cpp` rastreados + 176 novos não rastreados (o plano diz "~178").

### 1.1 Contagens (esperado × real)

| Pasta | Plano | Real `.cpp` | Observação |
|---|---:|---:|---|
| algebra | 8 | 8 | ok |
| combinatorics | 15 | 15 | ok |
| dp | 21 | 21 | ok |
| ds | 41 | 41 | ok |
| flow | 16 | 16 | ok |
| general | 30 | 28 | 30 só contando `stress.sh` + `stress.bat`; falta `template.cpp` no bullet |
| geometry | 18 | 18 | bullet lista só 17 nomes (falta `convexhull`) |
| graph | 23 | 22 | 23 só contando `code/graph/dijkstra`, fonte sem extensão e duplicada |
| math | 16 | 16 | ok |
| string | 13 | 13 | ok |
| tree | 7 | 7 | ok |
| **Total** | **208** | **205** | 207 contando os dois scripts |

Nomes citados na seção 4: todos existem no disco.

### 1.2 Seção 3 incompleta (compilação real)

Falham 24 arquivos com o prelude de 3 linhas; a seção 3 cobre 14. Os 10 não citados:

- `code/dp/coins.cpp:2` — `MAXN` não declarado
- `code/dp/comb.cpp:1` — `MAXN`
- `code/dp/frog.cpp:5` — `MAXN`
- `code/dp/knapsack.cpp:6` — `FORI` (passa com o template real)
- `code/dp/lis.cpp:4` — `all` (passa com o template real)
- `code/ds/sparse_min.cpp:53` — `lookup`
- `code/graph/kruskal.cpp:4` — `par`
- `code/math/sieve.cpp:9` — `MAXN`
- `code/string/hash.cpp:6` — `MAXN`
- `code/string/trie.cpp:3` — `MAXS`

### 1.3 Problemas de prelude/composição

- `code/general/template.cpp:4-9` tem `FORI`, `FORJ`, `endl`, `pb`, `all`, `pii` e `main()` em 15-24; o plano fala em "3 linhas".
- Com o template real, `flow/gomory_hu.cpp:50` (método `all()`) colide com `#define all(a)`.
- `geometry/convexhull.cpp:1` (`typedef pair<int,int> pii`) colide com `#define pii pair<ll,ll>`.
- Convenção "colar abaixo do template" não é consistente com o teste prescrito.

### 1.4 Outros

- `code/boom` vazio, `code/graph/dijkstra` sem extensão, `code/primitives/` vazio; `code/bits/` e `code/games/` vazios (como o Lote 1 diz).
- Existem `stress.sh`, `stress.bat`, `template.cpp`; `docs/lib-index.md` não existe.
- Seção 5: 9 itens já cobertos por arquivos existentes (lista no resumo executivo). Os "Verifique" restantes não estão cobertos: `bellman_ford` só cita restrições no cabeçalho; `toposort` usa `queue` (não é lexicográfico); `lis` só devolve tamanho; `digitdp` não conta mod k; `treap_implicito` é por posição.

---

## 2. Catálogo — achados por seção

### 2.1 Constraints (L20-88)

- **L42 [ERRO]** fecho transitivo com bitset é `O(n³/64)` (Warshall) ou `O(nm/64)` em DAG esparso, não `n²/64`. Para n=3·10⁴–10⁵, só DAG esparso; senão n≲3000–5000.
- **L33 [ERRO]** `n, x ≤ 10¹⁸ → √x` é 10⁹, inviável. Use Miller–Rabin + Pollard; `O(√x)` só até 10¹².
- **L41 [ERRO]** `n ≤ 300 → n⁴` é 8,1·10⁹; n⁴ só n≲100. Para 300 use n³/bitset.
- **L38 [ERRO]** `n ≤ 60/64 → 2^(n/2)` é ~10⁹–4·10⁹; MITM só até n≈40. 60/64 serve para máscara uint64/base linear/branch-and-bound.
- **L39 [ERRO]** `n ≤ 30 → 2^n` = 10⁹ estados (GiB); DP 2^n só n≈20–22. Para 30, MITM/branch.
- **L45 [ERRO]** `n·m ≤ 10⁵` só garante `min(n,m) ≤ 316`; profile DP é exponencial na largura. Exigir `min ≤ 20`; matriz 2^n×2^n só n≤5–8.
- **L47 [IMPRECISO]** "O(n²) por operação" com 10⁶ operações dá 10¹². Diga "O(n²) total" e O(1)/O(log) por operação emitida.
- **L26 [IMPRECISO]** 12!≈4,8·10⁸ e 12!·12≈5,8·10⁹; `n!·n` só até n=10.
- **L60 [IMPRECISO]** `Σ valores ≤ 10⁵ ⇒ √(2·10⁵)` distintos exige valores não negativos.
- **L75 [IMPRECISO]** TL 0,5–1 s com n=10⁶ comporta `O(n log n)`; contradiz L32. "Só O(n)" para n≥10⁷/constante alta.
- **L49/68, L50/73, L58/74, L63/75 [IMPRECISO]** duplicatas quase idênticas; consolidar para não divergirem.
- **L68-87 [documentação]** bloco sem marcador de revisão.

### 2.2 Reformulações universais (L89-155)

- **L126 [ERRO]** Hall sem quantificador/balanceamento: `∀S⊆L, |N(S)|≥|S|` satura L; matching perfeito exige `|L|=|R|`.
- **L111/94 [ERRO]** contribuição de máximo em subarrays sem desempate: `[5,5]` conta 4 em vez de 3. Fixe "anterior estritamente maior, próximo maior ou igual" (ou vice-versa).
- **L121/152 [ERRO]** soma por partes sem termo de borda: `Σa_i b_i = A_n b_n + Σ A_i(b_i−b_{i+1})`; monotonicidade não é necessária.
- **L137 [ERRO]** `I_A·I_B = I_{A∩B}`, não `I_A+I_B`; `max = Σ[max≥k]` exige inteiro não negativo.
- **L97 [GRAVE]** binária em k exige predicado monótono; testar antes.
- **L116 [GRAVE]** ordem de laços em mochila: 0/1 vs ilimitada; "capacidade fora/itens dentro" conta sequências no caso ilimitado, não 0/1.
- **L149 [IMPRECISO]** bolas idênticas atravessam em 1D/colisão frontal; em 2D discos desviam.
- **L118 [IMPRECISO]** bound `√` para valores distintos exige hipótese `a_i ≥ 0` e soma limitada.
- **L131 [IMPRECISO]** DSU é `O((n+m)α(n))`, não `O(n)`.
- **L113 [IMPRECISO]** `Σa_i = Σ_t #{a_i≥t}` e cauda de E[X] exigem não negativos (inteiros).
- **L99 [IMPRECISO]** paridade de inversões não é invariante geral; muda sob transposição.
- **L104 [IMPRECISO]** mediana por ±1 testa a mediana superior, não a inferior/média dos centrais.

### 2.3 Cadeias de pulos, 1ª metade (L156-275)

- **L246 [ERRO]** pigeonhole de prefix xor: são `n+1` prefixos; condição é `n+1 > 2^k`, não `n > nº de bits`.
- **L241 [ERRO]** fórmula de aniversário invertida: `e^{−n²/(2N)}` é "sem colisão"; `1−…` é "com colisão". 64 bits não basta para n≈10⁹.
- **L243 [GRAVE]** `C(n,k) mod p^e` com sinal alternado só vale mod `p`; para `p^e` use blocos de tamanho `p^e`/Granville e separe `v_p(n!)`.
- **L233 [GRAVE]** Burnside com "espelhos" precisa do grupo diédrico, não só `Σφ(d)k^{n/d}/n`.
- **L194 [GRAVE]** descida em BIT só vale com `a_i ≥ 0` (prefixos monótonos).
- **L179 [GRAVE]** "resposta estabiliza em 2–3 cópias" é falso; transiente pode ser `O(|p|/|s|)`.
- **L216 [IMPRECISO]** `√(2n)` limita o número de partes em partes distintas, não a maior parte; o DP O(n√n) indexa pelo número de partes.
- **L188/203/217 [IMPRECISO]** Aliens: minimização pede `f` convexa; maximização pede côncava. Explicitar o sinal de λ.
- **L264 [IMPRECISO]** só a **menor** ocorrência em `s+s` dá a raiz primitiva; qualquer p dá `gcd(p,n)`.
- **L226 [IMPRECISO]** recorrência de conexos não é a de DAGs; DAG usa IE sobre fontes/sorvedouros.
- **L175 [IMPRECISO]** mediana por prefixos: comparar `P[r]−P[l−1]`; sinal estrito para mediana inferior.
- **L193/218, L210/238, L211/239 [duplicatas]** consolidar.

### 2.4 Cadeias de pulos, 2ª metade (L276-398)

- **L381 [ERRO]** `Σ C(d_v,2)=O(n²)` vale para K₂,₂-free, não triangle-free: `K_{n/2,n/2}` é livre de triângulos e custa Θ(n³). Separar as condições.
- **L311 [GRAVE]** `i(n−i+1)` conta subarrays contendo i; pares não ordenados = n−1, ordenados = 2(n−1), subconjuntos = 2^{n−1}.
- **L307/376 [GRAVE]** LGV exige compatibilidade/ordenação de fontes e sumidouros; senão o determinante é assinado e pode zerar.
- **L384 [IMPRECISO]** interseção de matroides é polinomial só para **2**; 3+ é NP-difícil.
- **L343 [IMPRECISO]** "lance que o oponente desfaz" exige definição precisa (posição ≤ original, jogo finito); não é apagar o lance.
- **L285 [IMPRECISO]** segtree persistente (consulta por versão) ≠ soma histórica (acumulado ao longo das versões).
- **L331 [IMPRECISO]** Karp resolve média por aresta; para `min Σa/Σb` com b arbitrário use binária + Bellman-Ford.
- **L335 [IMPRECISO]** Dial é bucket por distância; estados `(v,tempo)` são outra técnica.
- **L351 [IMPRECISO]** periodicidade eventual só com conjunto de subtração finito; brute 10⁴ é heurístico.
- **L355 [IMPRECISO]** merge de Boyer–Moore não é associativo; preserva maioria estrita, mas exige verificação final.
- **L322 [IMPRECISO]** `⌈k/2⌉` trilhas falha para k=0 (grafo euleriano precisa de 1): use `max(1,k/2)`.
- **L306 [IMPRECISO]** Gauss mod p exige p primo/pivôs invertíveis; para p composto, CRT/Bareiss.

### 2.5 Arrays e busca binária (L399-527)

- **L431 [ERRO]** heap de venda: `[0,1,4,7]` retorna 10, máximo 7. A versão de um push ainda falha em `[3,1,4,1,5,9]` (dá 13, certo 11). Para o modelo "uma ação em mãos por vez", some as diferenças positivas adjacentes. Bug replicado em `code/general/guloso_heap.cpp:27-34` (corrigido).
- **L521 [ERRO]** convexidade separada não garante `g(x)=min_y f(x,y)` convexa/unimodal; ternária aninhada exige convexidade conjunta (Hessiana PSD) ou unimodalidade provada.
- **L406 [ERRO]** XOR usa `pref ⊕ k`, não `pref − k`.
- **L505 [ERRO]** k-ésimo na tabela n×m: conte `Σ min(m, ⌊x/i⌋)`.
- **L455 [GRAVE]** MITM n≤40 vale para 2 escolhas; 3 escolhas ⇒ n≈24–26.
- **L506 [IMPRECISO]** frações reduzidas exigem Farey/Stern–Brocot; binária em real + "maior ≤ x" não recupera exato.
- **L510 [IMPRECISO]** DSU rollback sem compressão ⇒ `O((n+q)log²n)`.
- **L502 [IMPRECISO]** platôs degradam busca em rotacionado com duplicatas, não a busca do pico bitônico.
- **L425 [IMPRECISO]** intervalos fechados exigem `fim < início`; `≤` só para semiabertos.
- **L508 [IMPRECISO]** descida em BIT exige frequências não negativas.
- **L465 [IMPRECISO]** trocar iguais não muda inversões; paridade só para valores distintos.
- **L516 [IMPRECISO]** Aliens: sinal de `val(λ)+λK` depende da convenção; definir.

### 2.6 DP, 1ª parte (L528-660)

- **L578 [ERRO]** "impressora estranha" perde caso base/turno; use `dp[l][r]=dp[l][r−1]+1` e, para `s[k]=s[r]`, `dp[l][r]=min(dp[l][r], dp[l][k]+dp[k+1][r−1])`, `dp[i][i]=1`.
- **L576 [ERRO]** remover caixas não fecha em 2D; precisa de `dp[l][r][k]` (tipicamente O(n⁴)).
- **L645 [ERRO]** Aliens: com `g(λ)=min_k[f(k)+λk]`, a resposta é `g(λ)−λk`, não `+λk`.
- **L627 [ERRO]** enumerar dois tipos já é Θ(W²); com busca no terceiro é O(W² log W), não O(W log).
- **L646 [IMPRECISO]** máximo em matroide é côncavo; convexo é o custo mínimo.
- **L574 [IMPRECISO]** rerooting resolve `f` estruturada (momentos); centroide é opção, não necessidade.
- **L658 [IMPRECISO]** 2 ovos ⇒ Θ(√n), não O(log n).
- **L603 [IMPRECISO]** `E[j]=n/(n−j)+E[j+1]` coleta tipos distintos; k cópias exige estado de contagens.
- **L623 [IMPRECISO]** binary splitting com bitset é `O(S√S log S/64)`; pesos distintos são `√(2S)`.
- **L673 [IMPRECISO]** "a mais de k" ⇒ `dp[i−k−1]`; `dp[i−k]` é "≥ k".
- **L566 [IMPRECISO]** Hamiltonianos: `O(2^n n³)` inviável em n=25; use n≲20 ou método O(2^n n²).
- **L544 [IMPRECISO]** Knuth exige quadrângulo **e** monotonia de w; não misturar com D&C DP.

### 2.7 DP, 2ª parte (L661-759)

- **L739 [ERRO]** k-colorações: a soma por OR-convolução conta coberturas com sobreposição; K₂,k=3 dá 12, não 6. Use subset convolution ou IE sobre arestas (`Σ_{F⊆E}(−1)^{|F|}k^{c(F)}`).
- **L696 [ERRO]** DP de reduzir n com transição `−1` literal visita Θ(n) estados; só subtraia até o múltiplo (`n%2`, `n%3`) para ficar O(log²).
- **L672 [ERRO]** compressão `a_i`, `a_i±d` insuficiente; pontos ótimos podem ser `a_i±k·d` (O(n²)) ou slope trick.
- **L681 [GRAVE]** broken profile não fecha a propagação lateral: `b=reach[i−1]&livre[i]`, depois `b |= (b<<1)&livre[i]` até estabilizar.
- **L673 [GRAVE]** mesmo off-by-one `>k` vs `≥k`.
- **L717 [IMPRECISO]** digit DP não pode usar `carry` (LSB) e `tight` (MSB) juntos; use carry+borrow ou tight.
- **L723 [IMPRECISO]** `1||Σw_jU_j` é NP-hard fraco; Moore–Hodgson resolve só o não ponderado (remove maior p_j).
- **L724 [IMPRECISO]** intervalos com sobreposição ≤ k não formam matroide; use min-cost flow/DP.
- **L695 [IMPRECISO]** binária + guloso para maior segmento exige `a_i ≥ 0`; com negativos use DP.
- **L732 [IMPRECISO]** "sem k iguais seguidos" tem ordem k−1, não k.
- **L744 [IMPRECISO]** dominating set usa 3^w; vertex cover/independent set usam 2^w.
- **L671 [IMPRECISO]** cadeia de divisibilidade por crivo é O(V log V) (ou O(n√V)), não "n·log por valor".

### 2.8 Teoria dos números (L760-858)

- **L812 [GRAVE]** `2^ω` raízes de `x²≡a` exige n ímpar, `gcd(a,n)=1` e QR em cada potência; `2^k` e `p|a` têm contagem especial.
- **L811 [GRAVE]** exBSGS precisa checar `g|b`, inverter `a/g` e contar deslocamento; não é só dividir.
- **L816 [GRAVE]** LTE para `x^n+y^n` exige `p∤xy`; sem isso a fórmula falha (`x=y=p`).
- **L808 [GRAVE]** ordem multiplicativa só existe com `gcd(a,n)=1`; senão há pré-período.
- **L798 [IMPRECISO]** Min_25/Lucy exige `f(p)` polinomial em p na fase 1; `f(p^e)` calculável é fase 2.
- **L809 [IMPRECISO]** raiz primitiva: `n∈{1,2,4}∪{p^k,2p^k}` com **p primo ímpar** (n=8 não tem).
- **L810 [IMPRECISO]** critério `a^{(p−1)/gcd}≡1` exige `a≠0`; `x^k≡0` tem 1 raiz.
- **L813 [IMPRECISO]** reciprocidade quadrática nessa forma exige a ímpar; separe `(2/p)`.
- **L794 [IMPRECISO]** divisão de blocos: `A·B ≤ n < (A+1)(B+1)`, não "≈ n".
- **L848 [IMPRECISO]** recorrência de ordem k tem período até `m^k`, não `m²` (m² é ordem 2).
- **L772 [IMPRECISO]** `x mod y = x−y` só para `x/2 < y ≤ x`; se `y>x`, é `x`.
- **L775/777/785 [duplicatas]** consolidar a receita de fatoração.

### 2.9 Combinatória (L859-966)

- **L884 [GRAVE]** caminhos tocando `y=x+c`: exige `m ≤ n+c`; senão todos tocam e a fórmula superconta. Ballot fraco exige `a ≥ b` (senão negativo).
- **L946 [ERRO]** variância do coupon collector não é `Σ(1−p_i)/p_i²` (soma marginal); use `E[T]`, `E[T²]` por IE.
- **L912 [ERRO]** classes de estruturas rotuladas: `#rotuladas·a/n!`, não `/a`; use Burnside.
- **L917 [GRAVE]** BEST exige grafo euleriano e produto só em vértices com grau > 0.
- **L894 [IMPRECISO]** `C(n−(k−1)(d−1),k)` é distância ≥ d; "folga" não definida.
- **L937 [IMPRECISO]** `Σ max` com ordenação crescente usa `2^{i−1}`; para `min`, inverta a ordem ou use `2^{n−i}`.
- **L926 [IMPRECISO]** `Σ i^k r^i = r^nP(n)−P(0)` falha em r=1 (Faulhaber, grau k+1).
- **L941 [IMPRECISO]** Erdős–Szekeres: `LIS·LDS ≥ n²+1`, não `≥ n`.
- **L934 [IMPRECISO]** LGV não exige planaridade; a hipótese é só a identidade contribuir.
- **L896 [IMPRECISO]** "partes > √n são < √n" → "o número de partes > √n é < √n".

### 2.10 Bits e strings (L967-1182)

- **L987 [ERRO]** MEX na trie: desça pelo ramo xor 0 **se não estiver cheio**; se cheio, bit 1 e outro ramo.
- **L1131 [GRAVE]** SAM/link: propague `min(best[v], len[link[v]])`, não `len[v]`, e faça o mínimo entre strings após propagar cada uma.
- **L1156 [GRAVE]** uma convolução complexa de raízes não recupera matching para alfabeto > 2; use σ convoluções ou `(a−b)²` com valores aleatórios.
- **L1160 [GRAVE]** `cnt[i] = 1 + Σ_c cnt[next[i][c]+1]`, com `cnt[n]=1`; falta o +1.
- **L1137 [GRAVE]** idem: `dp[i] = 1 + min_c dp[next[i][c]+1]`.
- **L999 [GRAVE]** custo para forma canônica não depende só de `n−rank`; depende da posição/redundância dos vetores.
- **L1020 [GRAVE]** pai no Fenwick é `i+lowbit(i)`; `i−lowbit(i)` é o bloco anterior da consulta.
- **L1111 [IMPRECISO]** `p0=n−π[n−1]`; se `p0∤n`, a raiz é a string inteira.
- **L1139 [IMPRECISO]** 2ª diferença conta palíndromos que **cobrem** posição; para terminar/começar use range add (1ª diferença).
- **L1012 [IMPRECISO]** contagem de subconjuntos por popcount esquece o próprio `x=n`; adicione +1 se `popcount(n)=k`.
- **L1089 [IMPRECISO]** "2–3 cópias" falso; use `⌈|p|/|s|⌉+1` para matching.
- **L1104 [IMPRECISO]** autômato KMP precisa base `aut[0][c] = (p[0]==c ? 1 : 0)`.
- **L1004 [IMPRECISO]** após reduzir mod `2^(k+1)`, a soma é `< 2^(k+2)`; segundo intervalo termina em `2^(k+2)`.

### 2.11 Grafos (L1183-1351)

- **L1302 [ERRO]** Ramsey: `2^{k/2}` é cota inferior de R(k,k), não condição suficiente (C5). Garantia: `n ≥ C(2k,k)`.
- **L1222 [ERRO]** SPFA tem pior caso `Θ(nm)`, não exponencial.
- **L1235 [ERRO]** contagem por degenerescência vale para triângulos/cliques de tamanho fixo; todas as cliques é #P-difícil.
- **L1241 [ERRO]** Brooks exige grafo conexo (e Δ≥3); componente isolada quebra.
- **L1262 [GRAVE]** fluxo com limites inferiores: resposta = `f(t→s) + augmento`, não só o augmento.
- **L1278 [GRAVE]** adicionar cláusulas vai SAT→UNSAT; "menor t satisfatível" é 0. Busque o maior t satisfatível/menor insatisfatível.
- **L1285 [GRAVE]** centroide: resto é `n−1−Σsz[child]`; pares desconectados `C(n−1,2)−ΣC(sz_i,2)`.
- **L1268 [IMPRECISO]** submodular em 3+ variáveis não é sempre representável por corte; exija grafos-representável/decomponível.
- **L1309 [GRAVE]** aresta em alguma MST: `w(e)=máximo do caminho`; em todas: ponte no subgrafo `≤ w(e)`. Custo forçado só para `e∉T`.
- **L1308 [IMPRECISO]** "MST sem aresta f" ≠ segundo MST global; use replacement edge.
- **L1263 [IMPRECISO]** splitting de vértices não pode dividir s,t com capacidade 1; divida só `v∉{s,t}` (ou ∞).
- **L1231 [IMPRECISO]** identidade `xor caminho = xor árvore ⊕ span dos ciclos` vale para passeios, não caminhos simples.
- **L1290 [IMPRECISO]** de Bruijn é cíclica; string linear com todos os n-gramas tem `k^n+n−1`.
- **L1275 [IMPRECISO]** `x→¬x` força x falso; `¬x→x` força verdadeiro; checar os dois (ambos ⇒ insatisfatível).

### 2.12 Árvores (L1352-1475)

- **L1425 [ERRO]** partição em 3 xors iguais: para T≠0 os dois nós com xor T precisam ser incomparáveis, ou um ancestral com xor 0 e descendente T; T=0 pede dois não-raiz com xor 0.
- **L1424 [ERRO]** `sz≡0 mod k` é necessário, não suficiente (estrela K1,5, n=6, k=2); cortes = nº de não-raiz com sz≡0 = n/k−1.
- **L1453 [ERRO]** ciclo por v: `d(u)+d(w)+1` é passeio fechado; ciclo fundamental = `d(u)+d(w)+1−2d(lca)`. Restringir a lca=v.
- **L1389 [GRAVE]** raio `⌈diâmetro/2⌉` e crescimento ≤1 só sem pesos; ponderado pode crescer w.
- **L1392 [ERRO]** DSU-on-tree: adicione **todos** os vértices das subárvores leves, não só folhas.
- **L1403 [GRAVE]** DP de separar especiais: se v é especial, é obrigatório cortar acima de v; definir dp[v] como custo de separar v do pai (`w(pai,v)` ou mínimo no caminho).
- **L1373 [IMPRECISO]** Euler tour de arestas tem 2n−2; de vértices 2n−1; eventos tin/tout 2n. Não misturar.
- **L1379 [IMPRECISO]** `f(u)+f(v)−2f(lca)+a[lca]` exige grupo abeliano.
- **L1398 [IMPRECISO]** distância via LCA da centroid tree é exata; remover a ressalva "use LCA normal".
- **L1360/1388 [IMPRECISO]** two-sweep exige DFS/Dijkstra com pesos; BFS só sem pesos; pesos negativos ⇒ DP.
- **L1390 [IMPRECISO]** `dp[v][d]` até k é O(nk) tempo/memória; O(n) só com long-path/k constante.
- **L1385 [IMPRECISO]** LCT mantém MST incremental (inserções); MST totalmente dinâmico exige D&C/ETT.

### 2.13 Estruturas de dados (L1476-1637)

- **L1484 [ERRO]** poda por máximo só vale para `mod`/`sqrt`; para `gcd` guarde `lcm`/divisibilidade; senão O(nq).
- **L1594 [ERRO]** Li Chao: reta `O(log C)`; **segmento** `O(log² C)`; query `O(log C)`.
- **L1567 [ERRO]** Mo para inversões: `O(√n)` por movimento × `O(n√n)` movimentos = `O(n²)`; use Mo+BIT `O(n√n log n)` ou sqrt estático.
- **L1601 [ERRO]** alcançabilidade: `n²/64` é o total de palavras, não "por vértice"; `n/64` por vértice, tempo `O(mn/64)`.
- **L1566 [GRAVE]** binária paralela é offline; não responde k-ésimo online.
- **L1587 [GRAVE]** ODT sob assigns aleatórios: custo esperado `O((n+q)log n)`, não "O(log n) intervalos"; pior caso O(nq).
- **L1571 [GRAVE]** prefix xor + trie persistente resolve xor de **subarray**; xor de **par** de elementos pede trie sobre valores/D&C.
- **L1569 [GRAVE]** MEX com updates: contagem não indica presença; use posições por valor/estrutura 2D.
- **L1632 [IMPRECISO]** Mo em árvore: toggle em toda ocorrência da Euler tour (ímpar = ativo), não só na segunda.
- **L1597 [IMPRECISO]** Bentley–Saxe: inserção amortizada O(log n); query = O(log n × Q_estática); O(log²) só se Q=O(log).
- **L1565 [IMPRECISO]** range mode custa `O(n√n log n)` com checagem por binária; O(1) exige tabela O(n√n).
- **L1583 [IMPRECISO]** DSU rollback faz conectividade/bipartição, não MST ponderado com remoções (LCT/dynamic MST).
- **L1543 [IMPRECISO]** KTT: fixar notação (`m_i t+c_i`) e condição de amortização.
- **L1615 [IMPRECISO]** LIS ponderado usa BIT de **máximo de prefixo**, não mínimo de sufixo.

### 2.14 Construtivos e jogos (L1638-1791)

- **L1780 [ERRO]** Kayles é tame (quociente de misère ordem 40/período 12); Dawson's Kayles é wild.
- **L1691 [GRAVE]** Ford–Johnson não é ótimo em geral (n=12: 30 vs 29); ótimo só para n pequeno (e 21–22); para n≥189 há melhores.
- **L1692 [GRAVE]** 3 queries `a+b,b+c,a+c` determinam soma/xor, não AND (bit com um único 1 é indistinguível).
- **L1693 [GRAVE]** comparar mods nos dois sentidos: o **maior** resultado é `min(p_i,p_j)`; o menor é só o resto.
- **L1765 [GRAVE]** Cram: os casos ímpar×ímpar não são cobertos pelo espelhamento central; resolver por Grundy/brute (3×3, 5×5, 1×5 são P; 3×5, 1×3 são N).
- **L1752 [GRAVE]** periodicidade de Grundy só é garantida para conjunto de subtração finito; quadrados é aberto.
- **L1736 [GRAVE]** jogo de escolher itens: ordenar `a_i+b_i` em ordem **decrescente**.
- **L1655/1747 [documentação]** "revisado" enganoso.
- **L1766 [IMPRECISO]** Chomp 1×1 é exceção (primeiro perde); m·n≥2 primeiro ganha.
- **L1690 [IMPRECISO]** segundo maior com queries de max: localize a posição p do máximo e compare os dois lados.
- **L1695 [IMPRECISO]** centroid queries: total `⌈log₂n⌉`, uma por nível; não por centroide.
- **L1778 [IMPRECISO]** jogos estocásticos com escolhas têm max/min; Bellman não é linear — value iteration/LP.
- **L1770 [IMPRECISO]** jogo de Euclides: paridade depende de terminar em quociente ≥2 ou terminal b=0.

### 2.15 Geometria e aleatorização (L1792-1959)

- **L1920 [ERRO]** rank da matriz de Tutte é `2ν(G)`; matching perfeito ⇔ det≠0 (n par).
- **L1875 [ERRO]** rotação 45° converte L1↔L∞; min-máximo L∞ usa caixa alinhada, não "caixa rotacionada".
- **L1810 [GRAVE]** interseção de segmentos: use `o1·o2≤0` e `o3·o4≤0`, `onSegment` para zeros e sobreposição se colineares; sinais opostos não pegam T-junction.
- **L1807 [ERRO]** projeção devolve parâmetro `t`; `foot=a+t(b−a)`, reflexão `2·foot−p`.
- **L1894 [ERRO]** Pareto ≠ camadas convexas: (0,0) pode estar no hull e ser dominado.
- **L1827 [GRAVE]** incentro usa lados (raízes), não é inteiro; circuncentro é interseção de **mediatrizes**, não bissetoras.
- **L1903 [ERRO]** XOR não identifica multiconjunto ({a,a} = ∅); use soma/hash.
- **L1914 [GRAVE]** hash duplo mod 1e9+7: bound por par ~`(n/p)²`; para n² comparações colide. Use dois primos grandes/2⁶¹−1 com duas bases.
- **L1939-40 [GRAVE]** xor de corte é zero com alta probabilidade, não equivalência determinística.
- **L1925 [ERRO]** sorteio sem reposição dá `(n−2)/(4(n−1)) < 1/4`; use reposição ou valor exato.
- **L1829 [IMPRECISO]** MST euclidiana ≠ Manhattan (8 octantes).
- **L1806/1870 [IMPRECISO]** cross com diferenças 2·10⁹ chega a 8·10⁸? (na verdade ~8·10¹⁸); use __int128 quando diferenças podem ser 2·10⁹.
- **L1906 [IMPRECISO]** color coding exige `Θ(e^k)` repetições.
- **L1944 [IMPRECISO]** 7/8 é MAX-3SAT; para cláusula k é `1−2^{−k}` (MAX-2SAT 3/4).

### 2.16 Álgebra, polinômios e FFT (L1960-2027)

- **L2014 [ERRO]** k-colorações erradas (ver L739): OR-convolução ≠ coloração própria.
- **L1998 [GRAVE]** FFT não vale para matriz circulante em (min,+)/(max,×); é O(n²) ou estrutura especial.
- **L2010 [IMPRECISO]** `Disc(f) = (−1)^{n(n−1)/2}·a_n^{−1}·Res(f,f′)`; falta sinal/fator líder.
- **L1997 [IMPRECISO]** `[[A,I],[0,I]]^k` dá `Σ_{i<k}A^i`; para 0..k use `M^{k+1}`.
- **L1975 [IMPRECISO]** distinguir subconjunto de cnt cópias, mochila ilimitada `(1−x^w)^{−1}` e limitada.
- **L1972 [IMPRECISO]** exp exige `A(0)=0`.
- **L1994 [IMPRECISO]** Bostan–Mori exige `Q(0)≠0`; fatorar `x^d` antes.
- **L1979 [IMPRECISO]** inversa composicional O(n log n) não sai de ln/exp por coeficiente (total O(n² log n)); use Newton+composição rápida.
- **L2012 [IMPRECISO]** potência ponto a ponto conta k-uplas ordenadas com repetição.
- **L2026 [IMPRECISO]** Wiedemann escalar dá o mínimo da projeção; det/posto exigem pré-condicionamento/block Wiedemann.
- **L2022 [duplicata]** multipoint/interpolação repetidos.

### 2.17 Matemática olímpica e LP/matroides (L2028-2144)

- **L2077 [ERRO]** para `ax+by=c`, distância é `|ax₀+by₀−c|/√(a²+b²)`; `+c` corresponde a `ax+by+c=0`.
- **L2104 [GRAVE]** LP do jogo: com A = payoff do jogador-linha, é `max v s.t. Σp_iA_ij ≥ v`; a formulação `min` dada não é maximin.
- **L2033 [ERRO]** inserção em caminho hamiltoniano de torneio não é monótona; use varredura linear O(n) por inserção (O(n²)).
- **L2089 [ERRO]** limiar de Frobenius é `max_r dist[r]` (menor representável por resíduo), não o maior resíduo; com gcd>1 só múltiplos.
- **L2117 [GRAVE]** minimização submodular irrestrita é polinomial para n arbitrário; "só pequeno" é limitação prática.
- **L2073 [IMPRECISO]** Helly com 1 par vale para intervalos 1D, não segmentos no plano.
- **L2045 [IMPRECISO]** para f convexa, `Σf(a_i−b_σ(i))` é mínimo com ordens iguais e máximo com opostas (direção invertida).
- **L2065 [IMPRECISO]** corte planar: ciclo mínimo no dual separando faces; mesma face exige dividir a face.
- **L2133 [IMPRECISO]** guloso de mochila é 1/2-aproximação; "quase ótimo" não garante poucas trocas.
- **L2115 [IMPRECISO]** Ishikawa exige `w_ij ≥ 0` e rótulos ordenados.
- **L2080 [IMPRECISO]** lcm(1..43) estoura signed 64, cabe em unsigned.
- **L2078 [IMPRECISO]** em métrica geral, ponto mais distante não é necessariamente extremo de diâmetro; ecc ≤ 2·max(d(a),d(b)).
- **L2069 [IMPRECISO]** Hall/perfect matching exige `|L|=|R|` ou Hall nos dois lados.
- **L2083 [IMPRECISO]** √ inteira: ajuste nos dois sentidos e multiplique em __int128.

### 2.18 Amostras ICPC e "quando nada funciona" (L2145-2252)

- **L2189 [ERRO]** paridade i+j não bipartição para torres/rainhas; torres = matching linhas×colunas; rainhas até com bloqueios é NP-difícil.
- **L2180 [GRAVE]** pares (i,j) no intervalo com a_i<a_j não se resolvem com pilha monotônica/soma histórica; use Mo+BIT/2D/wavelet.
- **L2199 [GRAVE]** ciclos ≤6 em planar: grau médio <6 não limita ΣC(deg,2) (estrela); use 5-degenerescência/orientação.
- **L2150 [IMPRECISO]** minimizar carga máxima usa max-flow com capacidades; maximizar o mínimo exige lower bounds/demandas.
- **L2232 [IMPRECISO]** O(n²) em vez de O(n log n) é TLE, não WA.
- **L2244 [IMPRECISO]** 1000 testes aleatórios não validam guloso; enumere instâncias pequenas e exija argumento de troca.
- **L2208 [IMPRECISO]** ODT amortizado só para range assign; range add/consultas podem ser O(nq).
- **L2242 [IMPRECISO]** ASan/UBSan/_GLIBCXX_DEBUG não detectam variável não inicializada; use MSan/Valgrind.
- **L2186 [IMPRECISO]** segtree de grafo precisa de duas árvores (in/out) ou arestas dirigidas; uma árvore 0 bidirecional colapsa distâncias.
- **L2184 [IMPRECISO]** união de retângulos: cobertura + comprimento coberto (ou min+count_min), não só contagem+mínimo.
- **L2180-81 [duplicata]** e **L2176/2177**, **L2206/2207**.
- **L2147/2230 [documentação]** dois marcadores "revisado"; reabrir revisão.

---

## 3. `mapa-rapido.md`

- **L68 [ERRO]** subconjuntos com soma ≡ r mod m: gerador é `∏(1+x^{a_i}) mod (x^m−1)`, não `(1+x)^n` (só vale se todos `a_i≡1`). Catálogo L2018 está correto; L927 não.
- **L56 [GRAVE]** `a^b^c… mod m` com `gcd(a,m)≠1` exige `a^{e mod φ(m)+φ(m)}` e comparar expoentes truncados.
- **L55 [GRAVE]** `a^x≡b` com `gcd(a,m)≠1` exige exBSGS.
- **L95 [GRAVE]** caminhos disjuntos em vértices × arestas: splitting só para vértices; arestas = corte de arestas.
- **L106 [GRAVE]** diferenças em caminho: vértice usa `−x` em lca e pai(lca); aresta usa `−2x` em lca e nada no pai.
- **L67 [GRAVE]** tempo esperado até padrão: some sobre todas as bordas **incluindo o padrão inteiro**; senão HH dá 2 em vez de 6.
- **L100 [GRAVE]** corte mínimo planar é ciclo mínimo no dual separando faces; mesma face exige dividir a face.
- **L90 [IMPRECISO]** restrições `x_j−x_i≤c` têm pesos possivelmente negativos; use Bellman-Ford/SPFA com super-fonte.
- **L107 [IMPRECISO]** `sz(n−sz)` conta caminhos pela aresta (soma de distâncias), não qualquer função de par.
- **L64 [IMPRECISO]** LGV exige compatibilidade das fontes/destinos.
- **L104 [IMPRECISO]** prefixos da raiz só para operação invertível (soma/xor); max/min/gcd exigem HLD/lifting.
- **L202 [FALTA]** sem Blossom (matching geral), árvore dominadora, LCT/ETT.
- **L202/216 [FALTA]** sem corte global (Stoer–Wagner/Karger/Gomory–Hu), fluxo com lower bounds/circulação, interseção de matroides.
- **L98/47 [FALTA]** sem postman chinês e plug DP/treewidth.
- **L21/24 [FALTA]** sem job sequencing com prazos (DSU/heap) e Huffman/Hu–Tucker.
- **Limites escondidos**: todos os números conferem (divisores, π, gap, 20!<2⁶³<21!, lcm(1..43), Fibonacci, 2⁵³, 998244353). Ressalvas: NTT `≤2²³` é o tamanho da transformada (para convoluir n, precisa `2n−1≤2²³ ⇒ n≤2²²`); "4·10¹⁰ pares" é `n²` ordenado (não ordenado ≈2·10¹⁰).
- **L3 [FALTA]** cita `mapa-rapido-longo.md`, que não existe no diretório.

---

## 4. Observações transversais

1. **Selo "revisado" não confiável.** Há 23 marcadores, todos "revisado", nenhum "não revisado". Erros [ERRO]/[GRAVE] aparecem em blocos marcados como revisados em quase todas as seções.
2. **Duplicatas entre seções** são numerosas (matrix-tree L306/375, potências L316/374, custo convexo L330/386, rollback L291/295/354/396, interpolação L314/373, k-colorações L739/2014, etc.). Algumas duplicam o mesmo erro; consolidar reduz risco.
3. **Hipóteses ausentes** são o padrão da maioria dos achados: não negatividade, `gcd=1`, primalidade do módulo, grafo conexo/euleriano, pesos unitários, operações invertíveis, `p∤xy`.
4. **Complexidades otimistas** aparecem nas constraints e em várias seções (`2^n`, `n⁴`, `n²/64`, Li Chao, Mo, range mode).
5. **Arquivos do repo com bug confirmado**: `code/general/guloso_heap.cpp` (push duplo). `code/general/annealing.cpp` compila trocando só `M_PI`.

---

## 5. Próximos passos sugeridos

1. **Corrigir `PLANO_LIB.md` e o prelude** antes de qualquer lote: completar a seção 3 (10 arquivos), adotar `template.cpp` sem `main`, resolver colisões `all`/`pii`, explicar o que é "obsoleto".
2. **Varredura de compilação completa** (`-std=c++17 -O2 -Wall -fsyntax-only`), registrando o status real; não confiar na seção 3.
3. **Corrigir primeiro os [ERRO]/[GRAVE]** deste relatório, seção por seção, começando pelas constraints e pelas fórmulas de DP/álgebra/geometria.
4. **Revisar os "Verifique"** da seção 5 e marcar os 9 já cobertos; só então implementar os lotes 1–9.
5. **Trocar o rótulo "revisado"** por um registro de revisão real (data/autor/escopo) e remover o aviso obsoleto da linha 3 ou cumpri-lo.
6. **Só no fim**: gerar `docs/lib-index.md`, `README.md` e regenerar `catalogo.pdf` (`python docs/build_pdf.py`).
