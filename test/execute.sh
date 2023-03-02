if [ ! -f "/test/exe" ]; then
    test/compile.sh
fi
rm -f test/out.txt
./test/exe "TCC-Instancia-2018-1" 10 >> test/out.txt
