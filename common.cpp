#include "common.h"

size_t getSizeOfObject(RFileMetadata data) {
    size_t sum = 0;
    sum += sizeof(data);
    sum += sizeof(char) * data.filename.size();
    sum += sizeof(char) * data.created.size();
    sum += sizeof(char) * data.updated.size();
    sum += sizeof(char) * data.contenthash.size();
    sum += sizeof(char) * data.valstr1.size();
    sum += sizeof(char) * data.valstr2.size();

    return sum;
}

size_t getSizeOfObject(Filedes data) {
    size_t sum = 0;
    sum += sizeof(data);
    sum += sizeof(char) * data.content.size();

    return sum;
}

size_t getSizeOfObject(Filechk data) {
    size_t sum = 0;
    sum += sizeof(data);
    sum += sizeof(char) * data.md5chk.size();

    return sum;
}

size_t getSizeOfObject(RFile data) {
    size_t sum = 0;
    sum += getSizeOfObject(data.meta);
    sum += sizeof(char) * data.content.size();

    return sum;
}

size_t getSizeOfObject(vector<Filechk> vdata) {
    size_t sum = 0;
    for (size_t i = 0; i < vdata.size(); ++i) 
        sum += getSizeOfObject(vdata[i]);

    return sum;
}

size_t getSizeOfObject(vector<Filedes> vdata) {
    size_t sum = 0;
    for (size_t i = 0; i < vdata.size(); ++i) 
        sum += getSizeOfObject(vdata[i]);

    return sum;
}

