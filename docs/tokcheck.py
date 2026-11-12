"""Confere que so comentarios/espacos mudaram em cada .cpp em relacao ao git HEAD
e que o arquivo tem o bloco LATEX_DESC. Uso: python tokcheck.py [pasta_ou_arquivos...]"""
import subprocess, sys, os, re
REPO = r"C:\Users\WINDOWS\Documents\lib"

def strip(src):
    out, i, n = [], 0, len(src)
    while i < n:
        c = src[i]
        if src.startswith("//", i):
            j = src.find("\n", i); i = n if j < 0 else j
        elif src.startswith("/*", i):
            j = src.find("*/", i + 2); i = n if j < 0 else j + 2
        elif c in "\"'":
            j = i + 1
            while j < n and src[j] != c:
                j += 2 if src[j] == "\\" else 1
            out.append(src[i:j + 1]); i = j + 1
        elif c == "R" and src.startswith('R"', i):  # raw string
            m = re.match(r'R"([^(]*)\(', src[i:]); d = m.group(1)
            j = src.find(")" + d + '"', i); out.append(src[i:j + len(d) + 2]); i = j + len(d) + 2
        else:
            out.append(c); i += 1
    return re.sub(r"\s+", "", "".join(out))

def head(path):
    rel = os.path.relpath(path, REPO).replace("\\", "/")
    r = subprocess.run(["git", "-C", REPO, "show", f"HEAD:{rel}"], capture_output=True)
    return r.stdout.decode("utf-8", "replace") if r.returncode == 0 else None

args = sys.argv[1:] or [os.path.join(REPO, "code")]
files = []
for a in args:
    if os.path.isdir(a):
        for root, _, fs in os.walk(a):
            files += [os.path.join(root, f) for f in fs if f.endswith(".cpp")]
    else:
        files.append(a)
bad = 0; nodesc = []
for f in sorted(files):
    new = open(f, encoding="utf-8", errors="replace").read()
    old = head(f)
    if old is not None and strip(old) != strip(new):
        bad += 1; print("CODIGO MUDOU:", os.path.relpath(f, REPO))
    if "LATEX_DESC_BEGIN" not in new:
        nodesc.append(os.path.relpath(f, REPO))
print(f"{len(files)} arquivos | codigo alterado: {bad} | sem bloco DESC: {len(nodesc)}")
if 0 < len(nodesc) <= 30: print("  sem DESC:", ", ".join(nodesc))
