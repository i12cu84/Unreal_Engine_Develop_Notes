#include <iostream>
#include <vector>

using namespace std;

class BigInt {
public:
    vector<int> digits;

    BigInt(int num) {
        while (num > 0) {
            digits.push_back(num % 10);
            num /= 10;
        }
    }

    BigInt& operator*=(const BigInt& other) {
        vector<int> result(digits.size() + other.digits.size(), 0);

        for (int i = 0; i < digits.size(); ++i) {
            int carry = 0;
            for (int j = 0; j < other.digits.size() || carry; ++j) {
                long long current = result[i + j] +
                                    (long long)digits[i] * (j < other.digits.size() ? other.digits[j] : 0) + carry;
                result[i + j] = current % 10;
                carry = current / 10;
            }
        }

        // Remove leading zeros
        while (result.size() > 1 && result.back() == 0) {
            result.pop_back();
        }

        digits = result;
        return *this;
    }

    friend ostream& operator<<(ostream& os, const BigInt& bigInt) {
        for (int i = bigInt.digits.size() - 1; i >= 0; --i) {
            os << bigInt.digits[i];
        }
        return os;
    }
};

BigInt power(const BigInt& base, int exponent) {
    BigInt result(1);
    for (int i = 0; i < exponent; ++i) {
        result *= base;
    }
    return result;
}

int main() {
    BigInt base4(4);
    BigInt base5(5);

    BigInt result1 = power(base4, 5321);
    BigInt result2 = power(base5, 4321);

    cout << "4的5321次幂：" << result1 << endl;
    cout << "5的4321次幂：" << result2 << endl;

    return 0;
}
