#!/usr/bin/env sh

find . -name "*.gv" -type f -exec sh -c 'dot -Tpng "$1" -o "graphs/${1%.gv}.png"' _ {} \;
