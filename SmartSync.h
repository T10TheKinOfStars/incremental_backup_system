/**
 * Autogenerated by Thrift Compiler (0.9.2)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#ifndef SmartSync_H
#define SmartSync_H

#include <thrift/TDispatchProcessor.h>
#include "smartSync_types.h"



class SmartSyncIf {
 public:
  virtual ~SmartSyncIf() {}
  virtual void writeFile2Server(StatusReport& _return, const RFile& rFile) = 0;
  virtual void getFileFromServer(std::string& _return, const std::string& fName) = 0;
  virtual void updateLocal(std::vector<Filedes> & _return, const std::vector<Filechk> & chks) = 0;
  virtual void updateServer(StatusReport& _return, const std::vector<Filedes> & des) = 0;
  virtual void request(std::vector<Filechk> & _return) = 0;
  virtual void checkFile(StatusReport& _return, const RFileMetadata& meta) = 0;
};

class SmartSyncIfFactory {
 public:
  typedef SmartSyncIf Handler;

  virtual ~SmartSyncIfFactory() {}

  virtual SmartSyncIf* getHandler(const ::apache::thrift::TConnectionInfo& connInfo) = 0;
  virtual void releaseHandler(SmartSyncIf* /* handler */) = 0;
};

class SmartSyncIfSingletonFactory : virtual public SmartSyncIfFactory {
 public:
  SmartSyncIfSingletonFactory(const boost::shared_ptr<SmartSyncIf>& iface) : iface_(iface) {}
  virtual ~SmartSyncIfSingletonFactory() {}

  virtual SmartSyncIf* getHandler(const ::apache::thrift::TConnectionInfo&) {
    return iface_.get();
  }
  virtual void releaseHandler(SmartSyncIf* /* handler */) {}

 protected:
  boost::shared_ptr<SmartSyncIf> iface_;
};

class SmartSyncNull : virtual public SmartSyncIf {
 public:
  virtual ~SmartSyncNull() {}
  void writeFile2Server(StatusReport& /* _return */, const RFile& /* rFile */) {
    return;
  }
  void getFileFromServer(std::string& /* _return */, const std::string& /* fName */) {
    return;
  }
  void updateLocal(std::vector<Filedes> & /* _return */, const std::vector<Filechk> & /* chks */) {
    return;
  }
  void updateServer(StatusReport& /* _return */, const std::vector<Filedes> & /* des */) {
    return;
  }
  void request(std::vector<Filechk> & /* _return */) {
    return;
  }
  void checkFile(StatusReport& /* _return */, const RFileMetadata& /* meta */) {
    return;
  }
};

typedef struct _SmartSync_writeFile2Server_args__isset {
  _SmartSync_writeFile2Server_args__isset() : rFile(false) {}
  bool rFile :1;
} _SmartSync_writeFile2Server_args__isset;

class SmartSync_writeFile2Server_args {
 public:

  static const char* ascii_fingerprint; // = "C7DD2B168C6B40342A46B9F708FA713A";
  static const uint8_t binary_fingerprint[16]; // = {0xC7,0xDD,0x2B,0x16,0x8C,0x6B,0x40,0x34,0x2A,0x46,0xB9,0xF7,0x08,0xFA,0x71,0x3A};

  SmartSync_writeFile2Server_args(const SmartSync_writeFile2Server_args&);
  SmartSync_writeFile2Server_args& operator=(const SmartSync_writeFile2Server_args&);
  SmartSync_writeFile2Server_args() {
  }

  virtual ~SmartSync_writeFile2Server_args() throw();
  RFile rFile;

  _SmartSync_writeFile2Server_args__isset __isset;

  void __set_rFile(const RFile& val);

  bool operator == (const SmartSync_writeFile2Server_args & rhs) const
  {
    if (!(rFile == rhs.rFile))
      return false;
    return true;
  }
  bool operator != (const SmartSync_writeFile2Server_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const SmartSync_writeFile2Server_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  friend std::ostream& operator<<(std::ostream& out, const SmartSync_writeFile2Server_args& obj);
};


class SmartSync_writeFile2Server_pargs {
 public:

  static const char* ascii_fingerprint; // = "C7DD2B168C6B40342A46B9F708FA713A";
  static const uint8_t binary_fingerprint[16]; // = {0xC7,0xDD,0x2B,0x16,0x8C,0x6B,0x40,0x34,0x2A,0x46,0xB9,0xF7,0x08,0xFA,0x71,0x3A};


