

echo "========================================"
echo "      APP 1: MEMORY ANALYZER TEST     "
echo "========================================"


echo "[*] Derleniyor..."
make app1


echo ""
echo "[*] Test 1: Temel Bellek Analizi (Maps)"
./app1

echo""
echo"# Memory monitoring (update every 5 seconds)"
./app1 --monitor 5


echo ""
echo "[*] Test 2: Memory Leak Check"
./app1 -leak-check


echo ""
echo "[*] Test 3: --all Modu"
./app1 --all

echo ""
echo "========================================"
echo "      APP 1 TESTI TAMAMLANDI          "
echo "========================================"