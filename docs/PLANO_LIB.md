# Plano de implementação da lib (para o DeepSeek executar)

Branch: `catalogo` (local, ainda sem commit). Fonte das ideias: `docs/catalogo-completo.md`; cada seção do catálogo diz quais técnicas existem.
O pente fino de 2026-11-11 já foi feito: catálogo corrigido, tudo compilado, testes pontuais rodados, `docs/lib-index.md` gerado e `docs/catalogo.pdf` regerado.

## 1. Convenções (obrigatórias)

- **Arquivos.** Um arquivo por técnica, em `code/<pasta>/<nome_curto>.cpp` (snake_case, sem acento).
- **Trecho, não programa.** O arquivo é colado abaixo de `code/general/template.cpp`, então assume as 3 linhas base (`#include <bits/stdc++.h>`, `using namespace std;`, `typedef long long ll;`) e também as macros `FORI`, `FORJ`, `endl`, `pb`, `all`, `pii`. Não tem `#include` nem `main`. Constantes (MOD, MAXN) ficam declaradas no próprio arquivo. Não defina identificadores que colidam com as macros (ex.: método `all()`, `typedef ... pii`); se precisar, renomeie.
- **Autocontido.** Pode repetir helpers pequenos, como `power` mod. Se depender de outro arquivo da lib, diga no cabeçalho: `// Requer: code/x/y.cpp (cole antes)`.
- **Exceções de programa completo.** `general/template.cpp`, `general/gen_exemplo.cpp`, `general/interativo.cpp`, `general/rng.cpp`, `general/buscaternaria.cpp` e `dp/frog3_cht.cpp` são standalone (têm `#include`; alguns têm `main`); `general/sosdp.cpp` também traz o próprio `#include`; `ds/ordered_set.cpp` e `general/hash_anti.cpp` precisam de `#include` de `pb_ds` (fora do `bits/stdc++.h`). Os demais arquivos seguem o formato de trecho.
- **Estilo.** Notebook de ICPC, no estilo KACTL: curto, legível, sem abstração exagerada.
- **Comentários.** Em português sem acentos, porque a lib é impressa. O cabeçalho é obrigatório:
  ```
  // Nome da tecnica
  //
  // O que faz: ...
  // Quando usar: gatilhos (cite a secao do catalogo, ex.: "Catalogo > Arvores")
  // Complexidade: ...
  // Uso: API, indexacao (0/1-based), exemplo de chamada
  // Cuidados: overflow, bordas, armadilhas
  ```
  No corpo, comente as linhas não óbvias. Pode ser generoso: o dono vai tirando com o tempo.
- **Arquivos existentes.** Não modifique arquivos que já existem, exceto os listados na seção 3.

## 2. Como testar cada arquivo

1. **Compilar.** Gere um `prelude.h` a partir de `code/general/template.cpp` removendo `solve()` e `main()`, mas mantendo as 3 linhas base e as macros (`FORI`, `FORJ`, `endl`, `pb`, `all`, `pii`). Rode:
   `g++ -std=c++17 -O2 -Wall -fsyntax-only -include prelude.h code/<pasta>/<arquivo>.cpp`
   Para os 9 arquivos de combinatória que declaram `// Requer:`, acrescente `-include code/combinatorics/binom_mod.cpp` antes do arquivo.
   Usar só as 3 linhas base gera falso negativo em `dp/lis.cpp` e `dp/knapsack.cpp` (faltam `all`/`FORI`); usar o template inteiro colide com `flow/gomory_hu.cpp` (método `all`) e `geometry/convexhull.cpp` (`typedef pii`).
2. **Stress test.** Para algoritmo ou estrutura não trivial, compare com um brute force usando `code/general/stress.sh` em algumas centenas de casos aleatórios pequenos. Testes e brutes ficam FORA do repo.
3. **Status.** Anote o status de cada arquivo (testado com brute / só compila) numa linha de `docs/lib-index.md`:
   `- code/<pasta>/<arquivo>.cpp | Nome | o que faz em uma frase | Seção do catálogo | testado/compilado`

