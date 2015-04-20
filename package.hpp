#ifndef PACKAGE_HPP
#define PACKAGE_HPP
#include <iostram>
#include <vector>
#include "md5.h"

namespace process {
    class Package {
        private:
            vector<unsigned long> checksums;
            unsigned long md5sum;
        public:
            Package() {};
            void fillSegs(vector<string> src);
            std::string getWholeChecksums();
            std::string getxChecksums(int idx);
            void setmd5(unsigned long val);
            unsigned long getmd5();
    };
}
#endif

