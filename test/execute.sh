if [ ! -f "/test/exe" ]; then
    test/compile.sh
fi
rm -f test/out.txt
./test/exe "Instancia-Facil-Comp" 10 >> test/out.txt
