#ifndef CHECKSUM_HPP
#define CHECKSUM_HPP
#include <iostream>
#include <string>

using namespace std;
extern int block_size;

namespace checksum {
    class ChksumWorker {
        private:
            int block_size;
            char* file;
        public:
            ChksumWorker():block_size(0),file(nullptr){}
            ChksumWorker(int val, char* add):block_size(val),file(add) {}
            unsigned long rolling_chksum1(const string &file_block, int k, int l, unsigned long num1, unsigned long num2);
            unsigned long rolling_chksum2();
            string md5_checksum(const string &file_block);
}

