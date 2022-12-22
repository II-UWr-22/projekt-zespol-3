#!/bin/bash

if [ -f xboard.debug ]; then
    rm xboard.debug
fi

xboard -debug &

touch xboard.debug
tail -f xboard.debug
