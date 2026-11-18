# Experiment Notes — C vs. Safe Rust

## C: `uaf.c`

After `free(p)`, the pointer still contains an address, but dereferencing it is undefined behavior. The compiler may build the program. AddressSanitizer instruments the executable to catch invalid memory accesses at runtime.

**Command:**

```bash
clang -g -O0 -fsanitize=address -fno-omit-frame-pointer uaf.c -o uaf
./uaf
```

**Expected ASan finding:** `heap-use-after-free`.

## Rust: `bad.rs`

The variable `x` owns the `Box`; `r` borrows it. `drop(x)` attempts to move and destroy the owner while the borrow is still required by `println!`. The borrow checker rejects this code at compile time.

**Command:** `rustc bad.rs`  
**Expected finding:** a borrow-checker error, typically `E0505`.

## Rust: `good.rs`

Moving `println!("{}", r)` before `drop(x)` makes `r`'s last use occur before the owner is dropped. This is allowed by Rust's non-lexical lifetimes.

**Commands:**

```bash
rustc good.rs -o good
./good
```

**Expected output:** `42`.

**Reproducibility note:** Test all three programs on your machine or in Rust Playground, and keep your actual terminal output or screenshots. The exact C output without ASan is not guaranteed.