## 3. Correções aplicadas em 2026-11-11

Todos os arquivos abaixo já foram corrigidos e compilam com o prelude derivado do template. Os 9 de combinatória compilam com `binom_mod.cpp` incluído antes.

- `code/general/annealing.cpp`: `M_PI` → `acos(-1.0)`.
- `code/string/bitset_match.cpp`: `lcs_bits` reescrito com palavras de 64 bits e soma com carry (Hyyrö); `bit_match` intacto.
- `code/combinatorics/*`: os 9 dependentes têm `// Requer: code/combinatorics/binom_mod.cpp (cole antes)`.
- `code/math/ntt.cpp`: declarados `roots`, `rev` e `power`.
- `code/geometry/convexhull.cpp`: `Point`/`pii` → `using P = pair<int,int>`.
- `code/math/mod.cpp`: `const ll MOD = 1000000007;`.
- `code/dp/coins.cpp`, `comb.cpp`, `frog.cpp`: constantes locais e retorno do valor correto; `coins` usa `INF = target + 1`; `frog` usa `INF = LLONG_MAX / 4`.
- `code/dp/knapsack.cpp`: assinatura `knapsack(peso, valor, w)` (sem ler entrada) e sem `FORI`.
- `code/dp/lis.cpp`: sem macros `all`/`pb`, compila até com as 3 linhas base.
- `code/math/sieve.cpp`, `code/string/hash.cpp`, `code/string/trie.cpp`: `MAXN`/`MAXS`/`sigma` locais.
- `code/ds/sparse_min.cpp`: reescrito como `struct SparseMin` (sem `lookup`, `main` ou macros).
- `code/graph/kruskal.cpp`: reescrito com DSU local e `KEdge`.
- `code/flow/gomory_hu.cpp`: método `all()` → `mincuts()`.
- `code/general/guloso_heap.cpp`: `stocks` agora soma as diferenças positivas adjacentes (a variante com heap superconta).
- `code/ds/seg_t.cpp`: estava vazio; preenchido com segtree iterativa (ponto + soma em intervalo, `struct IterSeg`).
- `code/ds/ps2d.cpp`: título e cabeçalho corrigidos (o arquivo dizia "dijkstra").
- `code/string/trie.cpp`: `init()` automático na primeira chamada (antes, sem `init()`, `trie[0]` ficava zerado e toda palavra caía no nó 0).
- `code/dp/digitdp.cpp`: tabela `dp[2][19][171]` (a soma máxima de dígitos de um `ll` é 170; antes 170 estourava por um).
- `code/dp/subsetsum.cpp`: ordena `w` no início; validado contra brute force em 20 mil casos.
- `code/graph/dijkstra` → `code/graph/dijkstra.cpp`, com cabeçalho completo.
- Todos os 206 `.cpp` têm cabeçalho (`O que faz`, `Quando usar` com `Catalogo > ...`, `Complexidade`, `Uso`, `Cuidados`); `docs/lib-index.md` foi gerado a partir deles.
- `docs/catalogo-completo.md`: substituído pela versão corrigida (2252 linhas, 23 seções).

Status (2026-11-11): varredura final de compilação nos 206 `.cpp` com os dois preludes (completo e mínimo) e `binom_mod.cpp` nos 9 de combinatória — **0 falhas**. Testes com brute force/casos conhecidos confirmados: `string/bitset_match.cpp` (LCS bit-parallel, 5 mil casos), `ds/sparse_min.cpp`, `dp/subsetsum.cpp` (20 mil casos), `dp/digitdp.cpp` (soma de dígitos até 5000), `string/trie.cpp` (incluindo `init` automático), `ds/seg_t.cpp`, `ds/ps2d.cpp` (3 mil casos), `dp/lis.cpp`, `dp/knapsack.cpp`, `dp/coins.cpp`, `dp/frog.cpp`, `general/guloso_heap.cpp` (exemplos). Os demais apenas compilam.

