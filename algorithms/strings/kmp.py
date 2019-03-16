"""
Knuth-Morris-Pratt algorithm

What is the maximum number of times that the condition of the inner while loop can be tested on the iteration 
i of the external for loop in this code (including the last time it is tested when either border border is 0 or P[i] == P[border]:

compute_prefix_function(P)
    let s be the array of integers of length |P|

    set s[0] to 0
    let border equal to 0

    for I from 1 to |P| - 1:
        while border > 0 and P[I] is not equal to P[border]:
            set border to s[border - 1]
    
        if P[I] == P[border]:
            increment border by 1
        else:
            set border to 0

        set s[i] to border
    return s 

The answer is i
 
If the string P is AAA…AAC with i as and one C, then on iteration i initially border = i - 1, and we will compare P[i] = B with P[i - 1], P[i - 2], …, P[1] and then border will become 0, we will make the last test, and then the while loop will stop. There cannot be more iterations, because the border cannot be more than i - 1 initially, it decreases on each iteration of the while loop, and the while loop stops as soon as border = 0


Lemma:
    P[0..i] has a border of length s(i + 1) − 1 

i.e: let substr be P[0..I]. Then, substr has some border of length of the longest border of the next char minus one.

Proof:
- get the longest border of P[0...i+1]
- cut off the last char
- the result will be the border of P[0...i].

Lemma:
    If s(i) > 0, then all borders of P[0..i] but for the longest one are also borders of P[0..s(i) − 1]. 
i.e: the border b is longest prefix and suffix of string P. As the b is the longest border, it repeats at the beginning and at the end of the string P. The prefix of this b ends at s(i) - 1. Of course, the border b can also contain borders too.

Proof:
- Let u be a border of P[0..i] such that |u| < s(i)
- Then u is both a pre􏰚x and a su􏰛ffix of P[0..s(i) − 1] 
- u = P[0..s(i) − 1], so u is a border of P[0..s(i) − 1] 

Computing s(i + 1): s(i + 1) = |some border of P[0..s(i) − 1]| + 1 

"""


def compute_prefix(p):
    s = [0] * (len(p))
    border = 0
    for i in range(1, len(p)):
        while border > 0 and p[i] != p[border]:
            border = s[border-1]
        
        if p[i] == p[border]:
            border += 1
        else:
            border = 0
        
        s[i] = border
    
    return s


def kmp(p, s):
    text = p + "$" + s
    prefix = compute_prefix(text)
    result = []
    
    for i in range(len(p) + 1, len(text)):
        if prefix[i] == len(p):
            result.append(i - 2*len(p))
    
    return result
    
print(kmp("AC", "ACATACATACACA"))
