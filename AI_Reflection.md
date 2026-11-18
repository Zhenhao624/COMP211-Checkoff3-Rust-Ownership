# COMP 211 Checkoff 3 — AI Exploration Reflection

**Topic:** Rust Ownership — Preventing Use-After-Free Errors  
**Student:** Zhenhao Yang

I chose to explore how Rust prevents use-after-free errors because we had learned about pointers, `malloc`, and `free` in COMP 211. My first question was whether a C compiler would stop a program from accessing memory after it had been freed. During a quiz with AI, I chose the answer saying that the C compiler would always reject the program. I learned that this was incorrect: the code may compile, but dereferencing freed memory causes undefined behavior. I then compared this with how Rust checks ownership and borrowing before a program can run.

Two representative prompts from my conversation were:

1. **“我选 C。请告诉我是否正确，并继续教我 Rust Ownership 和 Borrowing，帮助我准备 Checkoff 3。”** (I chose C. Tell me whether it is correct, then teach me Rust ownership and borrowing.)
2. **“对于 Rust Ownership 测试，我选 A。请解释为什么，然后带我完成 Checkoff 3 的 C/Rust 代码实验及 5 页 Slides 的内容规划。”** (For the Rust ownership test, I chose A. Explain why, then guide me through the C/Rust experiments and slide planning.)

Rather than just asking AI for definitions, I used its follow-up questions to check my understanding. The most useful example compared a reference used *after* `drop(x)` with a reference used *before* `drop(x)`. I learned that Rust's borrow checker prevents dropping an owner while a live borrow is still needed. I also examined the difference between a C runtime error detected by AddressSanitizer and a Rust compile-time error. This connected a new language feature directly to the manual memory management we studied in class.

If I repeated this project, I would run more variations myself, inspect real compiler output for each one, and use the official Rust documentation earlier to verify AI explanations. My main takeaway is that Safe Rust makes important memory-safety rules part of compilation, while C gives the programmer more responsibility for avoiding these mistakes.

**Permalink to AI conversation:** [PASTE YOUR SHARED CHATGPT CONVERSATION LINK HERE]
