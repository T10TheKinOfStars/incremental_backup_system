#include "search.hpp"

//init unordered_map<rollingchksum,blockNumber> rollchksum
//read all the the file blocks and add checksum to map
void SearchWorker::init() {
    int count = (int)ceil(fworker.getFileSize() / fworker.getBlockSize());
    int pos = 0;
    for (int i = 0; i < count; ++i) {
        pos *= i;
        //insert into rollchksum
}

//find the val, if found return true, else return false
bool SearchWorker::find(unsigned long val) {

}
