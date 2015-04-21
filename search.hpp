#include <iostream>
#include <unordered_map>
#include <cmath>

using namespace std;

namespace process {
    FileWorker fworker;

    class SearchWorker {
        private:
            unordered_map<unsigned long,int> rollchksum;
            void init();
        public:
            SearchWorker() {init(); };
            bool find(unsigned long val);
    }
}
