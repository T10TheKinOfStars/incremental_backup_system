typedef i64 Timestamp

exception SystemException {
  1: optional string message
}

enum Status {
    FAIL = 0;
    SUCCESS = 1;
}

struct StatusReport {
    1: required Status status;
}

struct RFileMetadata {
    1: optional string filename
    2: optional Timestamp created;
    3: optional Timestamp updated;
    4: optional i32 version;
}

struct Filedes {
    1: optional i32 flag;
    2: optional string content;
    3: optional i32 block;
}

struct RFile {
    1: optional RFileMetadata meta;
    2: optional list<Filedes> des;
}

service SmartSync {
    StatusReport writeFile(1: RFile rfile)
        throws (1: SystemException systemException),

    RFileMetadata checkFile(1: RFileMetadata meta)
        throws (1: SystemException systemException),
}
