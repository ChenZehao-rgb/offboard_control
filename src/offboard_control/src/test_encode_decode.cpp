#include <iostream>
#include <cmath>
#include <iomanip>
#include <string>

// test encode and decode functions
// g++ -o test_encode_decode test_encode_decode.cpp
// ./test_encode_decode
float encode(float num1, float num2) {
    // 获取符号
    int sign;
    if (num1 >= 0 && num2 >= 0) {
        sign = 1;
    } else if (num1 >= 0 && num2 < 0) {
        sign = 2;
    } else if (num1 < 0 && num2 >= 0) {
        sign = 3;
    } else {
        sign = 4;
    }

    // 获取绝对值并去掉小数点
    int abs_num1 = static_cast<int>(std::round(std::abs(num1) * 100));
    int abs_num2 = static_cast<int>(std::round(std::abs(num2) * 100));

    // 组合结果
    std::string combined = std::to_string(sign) + 
                           std::to_string(abs_num1) + "." + 
                           std::to_string(abs_num2);

    return std::stof(combined);
}

void decode(float combined, float& num1, float& num2) {
    // 将float转换为字符串
    std::string combined_str = std::to_string(combined);

    // 提取符号
    int sign = combined_str[0] - '0';

    // 提取数值部分
    size_t dot_pos = combined_str.find('.');
    int abs_num1 = std::stoi(combined_str.substr(1, dot_pos - 1));
    int abs_num2 = std::stoi(combined_str.substr(dot_pos + 1, 2)); // 只取两位小数

    // 计算浮点数
    switch (sign) {
        case 1:
            num1 = abs_num1 / 100.0f;
            num2 = abs_num2 / 100.0f;
            break;
        case 2:
            num1 = abs_num1 / 100.0f;
            num2 = -abs_num2 / 100.0f;
            break;
        case 3:
            num1 = -abs_num1 / 100.0f;
            num2 = abs_num2 / 100.0f;
            break;
        case 4:
            num1 = -abs_num1 / 100.0f;
            num2 = -abs_num2 / 100.0f;
            break;
    }
}

int main() {
    float num1 = 0.23f;
    float num2 = -0.88f;

    float encoded = encode(num1, num2);
    std::cout << "Encoded: " << encoded << std::endl;

    float decoded_num1, decoded_num2;
    decode(encoded, decoded_num1, decoded_num2);
    std::cout << "Decoded num1: " << std::fixed << std::setprecision(2) << decoded_num1 << std::endl;
    std::cout << "Decoded num2: " << std::fixed << std::setprecision(2) << decoded_num2 << std::endl;

    return 0;
}