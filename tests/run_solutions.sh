#!/usr/bin/env bash
set -euo pipefail

compiler="${COMPILER:-g++}"

check_part() {
    local part=$1
    local solution_line=$2
    local part_label=${part^^}

    if [ ! -f "$dir/$part.cpp" ]; then
        return
    fi

    local binary="../../build/$compiler/$dir/$part"
    local expected
    expected=$(sed -n "${solution_line}p" "$solution")
    local output
    output=$(cd "$dir" && "$binary")
    if [ "$output" != "$expected" ]; then
        echo "Year $year day $day part $part_label failed: expected '$expected', got '$output'" >&2
        exit 1
    fi

    local input_file="$dir/input.txt"
    local backup_file=""
    if [ -f "$input_file" ]; then
        backup_file="$dir/input.txt.missing_check"
        if [ -e "$backup_file" ]; then
            echo "Temporary input backup already exists for $dir" >&2
            exit 1
        fi
        mv "$input_file" "$backup_file"
    fi

    local status
    if (cd "$dir" && "$binary"); then
        status=0
    else
        status=$?
    fi

    if [ -n "$backup_file" ]; then
        mv "$backup_file" "$input_file"
    fi

    if [ "$status" -ne 1 ]; then
        echo "Year $year day $day part $part_label expected exit status 1 when input is missing, got $status" >&2
        exit 1
    fi
}

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

        check_part a 1
        check_part b 2
    done
done

echo "All solution tests passed."
