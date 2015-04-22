#include "package.hpp"

Package::~Package() {
    checksums.clear();
    filedes.clear();
}

void Package::insert2Filedes(ritem val) {
    filedes.push_back(val);
}

void Package::insert2Chksums(pitem val) {
    checksums.push_back(val);
}

vector<pitem> Package::getchksums() {
    return checksums;
}

vector<ritem> getFiledes() {
    return filedes;
}
