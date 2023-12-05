#pragma once
#include <iostream>
#include <sstream>
#include<cmath>

class Bigint_160 {
    unsigned int number[5];

public:
    Bigint_160() {
        for (int i = 0; i < 5; i++) {
            number[i] = 0;
        }
    }

    Bigint_160(std::string numberHex) {
        int digitValue = 0;
        int digitCount = 0;
        for (int i = 0; i < 5; i++) {
            number[i] = 0;
        }
        for (char hexChar : numberHex) {
            if (isdigit(hexChar)) {
                digitValue = hexChar - '0';
            }
            else {
                digitValue = std::tolower(hexChar) - 'a' + 10;
            }
            if (digitCount < 8) {
                number[0] <<= 4;
                number[0] += digitValue;
            }
            else if (digitCount < 16) {
                number[1] <<= 4;
                number[1] += digitValue;
            }
            else if (digitCount < 24) {
                number[2] <<= 4;
                number[2] += digitValue;
            }
            else if (digitCount < 32) {
                number[3] <<= 4;
                number[3] += digitValue;
            }
            else {
                number[4] <<= 4;
                number[4] += digitValue;
            }

            digitCount++;
        }
    }

    void PrintBigint_160() {
        std::stringstream stream;
        for (int i = 0; i < 5; i++)
            stream << std::hex << number[i];
        std::cout << stream.str() << std::endl;
    }

    Bigint_160 operator%(int sizeofBits) {
        std::stringstream stream;
        stream << "";
        unsigned   int current = 0;
        if (sizeofBits <= 32 && sizeofBits != 0) {
            current = number[4];
            current = current << 32 - sizeofBits;
            current = current >> (32 - sizeofBits);
            stream << std::hex << current;
        }
        else if (sizeofBits <= 64 && sizeofBits != 0) {
            current = number[3];
            sizeofBits -= 32;
            current = current << 32 - sizeofBits;
            current = current >> (32 - sizeofBits);
            stream << std::hex << current;
            stream << std::hex << number[4];
        }
        else if (sizeofBits <= 96 && sizeofBits != 0) {
            current = number[2];
            sizeofBits -= 64;
            current = current << 32 - sizeofBits;
            current = current >> (32 - sizeofBits);
            stream << std::hex << current;
            stream << std::hex << number[3];
            stream << std::hex << number[4];
        }
        else if (sizeofBits <= 128 && sizeofBits != 0) {
            current = number[1];
            sizeofBits -= 96;
            current = current << 32 - sizeofBits;
            current = current >> (32 - sizeofBits);
            stream << std::hex << current;
            stream << std::hex << number[2];
            stream << std::hex << number[3];
            stream << std::hex << number[4];
        }
        else if (sizeofBits != 0 && sizeofBits < 160) {
            current = number[0];
            sizeofBits -= 128;
            current = current << 32 - sizeofBits;
            current = current >> (32 - sizeofBits);
            stream << std::hex << current;
            for (int i = 1; i < 5; i++) {
                stream << std::hex << number[i];
            }
        }
        else if (sizeofBits != 0) {
            for (int i = 0; i < 5; i++) {
                stream << std::hex << number[i];

            }
        }
        int length = stream.str().length();
        std::stringstream stream2;
        while (stream2.str().length() < 40 - length)
            stream2 << 0;
        stream2 << stream.str();
        return Bigint_160(stream2.str());
    }
    std::string to_string() {
        std::stringstream stream;
        for (int i = 0; i < 5; i++) {
            stream << std::hex << number[i];
        }
        return stream.str();
    }
};

int main() {
    std::string number = "1a6c5bf62d42cb2853a3698bb42098c1d296f2a4";
    Bigint_160 b1(number);
    b1.PrintBigint_160();
    int sizeofBits;
    std::stringstream stream;
    std::cout << "PLease enter size of identifier space\n";
    std::cin >> sizeofBits;
    Bigint_160 b3 =  b1 % sizeofBits;
    b3.PrintBigint_160();
    std::cout << b3.to_string();
}
