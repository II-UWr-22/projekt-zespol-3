#!/bin/bash

if [ -f xboard.debug ]; then
    rm xboard.debug
fi

xboard -debug -fcp ./a.out &

touch xboard.debug
tail -f xboard.debug
