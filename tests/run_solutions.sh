#!/usr/bin/env bash
set -euo pipefail

compiler="${COMPILER:-g++}"

for year_dir in */; do
    if [[ ! $year_dir =~ ^[0-9]{4}/$ ]]; then
        continue
    fi

    year=${year_dir%/}

    for day in $(seq -w 1 25); do
        dir="$year/$day"
        solution="$dir/solution.txt"

        if [ -f "$dir/a.cpp" ] || [ -f "$dir/b.cpp" ]; then
            if [ ! -f "$solution" ]; then
                echo "Missing solution file for $dir" >&2
                exit 1
            fi
        else
            continue
        fi

        if [ -f "$dir/a.cpp" ]; then
            expected=$(sed -n '1p' "$solution")
            output=$(cd "$dir" && ../../build/"$compiler"/"$dir"/a)
            if [ "$output" != "$expected" ]; then
                echo "Year $year day $day part A failed: expected '$expected', got '$output'" >&2
                exit 1
            fi
        fi

        if [ -f "$dir/b.cpp" ]; then
            expected=$(sed -n '2p' "$solution")
            output=$(cd "$dir" && ../../build/"$compiler"/"$dir"/b)
            if [ "$output" != "$expected" ]; then
                echo "Year $year day $day part B failed: expected '$expected', got '$output'" >&2
                exit 1
            fi
        fi
    done
done

echo "All solution tests passed."
