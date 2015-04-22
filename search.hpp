#ifndef SEARCH_HPP
#define SEARCH_HPP
#include <iostream>
#include <unordered_map>
#include <cmath>
#include "types.h"

namespace process {
    using namespace std;
    using namespace checksum;
    class SearchWorker {
        private:
            ChecksumWorker chkworker;
            FileWorker fworker;
            Package pworker;
            //FileDstTb is unordered_multimap<unsigned long, package_item>
            FileDstTb chksumTb;
            void init();
        public:
            SearchWorker() {init(); };
            void find();
            FileWorker getfWorker();
            void setfWorker(const FileWorker &worker); 
            Package getpworker();
            void setpworker(const PackageWorker &worker);
            ChecksumWorker getchkworker();
            void setchkworker(const ChecksumWorker &worker);
    }
}

#endif