  virtual ~SmartSync_writeFile2Server_pargs() throw();
  const RFile* rFile;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  friend std::ostream& operator<<(std::ostream& out, const SmartSync_writeFile2Server_pargs& obj);
};

typedef struct _SmartSync_writeFile2Server_result__isset {
  _SmartSync_writeFile2Server_result__isset() : success(false), systemException(false) {}
  bool success :1;
  bool systemException :1;
} _SmartSync_writeFile2Server_result__isset;

class SmartSync_writeFile2Server_result {
 public:

  static const char* ascii_fingerprint; // = "3FF585046B57CAB37B1AE9B1FE6EDD6F";
  static const uint8_t binary_fingerprint[16]; // = {0x3F,0xF5,0x85,0x04,0x6B,0x57,0xCA,0xB3,0x7B,0x1A,0xE9,0xB1,0xFE,0x6E,0xDD,0x6F};

  SmartSync_writeFile2Server_result(const SmartSync_writeFile2Server_result&);
  SmartSync_writeFile2Server_result& operator=(const SmartSync_writeFile2Server_result&);
  SmartSync_writeFile2Server_result() {
  }

  virtual ~SmartSync_writeFile2Server_result() throw();
  StatusReport success;
  SystemException systemException;

  _SmartSync_writeFile2Server_result__isset __isset;

  void __set_success(const StatusReport& val);

  void __set_systemException(const SystemException& val);

  bool operator == (const SmartSync_writeFile2Server_result & rhs) const
  {
    if (!(success == rhs.success))
      return false;
    if (!(systemException == rhs.systemException))
      return false;
    return true;
  }
  bool operator != (const SmartSync_writeFile2Server_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const SmartSync_writeFile2Server_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  friend std::ostream& operator<<(std::ostream& out, const SmartSync_writeFile2Server_result& obj);
};

typedef struct _SmartSync_writeFile2Server_presult__isset {
  _SmartSync_writeFile2Server_presult__isset() : success(false), systemException(false) {}
  bool success :1;
  bool systemException :1;
} _SmartSync_writeFile2Server_presult__isset;

class SmartSync_writeFile2Server_presult {
 public:

  static const char* ascii_fingerprint; // = "3FF585046B57CAB37B1AE9B1FE6EDD6F";
  static const uint8_t binary_fingerprint[16]; // = {0x3F,0xF5,0x85,0x04,0x6B,0x57,0xCA,0xB3,0x7B,0x1A,0xE9,0xB1,0xFE,0x6E,0xDD,0x6F};


  virtual ~SmartSync_writeFile2Server_presult() throw();
  StatusReport* success;
  SystemException systemException;

  _SmartSync_writeFile2Server_presult__isset __isset;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

  friend std::ostream& operator<<(std::ostream& out, const SmartSync_writeFile2Server_presult& obj);
};

typedef struct _SmartSync_getFileFromServer_args__isset {
  _SmartSync_getFileFromServer_args__isset() : fName(false) {}
  bool fName :1;
} _SmartSync_getFileFromServer_args__isset;

class SmartSync_getFileFromServer_args {
 public:

  static const char* ascii_fingerprint; // = "EFB929595D312AC8F305D5A794CFEDA1";
  static const uint8_t binary_fingerprint[16]; // = {0xEF,0xB9,0x29,0x59,0x5D,0x31,0x2A,0xC8,0xF3,0x05,0xD5,0xA7,0x94,0xCF,0xED,0xA1};

  SmartSync_getFileFromServer_args(const SmartSync_getFileFromServer_args&);
  SmartSync_getFileFromServer_args& operator=(const SmartSync_getFileFromServer_args&);
  SmartSync_getFileFromServer_args() : fName() {
  }

  virtual ~SmartSync_getFileFromServer_args() throw();
  std::string fName;

  _SmartSync_getFileFromServer_args__isset __isset;

  void __set_fName(const std::string& val);

  bool operator == (const SmartSync_getFileFromServer_args & rhs) const
  {
    if (!(fName == rhs.fName))
      return false;
    return true;
  }
  bool operator != (const SmartSync_getFileFromServer_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const SmartSync_getFileFromServer_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  friend std::ostream& operator<<(std::ostream& out, const SmartSync_getFileFromServer_args& obj);
};


class SmartSync_getFileFromServer_pargs {
 public:

