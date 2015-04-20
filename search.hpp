#include <iostream>
#include <unordered_map>

using namespace std;

namespace process {
    class SearchWorker {
        private:
            unordered_map<unsigned long> rollchksum;
            void init();
        public:
            SearchWorker() {init(); };
            bool find(unsigned long val);
    }
}
