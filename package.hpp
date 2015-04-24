#ifndef PACKAGE_HPP
#define PACKAGE_HPP
#include <iostram>
#include <vector>
#include "md5.h"
#include "types.h"

namespace process {
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
}
#endif

