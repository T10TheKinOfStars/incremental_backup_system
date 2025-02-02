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
void SearchWorker::init(vector<Filechk> v) {
    //根据B发来的package来构建hashtable
    //vector<Filechk> v = pworker->getchksums();
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
    dprintf("blocksize: %d filesize: %d\n",bsize,fsize);
    string literal = "";

    while (i < fsize) {
        string blockstr = fworker->getBlock(i);
        checksum aprev = 0;
        checksum bprev = 0;
        checksum a = 1;
        checksum b = 0;
        checksum brollstr;
        //int l = i;
        int len;
        if (bsize > fsize - i)
            len = fsize - i - 1;
        else
            len = bsize - 1;
        //cout<<"blockstr is "<<blockstr<<endl;
        //cout<<"k is "<<i<<" l is "<<i+len<<endl;
        if (!roll) 
            brollstr = chkworker->rolling_chksum1(blockstr,i,i+len,a,b);
        else
            brollstr = chkworker->rolling_chksum2(aprev,bprev,i-1,i+len-1,fworker->getxChar(i-1),fworker->getxChar(i+len),a,b);
        //cout<<"computed rolling check is "<<brollstr<<endl;
        int bNum = -1;
        //find 1 level
        //cout<<"lv 1\n";
        auto it = chksumTb.find(brollstr);
        int num = chksumTb.count(brollstr);
        //cout<<"there are "<<num<<" "<<brollstr<<" in hashtable"<<endl;
        int j = 0;
        for (; j < num; ++j, ++it) {
            flag = false;
            //find 2 level, 有可能是不同key散落到了同一个地方
            //cout<<"in lv 2"<<endl;
            checksum rchk = it->second.rollchk;
            if (rchk == brollstr) {
                //find 3 level
                //cout<<"in lv 3\n";
                string mchk = it->second.md5chk;
                //cout<<"md5 in hashtable is "<<it->second.md5chk<<" md5 of fileblock is "<<chkworker->md5_chksum(blockstr)<<endl;
                if(mchk == chkworker->md5_chksum(blockstr)) {
                    bNum = it -> second.block;
                    i += bsize;
                    break;
                }
            }
        }
        if (j == num) {
            //not find in hashtable, need rolling
            flag = true;
            ++i;
        }
        if (flag) {
            //rolling and add char to literal
            literal.push_back(fworker->getxChar(i));
            aprev = a;
            bprev = b;
        } else {
            //first add literal to des
            if (literal.size() > 0) {
                Filedes stritem;
                stritem.__set_flag(0);
                stritem.__set_content(literal);
                stritem.__set_block(-1);
                pworker->insert2Filedes(stritem);
                literal = "";
            }
            //second process block
            Filedes bitem;
            bitem.__set_flag(1);
            bitem.__set_content("");
            bitem.__set_block(bNum);
            
            pworker->insert2Filedes(bitem);
        }
        //cout<<i<<endl;
    }
    //in case of add at the end of file or filesize is less than block size
    if (literal.size() > 0) {
        Filedes stritem;
        stritem.__set_flag(0);
        stritem.__set_content(literal);
        stritem.__set_block(-1);
        pworker->insert2Filedes(stritem);
        literal = "";
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
