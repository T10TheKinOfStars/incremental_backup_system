#ifndef SEARCH_HPP
#define SEARCH_HPP
#include <iostream>
#include <unordered_map>
#include <cmath>
#include <algorithm>
#include "mytypes.h"
#include "checksum.hpp"
#include "file.hpp"
#include "package.hpp"
#include "smartSync_types.h"

using namespace std;
class SearchWorker {
    private:
        ChksumWorker chkworker;
        FileWorker fworker;
        Package pworker;
        //FileDstTb is unordered_multimap<unsigned long, package_item>
        FileDstTb chksumTb;
    public:
        void init();
        void find();
        FileWorker getfWorker();
        void setfWorker(const FileWorker &worker); 
        Package getpworker();
        void setpworker(const Package &worker);
        ChksumWorker getchkworker();
        void setchkworker(const ChksumWorker &worker);
};

#endif
