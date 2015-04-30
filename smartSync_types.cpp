/**
 * Autogenerated by Thrift Compiler (0.9.2)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#include "smartSync_types.h"

#include <algorithm>
#include <ostream>

#include <thrift/TToString.h>



int _kStatusValues[] = {
  Status::SAME,
  Status::NOEXIST,
  Status::OLDER,
  Status::NEWER,
  Status::FAIL,
  Status::SUCCESS
};
const char* _kStatusNames[] = {
  "SAME",
  "NOEXIST",
  "OLDER",
  "NEWER",
  "FAIL",
  "SUCCESS"
};
const std::map<int, const char*> _Status_VALUES_TO_NAMES(::apache::thrift::TEnumIterator(6, _kStatusValues, _kStatusNames), ::apache::thrift::TEnumIterator(-1, NULL, NULL));


SystemException::~SystemException() throw() {
}


void SystemException::__set_message(const std::string& val) {
  this->message = val;
__isset.message = true;
}

const char* SystemException::ascii_fingerprint = "66E694018C17E5B65A59AE8F55CCA3CD";
const uint8_t SystemException::binary_fingerprint[16] = {0x66,0xE6,0x94,0x01,0x8C,0x17,0xE5,0xB6,0x5A,0x59,0xAE,0x8F,0x55,0xCC,0xA3,0xCD};

uint32_t SystemException::read(::apache::thrift::protocol::TProtocol* iprot) {

  uint32_t xfer = 0;
  std::string fname;
  ::apache::thrift::protocol::TType ftype;
  int16_t fid;

  xfer += iprot->readStructBegin(fname);

  using ::apache::thrift::protocol::TProtocolException;


  while (true)
  {
    xfer += iprot->readFieldBegin(fname, ftype, fid);
    if (ftype == ::apache::thrift::protocol::T_STOP) {
      break;
    }
    switch (fid)
    {
      case 1:
        if (ftype == ::apache::thrift::protocol::T_STRING) {
          xfer += iprot->readString(this->message);
          this->__isset.message = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      default:
        xfer += iprot->skip(ftype);
        break;
    }
    xfer += iprot->readFieldEnd();
  }

  xfer += iprot->readStructEnd();

  return xfer;
}

uint32_t SystemException::write(::apache::thrift::protocol::TProtocol* oprot) const {
  uint32_t xfer = 0;
  oprot->incrementRecursionDepth();
  xfer += oprot->writeStructBegin("SystemException");

  if (this->__isset.message) {
    xfer += oprot->writeFieldBegin("message", ::apache::thrift::protocol::T_STRING, 1);
    xfer += oprot->writeString(this->message);
    xfer += oprot->writeFieldEnd();
  }
  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  oprot->decrementRecursionDepth();
  return xfer;
}

void swap(SystemException &a, SystemException &b) {
  using ::std::swap;
  swap(a.message, b.message);
  swap(a.__isset, b.__isset);
}

SystemException::SystemException(const SystemException& other0) : TException() {
  message = other0.message;
  __isset = other0.__isset;
}
SystemException& SystemException::operator=(const SystemException& other1) {
  message = other1.message;
  __isset = other1.__isset;
  return *this;
}
std::ostream& operator<<(std::ostream& out, const SystemException& obj) {
  using apache::thrift::to_string;
  out << "SystemException(";
  out << "message="; (obj.__isset.message ? (out << to_string(obj.message)) : (out << "<null>"));
  out << ")";
  return out;
}


StatusReport::~StatusReport() throw() {
}


void StatusReport::__set_status(const Status::type val) {
  this->status = val;
}

const char* StatusReport::ascii_fingerprint = "8BBB3D0C3B370CB38F2D1340BB79F0AA";
const uint8_t StatusReport::binary_fingerprint[16] = {0x8B,0xBB,0x3D,0x0C,0x3B,0x37,0x0C,0xB3,0x8F,0x2D,0x13,0x40,0xBB,0x79,0xF0,0xAA};

uint32_t StatusReport::read(::apache::thrift::protocol::TProtocol* iprot) {

  uint32_t xfer = 0;
  std::string fname;
  ::apache::thrift::protocol::TType ftype;
  int16_t fid;

  xfer += iprot->readStructBegin(fname);

  using ::apache::thrift::protocol::TProtocolException;

  bool isset_status = false;

  while (true)
  {
    xfer += iprot->readFieldBegin(fname, ftype, fid);
    if (ftype == ::apache::thrift::protocol::T_STOP) {
      break;
    }
    switch (fid)
    {
      case 1:
        if (ftype == ::apache::thrift::protocol::T_I32) {
          int32_t ecast2;
          xfer += iprot->readI32(ecast2);
          this->status = (Status::type)ecast2;
          isset_status = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      default:
        xfer += iprot->skip(ftype);
        break;
    }
    xfer += iprot->readFieldEnd();
  }

  xfer += iprot->readStructEnd();

  if (!isset_status)
    throw TProtocolException(TProtocolException::INVALID_DATA);
  return xfer;
}

uint32_t StatusReport::write(::apache::thrift::protocol::TProtocol* oprot) const {
  uint32_t xfer = 0;
  oprot->incrementRecursionDepth();
  xfer += oprot->writeStructBegin("StatusReport");

  xfer += oprot->writeFieldBegin("status", ::apache::thrift::protocol::T_I32, 1);
  xfer += oprot->writeI32((int32_t)this->status);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  oprot->decrementRecursionDepth();
  return xfer;
}

void swap(StatusReport &a, StatusReport &b) {
  using ::std::swap;
  swap(a.status, b.status);
}

StatusReport::StatusReport(const StatusReport& other3) {
  status = other3.status;
}
StatusReport& StatusReport::operator=(const StatusReport& other4) {
  status = other4.status;
  return *this;
}
std::ostream& operator<<(std::ostream& out, const StatusReport& obj) {
  using apache::thrift::to_string;
  out << "StatusReport(";
  out << "status=" << to_string(obj.status);
  out << ")";
  return out;
}


RFileMetadata::~RFileMetadata() throw() {
}


void RFileMetadata::__set_filename(const std::string& val) {
  this->filename = val;
__isset.filename = true;
}

void RFileMetadata::__set_created(const Timestamp val) {
  this->created = val;
__isset.created = true;
}

void RFileMetadata::__set_updated(const Timestamp val) {
  this->updated = val;
__isset.updated = true;
}

void RFileMetadata::__set_version(const int32_t val) {
  this->version = val;
__isset.version = true;
}

void RFileMetadata::__set_contenthash(const std::string& val) {
  this->contenthash = val;
__isset.contenthash = true;
}

void RFileMetadata::__set_contentLen(const int32_t val) {
  this->contentLen = val;
__isset.contentLen = true;
}

const char* RFileMetadata::ascii_fingerprint = "E4CFBC1301040562F64C075EE28E8B53";
const uint8_t RFileMetadata::binary_fingerprint[16] = {0xE4,0xCF,0xBC,0x13,0x01,0x04,0x05,0x62,0xF6,0x4C,0x07,0x5E,0xE2,0x8E,0x8B,0x53};

uint32_t RFileMetadata::read(::apache::thrift::protocol::TProtocol* iprot) {

  uint32_t xfer = 0;
  std::string fname;
  ::apache::thrift::protocol::TType ftype;
  int16_t fid;

  xfer += iprot->readStructBegin(fname);

  using ::apache::thrift::protocol::TProtocolException;


  while (true)
  {
    xfer += iprot->readFieldBegin(fname, ftype, fid);
    if (ftype == ::apache::thrift::protocol::T_STOP) {
      break;
    }
    switch (fid)
    {
      case 1:
        if (ftype == ::apache::thrift::protocol::T_STRING) {
          xfer += iprot->readString(this->filename);
          this->__isset.filename = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 2:
        if (ftype == ::apache::thrift::protocol::T_I64) {
          xfer += iprot->readI64(this->created);
          this->__isset.created = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 3:
        if (ftype == ::apache::thrift::protocol::T_I64) {
          xfer += iprot->readI64(this->updated);
          this->__isset.updated = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 4:
        if (ftype == ::apache::thrift::protocol::T_I32) {
          xfer += iprot->readI32(this->version);
          this->__isset.version = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 5:
        if (ftype == ::apache::thrift::protocol::T_STRING) {
          xfer += iprot->readString(this->contenthash);
          this->__isset.contenthash = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 6:
        if (ftype == ::apache::thrift::protocol::T_I32) {
          xfer += iprot->readI32(this->contentLen);
          this->__isset.contentLen = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      default:
        xfer += iprot->skip(ftype);
        break;
    }
    xfer += iprot->readFieldEnd();
  }

  xfer += iprot->readStructEnd();

  return xfer;
}

uint32_t RFileMetadata::write(::apache::thrift::protocol::TProtocol* oprot) const {
  uint32_t xfer = 0;
  oprot->incrementRecursionDepth();
  xfer += oprot->writeStructBegin("RFileMetadata");

  if (this->__isset.filename) {
    xfer += oprot->writeFieldBegin("filename", ::apache::thrift::protocol::T_STRING, 1);
    xfer += oprot->writeString(this->filename);
    xfer += oprot->writeFieldEnd();
  }
  if (this->__isset.created) {
    xfer += oprot->writeFieldBegin("created", ::apache::thrift::protocol::T_I64, 2);
    xfer += oprot->writeI64(this->created);
    xfer += oprot->writeFieldEnd();
  }
  if (this->__isset.updated) {
    xfer += oprot->writeFieldBegin("updated", ::apache::thrift::protocol::T_I64, 3);
    xfer += oprot->writeI64(this->updated);
    xfer += oprot->writeFieldEnd();
  }
  if (this->__isset.version) {
    xfer += oprot->writeFieldBegin("version", ::apache::thrift::protocol::T_I32, 4);
    xfer += oprot->writeI32(this->version);
    xfer += oprot->writeFieldEnd();
  }
  if (this->__isset.contenthash) {
    xfer += oprot->writeFieldBegin("contenthash", ::apache::thrift::protocol::T_STRING, 5);
    xfer += oprot->writeString(this->contenthash);
    xfer += oprot->writeFieldEnd();
  }
  if (this->__isset.contentLen) {
    xfer += oprot->writeFieldBegin("contentLen", ::apache::thrift::protocol::T_I32, 6);
    xfer += oprot->writeI32(this->contentLen);
    xfer += oprot->writeFieldEnd();
  }
  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  oprot->decrementRecursionDepth();
  return xfer;
}

void swap(RFileMetadata &a, RFileMetadata &b) {
  using ::std::swap;
  swap(a.filename, b.filename);
  swap(a.created, b.created);
  swap(a.updated, b.updated);
  swap(a.version, b.version);
  swap(a.contenthash, b.contenthash);
  swap(a.contentLen, b.contentLen);
  swap(a.__isset, b.__isset);
}

RFileMetadata::RFileMetadata(const RFileMetadata& other5) {
  filename = other5.filename;
  created = other5.created;
  updated = other5.updated;
  version = other5.version;
  contenthash = other5.contenthash;
  contentLen = other5.contentLen;
  __isset = other5.__isset;
}
RFileMetadata& RFileMetadata::operator=(const RFileMetadata& other6) {
  filename = other6.filename;
  created = other6.created;
  updated = other6.updated;
  version = other6.version;
  contenthash = other6.contenthash;
  contentLen = other6.contentLen;
  __isset = other6.__isset;
  return *this;
}
std::ostream& operator<<(std::ostream& out, const RFileMetadata& obj) {
  using apache::thrift::to_string;
  out << "RFileMetadata(";
  out << "filename="; (obj.__isset.filename ? (out << to_string(obj.filename)) : (out << "<null>"));
  out << ", " << "created="; (obj.__isset.created ? (out << to_string(obj.created)) : (out << "<null>"));
  out << ", " << "updated="; (obj.__isset.updated ? (out << to_string(obj.updated)) : (out << "<null>"));
  out << ", " << "version="; (obj.__isset.version ? (out << to_string(obj.version)) : (out << "<null>"));
  out << ", " << "contenthash="; (obj.__isset.contenthash ? (out << to_string(obj.contenthash)) : (out << "<null>"));
  out << ", " << "contentLen="; (obj.__isset.contentLen ? (out << to_string(obj.contentLen)) : (out << "<null>"));
  out << ")";
  return out;
}


Filedes::~Filedes() throw() {
}


void Filedes::__set_flag(const int32_t val) {
  this->flag = val;
__isset.flag = true;
}

void Filedes::__set_content(const std::string& val) {
  this->content = val;
__isset.content = true;
}

void Filedes::__set_block(const int32_t val) {
  this->block = val;
__isset.block = true;
}

const char* Filedes::ascii_fingerprint = "538B9E45F78E9805971ED8D100FFED5A";
const uint8_t Filedes::binary_fingerprint[16] = {0x53,0x8B,0x9E,0x45,0xF7,0x8E,0x98,0x05,0x97,0x1E,0xD8,0xD1,0x00,0xFF,0xED,0x5A};

uint32_t Filedes::read(::apache::thrift::protocol::TProtocol* iprot) {

  uint32_t xfer = 0;
  std::string fname;
  ::apache::thrift::protocol::TType ftype;
  int16_t fid;

  xfer += iprot->readStructBegin(fname);

  using ::apache::thrift::protocol::TProtocolException;


  while (true)
  {
    xfer += iprot->readFieldBegin(fname, ftype, fid);
    if (ftype == ::apache::thrift::protocol::T_STOP) {
      break;
    }
    switch (fid)
    {
      case 1:
        if (ftype == ::apache::thrift::protocol::T_I32) {
          xfer += iprot->readI32(this->flag);
          this->__isset.flag = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 2:
        if (ftype == ::apache::thrift::protocol::T_STRING) {
          xfer += iprot->readString(this->content);
          this->__isset.content = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 3:
        if (ftype == ::apache::thrift::protocol::T_I32) {
          xfer += iprot->readI32(this->block);
          this->__isset.block = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      default:
        xfer += iprot->skip(ftype);
        break;
    }
    xfer += iprot->readFieldEnd();
  }

  xfer += iprot->readStructEnd();

  return xfer;
}

uint32_t Filedes::write(::apache::thrift::protocol::TProtocol* oprot) const {
  uint32_t xfer = 0;
  oprot->incrementRecursionDepth();
  xfer += oprot->writeStructBegin("Filedes");

  if (this->__isset.flag) {
    xfer += oprot->writeFieldBegin("flag", ::apache::thrift::protocol::T_I32, 1);
    xfer += oprot->writeI32(this->flag);
    xfer += oprot->writeFieldEnd();
  }
  if (this->__isset.content) {
    xfer += oprot->writeFieldBegin("content", ::apache::thrift::protocol::T_STRING, 2);
    xfer += oprot->writeString(this->content);
    xfer += oprot->writeFieldEnd();
  }
  if (this->__isset.block) {
    xfer += oprot->writeFieldBegin("block", ::apache::thrift::protocol::T_I32, 3);
    xfer += oprot->writeI32(this->block);
    xfer += oprot->writeFieldEnd();
  }
  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  oprot->decrementRecursionDepth();
  return xfer;
}

void swap(Filedes &a, Filedes &b) {
  using ::std::swap;
  swap(a.flag, b.flag);
  swap(a.content, b.content);
  swap(a.block, b.block);
  swap(a.__isset, b.__isset);
}

Filedes::Filedes(const Filedes& other7) {
  flag = other7.flag;
  content = other7.content;
  block = other7.block;
  __isset = other7.__isset;
}
Filedes& Filedes::operator=(const Filedes& other8) {
  flag = other8.flag;
  content = other8.content;
  block = other8.block;
  __isset = other8.__isset;
  return *this;
}
std::ostream& operator<<(std::ostream& out, const Filedes& obj) {
  using apache::thrift::to_string;
  out << "Filedes(";
  out << "flag="; (obj.__isset.flag ? (out << to_string(obj.flag)) : (out << "<null>"));
  out << ", " << "content="; (obj.__isset.content ? (out << to_string(obj.content)) : (out << "<null>"));
  out << ", " << "block="; (obj.__isset.block ? (out << to_string(obj.block)) : (out << "<null>"));
  out << ")";
  return out;
}


Filechk::~Filechk() throw() {
}


void Filechk::__set_rollchk(const int64_t val) {
  this->rollchk = val;
__isset.rollchk = true;
}

void Filechk::__set_num1(const int64_t val) {
  this->num1 = val;
__isset.num1 = true;
}

void Filechk::__set_num2(const int64_t val) {
  this->num2 = val;
__isset.num2 = true;
}

void Filechk::__set_md5chk(const std::string& val) {
  this->md5chk = val;
__isset.md5chk = true;
}

void Filechk::__set_block(const int32_t val) {
  this->block = val;
__isset.block = true;
}

const char* Filechk::ascii_fingerprint = "878E63FD1BE8911E810E69D016B3BA19";
const uint8_t Filechk::binary_fingerprint[16] = {0x87,0x8E,0x63,0xFD,0x1B,0xE8,0x91,0x1E,0x81,0x0E,0x69,0xD0,0x16,0xB3,0xBA,0x19};

uint32_t Filechk::read(::apache::thrift::protocol::TProtocol* iprot) {

  uint32_t xfer = 0;
  std::string fname;
  ::apache::thrift::protocol::TType ftype;
  int16_t fid;

  xfer += iprot->readStructBegin(fname);

  using ::apache::thrift::protocol::TProtocolException;


  while (true)
  {
    xfer += iprot->readFieldBegin(fname, ftype, fid);
    if (ftype == ::apache::thrift::protocol::T_STOP) {
      break;
    }
    switch (fid)
    {
      case 1:
        if (ftype == ::apache::thrift::protocol::T_I64) {
          xfer += iprot->readI64(this->rollchk);
          this->__isset.rollchk = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 2:
        if (ftype == ::apache::thrift::protocol::T_I64) {
          xfer += iprot->readI64(this->num1);
          this->__isset.num1 = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 3:
        if (ftype == ::apache::thrift::protocol::T_I64) {
          xfer += iprot->readI64(this->num2);
          this->__isset.num2 = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 4:
        if (ftype == ::apache::thrift::protocol::T_STRING) {
          xfer += iprot->readString(this->md5chk);
          this->__isset.md5chk = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 5:
        if (ftype == ::apache::thrift::protocol::T_I32) {
          xfer += iprot->readI32(this->block);
          this->__isset.block = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      default:
        xfer += iprot->skip(ftype);
        break;
    }
    xfer += iprot->readFieldEnd();
  }

  xfer += iprot->readStructEnd();

  return xfer;
}

uint32_t Filechk::write(::apache::thrift::protocol::TProtocol* oprot) const {
  uint32_t xfer = 0;
  oprot->incrementRecursionDepth();
  xfer += oprot->writeStructBegin("Filechk");

  if (this->__isset.rollchk) {
    xfer += oprot->writeFieldBegin("rollchk", ::apache::thrift::protocol::T_I64, 1);
    xfer += oprot->writeI64(this->rollchk);
    xfer += oprot->writeFieldEnd();
  }
  if (this->__isset.num1) {
    xfer += oprot->writeFieldBegin("num1", ::apache::thrift::protocol::T_I64, 2);
    xfer += oprot->writeI64(this->num1);
    xfer += oprot->writeFieldEnd();
  }
  if (this->__isset.num2) {
    xfer += oprot->writeFieldBegin("num2", ::apache::thrift::protocol::T_I64, 3);
    xfer += oprot->writeI64(this->num2);
    xfer += oprot->writeFieldEnd();
  }
  if (this->__isset.md5chk) {
    xfer += oprot->writeFieldBegin("md5chk", ::apache::thrift::protocol::T_STRING, 4);
    xfer += oprot->writeString(this->md5chk);
    xfer += oprot->writeFieldEnd();
  }
  if (this->__isset.block) {
    xfer += oprot->writeFieldBegin("block", ::apache::thrift::protocol::T_I32, 5);
    xfer += oprot->writeI32(this->block);
    xfer += oprot->writeFieldEnd();
  }
  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  oprot->decrementRecursionDepth();
  return xfer;
}

void swap(Filechk &a, Filechk &b) {
  using ::std::swap;
  swap(a.rollchk, b.rollchk);
  swap(a.num1, b.num1);
  swap(a.num2, b.num2);
  swap(a.md5chk, b.md5chk);
  swap(a.block, b.block);
  swap(a.__isset, b.__isset);
}

Filechk::Filechk(const Filechk& other9) {
  rollchk = other9.rollchk;
  num1 = other9.num1;
  num2 = other9.num2;
  md5chk = other9.md5chk;
  block = other9.block;
  __isset = other9.__isset;
}
Filechk& Filechk::operator=(const Filechk& other10) {
  rollchk = other10.rollchk;
  num1 = other10.num1;
  num2 = other10.num2;
  md5chk = other10.md5chk;
  block = other10.block;
  __isset = other10.__isset;
  return *this;
}
std::ostream& operator<<(std::ostream& out, const Filechk& obj) {
  using apache::thrift::to_string;
  out << "Filechk(";
  out << "rollchk="; (obj.__isset.rollchk ? (out << to_string(obj.rollchk)) : (out << "<null>"));
  out << ", " << "num1="; (obj.__isset.num1 ? (out << to_string(obj.num1)) : (out << "<null>"));
  out << ", " << "num2="; (obj.__isset.num2 ? (out << to_string(obj.num2)) : (out << "<null>"));
  out << ", " << "md5chk="; (obj.__isset.md5chk ? (out << to_string(obj.md5chk)) : (out << "<null>"));
  out << ", " << "block="; (obj.__isset.block ? (out << to_string(obj.block)) : (out << "<null>"));
  out << ")";
  return out;
}


RFile::~RFile() throw() {
}


void RFile::__set_meta(const RFileMetadata& val) {
  this->meta = val;
__isset.meta = true;
}

void RFile::__set_content(const std::string& val) {
  this->content = val;
__isset.content = true;
}

const char* RFile::ascii_fingerprint = "804A806F307222AB98994824DBA02B04";
const uint8_t RFile::binary_fingerprint[16] = {0x80,0x4A,0x80,0x6F,0x30,0x72,0x22,0xAB,0x98,0x99,0x48,0x24,0xDB,0xA0,0x2B,0x04};

uint32_t RFile::read(::apache::thrift::protocol::TProtocol* iprot) {

  uint32_t xfer = 0;
  std::string fname;
  ::apache::thrift::protocol::TType ftype;
  int16_t fid;

  xfer += iprot->readStructBegin(fname);

  using ::apache::thrift::protocol::TProtocolException;


  while (true)
  {
    xfer += iprot->readFieldBegin(fname, ftype, fid);
    if (ftype == ::apache::thrift::protocol::T_STOP) {
      break;
    }
    switch (fid)
    {
      case 1:
        if (ftype == ::apache::thrift::protocol::T_STRUCT) {
          xfer += this->meta.read(iprot);
          this->__isset.meta = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 2:
        if (ftype == ::apache::thrift::protocol::T_STRING) {
          xfer += iprot->readString(this->content);
          this->__isset.content = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      default:
        xfer += iprot->skip(ftype);
        break;
    }
    xfer += iprot->readFieldEnd();
  }

  xfer += iprot->readStructEnd();

  return xfer;
}

uint32_t RFile::write(::apache::thrift::protocol::TProtocol* oprot) const {
  uint32_t xfer = 0;
  oprot->incrementRecursionDepth();
  xfer += oprot->writeStructBegin("RFile");

  if (this->__isset.meta) {
    xfer += oprot->writeFieldBegin("meta", ::apache::thrift::protocol::T_STRUCT, 1);
    xfer += this->meta.write(oprot);
    xfer += oprot->writeFieldEnd();
  }
  if (this->__isset.content) {
    xfer += oprot->writeFieldBegin("content", ::apache::thrift::protocol::T_STRING, 2);
    xfer += oprot->writeString(this->content);
    xfer += oprot->writeFieldEnd();
  }
  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  oprot->decrementRecursionDepth();
  return xfer;
}

void swap(RFile &a, RFile &b) {
  using ::std::swap;
  swap(a.meta, b.meta);
  swap(a.content, b.content);
  swap(a.__isset, b.__isset);
}

RFile::RFile(const RFile& other11) {
  meta = other11.meta;
  content = other11.content;
  __isset = other11.__isset;
}
RFile& RFile::operator=(const RFile& other12) {
  meta = other12.meta;
  content = other12.content;
  __isset = other12.__isset;
  return *this;
}
std::ostream& operator<<(std::ostream& out, const RFile& obj) {
  using apache::thrift::to_string;
  out << "RFile(";
  out << "meta="; (obj.__isset.meta ? (out << to_string(obj.meta)) : (out << "<null>"));
  out << ", " << "content="; (obj.__isset.content ? (out << to_string(obj.content)) : (out << "<null>"));
  out << ")";
  return out;
}


