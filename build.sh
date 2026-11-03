#!/bin/bash
set -euo pipefail
cd "$(dirname "$0")"
export PATH="/opt/homebrew/bin:/usr/local/bin:$PATH"
mkdir -p build
/usr/bin/clang++ -std=c++17 -g -O0 -Wall -Wextra $(pkg-config --cflags raylib) -c main.cpp -o build/main.o
/usr/bin/clang++ build/main.o -o build/raylib-starter $(pkg-config --libs raylib)
echo "Built build/raylib-starter"
