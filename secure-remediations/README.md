# Secure Remediations

This folder contains corrected or safer follow-up examples that complement the original coursework modules without replacing them.

## Parameterized SQLite Query

[`ParameterizedQueryExample.cpp`](./ParameterizedQueryExample.cpp) demonstrates the preferred control for SQL injection in SQLite applications:

- prepare a fixed SQL statement with `sqlite3_prepare_v2`
- bind untrusted input with `sqlite3_bind_text`
- execute the prepared statement with `sqlite3_step`
- treat attack strings as data rather than executable SQL
- avoid displaying or storing plaintext passwords in the example

The original [`Injection-Prevention/SQLInjection.cpp`](../Injection-Prevention/SQLInjection.cpp) remains available as an educational attack-pattern detection exercise. Pattern matching can illustrate suspicious input, but it is not a reliable replacement for parameter binding.

## Build Example

A typical Linux or macOS command with SQLite development libraries installed is:

```bash
g++ -std=c++17 ParameterizedQueryExample.cpp -lsqlite3 -o parameterized-query
./parameterized-query
```

Visual Studio users can add the source file to a C++ project and link the SQLite library used by the original course module.

## Cryptography Guidance

The original `Encryption/` module demonstrates reversible XOR transformation. It is intentionally preserved as coursework, but it should not be used to protect real data.

Production software should use a reviewed cryptographic library and an authenticated-encryption construction such as AES-GCM or ChaCha20-Poly1305. Applications should also use secure random nonces, keep keys outside source code and avoid writing secret keys into output files.
