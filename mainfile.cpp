#include <iostream>
#include <cstdlib>
#include "sepfile.hpp"

using namespace std;
using namespace file;

int main(int argc, char* argv[]) {
    if (argc < 1) {
        cout<<"you should have one arg which is string"<<endl;
        exit(-1);
    }

    file::FileWorker myfile(argv[1],2);
    myfile.processFile();
    for (int i = 0; i < myfile.getBlockSize(); ++i) {
        cout<<myfile.getxFileBlock(i)<<endl;
    }

    return 0;
}

