# Dolar - BCRA USD Exchange Rate Query

C++ tool to query the USD exchange rate from Argentina's BCRA API.

## Project Structure

```
.
├── Makefile
├── README.md
├── .gitignore
├── .opencode/skills/dolar/SKILL.md
├── assets/               # Static resources
├── bin/                  # Compiled binary
├── include/
│   ├── http_client.h
│   └── json.hpp
├── obj/                  # Build artifacts
├── outouts/              # Generated output files
├── scripts/
│   ├── code.sh           # Shell script (legacy)
│   └── token.txt         # API token (legacy)
└── src/
    ├── main.cc           # Original source (legacy)
    ├── main.cpp
    └── http_client.cpp
```

## Requirements

- C++11 compiler
- libcurl

### Setup

**macOS:**
```bash
xcode-select --install
```

**Linux:**
```bash
sudo apt install build-essential libcurl4-openssl-dev
```

## Build & Run

```bash
make
./bin/dolar
```

## Clean

```bash
make clean
```
