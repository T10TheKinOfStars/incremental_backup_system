#include "package.hpp"

using namespace network;

void Package::fillSegs(vector<string> src) {
   for (string s : src) {
       unsigned long res = rolling_checksum(s,0,(int)s.size()-1,1,0);
       checksums.push_back(res);
   }
}

std::string Package::getWholeChecksums() {
    string str;
    stringstream ss;
    for (string s : checksums) {
        ss<<s<<",";
        str.push_back(ss.str());
        ss.str("");
    }

    str.pop_back();
    return str;
}

std::string Package::getxChecksums(int idx) {
    stringstream ss;
    ss<<checksums[idx];

    return ss.str();
}

void Package::setmd5(unsigned long val) {
    md5sum = val;
}

unsigned long Package::getmd5() {
    return md5sum;
}
