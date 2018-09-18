// Copyright 2015 Maksadbek
#include <iostream>
using std::cin;
using std::cout;

int main() {
    char ch;
    cin.get(ch);
    while (ch != '#') {
        cout << ch;
        cin.get(ch);
    }
    return 0;
}
