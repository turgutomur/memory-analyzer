#!/bin/bash

echo "========================================"
echo "      APP 2: SECURITY CHECKER TEST    "
echo "========================================"

SAMPLE_FILE="tests/samples/vulnerable1.c"


echo "[*] Derleniyor..."
make app2


if [ ! -f "$SAMPLE_FILE" ]; then
    echo "Hata: $SAMPLE_FILE bulunamadi!"
    exit 1
fi


echo ""
echo "[*] Test 1: Scan Mode (-s)"
./app2 -s $SAMPLE_FILE


echo ""
echo "[*] Test 2: Recommendation Mode (-r)"
./app2 -r $SAMPLE_FILE


echo ""
echo "[*] Test 3: Extended Mode (-x)"
./app2 -x $SAMPLE_FILE

echo ""
echo "========================================"
echo "      APP 2 TESTI TAMAMLANDI          "
echo "========================================"