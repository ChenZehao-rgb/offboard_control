#include <iostream>
#include <cassert>
#include <cstring>
#include <cmath>

float encodeTwoDoubles(double val1, double val2);
void decodeTwoDoubles(float encoded, double& val1, double& val2);

int main() {
    double original_val1 = 0.23;
    double original_val2 = -1.67;

    // Encode
    float encoded = encodeTwoDoubles(original_val1, original_val2);
    std::cout << "Encoded value: " << encoded << std::endl;

    // Decode
    double decoded_val1, decoded_val2;
    decodeTwoDoubles(encoded, decoded_val1, decoded_val2);

    std::cout << "Decoded values: " << decoded_val1 << ", " << decoded_val2 << std::endl;

    // Verify decoded values are close to original values
    assert(std::abs(original_val1 - decoded_val1) < 0.01);
    assert(std::abs(original_val2 - decoded_val2) < 0.01);

    std::cout << "Test passed!" << std::endl;

    return 0;
}

float encodeTwoDoubles(double val1, double val2) {
    // Scale and pack two doubles into 16 bits each
    int16_t x = static_cast<int16_t>(std::round(val1 * 100.0));
    int16_t y = static_cast<int16_t>(std::round(val2 * 100.0));
    uint32_t packed = (static_cast<uint32_t>(x) << 16) | (static_cast<uint16_t>(y));

    float result;
    std::memcpy(&result, &packed, sizeof(result));
    return result;
}

void decodeTwoDoubles(float encoded, double& val1, double& val2) {
    uint32_t packed;
    std::memcpy(&packed, &encoded, sizeof(packed));

    int16_t x = packed >> 16;
    int16_t y = packed & 0xFFFF;
    val1 = static_cast<double>(x) / 100.0;
    val2 = static_cast<double>(y) / 100.0;
}