## 4. O que já existe (não refazer)

- **algebra (8):** berlekamp_massey, bostan_mori, conv_mod, fft, lagrange, ntt, poly, power_sum
- **combinatorics (15):** binom_general, binom_mod, burnside, catalan_family, counting_misc, grid_paths, inclusion_exclusion, lgv, lucas, matrix_tree, partitions, perm_counts, prob_expect, stirling_bell, tree_counting
- **dp (21):** bitset_subset_sum, broken_profile, dc_opt, edit_distance, interval_dp, knapsack_bounded, knuth, lcs_bitset, slope_trick, tree_knapsack, tsp_bitmask, e os antigos coins, comb, digitdp, frog, frog3_cht, knapsack, lcs, lis, sosdp, subsetsum
- **ds (41):**
  - BITs: bit, bit2d, bit_rr
  - Segtrees: seg_iter, seg_lazy, seg_nodes, seg_descent, seg_beats, seg_persist, seg_dyn, seg2d
  - Outras de intervalo: sparse_table, disjoint_sparse, merge_sort_tree, wavelet, sqrt_decomp, distinct_range
  - DSU: dsu_rollback, dsu_paridade, dsu_potencial, dsu_proximo_livre, conectividade_dinamica
  - Árvores e heaps: treap_implicito, ordered_set, odt, heap_lazy, heap_mergeavel, kdtree
  - CHT e otimização: lichao, cht_monotono, cht_dinamico, fila_monotonica, aliens
  - Offline e busca: cdq, busca_binaria, busca_binaria_paralela, busca_ternaria
  - Antigos: segtree, seg_t, sparse_min, ps2d
- **flow (16):** blossom, dag_path_cover, dinic, flow_lower_bounds, gale_shapley, gomory_hu, hopcroft_karp, hungarian, konig, kuhn, matroid_intersection, mcmf, mcmf_spfa, project_selection, push_relabel, simplex
- **general (28 .cpp + stress.sh/.bat = 30 entradas):** annealing, compressao, debruijn, debug, diff2d, fastio, gale_ryser, gen_exemplo, grau_seq, gray_code, guloso_heap, hash_anti, int128_io, interativo, intervalos, inversoes, maioria, mediana_janela, meet_middle, perm_ciclos, pilha_monotonica, stress.sh/.bat, template.cpp, torneio_landau, two_pointers, e os antigos
- **geometry (18):** angle_sort, calipers, circles, closest_pair, convex_extreme, convex_layers, convexhull, geometry3d, half_plane, hull_andrew, min_circle, minkowski, point_dbl, point_int, polygon, polygon_cut, rect_union, seg_any_inter
- **graph (22 .cpp; 23 se contar `code/graph/dijkstra` sem extensão):** bcc_block_cut, bellman_ford, bfs01, bipartite, bridges_2ecc, ciclos, dijkstra_estados, dijkstra_variantes, euler, floyd, grafo_funcional, johnson, kth_walks, range_graph, scc_kosaraju, scc_tarjan, spfa, two_sat, e os antigos
- **math (16):** bsgs, crt, divisores, exgcd, floor_sum, inv_lote, miller_rabin, mint, pollard_rho, primitive_root, sieve_linear, sieve_seg, tonelli, e os antigos
- **string (13):** aho_corasick, bitset_match, eertree, hash2d, hash61, kmp, lyndon, manacher, suffix_array, suffix_automaton, zfunc, e os antigos
- **tree (7):** centroid, centroid_paths, hld, hld_bit, lca_lifting, lca_sparse, lca_tarjan

## 5. O que falta implementar

Formato: `arquivo.cpp`: o que faz / API sugerida. "Verifique" quer dizer: abra o arquivo citado primeiro; se ele já cobre o assunto, pule.

