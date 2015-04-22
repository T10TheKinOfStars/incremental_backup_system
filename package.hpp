#ifndef PACKAGE_HPP
#define PACKAGE_HPP
#include <iostram>
#include <vector>
#include "md5.h"
#include "types.h"

namespace process {
    class Package {
        private:
            vector<pitem> checksums;
            vector<ritem> filedes;
        public:
            Package() {};
            void insert2Filedes(ritem val);
            void insert2Chksums(pitem val);
            vector<pitem> getchksums();
            vector<ritem> getFiledes();
    };
}
#endif

