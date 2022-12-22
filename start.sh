#!/bin/bash

if [ -f xboard.debug ]; then
    rm xboard.debug
fi

xboard -fcp ./main -debug &

touch xboard.debug
tail -f xboard.debug