  static const char* ascii_fingerprint; // = "EFB929595D312AC8F305D5A794CFEDA1";
  static const uint8_t binary_fingerprint[16]; // = {0xEF,0xB9,0x29,0x59,0x5D,0x31,0x2A,0xC8,0xF3,0x05,0xD5,0xA7,0x94,0xCF,0xED,0xA1};


  virtual ~SmartSync_getFileFromServer_pargs() throw();
  const std::string* fName;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  friend std::ostream& operator<<(std::ostream& out, const SmartSync_getFileFromServer_pargs& obj);
};

typedef struct _SmartSync_getFileFromServer_result__isset {
  _SmartSync_getFileFromServer_result__isset() : success(false), systemException(false) {}
  bool success :1;
  bool systemException :1;
} _SmartSync_getFileFromServer_result__isset;

class SmartSync_getFileFromServer_result {
 public:

  static const char* ascii_fingerprint; // = "2686E5359AB385D9E421AC147E1B296E";
  static const uint8_t binary_fingerprint[16]; // = {0x26,0x86,0xE5,0x35,0x9A,0xB3,0x85,0xD9,0xE4,0x21,0xAC,0x14,0x7E,0x1B,0x29,0x6E};

  SmartSync_getFileFromServer_result(const SmartSync_getFileFromServer_result&);
  SmartSync_getFileFromServer_result& operator=(const SmartSync_getFileFromServer_result&);
  SmartSync_getFileFromServer_result() : success() {
  }

  virtual ~SmartSync_getFileFromServer_result() throw();
  std::string success;
  SystemException systemException;

  _SmartSync_getFileFromServer_result__isset __isset;

  void __set_success(const std::string& val);

  void __set_systemException(const SystemException& val);

  bool operator == (const SmartSync_getFileFromServer_result & rhs) const
  {
    if (!(success == rhs.success))
      return false;
    if (!(systemException == rhs.systemException))
      return false;
    return true;
  }
  bool operator != (const SmartSync_getFileFromServer_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const SmartSync_getFileFromServer_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  friend std::ostream& operator<<(std::ostream& out, const SmartSync_getFileFromServer_result& obj);
};

typedef struct _SmartSync_getFileFromServer_presult__isset {
  _SmartSync_getFileFromServer_presult__isset() : success(false), systemException(false) {}
  bool success :1;
  bool systemException :1;
} _SmartSync_getFileFromServer_presult__isset;

class SmartSync_getFileFromServer_presult {
 public:

  static const char* ascii_fingerprint; // = "2686E5359AB385D9E421AC147E1B296E";
  static const uint8_t binary_fingerprint[16]; // = {0x26,0x86,0xE5,0x35,0x9A,0xB3,0x85,0xD9,0xE4,0x21,0xAC,0x14,0x7E,0x1B,0x29,0x6E};


  virtual ~SmartSync_getFileFromServer_presult() throw();
  std::string* success;
  SystemException systemException;

  _SmartSync_getFileFromServer_presult__isset __isset;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

  friend std::ostream& operator<<(std::ostream& out, const SmartSync_getFileFromServer_presult& obj);
};

typedef struct _SmartSync_updateLocal_args__isset {
  _SmartSync_updateLocal_args__isset() : chks(false) {}
  bool chks :1;
} _SmartSync_updateLocal_args__isset;

class SmartSync_updateLocal_args {
 public:

  static const char* ascii_fingerprint; // = "19B1BAC76D5A4185FBFD1EBC175F219E";
  static const uint8_t binary_fingerprint[16]; // = {0x19,0xB1,0xBA,0xC7,0x6D,0x5A,0x41,0x85,0xFB,0xFD,0x1E,0xBC,0x17,0x5F,0x21,0x9E};

  SmartSync_updateLocal_args(const SmartSync_updateLocal_args&);
  SmartSync_updateLocal_args& operator=(const SmartSync_updateLocal_args&);
  SmartSync_updateLocal_args() {
  }

  virtual ~SmartSync_updateLocal_args() throw();
  std::vector<Filechk>  chks;

  _SmartSync_updateLocal_args__isset __isset;

  void __set_chks(const std::vector<Filechk> & val);

