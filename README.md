# Advent of Code 2024

This repository contains C++ solutions for the Advent of Code 2024 puzzles.

[![Build Status](https://github.com/miracoli/Advent-of-Code/actions/workflows/build.yml/badge.svg)](https://github.com/miracoli/Advent-of-Code/actions/workflows/build.yml)

[![Quality Gate Status](https://sonarcloud.io/api/project_badges/measure?project=miracoli_Advent-of-Code&metric=alert_status)](https://sonarcloud.io/summary/new_code?id=miracoli_Advent-of-Code)

Each day has its own directory under `2024/` containing `a.cpp`, `b.cpp` and a `README.md` describing the approach.

An overview of the line counts for all solutions is published on [GitHub Pages](https://miracoli.github.io/Advent-of-Code/).

The automated build runs on GitHub Actions using GCC, Clang and MSVC.

## Building

Run `make` from the repository root to compile every C++ solution. The resulting executables are placed in the corresponding subdirectories under `build/`. You can target specific Advent of Code years by passing `DIRS="2023 2024"` (or any other subset) to the command.

For faster local builds, invoke `make -j$(nproc)` to compile the solutions in parallel.

