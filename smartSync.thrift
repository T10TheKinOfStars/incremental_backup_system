typedef string Timestamp

exception SystemException {
  1: optional string message
}

enum Status {
    SAME = 0;
    NOEXIST = 1;
    OLDER = 2;
    NEWER = 3;
    FAIL = 4;
    SUCCESS = 5;
    BLOCK = 6;
}

struct StatusReport {
    1: required Status status;
}

struct RFileMetadata {
    1: optional string filename
    2: optional Timestamp created;
    3: optional Timestamp updated;
    4: optional i32 version;
    5: optional string contenthash;
    6: optional i32 contentLen;
    7: optional i32 target;
}

struct Filedes {
    1: optional i32 flag;
    2: optional string content;
    3: optional i32 block;
}
struct Filechk {
    1: optional i64 rollchk;
    2: optional i64 num1;
    3: optional i64 num2;
    4: optional string md5chk;
    5: optional i32 block;
}

struct RFile {
    1: optional RFileMetadata meta;
    2: optional string content;
}

/*
struct NodeID {
  1: string ip;
  2: i32 port;
}
*/

service SmartSync {
    StatusReport writeFile2Server(1:RFile rFile)
        throws (1: SystemException systemException),

    string getFileFromServer(1:string fName)
        throws (1: SystemException systemException),

    list<Filedes> updateLocal(1: list<Filechk> chks)
        throws (1: SystemException systemException),

    StatusReport updateServer(1: list<Filedes> des)
        throws (1: SystemException systemException),

    list<Filechk> request()
        throws (1: SystemException systemException),

    StatusReport checkFile(1: RFileMetadata meta)
        throws (1: SystemException systemException),
}
