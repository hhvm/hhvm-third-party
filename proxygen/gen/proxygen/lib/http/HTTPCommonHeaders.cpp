/* C++ code produced by gperf version 3.0.4 */
/* Command-line: /usr/bin/gperf -m5 --output-file=gen/proxygen/lib/http/HTTPCommonHeaders.cpp  */
/* Computed positions: -k'1,8,22,$' */

#if !((' ' == 32) && ('!' == 33) && ('"' == 34) && ('#' == 35) \
      && ('%' == 37) && ('&' == 38) && ('\'' == 39) && ('(' == 40) \
      && (')' == 41) && ('*' == 42) && ('+' == 43) && (',' == 44) \
      && ('-' == 45) && ('.' == 46) && ('/' == 47) && ('0' == 48) \
      && ('1' == 49) && ('2' == 50) && ('3' == 51) && ('4' == 52) \
      && ('5' == 53) && ('6' == 54) && ('7' == 55) && ('8' == 56) \
      && ('9' == 57) && (':' == 58) && (';' == 59) && ('<' == 60) \
      && ('=' == 61) && ('>' == 62) && ('?' == 63) && ('A' == 65) \
      && ('B' == 66) && ('C' == 67) && ('D' == 68) && ('E' == 69) \
      && ('F' == 70) && ('G' == 71) && ('H' == 72) && ('I' == 73) \
      && ('J' == 74) && ('K' == 75) && ('L' == 76) && ('M' == 77) \
      && ('N' == 78) && ('O' == 79) && ('P' == 80) && ('Q' == 81) \
      && ('R' == 82) && ('S' == 83) && ('T' == 84) && ('U' == 85) \
      && ('V' == 86) && ('W' == 87) && ('X' == 88) && ('Y' == 89) \
      && ('Z' == 90) && ('[' == 91) && ('\\' == 92) && (']' == 93) \
      && ('^' == 94) && ('_' == 95) && ('a' == 97) && ('b' == 98) \
      && ('c' == 99) && ('d' == 100) && ('e' == 101) && ('f' == 102) \
      && ('g' == 103) && ('h' == 104) && ('i' == 105) && ('j' == 106) \
      && ('k' == 107) && ('l' == 108) && ('m' == 109) && ('n' == 110) \
      && ('o' == 111) && ('p' == 112) && ('q' == 113) && ('r' == 114) \
      && ('s' == 115) && ('t' == 116) && ('u' == 117) && ('v' == 118) \
      && ('w' == 119) && ('x' == 120) && ('y' == 121) && ('z' == 122) \
      && ('{' == 123) && ('|' == 124) && ('}' == 125) && ('~' == 126))
/* The character set is not based on ISO-646.  */
#error "gperf generated tables don't work with this execution character set. Please report a bug to <bug-gnu-gperf@gnu.org>."
#endif


// Copyright 2004-present Facebook.  All rights reserved.

#include "proxygen/lib/http/HTTPCommonHeaders.h"

#include <cstring>

#include <glog/logging.h>

