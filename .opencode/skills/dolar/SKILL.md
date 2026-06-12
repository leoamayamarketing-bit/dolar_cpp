---
name: dolar
description: Use for the BCRA USD exchange rate C++ project in dolar/. Build, run, or modify this project. Trigger on filenames like main.cpp, http_client.h, Makefile, or keywords "dolar", "bcra", "usd".
---

# Dolar Project

C++ project that queries the USD exchange rate from Argentina's BCRA API.

## Structure

- `bin/` — compiled binary
- `src/` — source code
- `include/` — headers
- `obj/` — build artifacts
- `scripts/` — shell scripts

## Build

```bash
make
```

## Run

```bash
./bin/dolar
```

## Dependencies

- libcurl
- C++11 compiler