  bool operator == (const SmartSync_updateLocal_args & rhs) const
  {
    if (!(chks == rhs.chks))
      return false;
    return true;
  }
  bool operator != (const SmartSync_updateLocal_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const SmartSync_updateLocal_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  friend std::ostream& operator<<(std::ostream& out, const SmartSync_updateLocal_args& obj);
};


class SmartSync_updateLocal_pargs {
 public:

  static const char* ascii_fingerprint; // = "19B1BAC76D5A4185FBFD1EBC175F219E";
  static const uint8_t binary_fingerprint[16]; // = {0x19,0xB1,0xBA,0xC7,0x6D,0x5A,0x41,0x85,0xFB,0xFD,0x1E,0xBC,0x17,0x5F,0x21,0x9E};


  virtual ~SmartSync_updateLocal_pargs() throw();
  const std::vector<Filechk> * chks;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  friend std::ostream& operator<<(std::ostream& out, const SmartSync_updateLocal_pargs& obj);
};

typedef struct _SmartSync_updateLocal_result__isset {
  _SmartSync_updateLocal_result__isset() : success(false), systemException(false) {}
  bool success :1;
  bool systemException :1;
} _SmartSync_updateLocal_result__isset;

class SmartSync_updateLocal_result {
 public:

  static const char* ascii_fingerprint; // = "0708DD83212BFC89AE61A1CDBD89F832";
  static const uint8_t binary_fingerprint[16]; // = {0x07,0x08,0xDD,0x83,0x21,0x2B,0xFC,0x89,0xAE,0x61,0xA1,0xCD,0xBD,0x89,0xF8,0x32};

  SmartSync_updateLocal_result(const SmartSync_updateLocal_result&);
  SmartSync_updateLocal_result& operator=(const SmartSync_updateLocal_result&);
  SmartSync_updateLocal_result() {
  }

  virtual ~SmartSync_updateLocal_result() throw();
  std::vector<Filedes>  success;
  SystemException systemException;

  _SmartSync_updateLocal_result__isset __isset;

  void __set_success(const std::vector<Filedes> & val);

  void __set_systemException(const SystemException& val);

  bool operator == (const SmartSync_updateLocal_result & rhs) const
  {
    if (!(success == rhs.success))
      return false;
    if (!(systemException == rhs.systemException))
      return false;
    return true;
  }
  bool operator != (const SmartSync_updateLocal_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const SmartSync_updateLocal_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  friend std::ostream& operator<<(std::ostream& out, const SmartSync_updateLocal_result& obj);
};

typedef struct _SmartSync_updateLocal_presult__isset {
  _SmartSync_updateLocal_presult__isset() : success(false), systemException(false) {}
  bool success :1;
  bool systemException :1;
} _SmartSync_updateLocal_presult__isset;

class SmartSync_updateLocal_presult {
 public:

  static const char* ascii_fingerprint; // = "0708DD83212BFC89AE61A1CDBD89F832";
  static const uint8_t binary_fingerprint[16]; // = {0x07,0x08,0xDD,0x83,0x21,0x2B,0xFC,0x89,0xAE,0x61,0xA1,0xCD,0xBD,0x89,0xF8,0x32};


  virtual ~SmartSync_updateLocal_presult() throw();
  std::vector<Filedes> * success;
  SystemException systemException;

  _SmartSync_updateLocal_presult__isset __isset;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

  friend std::ostream& operator<<(std::ostream& out, const SmartSync_updateLocal_presult& obj);
};

typedef struct _SmartSync_updateServer_args__isset {
  _SmartSync_updateServer_args__isset() : des(false) {}
  bool des :1;
} _SmartSync_updateServer_args__isset;

class SmartSync_updateServer_args {
 public:

  static const char* ascii_fingerprint; // = "B2B8C604CBD25F8DA59BB142404EDAE2";
  static const uint8_t binary_fingerprint[16]; // = {0xB2,0xB8,0xC6,0x04,0xCB,0xD2,0x5F,0x8D,0xA5,0x9B,0xB1,0x42,0x40,0x4E,0xDA,0xE2};

  SmartSync_updateServer_args(const SmartSync_updateServer_args&);
  SmartSync_updateServer_args& operator=(const SmartSync_updateServer_args&);
  SmartSync_updateServer_args() {
  }

