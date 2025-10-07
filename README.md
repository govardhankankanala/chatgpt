# Dropcopy Skeleton

Minimal C++ project your automation can **auto-update** from NSE circulars:
- `include/dropcopy/*` public API (opcodes, message structs, parser, config)
- `src/dropcopy/*` implementations
- `data/symbols.csv` seed lot/tick sizes (editable by circulars)
- `tests/` a tiny parser test

## Build
```bash
cmake -S . -B build
cmake --build build -j
ctest --test-dir build
