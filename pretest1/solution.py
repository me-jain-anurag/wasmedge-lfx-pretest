"""
WasmEdge LFX Mentorship Pre-test 1
Author: Anurag Jain
Date: 02/02/2026

Problem: Calculate the sum of character values based on conversion rules.

Answer: 120903

Explanation:
The alphabetToNum function converts characters to numbers:
- Lowercase (a-z): position in alphabet x 100 (a=100, b=200, ... z=2600)
- Uppercase (A-Z): position in alphabet x 10000 (A=10000, B=20000, ... Z=260000)
- Digits (0-9): the numeric value itself
- Special characters: 10000

For input "111BBBccc!@#$^*":
- '1' three times: 3 x 1 = 3
- 'B' three times: 3 x 20000 = 60000
- 'c' three times: 3 x 300 = 900
- Special chars (!@#$^*) six times: 6 x 10000 = 60000
Total: 3 + 60000 + 900 + 60000 = 120903
"""

def alphabetToNum(c):
    if c >= 'a' and c <= 'z':
        return (ord(c) - ord('a') + 1) * 100
    elif c >= 'A' and c <= 'Z':
        return (ord(c) - ord('A') + 1) * 10000
    elif c >= '0' and c <= '9':
        return int(c)
    else:
        return 10000

result = 0
for a in "111BBBccc!@#$^*":
    result += alphabetToNum(a)
print(result) # Output is 120903