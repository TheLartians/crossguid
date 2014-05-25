#include "guid.h"

#ifdef GUID_CFUUID
#include "CFUUID.h"
#endif

using namespace std;

// overload << so that it's easy to convert to a string
ostream &operator<<(ostream &s, const Guid &guid)
{
  return s << hex << setfill('0')
    << setw(2) << (int)guid._bytes[0]
    << setw(2) << (int)guid._bytes[1]
    << setw(2) << (int)guid._bytes[2]
    << setw(2) << (int)guid._bytes[3]
    << "-"
    << setw(2) << (int)guid._bytes[4]
    << setw(2) << (int)guid._bytes[5]
    << "-"
    << setw(2) << (int)guid._bytes[6]
    << setw(2) << (int)guid._bytes[7]
    << "-"
    << setw(2) << (int)guid._bytes[8]
    << setw(2) << (int)guid._bytes[9]
    << "-"
    << setw(2) << (int)guid._bytes[10]
    << setw(2) << (int)guid._bytes[11]
    << setw(2) << (int)guid._bytes[12]
    << setw(2) << (int)guid._bytes[13]
    << setw(2) << (int)guid._bytes[14]
    << setw(2) << (int)guid._bytes[15];
}

// create a guid from vector of bytes
Guid::Guid(const vector<unsigned char> &bytes)
{
  _bytes = bytes;
}

// create a guid from array of bytes
Guid::Guid(const unsigned char *bytes)
{
  _bytes.assign(bytes, bytes + 16);
}

// create a guid from string
Guid::Guid(const string &fromString)
{
  _bytes.clear();
  char byteHexString[3] = {0};

  bool lookingForFirstChar = true;

  for (const char &ch : fromString)
  {
    if (ch == '-')
      continue;

    if (lookingForFirstChar)
    {
      byteHexString[0] = ch;
      lookingForFirstChar = false;
    }
    else
    {
      byteHexString[1] = ch;
      unsigned long byte;
      byte = stoul(byteHexString, 0, 16);
      _bytes.push_back(byte);
      lookingForFirstChar = true;
    }
  }
  
}

// create empty guid
Guid::Guid()
{
  _bytes = vector<unsigned char>(16, 0);
}

// copy constructor
Guid::Guid(const Guid &other)
{
  _bytes = other._bytes;
}

// overload assignment operator
Guid &Guid::operator=(const Guid &other)
{
  _bytes = other._bytes;
  return *this;
}

// overload equality operator
bool Guid::operator==(const Guid &other) const
{
  return _bytes == other._bytes;
}

// overload inequality operator
bool Guid::operator!=(const Guid &other) const
{
  return !((*this) == other);
}

// This is the linux friendly implementation, but it coul work on other
// systems that have libuuid available
#ifdef GUID_LIBUUID
Guid generateGuid()
{
  uuid_t id;
  uuid_generate(id);
  return id;
}
#endif

// this is the mac and ios version 
#ifdef GUID_CFUUID
Guid generateGuid()
{
  CFUUIDRef id = CFUUIDCreate(NULL);
  const unsigned char *bytes =
  {
    id.bytes.byte0,
    id.bytes.byte1,
    id.bytes.byte2,
    id.bytes.byte3,
    id.bytes.byte4,
    id.bytes.byte5,
    id.bytes.byte6,
    id.bytes.byte7,
    id.bytes.byte8,
    id.bytes.byte9,
    id.bytes.byte10,
    id.bytes.byte11,
    id.bytes.byte12,
    id.bytes.byte13,
    id.bytes.byte14,
    id.bytes.byte15
  };
  return bytes;
}
#endif