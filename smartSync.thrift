typedef i64 Timestamp

exception SystemException {
  1: optional string message
}

enum Status {
    SAME = 0;
    NOEXIST = 1;
    OLDER = 2;
    NEWER = 3;
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
}

struct Filedes {
    1: optional i32 flag;
    2: optional string content;
    3: optional i32 block;
}

struct RFile {
    1: optional RFileMetadata meta;
    2: optional list<Filedes> des;
    3: optional string content;
    4: optional i32 flag;
}

struct NodeID {
  1: string ip;
  2: i32 port;
}

service SmartSync {
    RFile update(1: RFile rfile, 2: NodeID node)
        throws (1: SystemException systemException),

    RFile request(1: NodeID node)
        throws (1: SystemException systemException),

    RFileMetadata checkFile(1: RFileMetadata meta, 2: NodeID node)
        throws (1: SystemException systemException),
}
