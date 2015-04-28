#ifndef PACKAGE_HPP
#define PACKAGE_HPP
#include <iostream>
#include <vector>
#include "smartSync_types.h"
#include "md5.h"
#include "mytypes.h"

using namespace std;

class Package {
    private:
        vector<Filechk> checksums;
        vector<Filedes> filedes;
    public:
        Package() {};
        ~Package();
        void initchksums(vector<Filechk> v);
        void insert2Filedes(Filedes val);
        void insert2Chksums(Filechk val);
        vector<Filechk> getchksums();
        vector<Filedes> getFiledes();
};
#endif

