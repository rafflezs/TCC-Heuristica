#!/bin/bash

if [ ! -f "/test/exe" ]
then
    test/compile.sh
fi

if [ -f "data/output/test.latex" ]
then
    rm -f data/output/test.latex
fi

rm -f test/out.txt

./test/exe "Instancia-Facil-Comp" 10 1 1 >> test/out.txt

rm -f test/exe