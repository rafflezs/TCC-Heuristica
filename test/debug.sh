#!/bin/bash

if [ ! -f "/test/exe" ]
then
    test/compile.sh
fi

if [ -f "data/output/test.latex" ]
then
    rm -f data/output/test.latex
fi

gdb test/exe