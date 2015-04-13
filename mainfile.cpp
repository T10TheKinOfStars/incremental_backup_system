#include <iostream>
#include <cstdlib>
#include <fstream>
#include "sepfile.hpp"

using namespace std;
using namespace file;

int main(int argc, char* argv[]) {
    if (argc < 3) {
        cout<<"you should have one arg which is string"<<endl;
        exit(-1);
    }
    
    ifstream ifs(argv[1],ios::binary);
    file::FileWorker myfile(atoi(argv[2]),atoi(argv[3]));
    myfile.setBlock(ifs);
    myfile.processBlock();
    for (int i = 0; i < myfile.getSegSize(); ++i) {
        cout<<myfile.getxFileSeg(i)<<endl;
    }

    return 0;
}