  virtual ~SmartSync_updateServer_args() throw();
  std::vector<Filedes>  des;

  _SmartSync_updateServer_args__isset __isset;

  void __set_des(const std::vector<Filedes> & val);

  bool operator == (const SmartSync_updateServer_args & rhs) const
  {
    if (!(des == rhs.des))
      return false;
    return true;
  }
  bool operator != (const SmartSync_updateServer_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const SmartSync_updateServer_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  friend std::ostream& operator<<(std::ostream& out, const SmartSync_updateServer_args& obj);
};


class SmartSync_updateServer_pargs {
 public:

  static const char* ascii_fingerprint; // = "B2B8C604CBD25F8DA59BB142404EDAE2";
  static const uint8_t binary_fingerprint[16]; // = {0xB2,0xB8,0xC6,0x04,0xCB,0xD2,0x5F,0x8D,0xA5,0x9B,0xB1,0x42,0x40,0x4E,0xDA,0xE2};


  virtual ~SmartSync_updateServer_pargs() throw();
  const std::vector<Filedes> * des;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  friend std::ostream& operator<<(std::ostream& out, const SmartSync_updateServer_pargs& obj);
};

typedef struct _SmartSync_updateServer_result__isset {
  _SmartSync_updateServer_result__isset() : success(false), systemException(false) {}
  bool success :1;
  bool systemException :1;
} _SmartSync_updateServer_result__isset;

class SmartSync_updateServer_result {
 public:

  static const char* ascii_fingerprint; // = "3FF585046B57CAB37B1AE9B1FE6EDD6F";
  static const uint8_t binary_fingerprint[16]; // = {0x3F,0xF5,0x85,0x04,0x6B,0x57,0xCA,0xB3,0x7B,0x1A,0xE9,0xB1,0xFE,0x6E,0xDD,0x6F};

  SmartSync_updateServer_result(const SmartSync_updateServer_result&);
  SmartSync_updateServer_result& operator=(const SmartSync_updateServer_result&);
  SmartSync_updateServer_result() {
  }

  virtual ~SmartSync_updateServer_result() throw();
  StatusReport success;
  SystemException systemException;

  _SmartSync_updateServer_result__isset __isset;

  void __set_success(const StatusReport& val);

  void __set_systemException(const SystemException& val);

  bool operator == (const SmartSync_updateServer_result & rhs) const
  {
    if (!(success == rhs.success))
      return false;
    if (!(systemException == rhs.systemException))
      return false;
    return true;
  }
  bool operator != (const SmartSync_updateServer_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const SmartSync_updateServer_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  friend std::ostream& operator<<(std::ostream& out, const SmartSync_updateServer_result& obj);
};

typedef struct _SmartSync_updateServer_presult__isset {
  _SmartSync_updateServer_presult__isset() : success(false), systemException(false) {}
  bool success :1;
  bool systemException :1;
} _SmartSync_updateServer_presult__isset;

class SmartSync_updateServer_presult {
 public:

  static const char* ascii_fingerprint; // = "3FF585046B57CAB37B1AE9B1FE6EDD6F";
  static const uint8_t binary_fingerprint[16]; // = {0x3F,0xF5,0x85,0x04,0x6B,0x57,0xCA,0xB3,0x7B,0x1A,0xE9,0xB1,0xFE,0x6E,0xDD,0x6F};


  virtual ~SmartSync_updateServer_presult() throw();
  StatusReport* success;
  SystemException systemException;

  _SmartSync_updateServer_presult__isset __isset;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

  friend std::ostream& operator<<(std::ostream& out, const SmartSync_updateServer_presult& obj);
};


class SmartSync_request_args {
 public:

  static const char* ascii_fingerprint; // = "99914B932BD37A50B983C5E7C90AE93B";
  static const uint8_t binary_fingerprint[16]; // = {0x99,0x91,0x4B,0x93,0x2B,0xD3,0x7A,0x50,0xB9,0x83,0xC5,0xE7,0xC9,0x0A,0xE9,0x3B};

  SmartSync_request_args(const SmartSync_request_args&);
  SmartSync_request_args& operator=(const SmartSync_request_args&);
  SmartSync_request_args() {
  }

  virtual ~SmartSync_request_args() throw();

