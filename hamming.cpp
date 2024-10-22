#include <iostream>
#include <cmath>
using namespace std;

int main() {
    int a, r = 0;
    cout << "Enter the No of Data Bits you want to Enter: ";
    cin >> a;
    while (a + r + 1 > pow(2, r)) r++;

    int c[a + 1], data[a + r + 1];
    cout << "Enter the Data Bits One by One:" << endl;
    for (int i = 1; i <= a; ++i) cin >> c[i];

    int d = 0, d1 = 1;
    for (int i = 1; i <= a + r; ++i) {
        if (i == pow(2, d)) {
            data[i] = 0;
            d++;
        } else {
            data[i] = c[d1++];
        }
    }

    d1 = 0;
    for (int i = 1; i <= a + r; i = pow(2, d1++)) {
        int parity = 0;
        for (int j = i; j <= a + r;) {
            for (int s = j; s < j + i && s <= a + r; ++s) {
                if (data[s] == 1) parity++;
            }
            j += 2 * i;
        }
        data[i] = (parity % 2 == 0) ? 0 : 1;
    }

    cout << "Hamming codeword bits for even parity are: ";
    for (int i = 1; i <= a + r; ++i) cout << data[i] << " ";
    cout << endl;
}