**Já cobertos por arquivos existentes (pular, salvo se faltar algo):** `tree/kth_ancestor` (`lca_lifting`), `string/periodos` (`kmp`), `string/rotacao_minima` (`lyndon`), `string/lcp_queries` (`suffix_array`), `dp/knapsack_binario` (`knapsack_bounded`), `math/phi_mu_sieve` (`sieve_linear`), `algebra/multipoint` (`poly`), `geometry/pick_lattice` (`polygon`), `geometry/point_in_convex` (`polygon`).

### Lote 1: bits e jogos (pastas vazias, prioridade alta)

**code/bits**
- `xor_basis.cpp`: base linear em GF(2). `insert(x)`, `can(x)`, `max_xor(x)`, `kth` menor xor, `size`. Tem também a versão "com prefixo", que guarda o índice mais recente para queries [l, r] de max xor.
- `xor_trie.cpp`: trie binária com contador. `insert`, `erase`, `max_xor(x)`, `count(a ^ x < k)`.
- `xor_trie_persistente.cpp`: max xor de x com a\_i, para i em [l, r], via versões e `cnt`.
- `bit_tricks.cpp`: popcount, lowbit, ctz e clz em ll, xor de 1..n, Gosper (próxima máscara com o mesmo popcount), iterar submáscaras e supermáscaras, msb.
- `xor_hashing.cpp`: hash aleatório de 64 bits por valor. Prefix xor detecta "todo valor aparece um número par de vezes em [l, r]". Também traz a soma de hashes para multiconjuntos.

**code/games**
- `grundy.cpp`: Grundy genérico por memo (mex dos sucessores) e soma de jogos via xor. Inclui um exemplo de jogo de subtração com detecção de período.
- `nim_variantes.cpp`: Nim normal e misère, staircase Nim, Moore's Nim\_k (soma dos bits mod (k + 1)) e Nim com remoção limitada (a\_i mod (k + 1)).
- `wythoff.cpp`: posições perdedoras (⌊kφ⌋, ⌊kφ²⌋) em inteiros, sem float (use a sequência de Beatty com o par complementar).
- `jogo_retrogrado.cpp`: BFS retrógrada em grafo de jogo com ciclos (vitória, derrota, empate) usando o grau de saída.
- `minimax_intervalo.cpp`: jogo de tirar das pontas. dp[l][r] = melhor diferença, O(n²).

### Lote 2: estruturas de dados (code/ds)
- `mo.cpp`: Mo clássico com ordem de Hilbert ou par/ímpar. Interface `add(i)`, `remove(i)`, `get()`.
- `mo_updates.cpp`: Mo com updates, blocos n^(2/3).
- `mo_arvore.cpp`: Mo em caminhos de árvore, via Euler tour com in/out e o caso do LCA.
- `mo_rollback.cpp`: Mo só com add, com rollback por bloco.
- `treap.cpp`: treap por chave (split/merge) com tamanho, k-ésimo, contagem < x e merge de duas treaps. Verifique antes `treap_implicito.cpp`.

### Lote 3: árvores (code/tree)
- `euler_tour.cpp`: tin/tout, subárvore como intervalo, e versão de arestas com +w/−w.
- `virtual_tree.cpp`: árvore auxiliar de k vértices em O(k log k). Requer LCA.
- `rerooting.cpp`: template genérico. Combina filhos com prefixo e sufixo e entrega a resposta para todas as raízes.
- `dsu_on_tree.cpp`: small-to-large (sack) com o filho pesado mantido.
- `diametro_centro.cpp`: diâmetro com 2 BFS, caminho, centro(s) e excentricidades.
- `tree_hash.cpp`: isomorfismo de árvores com e sem raiz (AHU ou hash aleatório, raízes no centro).
- `prufer.cpp`: árvore → Prüfer e Prüfer → árvore, em O(n).
- `link_cut.cpp`: link, cut, connected, lca, e agregado de caminho com reroot (evert).
- `kth_ancestor.cpp`: k-ésimo ancestral e k-ésimo vértice no caminho u → v. Verifique antes `lca_lifting.cpp`.
- `cartesian_tree.cpp`: construção O(n) com pilha. Liga RMQ ↔ LCA.
- `lifting_agregado.cpp`: binary lifting com max/min/soma no caminho.

