#include "search.hpp"

using namespace std;

SearchWorker::SearchWorker() {
    chkworker = NULL;
    fworker = NULL;
    pworker = NULL;
}

SearchWorker::SearchWorker(ChksumWorker *chkval, FileWorker *fval, Package *pval) {
    chkworker = chkval;
    fworker = fval;
    pworker = pval;
}

//init unordered_map<rollingchksum,blockNumber> rollchksum
//read all the the file blocks and add checksum to map
void SearchWorker::init() {
    //根据B发来的package来构建hashtable
    vector<Filechk> v = pworker->getchksums();
    for (int i = 0; i < (int)v.size(); ++i) {
        pair<checksum,Filechk> mypair(v[i].rollchk,v[i]);
        chksumTb.insert(mypair);
    }
}

//find the val, if found return true, else return false
//if return false, means we should check next block
void SearchWorker::find() {
    int i = 0;
    //flag turn to false when finding block in hashtable
    //flag turn to true when not finding block in hashtable
    bool flag = true;
    //when needs rolling, roll is true
    //else false
    bool roll = false;
    int bsize = fworker->getBlockSize();
    int fsize = fworker->getFileSize();
    string literal = "";

    while (i < fsize) {
        string blockstr = fworker->getBlock(i);
        checksum aprev = 0;
        checksum bprev = 0;
        checksum a = 1;
        checksum b = 0;
        checksum brollstr;
        int l = i;
        if (bsize > fsize - i)
            l = fsize-1;
        else
            l += bsize;

        if (!roll) 
            brollstr = chkworker->rolling_chksum1(blockstr,i,l,a,b);
        else
            brollstr = chkworker->rolling_chksum2(aprev,bprev,i-1,l-1,fworker->getxChar(i-1),fworker->getxChar(l),a,b);

        int bNum = -1;
        //find 1 level
        auto it = chksumTb.find(brollstr);
        int num = chksumTb.count(brollstr);
        int j = 0;
        for (; j < num; ++j, ++it) {
            flag = false;
                //find 2 level, 有可能是不同key散落到了同一个地方
            checksum rchk = it->second.rollchk;
            if (rchk == brollstr) {
                    //find 3 level
                string mchk = it->second.md5chk;
                if(mchk == chkworker->md5_chksum(blockstr)) {
                    bNum = it -> second.block;
                    i += bsize;
                    break;
                }
            }
        }
        if (j == num) {
            flag = true;
            ++i;
        }
        if (flag) {
            literal.push_back(fworker->getxChar(i));
            aprev = a;
            bprev = b;
        } else {
            if (literal.size() > 0) {
                Filedes stritem;
                stritem.__set_flag(0);
                stritem.__set_content(literal);
                stritem.__set_block(0);
                
                pworker->insert2Filedes(stritem);
                literal = "";
            }
            Filedes bitem;
            bitem.__set_flag(1);
            bitem.__set_content("");
            bitem.__set_block(bNum);
            
            pworker->insert2Filedes(bitem);
        }
    }
}



FileWorker* SearchWorker::getfWorker() {
    return fworker;
}

void SearchWorker::setfWorker(FileWorker *worker) {
    fworker = worker;
}

Package* SearchWorker::getpworker() {
    return pworker;
}

void SearchWorker::setpworker(Package *worker) {
    pworker = worker;
}

ChksumWorker* SearchWorker::getchkworker() {
    return chkworker;
}

void SearchWorker::setchkworker(ChksumWorker *worker) {
    chkworker = worker;
}
