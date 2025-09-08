#!/usr/bin/env python3
import re, sys, json, argparse, math

p = argparse.ArgumentParser()
p.add_argument("--log", required=True)
p.add_argument("--cfg", required=True)
args = p.parse_args()

with open(args.cfg) as f:
    rules = json.load(f)

txt = open(args.log, "r", errors="ignore").read()

failed_blocks = re.findall(r"\.meas.*failed!", txt)
meas = {}
for m in re.finditer(r"(?:Measurement:\s*)?([A-Za-z0-9_]+)\s*=\s*([-+0-9.eE]+)", txt):
    meas[m.group(1)] = float(m.group(2))

status = 0
lines = []
if failed_blocks:
    status = 1
    lines.append(f"Found failed .meas blocks: {len(failed_blocks)}")

def ok(op, val, thr):
    if op in (">=", "ge"): return val >= thr
    if op in (">",  "gt"): return val >  thr
    if op in ("<=", "le"): return val <= thr
    if op in ("<",  "lt"): return val <  thr
    if op in ("==", "eq"): return math.isclose(val, thr, rel_tol=1e-6, abs_tol=1e-9)
    raise ValueError(f"Unknown op {op}")

for key, rule in rules.items():
    if key not in meas:
        status = 1
        lines.append(f"[MISS] {key} not measured")
        continue
    val = meas[key]
    # rule format: {"op":"<", "value":2e-7}  OR  {">=":2.0}
    if "op" in rule:
        op, thr = rule["op"], float(rule["value"])
    else:
        ((op, thr),) = list((k, float(v)) for k, v in rule.items())
    if ok(op, val, thr):
        lines.append(f"[PASS] {key}: {val:g} {op} {thr:g}")
    else:
        status = 1
        lines.append(f"[FAIL] {key}: {val:g} !{op} {thr:g}")

print("\n".join(lines))
sys.exit(status)
