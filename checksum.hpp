#ifndef CHECKSUM_HPP
#define CHECKSUM_HPP
#include <iostream>
#include <string>
#include "types.h"

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
            checksum rolling_chksum1(const string &file_block, int k, int l, checksum &num1, checksum &num2);
            checksum rolling_chksum2(checksum aprev, checksum bprev, int k, int l, char ck, char cl1, checksum &num1, checksum &num2);
            string md5_chksum(const string &file_block);
}

