#ifndef CHECKSUM_HPP
#define CHECKSUM_HPP
#include <iostream>
#include <string>

extern int block_size;

namespace utility {
    unsigned long rolling_checksum(const std::string &file_block, int k, int l, unsigned long num1, unsigned long num2);
    std::string md5_checksum(const std::string &file_block);
}

