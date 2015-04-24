#include "package.hpp"

Package::~Package() {
    checksums.clear();
    filedes.clear();
}

void Package::insert2Filedes(Filedes val) {
    filedes.push_back(val);
}

void Package::insert2Chksums(Filechk val) {
    checksums.push_back(val);
}

vector<Filechk> Package::getchksums() {
    return checksums;
}

vector<Filedes> Package::getFiledes() {
    return filedes;
}

void Package::initchksums(vector<Filechk> v) {
    checksums = v;
}