  bool operator == (const SmartSync_request_args & /* rhs */) const
  {
    return true;
  }
  bool operator != (const SmartSync_request_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const SmartSync_request_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  friend std::ostream& operator<<(std::ostream& out, const SmartSync_request_args& obj);
};


class SmartSync_request_pargs {
 public:

  static const char* ascii_fingerprint; // = "99914B932BD37A50B983C5E7C90AE93B";
  static const uint8_t binary_fingerprint[16]; // = {0x99,0x91,0x4B,0x93,0x2B,0xD3,0x7A,0x50,0xB9,0x83,0xC5,0xE7,0xC9,0x0A,0xE9,0x3B};


  virtual ~SmartSync_request_pargs() throw();

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  friend std::ostream& operator<<(std::ostream& out, const SmartSync_request_pargs& obj);
};

typedef struct _SmartSync_request_result__isset {
  _SmartSync_request_result__isset() : success(false), systemException(false) {}
  bool success :1;
  bool systemException :1;
} _SmartSync_request_result__isset;

class SmartSync_request_result {
 public:

  static const char* ascii_fingerprint; // = "0C5F99E236AD40A16C475D0F9081CC33";
  static const uint8_t binary_fingerprint[16]; // = {0x0C,0x5F,0x99,0xE2,0x36,0xAD,0x40,0xA1,0x6C,0x47,0x5D,0x0F,0x90,0x81,0xCC,0x33};

  SmartSync_request_result(const SmartSync_request_result&);
  SmartSync_request_result& operator=(const SmartSync_request_result&);
  SmartSync_request_result() {
  }

  virtual ~SmartSync_request_result() throw();
  std::vector<Filechk>  success;
  SystemException systemException;

  _SmartSync_request_result__isset __isset;

  void __set_success(const std::vector<Filechk> & val);

  void __set_systemException(const SystemException& val);

  bool operator == (const SmartSync_request_result & rhs) const
  {
    if (!(success == rhs.success))
      return false;
    if (!(systemException == rhs.systemException))
      return false;
    return true;
  }
  bool operator != (const SmartSync_request_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const SmartSync_request_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  friend std::ostream& operator<<(std::ostream& out, const SmartSync_request_result& obj);
};

typedef struct _SmartSync_request_presult__isset {
  _SmartSync_request_presult__isset() : success(false), systemException(false) {}
  bool success :1;
  bool systemException :1;
} _SmartSync_request_presult__isset;

class SmartSync_request_presult {
 public:

  static const char* ascii_fingerprint; // = "0C5F99E236AD40A16C475D0F9081CC33";
  static const uint8_t binary_fingerprint[16]; // = {0x0C,0x5F,0x99,0xE2,0x36,0xAD,0x40,0xA1,0x6C,0x47,0x5D,0x0F,0x90,0x81,0xCC,0x33};


  virtual ~SmartSync_request_presult() throw();
  std::vector<Filechk> * success;
  SystemException systemException;

  _SmartSync_request_presult__isset __isset;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

  friend std::ostream& operator<<(std::ostream& out, const SmartSync_request_presult& obj);
};

typedef struct _SmartSync_checkFile_args__isset {
  _SmartSync_checkFile_args__isset() : meta(false) {}
  bool meta :1;
} _SmartSync_checkFile_args__isset;

class SmartSync_checkFile_args {
 public:

  static const char* ascii_fingerprint; // = "A852320E4AC7DBEFB567E3CBB97C6954";
  static const uint8_t binary_fingerprint[16]; // = {0xA8,0x52,0x32,0x0E,0x4A,0xC7,0xDB,0xEF,0xB5,0x67,0xE3,0xCB,0xB9,0x7C,0x69,0x54};

  SmartSync_checkFile_args(const SmartSync_checkFile_args&);
  SmartSync_checkFile_args& operator=(const SmartSync_checkFile_args&);
  SmartSync_checkFile_args() {
  }

  virtual ~SmartSync_checkFile_args() throw();
  RFileMetadata meta;

  _SmartSync_checkFile_args__isset __isset;

  void __set_meta(const RFileMetadata& val);

  bool operator == (const SmartSync_checkFile_args & rhs) const
  {
    if (!(meta == rhs.meta))
      return false;
    return true;
  }
  bool operator != (const SmartSync_checkFile_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const SmartSync_checkFile_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  friend std::ostream& operator<<(std::ostream& out, const SmartSync_checkFile_args& obj);
};


class SmartSync_checkFile_pargs {
 public:

