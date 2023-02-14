if [ ! -f "/test/exe" ]; then
    test/compile.sh
fi
rm -f test/out.txt
./test/exe "Instancia-Facil-Comp" 1 >> test/out.txt
