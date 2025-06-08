#!/usr/bin/env bash
set -euo pipefail

compiler="${COMPILER:-g++}"

for day in $(seq -w 1 1); do
    dir="2024/$day"
    solution="$dir/solution.txt"
    [ -f "$solution" ] || continue

    if [ -f "$dir/a.cpp" ]; then
        expected=$(sed -n '1p' "$solution")
        output=$(cd "$dir" && ../../build/"$compiler"/"$dir"/a)
        if [ "$output" != "$expected" ]; then
            echo "Day $day part A failed: expected '$expected', got '$output'" >&2
            exit 1
        fi
    fi

    if [ -f "$dir/b.cpp" ]; then
        expected=$(sed -n '2p' "$solution")
        output=$(cd "$dir" && ../../build/"$compiler"/"$dir"/b)
        if [ "$output" != "$expected" ]; then
            echo "Day $day part B failed: expected '$expected', got '$output'" >&2
            exit 1
        fi
    fi

done

echo "All solution tests passed."
