#include "checksum.h"
#include "md5.h"
#include <string>

using namespace std;
using namespace checksum;

/*   num1 = 1, num2 = 0
 *   input is the block of file that needs to compute rolling checksum
 *   output is the rolling checksum of this block
 *   the checksum is defined by:
 *   a(k,l) = (sigma(Xi) % M;
 *   b(k,l) = (sigma(l-i+1)*Xi) % M;
 *   s(k,l) = a(k,l) + 2^16*b(k,l);
 *   M =  2^16
 */
checksum ChksumWorker::rolling_chksum1(const string &file_block, int k, int l,checksum &num1, checksum &num2) {
    checksum M = 1 << 16;

    for (int i = k; i <= l; ++i) {
        num1 += file_block[i];
        num2 += (l - i + 1) * file_block[i];
    }

    return num2 << 16 | num1;
}

/*
    a(k+1,l+1) = (a(k,l)-Xk+X(l+1)) mod M
    b(k+1,l+1) = (b(k,l)-(l-k+1)*Xk + a(k+1,l+1)) mod M
*/
checksum ChksumWorker::rolling_chksum2(checksum aprev, checksum bprev, int k, int l, char ck, char cl1, checksum &num1, checksum &num2) {
    checksum M = 1 << 16;
    num1 = (aprev - ck + cl1) % M;
    num2 = (bprev - (l-k+1) * ck + num1) % M;

    return num2 << 16 | num1;
}

string ChksumWorker::md5_checksum(const string &file_block) {
    return md5(file_block);
}