  static const char* ascii_fingerprint; // = "A852320E4AC7DBEFB567E3CBB97C6954";
  static const uint8_t binary_fingerprint[16]; // = {0xA8,0x52,0x32,0x0E,0x4A,0xC7,0xDB,0xEF,0xB5,0x67,0xE3,0xCB,0xB9,0x7C,0x69,0x54};


  virtual ~SmartSync_checkFile_pargs() throw();
  const RFileMetadata* meta;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  friend std::ostream& operator<<(std::ostream& out, const SmartSync_checkFile_pargs& obj);
};

typedef struct _SmartSync_checkFile_result__isset {
  _SmartSync_checkFile_result__isset() : success(false), systemException(false) {}
  bool success :1;
  bool systemException :1;
} _SmartSync_checkFile_result__isset;

class SmartSync_checkFile_result {
 public:

  static const char* ascii_fingerprint; // = "3FF585046B57CAB37B1AE9B1FE6EDD6F";
  static const uint8_t binary_fingerprint[16]; // = {0x3F,0xF5,0x85,0x04,0x6B,0x57,0xCA,0xB3,0x7B,0x1A,0xE9,0xB1,0xFE,0x6E,0xDD,0x6F};

  SmartSync_checkFile_result(const SmartSync_checkFile_result&);
  SmartSync_checkFile_result& operator=(const SmartSync_checkFile_result&);
  SmartSync_checkFile_result() {
  }

  virtual ~SmartSync_checkFile_result() throw();
  StatusReport success;
  SystemException systemException;

  _SmartSync_checkFile_result__isset __isset;

  void __set_success(const StatusReport& val);

  void __set_systemException(const SystemException& val);

  bool operator == (const SmartSync_checkFile_result & rhs) const
  {
    if (!(success == rhs.success))
      return false;
    if (!(systemException == rhs.systemException))
      return false;
    return true;
  }
  bool operator != (const SmartSync_checkFile_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const SmartSync_checkFile_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  friend std::ostream& operator<<(std::ostream& out, const SmartSync_checkFile_result& obj);
};

typedef struct _SmartSync_checkFile_presult__isset {
  _SmartSync_checkFile_presult__isset() : success(false), systemException(false) {}
  bool success :1;
  bool systemException :1;
} _SmartSync_checkFile_presult__isset;

class SmartSync_checkFile_presult {
 public:

  static const char* ascii_fingerprint; // = "3FF585046B57CAB37B1AE9B1FE6EDD6F";
  static const uint8_t binary_fingerprint[16]; // = {0x3F,0xF5,0x85,0x04,0x6B,0x57,0xCA,0xB3,0x7B,0x1A,0xE9,0xB1,0xFE,0x6E,0xDD,0x6F};


  virtual ~SmartSync_checkFile_presult() throw();
  StatusReport* success;
  SystemException systemException;

  _SmartSync_checkFile_presult__isset __isset;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

