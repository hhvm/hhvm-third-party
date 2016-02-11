/*
 *  Copyright (c) 2016, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the BSD-style license found in the
 *  LICENSE file in the root directory of this source tree. An additional grant
 *  of patent rights can be found in the PATENTS file in the same directory.
 *
 */
#pragma once

#include <cstdint>
#include <string>

#include <proxygen/lib/utils/Export.h>

namespace proxygen {

/**
 * Codes (hashes) of common HTTP header names
 */
enum HTTPHeaderCode : uint8_t {
  // code reserved to indicate the absence of an HTTP header
  HTTP_HEADER_NONE = 0,
  // code for any HTTP header name not in the list of common headers
  HTTP_HEADER_OTHER = 1,

  /* the following is a placeholder for the build script to generate a list
   * of enum values from the list in HTTPCommonHeaders.txt
   *
   * enum name of Some-Header is HTTP_HEADER_SOME_HEADER,
   * so an example fragment of the generated list could be:
   * ...
   * HTTP_HEADER_WARNING = 65,
   * HTTP_HEADER_WWW_AUTHENTICATE = 66,
   * HTTP_HEADER_X_BACKEND = 67,
   * HTTP_HEADER_X_BLOCKID = 68,
   * ...
   */
  HTTP_HEADER_ACCESS_CONTROL_ALLOW_ORIGIN = 11,
  HTTP_HEADER_ACCESS_CONTROL_EXPOSE_HEADERS = 12,
  HTTP_HEADER_ACCESS_CONTROL_MAX_AGE = 13,
  HTTP_HEADER_ACCESS_CONTROL_REQUEST_HEADERS = 14,
  HTTP_HEADER_ACCESS_CONTROL_REQUEST_METHOD = 15,
  HTTP_HEADER_AGE = 16,
  HTTP_HEADER_ALLOW = 17,
  HTTP_HEADER_DATE = 31,
  HTTP_HEADER_AUTHORIZATION = 18,
  HTTP_HEADER_ETAG = 32,
  HTTP_HEADER_CACHE_CONTROL = 19,
  HTTP_HEADER_EXPECT = 33,
  HTTP_HEADER_CONNECTION = 20,
  HTTP_HEADER_EXPIRES = 34,
  HTTP_HEADER_FROM = 35,
  HTTP_HEADER_FRONT_END_HTTPS = 36,
  HTTP_HEADER_HOST = 37,
  HTTP_HEADER_PROXY_AUTHENTICATE = 51,
  HTTP_HEADER_IF_MATCH = 38,
  HTTP_HEADER_PROXY_AUTHORIZATION = 52,
  HTTP_HEADER_IF_MODIFIED_SINCE = 39,
  HTTP_HEADER_PROXY_CONNECTION = 53,
  HTTP_HEADER_IF_NONE_MATCH = 40,
  HTTP_HEADER_RANGE = 54,
  HTTP_HEADER_REFERER = 55,
  HTTP_HEADER_REFRESH = 56,
  HTTP_HEADER_RETRY_AFTER = 57,
  HTTP_HEADER_ACCEPT = 2,
  HTTP_HEADER_WARNING = 71,
  HTTP_HEADER_SERVER = 58,
  HTTP_HEADER_ACCEPT_CHARSET = 3,
  HTTP_HEADER_X_ACCEL_REDIRECT = 72,
  HTTP_HEADER_SET_COOKIE = 59,
  HTTP_HEADER_ACCEPT_DATETIME = 4,
  HTTP_HEADER_X_CONTENT_SECURITY_POLICY_REPORT_ONLY = 73,
  HTTP_HEADER_STRICT_TRANSPORT_SECURITY = 60,
  HTTP_HEADER_ACCEPT_ENCODING = 5,
  HTTP_HEADER_X_CONTENT_TYPE_OPTIONS = 74,
  HTTP_HEADER_ACCEPT_LANGUAGE = 6,
  HTTP_HEADER_X_FORWARDED_FOR = 75,
  HTTP_HEADER_ACCEPT_RANGES = 7,
  HTTP_HEADER_X_FORWARDED_PROTO = 76,
  HTTP_HEADER_ACCESS_CONTROL_ALLOW_CREDENTIALS = 8,
  HTTP_HEADER_X_FRAME_OPTIONS = 77,
  HTTP_HEADER_ACCESS_CONTROL_ALLOW_HEADERS = 9,
  HTTP_HEADER_X_POWERED_BY = 78,
  HTTP_HEADER_ACCESS_CONTROL_ALLOW_METHODS = 10,
  HTTP_HEADER_X_REAL_IP = 79,
  HTTP_HEADER_X_REQUESTED_WITH = 80,
  HTTP_HEADER_CONTENT_DISPOSITION = 21,
  HTTP_HEADER_CONTENT_ENCODING = 22,
  HTTP_HEADER_CONTENT_LANGUAGE = 23,
  HTTP_HEADER_CONTENT_LENGTH = 24,
  HTTP_HEADER_CONTENT_LOCATION = 25,
  HTTP_HEADER_CONTENT_MD5 = 26,
  HTTP_HEADER_CONTENT_RANGE = 27,
  HTTP_HEADER_IF_RANGE = 41,
  HTTP_HEADER_CONTENT_TYPE = 28,
  HTTP_HEADER_IF_UNMODIFIED_SINCE = 42,
  HTTP_HEADER_COOKIE = 29,
  HTTP_HEADER_KEEP_ALIVE = 43,
  HTTP_HEADER_DNT = 30,
  HTTP_HEADER_LAST_MODIFIED = 44,
  HTTP_HEADER_LINK = 45,
  HTTP_HEADER_LOCATION = 46,
  HTTP_HEADER_MAX_FORWARDS = 47,
  HTTP_HEADER_TE = 61,
  HTTP_HEADER_ORIGIN = 48,
  HTTP_HEADER_TIMESTAMP = 62,
  HTTP_HEADER_P3P = 49,
  HTTP_HEADER_TRAILER = 63,
  HTTP_HEADER_PRAGMA = 50,
  HTTP_HEADER_TRANSFER_ENCODING = 64,
  HTTP_HEADER_UPGRADE = 65,
  HTTP_HEADER_USER_AGENT = 66,
  HTTP_HEADER_VIP = 67,
  HTTP_HEADER_X_UA_COMPATIBLE = 81,
  HTTP_HEADER_VARY = 68,
  HTTP_HEADER_X_WAP_PROFILE = 82,
  HTTP_HEADER_VIA = 69,
  HTTP_HEADER_X_XSS_PROTECTION = 83,
  HTTP_HEADER_WWW_AUTHENTICATE = 70,

};

class HTTPCommonHeaders {
 public:
  // Perfect hash function to match common HTTP header names
  FB_EXPORT static HTTPHeaderCode hash(const char* name, size_t len);

  FB_EXPORT inline static HTTPHeaderCode hash(const std::string& name) {
    return hash(name.data(), name.length());
  }

  FB_EXPORT static std::string* initHeaderNames();

  inline static const std::string* getPointerToHeaderName(HTTPHeaderCode code) {
    static const auto headerNames = initHeaderNames();

    return headerNames + code;
  }
};

} // proxygen
