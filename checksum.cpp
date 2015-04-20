#include "checksum.h"
#include "md5.h"
#include <string>

using namespace std;
using namespace checksum;

/*
 *   input is the block of file that needs to compute rolling checksum
 *   output is the rolling checksum of this block
 *   the checksum is defined by:
 *   a(k,l) = (sigma(Xi) % M;
 *   b(k,l) = (sigma(l-i+1)*Xi) % M;
 *   s(k,l) = a(k,l) + 2^16*b(k,l);
 *   M =  2^16
 */
unsigned long ChksumWorker::rolling_chksum1(const string &file_block, int k, int l,unsigned long num1, unsigned long num2) {
    unsigned long M = 1 << 16;

    for (int i = k; i <= l; ++i) {
        num1 += file_block[i];
        num2 += (l - i + 1) * file_block[i];
    }

    return num2 << 16 | num1;
}

unsigned long ChksumWorker::rolling_chksum2() {

}

string ChksumWorker::md5_checksum(const string &file_block) {
    return md5(file_block);
}