  friend std::ostream& operator<<(std::ostream& out, const SmartSync_checkFile_presult& obj);
};

class SmartSyncClient : virtual public SmartSyncIf {
 public:
  SmartSyncClient(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) {
    setProtocol(prot);
  }
  SmartSyncClient(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, boost::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) {
    setProtocol(iprot,oprot);
  }
 private:
  void setProtocol(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) {
  setProtocol(prot,prot);
  }
  void setProtocol(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, boost::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) {
    piprot_=iprot;
    poprot_=oprot;
    iprot_ = iprot.get();
    oprot_ = oprot.get();
  }
 public:
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> getInputProtocol() {
    return piprot_;
  }
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> getOutputProtocol() {
    return poprot_;
  }
  void writeFile2Server(StatusReport& _return, const RFile& rFile);
  void send_writeFile2Server(const RFile& rFile);
  void recv_writeFile2Server(StatusReport& _return);
  void getFileFromServer(std::string& _return, const std::string& fName);
  void send_getFileFromServer(const std::string& fName);
  void recv_getFileFromServer(std::string& _return);
  void updateLocal(std::vector<Filedes> & _return, const std::vector<Filechk> & chks);
  void send_updateLocal(const std::vector<Filechk> & chks);
  void recv_updateLocal(std::vector<Filedes> & _return);
  void updateServer(StatusReport& _return, const std::vector<Filedes> & des);
  void send_updateServer(const std::vector<Filedes> & des);
  void recv_updateServer(StatusReport& _return);
  void request(std::vector<Filechk> & _return);
  void send_request();
  void recv_request(std::vector<Filechk> & _return);
  void checkFile(StatusReport& _return, const RFileMetadata& meta);
  void send_checkFile(const RFileMetadata& meta);
  void recv_checkFile(StatusReport& _return);
 protected:
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> piprot_;
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> poprot_;
  ::apache::thrift::protocol::TProtocol* iprot_;
  ::apache::thrift::protocol::TProtocol* oprot_;
};

class SmartSyncProcessor : public ::apache::thrift::TDispatchProcessor {
 protected:
  boost::shared_ptr<SmartSyncIf> iface_;
  virtual bool dispatchCall(::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, const std::string& fname, int32_t seqid, void* callContext);
 private:
  typedef  void (SmartSyncProcessor::*ProcessFunction)(int32_t, ::apache::thrift::protocol::TProtocol*, ::apache::thrift::protocol::TProtocol*, void*);
  typedef std::map<std::string, ProcessFunction> ProcessMap;
  ProcessMap processMap_;
  void process_writeFile2Server(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
  void process_getFileFromServer(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
  void process_updateLocal(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
  void process_updateServer(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
  void process_request(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
  void process_checkFile(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
 public:
  SmartSyncProcessor(boost::shared_ptr<SmartSyncIf> iface) :
    iface_(iface) {
    processMap_["writeFile2Server"] = &SmartSyncProcessor::process_writeFile2Server;
    processMap_["getFileFromServer"] = &SmartSyncProcessor::process_getFileFromServer;
    processMap_["updateLocal"] = &SmartSyncProcessor::process_updateLocal;
    processMap_["updateServer"] = &SmartSyncProcessor::process_updateServer;
    processMap_["request"] = &SmartSyncProcessor::process_request;
    processMap_["checkFile"] = &SmartSyncProcessor::process_checkFile;
  }

  virtual ~SmartSyncProcessor() {}
};

class SmartSyncProcessorFactory : public ::apache::thrift::TProcessorFactory {
 public:
  SmartSyncProcessorFactory(const ::boost::shared_ptr< SmartSyncIfFactory >& handlerFactory) :
      handlerFactory_(handlerFactory) {}

  ::boost::shared_ptr< ::apache::thrift::TProcessor > getProcessor(const ::apache::thrift::TConnectionInfo& connInfo);

 protected:
  ::boost::shared_ptr< SmartSyncIfFactory > handlerFactory_;
};

class SmartSyncMultiface : virtual public SmartSyncIf {
 public:
  SmartSyncMultiface(std::vector<boost::shared_ptr<SmartSyncIf> >& ifaces) : ifaces_(ifaces) {
  }
  virtual ~SmartSyncMultiface() {}
 protected:
  std::vector<boost::shared_ptr<SmartSyncIf> > ifaces_;
  SmartSyncMultiface() {}
  void add(boost::shared_ptr<SmartSyncIf> iface) {
    ifaces_.push_back(iface);
  }
 public:
  void writeFile2Server(StatusReport& _return, const RFile& rFile) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->writeFile2Server(_return, rFile);
    }
    ifaces_[i]->writeFile2Server(_return, rFile);
    return;
  }

  void getFileFromServer(std::string& _return, const std::string& fName) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->getFileFromServer(_return, fName);
    }
    ifaces_[i]->getFileFromServer(_return, fName);
    return;
  }

  void updateLocal(std::vector<Filedes> & _return, const std::vector<Filechk> & chks) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->updateLocal(_return, chks);
    }
    ifaces_[i]->updateLocal(_return, chks);
    return;
  }

  void updateServer(StatusReport& _return, const std::vector<Filedes> & des) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->updateServer(_return, des);
    }
    ifaces_[i]->updateServer(_return, des);
    return;
  }

  void request(std::vector<Filechk> & _return) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->request(_return);
    }
    ifaces_[i]->request(_return);
    return;
  }

  void checkFile(StatusReport& _return, const RFileMetadata& meta) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->checkFile(_return, meta);
    }
    ifaces_[i]->checkFile(_return, meta);
    return;
  }

};



#endif
