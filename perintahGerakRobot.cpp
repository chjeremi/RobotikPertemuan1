#include <iostream>
#include <string>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    string s;
    if (!(cin >> n >> s)) return 0;

    int balance = 0;
    bool is_valid = true;

    for (char c : s) {
        if (c == '(') {
            balance++;
        } else if (c == ')') {
            balance--;
        }

        if (balance < 0) {
            is_valid = false;
            break;
        }
    }

    if (is_valid && balance == 0) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }

    return 0;
}