### Lote 4: grafos (code/graph)
- `mst_prim.cpp`: Prim O(n²) para grafo denso, e Prim com heap.
- `boruvka.cpp`: Borůvka genérico, que serve para MST em grafo implícito (xor-MST, Manhattan).
- `kruskal_tree.cpp`: Kruskal reconstruction tree. Gargalo minimax entre u e v vira LCA. Também "componentes alcançáveis com peso ≤ x".
- `segundo_mst.cpp`: segundo melhor MST, estrito, com lifting de max e segundo max.
- `manhattan_mst.cpp`: MST de pontos em Manhattan em O(n log n), varrendo os 4 octantes com BIT.
- `dominator_tree.cpp`: Lengauer–Tarjan.
- `difference_constraints.cpp`: sistema x\_j − x\_i ≤ c via Bellman-Ford com super-fonte. Verifique `bellman_ford.cpp`.
- `triangulos.cpp`: contagem de triângulos O(m√m), orientando do menor grau para o maior. Inclui ciclos de 4.
- `topo_lex.cpp`: ordem topológica lexicograficamente mínima (heap) e contagem de ordens se n ≤ 20. Verifique `toposort.cpp`.
- `bfs_complemento.cpp`: BFS e componentes no grafo complementar em O(n + m), com conjunto de não visitados.
- `fecho_transitivo.cpp`: alcançabilidade com bitset em DAG (ordem topológica reversa), O(nm/64).
- `stoer_wagner.cpp`: corte mínimo global, O(n³).
- `k_caminhos.cpp`: k caminhos simples mínimos (Yen). Verifique `kth_walks.cpp`, que é para walks.

### Lote 5: teoria dos números (code/math)
- `phi_mu_sieve.cpp`: φ e μ até N pelo crivo linear. Verifique `sieve_linear.cpp`.
- `blocos_floor.cpp`: iterar os valores distintos de ⌊n/i⌋ (e ⌈n/i⌉), e Σ f(i)·⌊n/i⌋.
- `prime_count_lucy.cpp`: π(n) e soma de primos até 10¹¹ (Lucy_Hedgehog).
- `min25.cpp`: soma de função multiplicativa até 10¹⁰ (Min\_25). Opcional se ficar grande.
- `dirichlet.cpp`: convolução de Dirichlet O(n log n) e prefixos de φ e μ por hipérbole/Du Jiao sieve.
- `ordem_mult.cpp`: ordem multiplicativa de a mod m, fatorando φ(m).
- `torre_potencias.cpp`: a^b^c^... mod m com φ iterado e o caso expoente ≥ log m.
- `legendre.cpp`: v\_p(n!), v\_p(C(n, k)) por Kummer, e LTE como comentário.
- `fracoes_continuas.cpp`: fração contínua de p/q, convergentes, Stern–Brocot (melhor aproximação com denominador ≤ N) e fração entre a/b e c/d.
- `pell.cpp`: solução fundamental de x² − D·y² = 1 por frações contínuas, com __int128.
- `raiz_discreta.cpp`: x^k ≡ a (mod p) via raiz primitiva + BSGS. Opcional.

### Lote 6: álgebra (code/algebra)
- `matriz.cpp`: struct Matriz mod p, com produto, exponenciação e identidade. Também uma versão min-plus.
- `gauss_mod.cpp`: eliminação mod p, com solução, posto, determinante e inversa.
- `gauss_real.cpp`: eliminação com pivô parcial em double e eps.
- `gauss_xor.cpp`: sistema em GF(2) com bitset (n ≤ 2000), com solução e posto.
- `walsh.cpp`: FWHT para xor, and e or, mod p, com a inversa.
- `subset_convolution.cpp`: convolução de subconjuntos em O(2^n·n²) (ranked zeta).
- `multipoint.cpp`: avaliação multiponto e interpolação rápida. Verifique `poly.cpp`; se já tiver, pule.
- `stirling_fft.cpp`: Stirling de 1ª espécie (linha) via produto (x)(x+1)…(x+n−1) por D&C e NTT. Opcional.

