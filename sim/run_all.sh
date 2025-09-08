#!/usr/bin/env bash
set -euo pipefail

WORKDIR="$(cd "$(dirname "$0")" && pwd)"

OUTDIR="$WORKDIR/out"
LOGDIR="$WORKDIR/logs"
INCDIR="$WORKDIR/inc"
CFGDIR="$WORKDIR/cfg"

mkdir -p "$OUTDIR" "$LOGDIR"

# 1) Берём GUI-нетлист из корня проекта
GUI_NETLIST="$WORKDIR/gui.cir"
BASE="$OUTDIR/exported.cir"
cp -f "$GUI_NETLIST" "$BASE"

# 2) Чистим от сеансовых директив (.control/.endc, .tran/.op/.ac/...,
#    .meas, .save, .probe, .option) и отрезаем финальную .end
BASE_BODY="$OUTDIR/base_body.cir"
awk '
  BEGIN { IGN=0 }
  tolower($1)==".end"{ exit }
  IGN==0 && tolower($1)==".control" { IGN=1; next }
  IGN==1 && tolower($1)==".endc"    { IGN=0; next }
  IGN==1 { next }
  $0 ~ /^[[:space:]]*\.(tran|ac|dc|op|tf|noise|four|sens|pz)[[:space:]]*/ { next }
  $0 ~ /^[[:space:]]*\.meas[[:space:]]*/   { next }
  $0 ~ /^[[:space:]]*\.save[[:space:]]*/   { next }
  $0 ~ /^[[:space:]]*\.probe[[:space:]]*/  { next }
  $0 ~ /^[[:space:]]*\.option[[:space:]]*/ { next }
  { print $0 }
' "$BASE" > "$BASE_BODY"

run_case () {
  local name="$1" scenefile="$2" cfg="$3"
  local deck="$OUTDIR/deck_${name}.cir"
  local log="$LOGDIR/${name}.log"

  {
    cat "$BASE_BODY"
    echo
    cat "$INCDIR/common.inc"
    echo
    cat "$INCDIR/scenarios/$scenefile"
    echo
    echo ".end"
  } > "$deck"

  echo "== NGSPICE: $name =="
  ngspice -b -o "$log" "$deck"
  python3 "$WORKDIR/check_meas.py" --log "$log" --cfg "$CFGDIR/$cfg"
}

echo "Run cases"

# 3) Сценарии
run_case "INT"      "INT.inc"      "INT.json"
run_case "SPI_DOWN" "SPI_down.inc" "SPI_DOWN.json"
run_case "SPI_UP"   "SPI_up.inc"   "SPI_UP.json"
run_case "MOTOR"    "MOTOR.inc"    "MOTOR.json"

echo "All scenarios executed."
