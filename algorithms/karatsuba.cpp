#include <iostream>
#include <cmath>

int nlength(long long n) {
        int c = 0;

        while(n > 0) {
                c++;
                n = n / 10;
        }

        return c;
}

long long karatsuba(long long a, long long b) {
        // printf("a: %lld, b: %lld\n", a, b);
        // base case
        if (a < 10 and b < 10) {
                return a * b;
        }

        int n = std::max(nlength(a), nlength(b));
        long long m = std::ceil(n/2);
        // printf("m: %lld\n", m);

        long long bm = (long long) std::pow(10, m);

        long long x1 = a / bm;
        long long x0 = a % bm;

        long long y1 = b / bm;
        long long y0 = b % bm;

        // printf("x1: %lld, x2: %lld, y1: %lld, y0: %lld\n", x1, x0, y1, y0);

        long long z1 = karatsuba(x1, y1);
        long long z2 = karatsuba(x0, y0);
        long long z3 = karatsuba(x1+x0, y1+y0) - z1 - z2;

        // std::cout << z1 << "," << z2 << "," << z3 << std::endl;
        // result = z1 · (Bm)^2 + z3 · (Bm)^1 + z0 · (Bm)0
        return z1 * std::pow(10, m*2) + z3 * std::pow(10, m) + z2;
}

int main(int argc, char** argv) {
        std::cout << karatsuba(1000, 1234) << std::endl;
        return 0;
}
