#ifndef TYPES_H
#define TYPES_H
#include <unordered_map>
#include <iostream>
#include "smartSync_types.h"

typedef unsigned long checksum;
typedef unordered_multimap<unsigned long,package_item> FileDstTb;
typedef std::map<std::string, RFileMetadata> NameDataMap;
/*
typedef struct package_item {          
    checksum s;
    checksum a;
    checksum b;
    checksum md5sum;
    int blockNum;
    packate_item(checksum roll, checksum num1, checksum num2, checksum md5s, int bNum): s(roll), a(num1), b(num2), md5sum(md5s), blockNum(bNum) {}
} pitem;

typedef struct respond_item {
    int isblock;
    string content;
    int blockNum;
    respond_item(int val, string str, int bNum):isblock(val),content(str), blockNum(bNum) {}
} ritem;
*/
#endif