### Lote 7: strings (code/string)
- `wildcard_fft.cpp`: matching com curingas via 3 convoluções Σ p·t·(p − t)². Requer FFT/NTT; cole uma local.
- `expr_parser.cpp`: parser recursivo descendente (+ − * / ^, parênteses, unário). Inclui o shunting-yard como alternativa.
- `periodos.cpp`: todos os períodos e bordas via prefix function, período mínimo e teste "s é k-periódica". Verifique `kmp.cpp`.
- `rotacao_minima.cpp`: rotação mínima de Booth / Duval em O(n). Verifique `lyndon.cpp`.
- `lcp_queries.cpp`: LCP de dois sufixos quaisquer via SA + sparse table, e comparação de substrings. Verifique `suffix_array.cpp`.

### Lote 8: DP (code/dp)
- `insertion_dp.cpp`: DP de "componentes conexas" (inserir elementos em ordem e contar permutações com restrição de adjacência).
- `digit_dp_template.cpp`: template genérico (pos, tight, started, estado) com exemplo de "contar números em [L, R] com soma de dígitos ≡ 0 mod k". Verifique `digitdp.cpp`.
- `esperanca_dp.cpp`: esperança com ciclo, resolvida como sistema linear (cite `gauss_mod`/`gauss_real`), e exemplo de E[passos] em random walk na linha.
- `subseq_distintas.cpp`: número de subsequências distintas, O(n·Σ) ou O(n) com last.
- `lis_reconstrucao.cpp`: LIS O(n log n) com reconstrução e variante não decrescente. Verifique `lis.cpp`.
- `knapsack_binario.cpp`: bounded knapsack por binary splitting. Verifique `knapsack_bounded.cpp`.

### Lote 9: geometria (code/geometry), só se faltar
- `pick_lattice.cpp`: pontos inteiros no segmento (gcd) e no polígono (Pick). Verifique `polygon.cpp`.
- `point_in_convex.cpp`: ponto em polígono convexo em O(log n). Verifique `polygon.cpp` e `convex_extreme.cpp`.

## 6. Prompt sugerido para o DeepSeek (um lote por vez)

> Você vai implementar o Lote N do arquivo `docs/PLANO_LIB.md` do repositório em `C:\Users\WINDOWS\Documents\lib`. Leia as seções 1 e 2 (convenções e testes) e siga à risca. Para cada arquivo do lote: (1) verifique se já existe algo equivalente (seção 4 e "Verifique"); (2) implemente com o cabeçalho de comentários; (3) compile com o prelude; (4) faça stress test contra brute force fora do repo; (5) adicione a linha em `docs/lib-index.md`. Não faça commit. Não modifique arquivos fora do lote, exceto as correções da seção 3 quando o lote for "Correções".

Ordem sugerida: seção 3 (correções) → Lote 1 → 2 → 3 → 4 → 5 → 6 → 7 → 8 → 9.

## 7. Pente fino (Claude, depois)

1. Compilar todos os `.cpp` com o prelude derivado do `template.cpp` e `-Wall`; hoje 24 falham. Corrigir warnings relevantes.
2. Stress test por amostragem: tudo de ds/, tree/, flow/, string/ e algebra/ (as áreas com mais bug).
3. Revisar cabeçalhos: complexidade e API corretas, citação do catálogo.
4. Gerar `docs/lib-index.md` completo, um `README.md` e regenerar `docs/catalogo.pdf` (`python docs/build_pdf.py`).
5. Commit na branch `catalogo`. O push só depois do seu ok.