namespace proxygen {

struct HTTPCommonHeaderName { const char* name; uint8_t code; };





/* the following is a placeholder for the build script to generate a list
 * of enum values from the list in HTTPCommonHeaders.txt
 */;
enum
  {
    TOTAL_KEYWORDS = 82,
    MIN_WORD_LENGTH = 2,
    MAX_WORD_LENGTH = 37,
    MIN_HASH_VALUE = 2,
    MAX_HASH_VALUE = 124
  };

/* maximum key range = 123, duplicates = 0 */

#ifndef GPERF_DOWNCASE
#define GPERF_DOWNCASE 1
static unsigned char gperf_downcase[256] =
  {
      0,   1,   2,   3,   4,   5,   6,   7,   8,   9,  10,  11,  12,  13,  14,
     15,  16,  17,  18,  19,  20,  21,  22,  23,  24,  25,  26,  27,  28,  29,
     30,  31,  32,  33,  34,  35,  36,  37,  38,  39,  40,  41,  42,  43,  44,
     45,  46,  47,  48,  49,  50,  51,  52,  53,  54,  55,  56,  57,  58,  59,
     60,  61,  62,  63,  64,  97,  98,  99, 100, 101, 102, 103, 104, 105, 106,
    107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121,
    122,  91,  92,  93,  94,  95,  96,  97,  98,  99, 100, 101, 102, 103, 104,
    105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119,
    120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134,
    135, 136, 137, 138, 139, 140, 141, 142, 143, 144, 145, 146, 147, 148, 149,
    150, 151, 152, 153, 154, 155, 156, 157, 158, 159, 160, 161, 162, 163, 164,
    165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175, 176, 177, 178, 179,
    180, 181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 191, 192, 193, 194,
    195, 196, 197, 198, 199, 200, 201, 202, 203, 204, 205, 206, 207, 208, 209,
    210, 211, 212, 213, 214, 215, 216, 217, 218, 219, 220, 221, 222, 223, 224,
    225, 226, 227, 228, 229, 230, 231, 232, 233, 234, 235, 236, 237, 238, 239,
    240, 241, 242, 243, 244, 245, 246, 247, 248, 249, 250, 251, 252, 253, 254,
    255
  };
#endif

#ifndef GPERF_CASE_MEMCMP
#define GPERF_CASE_MEMCMP 1
static int
gperf_case_memcmp (register const char *s1, register const char *s2, register unsigned int n)
{
  for (; n > 0;)
    {
      unsigned char c1 = gperf_downcase[(unsigned char)*s1++];
      unsigned char c2 = gperf_downcase[(unsigned char)*s2++];
      if (c1 == c2)
        {
          n--;
          continue;
        }
      return (int)c1 - (int)c2;
    }
  return 0;
}
#endif

class HTTPCommonHeadersInternal
{
private:
  static inline unsigned int hash (const char *str, unsigned int len);
public:
  static const struct HTTPCommonHeaderName *in_word_set (const char *str, unsigned int len);
};

inline unsigned int
HTTPCommonHeadersInternal::hash (register const char *str, register unsigned int len)
{
  static const unsigned char asso_values[] =
    {
      125, 125, 125, 125, 125, 125, 125, 125, 125, 125,
      125, 125, 125, 125, 125, 125, 125, 125, 125, 125,
      125, 125, 125, 125, 125, 125, 125, 125, 125, 125,
      125, 125, 125, 125, 125, 125, 125, 125, 125, 125,
      125, 125, 125, 125, 125,   9, 125, 125, 125, 125,
      125, 125, 125,  28, 125, 125, 125, 125, 125, 125,
      125, 125, 125, 125, 125,   2, 125,   4,  40,   0,
       47,  47,  15,  22, 125,  48,  31,  33,   3,  25,
       25, 125,   2,   5,   0,  58,  66,  48,   2,   4,
       22, 125, 125, 125, 125, 125, 125,   2, 125,   4,
       40,   0,  47,  47,  15,  22, 125,  48,  31,  33,
        3,  25,  25, 125,   2,   5,   0,  58,  66,  48,
        2,   4,  22, 125, 125, 125, 125, 125, 125, 125,
      125, 125, 125, 125, 125, 125, 125, 125, 125, 125,
      125, 125, 125, 125, 125, 125, 125, 125, 125, 125,
      125, 125, 125, 125, 125, 125, 125, 125, 125, 125,
      125, 125, 125, 125, 125, 125, 125, 125, 125, 125,
      125, 125, 125, 125, 125, 125, 125, 125, 125, 125,
      125, 125, 125, 125, 125, 125, 125, 125, 125, 125,
      125, 125, 125, 125, 125, 125, 125, 125, 125, 125,
      125, 125, 125, 125, 125, 125, 125, 125, 125, 125,
      125, 125, 125, 125, 125, 125, 125, 125, 125, 125,
      125, 125, 125, 125, 125, 125, 125, 125, 125, 125,
      125, 125, 125, 125, 125, 125, 125, 125, 125, 125,
      125, 125, 125, 125, 125, 125, 125, 125, 125, 125,
      125, 125, 125, 125, 125, 125
    };
  register int hval = len;

  switch (hval)
    {
      default:
        hval += asso_values[(unsigned char)str[21]];
      /*FALLTHROUGH*/
      case 21:
      case 20:
      case 19:
      case 18:
      case 17:
      case 16:
      case 15:
      case 14:
      case 13:
      case 12:
      case 11:
      case 10:
      case 9:
      case 8:
        hval += asso_values[(unsigned char)str[7]];
      /*FALLTHROUGH*/
      case 7:
      case 6:
      case 5:
      case 4:
      case 3:
      case 2:
      case 1:
        hval += asso_values[(unsigned char)str[0]];
        break;
    }
  return hval + asso_values[(unsigned char)str[len - 1]];
}

static const unsigned char lengthtable[] =
  {
     0,  0,  2,  0,  0,  3,  6,  5,  6,  7,  6,  7,  7,  6,
     0,  0,  0, 13, 12,  4, 14, 15, 13, 16,  7, 12, 13, 16,
    22, 16,  8, 15, 16,  6,  6, 19, 25, 22, 16, 10, 13, 30,
    14,  3,  4,  8, 17, 32, 15, 29, 15,  4, 11,  3, 28,  5,
     0, 15,  9, 13,  8, 27, 11, 10, 15,  7, 17,  9, 10, 16,
    15,  3, 28, 13,  4, 29, 16, 37,  0, 16, 10, 19,  0,  4,
     4,  0, 17,  0,  0,  0,  0,  0,  0,  0,  3,  0,  0,  0,
    12,  0,  0, 18,  7,  0,  0, 19,  0,  0,  0,  0,  0,  0,
     0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 13
  };

static const struct HTTPCommonHeaderName wordlist[] =
  {
    {""}, {""},
    {"TE", HTTP_HEADER_TE},
    {""}, {""},
    {"Age", HTTP_HEADER_AGE},
    {"Expect", HTTP_HEADER_EXPECT},
    {"Range", HTTP_HEADER_RANGE},
    {"Accept", HTTP_HEADER_ACCEPT},
    {"Trailer", HTTP_HEADER_TRAILER},
    {"Cookie", HTTP_HEADER_COOKIE},
    {"Referer", HTTP_HEADER_REFERER},
    {"Expires", HTTP_HEADER_EXPIRES},
    {"Server", HTTP_HEADER_SERVER},
    {""}, {""}, {""},
    {"X-Wap-Profile", HTTP_HEADER_X_WAP_PROFILE},
    {"X-Powered-By", HTTP_HEADER_X_POWERED_BY},
    {"Host", HTTP_HEADER_HOST},
    {"Accept-Charset", HTTP_HEADER_ACCEPT_CHARSET},
    {"X-Forwarded-For", HTTP_HEADER_X_FORWARDED_FOR},
    {"Accept-Ranges", HTTP_HEADER_ACCEPT_RANGES},
    {"X-XSS-Protection", HTTP_HEADER_X_XSS_PROTECTION},
    {"Refresh", HTTP_HEADER_REFRESH},
    {"Content-Type", HTTP_HEADER_CONTENT_TYPE},
    {"Content-Range", HTTP_HEADER_CONTENT_RANGE},
    {"X-Accel-Redirect", HTTP_HEADER_X_ACCEL_REDIRECT},
    {"Access-Control-Max-Age", HTTP_HEADER_ACCESS_CONTROL_MAX_AGE},
    {"Content-Language", HTTP_HEADER_CONTENT_LANGUAGE},
    {"If-Range", HTTP_HEADER_IF_RANGE},
    {"X-Frame-Options", HTTP_HEADER_X_FRAME_OPTIONS},
    {"Content-Location", HTTP_HEADER_CONTENT_LOCATION},
    {"Pragma", HTTP_HEADER_PRAGMA},
    {"Origin", HTTP_HEADER_ORIGIN},
    {"Content-Disposition", HTTP_HEADER_CONTENT_DISPOSITION},
    {"Strict-Transport-Security", HTTP_HEADER_STRICT_TRANSPORT_SECURITY},
    {"X-Content-Type-Options", HTTP_HEADER_X_CONTENT_TYPE_OPTIONS},
    {"X-Requested-With", HTTP_HEADER_X_REQUESTED_WITH},
    {"Connection", HTTP_HEADER_CONNECTION},
    {"Authorization", HTTP_HEADER_AUTHORIZATION},
    {"Access-Control-Request-Headers", HTTP_HEADER_ACCESS_CONTROL_REQUEST_HEADERS},
    {"Content-Length", HTTP_HEADER_CONTENT_LENGTH},
    {"DNT", HTTP_HEADER_DNT},
    {"Date", HTTP_HEADER_DATE},
    {"Location", HTTP_HEADER_LOCATION},
    {"X-Forwarded-Proto", HTTP_HEADER_X_FORWARDED_PROTO},
    {"Access-Control-Allow-Credentials", HTTP_HEADER_ACCESS_CONTROL_ALLOW_CREDENTIALS},
    {"Accept-Language", HTTP_HEADER_ACCEPT_LANGUAGE},
    {"Access-Control-Expose-Headers", HTTP_HEADER_ACCESS_CONTROL_EXPOSE_HEADERS},
    {"X-UA-Compatible", HTTP_HEADER_X_UA_COMPATIBLE},
    {"ETag", HTTP_HEADER_ETAG},
    {"Content-MD5", HTTP_HEADER_CONTENT_MD5},
    {"P3P", HTTP_HEADER_P3P},
    {"Access-Control-Allow-Headers", HTTP_HEADER_ACCESS_CONTROL_ALLOW_HEADERS},
    {"Allow", HTTP_HEADER_ALLOW},
    {""},
    {"Accept-Datetime", HTTP_HEADER_ACCEPT_DATETIME},
    {"X-Real-IP", HTTP_HEADER_X_REAL_IP},
    {"If-None-Match", HTTP_HEADER_IF_NONE_MATCH},
    {"If-Match", HTTP_HEADER_IF_MATCH},
    {"Access-Control-Allow-Origin", HTTP_HEADER_ACCESS_CONTROL_ALLOW_ORIGIN},
    {"Retry-After", HTTP_HEADER_RETRY_AFTER},
    {"Set-Cookie", HTTP_HEADER_SET_COOKIE},
    {"Accept-Encoding", HTTP_HEADER_ACCEPT_ENCODING},
    {"Upgrade", HTTP_HEADER_UPGRADE},
    {"Transfer-Encoding", HTTP_HEADER_TRANSFER_ENCODING},
    {"Timestamp", HTTP_HEADER_TIMESTAMP},
    {"User-Agent", HTTP_HEADER_USER_AGENT},
    {"Proxy-Connection", HTTP_HEADER_PROXY_CONNECTION},
    {"Front-End-Https", HTTP_HEADER_FRONT_END_HTTPS},
    {"Via", HTTP_HEADER_VIA},
    {"Access-Control-Allow-Methods", HTTP_HEADER_ACCESS_CONTROL_ALLOW_METHODS},
    {"Cache-Control", HTTP_HEADER_CACHE_CONTROL},
    {"Vary", HTTP_HEADER_VARY},
    {"Access-Control-Request-Method", HTTP_HEADER_ACCESS_CONTROL_REQUEST_METHOD},
    {"Content-Encoding", HTTP_HEADER_CONTENT_ENCODING},
    {"X-Content-Security-Policy-Report-Only", HTTP_HEADER_X_CONTENT_SECURITY_POLICY_REPORT_ONLY},
    {""},
    {"WWW-Authenticate", HTTP_HEADER_WWW_AUTHENTICATE},
    {"Keep-Alive", HTTP_HEADER_KEEP_ALIVE},
    {"If-Unmodified-Since", HTTP_HEADER_IF_UNMODIFIED_SINCE},
    {""},
    {"Link", HTTP_HEADER_LINK},
    {"From", HTTP_HEADER_FROM},
    {""},
    {"If-Modified-Since", HTTP_HEADER_IF_MODIFIED_SINCE},
    {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {"VIP", HTTP_HEADER_VIP},
    {""}, {""}, {""},
    {"Max-Forwards", HTTP_HEADER_MAX_FORWARDS},
    {""}, {""},
    {"Proxy-Authenticate", HTTP_HEADER_PROXY_AUTHENTICATE},
    {"Warning", HTTP_HEADER_WARNING},
    {""}, {""},
    {"Proxy-Authorization", HTTP_HEADER_PROXY_AUTHORIZATION},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {"Last-Modified", HTTP_HEADER_LAST_MODIFIED}
  };

const struct HTTPCommonHeaderName *
HTTPCommonHeadersInternal::in_word_set (register const char *str, register unsigned int len)
{
  if (len <= MAX_WORD_LENGTH && len >= MIN_WORD_LENGTH)
    {
      register int key = hash (str, len);

      if (key <= MAX_HASH_VALUE && key >= 0)
        if (len == lengthtable[key])
          {
            register const char *s = wordlist[key].name;

            if ((((unsigned char)*str ^ (unsigned char)*s) & ~32) == 0 && !gperf_case_memcmp (str, s, len))
              return &wordlist[key];
          }
    }
  return 0;
}





HTTPHeaderCode HTTPCommonHeaders::hash(const char* name, size_t len) {
  const HTTPCommonHeaderName* match =
    HTTPCommonHeadersInternal::in_word_set(name, len);
  return (match == nullptr) ? HTTP_HEADER_OTHER : HTTPHeaderCode(match->code);
}

std::string* HTTPCommonHeaders::initHeaderNames() {
  DCHECK_LE(MAX_HASH_VALUE, 255);
  auto headerNames = new std::string[256];
  for (int j = MIN_HASH_VALUE; j <= MAX_HASH_VALUE; ++j) {
    uint8_t code = wordlist[j].code;
    const uint8_t OFFSET = 2; // first 2 values are reserved for special cases
    if (code >= OFFSET && code < TOTAL_KEYWORDS + OFFSET
                       && wordlist[j].name[0] != '\0') {
      DCHECK_EQ(headerNames[code], std::string());
      // this would mean a duplicate header code in the .gperf file

      headerNames[code] = wordlist[j].name;
    }
  }
  return headerNames;
}

} // proxygen
