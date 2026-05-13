# Balanced String — Longest Balanced Substring

> Find the length of the longest balanced substring in a given string.

---

## Problem Definition

A string is **balanced** if it contains **exactly two different characters**, both appearing **exactly the same number of times**.

**Goal:** Given a string `S`, find the length of its longest balanced substring.

### Examples

| Input | Output | Longest Balanced Substring |
|-------|--------|---------------------------|
| `"cabbacc"` | `4` | `"abba"` |
| `"abababa"` | `6` | `"ababab"` or `"bababa"` |
| `"aaaaaaa"` | `0` | None |

---

## Algorithms

### 1. Non-Recursive (Iterative)

Uses two nested loops to fix a starting index and extend the window character by character. The window is abandoned as soon as more than two distinct characters are detected.

- **Time Complexity:** O(n²)
- **Space Complexity:** O(1)

### 2. Recursive

Uses a recursive helper `solve()` that advances the index forward, tracking distinct characters and their frequencies. `maxLen` is passed by reference to avoid global state.

- **Time Complexity:** O(n²)
- **Space Complexity:** O(n) — call stack

### Comparison

| Feature | Iterative | Recursive |
|--------|-----------|-----------|
| Time Complexity | O(n²) | O(n²) |
| Space Complexity | O(1) | O(n) |
| Stack Overflow Risk | No | Yes (very long strings) |
| Practical Speed | Faster | Slower |
| String Parameter | `const string&` | `const string&` |
| `maxLen` Scope | Local variable | Local (passed by reference) |

---

## Project Structure

```
├── main.cpp
├── Algorithms.h
├── Algorithms.cpp
└── README.md
```

---

## How to Build & Run

```bash
g++ -o balanced main.cpp Algorithms.cpp
./balanced
```

---

## Team Members

| # | Full Name | ID |
|---|-----------|-----|
| 1 | ادهم محمد فتوح | 20240113 |
| 2 | اسلام محمد صابر عقل | 20240131 |
| 3 | زياد طارق محمد عبده | 20240380 |
| 4 | زياد ناصر علي مكي | 20240392 |
| 5 | عمرو خالد عبدالغفار محمود | 20240666 |
| 6 | يحيى خالد يحيى | 20241120 |

---

> **Course:** Algorithms Analysis — CS316  
> **Faculty of Computing & Artificial Intelligence — Helwan University**
