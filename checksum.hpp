#ifndef CHECKSUM_HPP
#define CHECKSUM_HPP
#include <iostream>
#include <string>
#include "mytypes.h"
#include "md5.h"


class ChksumWorker {
    public:
        ChksumWorker(){}
        checksum rolling_chksum1(const std::string &file_block, int k, int l, checksum &num1, checksum &num2);
        checksum rolling_chksum2(checksum aprev, checksum bprev, int k, int l, char ck, char cl1, checksum &num1, checksum &num2);
        checksum md5_chksum(const std::string &file_block);
};
#endif
