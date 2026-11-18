# COMP 211 Checkoff 3 — Use-After-Free in C vs. Rust

**Topic:** Rust Ownership — Preventing Use-After-Free Errors  
**Course:** COMP 211 | **Presenter:** Zhenhao Yang

## Overview

A **use-after-free** bug happens when a program accesses memory after the allocation has been freed. In C, freeing the allocation does not automatically make other uses of the pointer safe. Dereferencing a pointer to freed storage has **undefined behavior**: it might seem to work, produce unexpected output, crash, or cause other problems. Safe Rust uses **ownership** and **borrowing** rules to reject the analogous invalid access during compilation.

This repository accompanies my short presentation comparing a C use-after-free example with Rust's compile-time checks.

## Questions explored

1. Why can C compile a use-after-free program?
2. How does AddressSanitizer detect this problem when the code runs?
3. What do `Box`, ownership, borrowing, and `drop` mean in Rust?
4. Why does moving `println!` before `drop(x)` make the Rust example legal?

## Files

| File | Purpose |
| --- | --- |
| [`uaf.c`](uaf.c) | Intentionally unsafe C example: dereference after `free` |
| [`bad.rs`](bad.rs) | Rust example rejected by the borrow checker |
| [`good.rs`](good.rs) | Corrected Rust program; prints `42` |
| [`Presentation.pptx`](Presentation.pptx) | Presentation slides created for the class |
| [`Experiment_Notes.md`](Experiment_Notes.md) | What the experiments demonstrate and verification notes |
| [`References.md`](References.md) | Official background resources |
| [`AI_Reflection.md`](AI_Reflection.md) | Written reflection draft; add a shared-chat link and personalize before submitting |

## Experiment 1: C use-after-free

> **Warning:** This file deliberately contains undefined behavior, for a classroom demonstration only.

### Compile with AddressSanitizer (macOS/Linux with Clang)

```bash
clang -g -O0 -fsanitize=address -fno-omit-frame-pointer uaf.c -o uaf
./uaf
```

**Expected observation:** the C code builds; when it is run with AddressSanitizer, it should report a `heap-use-after-free` involving a read after `free`.

Without a sanitizer, output is **not predictable**. A displayed number is only one possible outcome; it is not proof that the code is safe. Compilers may also issue warnings.

## Experiment 2: Rust rejects a potential use-after-free

```bash
rustc bad.rs
```

**Expected observation:** a compiler error such as `E0505` (cannot move out of `x` because it is borrowed). `r` is used later, so Rust does not allow `drop(x)` beforehand.

## Experiment 3: Rust accepts a safe ordering

```bash
rustc good.rs -o good
./good
```

**Expected output:**

```text
42
```

You can test the Rust examples without installing Rust in [Rust Playground](https://play.rust-lang.org/) by pasting one program at a time.

## What I learned

- `free(p)` ends the lifetime of an allocation, but the C pointer variable may still contain its old address; dereferencing it is undefined behavior.
- AddressSanitizer can expose the bug **at runtime**, on an executed path.
- In Safe Rust, the borrow checker rejects a `drop` that would invalidate a reference used later.
- Rust can end a borrow at its **last use**, so `println!("{}", r)` followed by `drop(x)` is valid.
- Rust's guarantees apply to **Safe Rust**; inappropriate use of `unsafe` can still introduce memory-safety problems.

## Discussion prompt

**Would the C compiler reject a program that dereferences a pointer after `free`, or could it compile?**

## AI-assisted learning

I used AI as a tutor to quiz myself, correct an initial misunderstanding, compare C and Rust examples, and practice explaining the concept. See `AI_Reflection.md` for a short reflection and representative prompts.

## References

See [`References.md`](References.md).
