# Balanced String — Longest Balanced Substring

<div align="center">

**Faculty of Computing & Artificial Intelligence**  
**Helwan University**  
**Algorithms Analysis — CS316**

</div>

---

## Table of Contents

1. [Problem Definition](#problem-definition)
2. [Approach & Core Idea](#approach--core-idea)
3. [Algorithm 1 — Iterative](#algorithm-1--non-recursive-iterative)
4. [Algorithm 2 — Recursive](#algorithm-2--recursive)
5. [Complexity Analysis](#complexity-analysis)
6. [Comparison](#comparison)
7. [Project Structure](#project-structure)
8. [How to Build & Run](#how-to-build--run)
9. [Team Members](#team-members)

---

## Problem Definition

A string is considered **balanced** if it satisfies **both** of the following conditions:

- It contains **exactly two distinct characters**.
- Both characters appear **exactly the same number of times**.

**Objective:** Given a string `S` of lowercase English letters, find the **length** of its longest balanced substring.

### Examples

| Input | Output | Explanation |
|-------|--------|-------------|
| `"cabbacc"` | `4` | `"abba"` → two chars `a`,`b`, each appears twice |
| `"abababa"` | `6` | `"ababab"` or `"bababa"` → each char appears 3 times |
| `"aaaaaaa"` | `0` | Only one distinct character → no balanced substring |
| `"aabb"` | `4` | The full string → `a` x 2, `b` x 2 |
| `"abcabc"` | `4` | e.g. `"abab"` or `"bcbc"` → length 4 |

---

## Approach & Core Idea

Both algorithms are built around the same **sliding window** strategy:

1. **Fix a starting index `i`** — this is the left edge of our window.
2. **Extend the window right** by moving index `j` (or recursing on `index`), one character at a time.
3. At every step, maintain:
   - `freq[26]` — the frequency of each character in the current window.
   - `diff` — the number of distinct characters seen so far in the window.
4. **Prune early:** if `diff > 2`, this window can never be balanced — stop immediately.
5. **Check balance:** if `diff == 2` and both characters have equal frequency, we have a valid balanced substring. Update `maxLen` if this window is longer than any seen before.
6. Repeat for all possible starting indices.

The key insight is that we only need to track **two values** out of the frequency array at any moment (the counts of the two active characters), making the inner frequency scan O(26) = O(1).

---

## Algorithm 1 — Non-Recursive (Iterative)

### Pseudocode

```
FUNCTION NonRecursiveAlgorithm(S):
    n      <- length(S)
    maxLen <- 0

    FOR i FROM 0 TO n-1:
        freq[26] <- {0}
        diff     <- 0

        FOR j FROM i TO n-1:
            index <- S[j] - 'a'
            IF freq[index] == 0 : diff <- diff + 1
            freq[index] <- freq[index] + 1

            IF diff > 2 : BREAK

            IF diff == 2:
                first <- 0,  second <- 0
                FOR k FROM 0 TO 25:
                    IF freq[k] > 0:
                        IF first == 0 : first  <- freq[k]
                        ELSE          : second <- freq[k]
                IF first == second:
                    len <- j - i + 1
                    IF len > maxLen : maxLen <- len

    RETURN maxLen
```

### C++ Implementation

```cpp
#include <iostream>
#include <string>
#include <algorithm>
#include "Algorithms.h"
using namespace std;

int NonRecursiveAlgorithm(const string& s) {
    int n      = s.length();
    int maxLen = 0;

    for (int i = 0; i < n; i++) {
        int freq[26] = {0};
        int diff     = 0;

        for (int j = i; j < n; j++) {
            int index = s[j] - 'a';
            if (freq[index] == 0) diff++;
            freq[index]++;

            if (diff > 2) break;

            if (diff == 2) {
                int first = 0, second = 0;
                for (int k = 0; k < 26; k++) {
                    if (freq[k] > 0) {
                        if (first == 0) first  = freq[k];
                        else            second = freq[k];
                    }
                }
                if (first == second) {
                    int len = j - i + 1;
                    if (len > maxLen) maxLen = len;
                }
            }
        }
    }
    return maxLen;
}
```

### Walkthrough — `"cabbacc"`

| `i` | Window grows… | Event |
|-----|---------------|-------|
| 0 | `c` -> `ca` -> `cab` | diff=3 → break |
| 1 | `a` -> `ab` -> `abb` -> `abba` | first==second=2 → **maxLen = 4** |
| 2 | `b` -> `bb` -> `bba` -> `bbac` | diff=3 → break |
| 3 | `b` -> `ba` -> `bac` | diff=3 → break |
| 4 | `a` -> `ac` -> `acc` | first(1) != second(2) → skip |
| 5 | `c` -> `cc` | diff=1 only → no update |

**Result → 4**

---

## Algorithm 2 — Recursive

### Pseudocode

```
FUNCTION solve(S, start, index, freq[], diff, maxLen):
    IF index == length(S) : RETURN

    c <- S[index] - 'a'
    IF freq[c] == 0 : diff <- diff + 1
    freq[c] <- freq[c] + 1

    IF diff > 2 : RETURN

    IF diff == 2:
        first <- 0,  second <- 0
        FOR i FROM 0 TO 25:
            IF freq[i] > 0:
                IF first == 0 : first  <- freq[i]
                ELSE          : second <- freq[i]
        IF first == second:
            maxLen <- MAX(maxLen, index - start + 1)

    CALL solve(S, start, index + 1, freq, diff, maxLen)


FUNCTION RecursiveAlgorithm(S):
    maxLen <- 0
    FOR i FROM 0 TO length(S)-1:
        freq[26] <- {0}
        CALL solve(S, i, i, freq, 0, maxLen)
    RETURN maxLen
```

### C++ Implementation

```cpp
#include <iostream>
#include <string>
#include <algorithm>
#include "Algorithms.h"
using namespace std;

void solve(const string& s, int start, int index,
           int freq[26], int diff, int& maxLen) {

    if (index == (int)s.size()) return;

    int c = s[index] - 'a';
    if (freq[c] == 0) diff++;
    freq[c]++;

    if (diff > 2) return;

    if (diff == 2) {
        int first = 0, second = 0;
        for (int i = 0; i < 26; i++) {
            if (freq[i] > 0) {
                if (first == 0) first  = freq[i];
                else            second = freq[i];
            }
        }
        if (first == second)
            maxLen = max(maxLen, index - start + 1);
    }

    solve(s, start, index + 1, freq, diff, maxLen);
}

int RecursiveAlgorithm(const string& s) {
    int maxLen = 0;
    for (int i = 0; i < (int)s.size(); i++) {
        int freq[26] = {0};
        solve(s, i, i, freq, 0, maxLen);
    }
    return maxLen;
}
```

### Key Design Decisions

| Decision | Rationale |
|----------|-----------|
| `const string&` parameter | Avoids copying the full string on every call |
| `int& maxLen` by reference | Eliminates global variable; all recursive paths share one counter safely |
| `diff` passed by value | Each recursive path gets its own copy; no interference between sibling chains |
| `freq[]` reset per outer-loop iteration | Ensures each starting index begins with a clean frequency state |

### Recursion Tree — `"ab"`, start=0

```
solve("ab", 0, 0, freq={}, diff=0)
 └─ c='a', diff=1, freq={a:1}
    └─ solve("ab", 0, 1, freq={a:1}, diff=1)
        └─ c='b', diff=2, freq={a:1, b:1}
            └─ first=1 == second=1  -->  maxLen = 2
               └─ solve("ab", 0, 2, ...)
                   └─ index == size  -->  RETURN
```

---

## Complexity Analysis

### Iterative

| Step | Operation | Cost |
|------|-----------|------|
| 1 | Outer loop over all starting positions | O(n) |
| 2 | Inner loop extends window from each start | O(n) |
| 3 | Frequency update and two-char check (26 slots) | O(1) |
| | **Total Time Complexity** | **O(n²)** |
| | **Space Complexity** | **O(1)** |

### Recursive

| Step | Operation | Cost |
|------|-----------|------|
| 1 | Outer loop calls `solve()` for each starting index | O(n) |
| 2 | Each `solve()` call recurses at most `(n - start)` levels | O(n) |
| 3 | Each recursion level does O(26) = constant work | O(1) |
| 4 | Call stack depth per start position | O(n) space |
| | **Total Time Complexity** | **O(n²)** |
| | **Space Complexity** | **O(n)** |

---

## Comparison

| Feature | Iterative | Recursive |
|---------|-----------|-----------|
| Time Complexity | O(n²) | O(n²) |
| Space Complexity | **O(1)** | O(n) — call stack |
| Stack Overflow Risk | **No** | Yes (very long strings) |
| Practical Speed | **Faster** | Slower (call overhead) |
| Readability | Clear, direct | Elegant logic |
| `maxLen` Scope | Local variable | Local (passed by `int&`) |
| String Parameter | `const string&` | `const string&` |
| Backtracking | N/A | None — forward only |

**Verdict:** Both algorithms are correct and produce identical results.  
The iterative version is preferred in practice due to its O(1) space and absence of call-stack risk.  
The recursive version illustrates the same logic in a more declarative style and is useful for understanding the problem structure.

---

## Project Structure

```
balanced-string/
├── main.cpp          # Entry point — runs both algorithms and compares output
├── Algorithms.h      # Function declarations
├── Algorithms.cpp    # NonRecursiveAlgorithm + solve + RecursiveAlgorithm
└── README.md         # This file
```

---

## How to Build & Run

### Prerequisites

- GCC / G++ (MinGW on Windows, or GCC on Linux/macOS)
- C++11 or later

### Compile

```bash
g++ -std=c++11 -o balanced main.cpp Algorithms.cpp
```

### Run

```bash
./balanced
```

### Expected Output (sample)

```
Input: "cabbacc"
  Iterative  -> 4
  Recursive  -> 4

Input: "abababa"
  Iterative  -> 6
  Recursive  -> 6

Input: "aaaaaaa"
  Iterative  -> 0
  Recursive  -> 0
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

<div align="center">

*Faculty of Computing & Artificial Intelligence — Helwan University*  
*Algorithms Analysis — CS316*

</div>
