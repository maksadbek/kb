#include <iostream>

using namespace std;

const int64_t mod = 1000007;

int64_t norm(int64_t a) {
    return ((a % mod) + mod) % mod;
}

int64_t modmul(int64_t a, int64_t b) {
    return norm(norm(a) * norm(b));
}

int64_t modsub(int64_t a, int64_t b) {
    return norm(norm(a) - norm(b));
}

int64_t modadd(int64_t a, int64_t b) {
    return norm(norm(a) + norm(b));
}

int main() {
    // compute the a^2 - b^2
    int64_t a, b; cin >> a >> b;

    cout << modsub(modmul(a, a), modmul(b, b)) << endl;

    return 0;
}
