#pragma once

#include "Arduino.h"
#include "WiFiS3.h"

class HttpIno {
 public:
  /**
   * Parses the first line of a request and returns the query string. It takes
   * care of some URL decodings, but probably not all of them. For now it
   * naively assumes there are no commans in keys or values
   *
   * @param line e.g. GET /save?name=Blue+bird&value=jose&name=Uno&value=One
   * HTTP/1.1
   * @return comma separated list of key values for the query params
   * (e.g. Blue bird=jose,Uno=One)
   */
  String parseQueryString(const String& line);

  /**
   * Returns the given content to the given WiFiClient
   *
   */
  void renderHtml(WiFiClient& client, const String& content);

 private:
  /**
   * My own implementation of search an replace a character in a string so I can
   * unit test parseQueryString
   * TODO: Find a way to use Arduino's implementation and still be able to unit
   * test
   */
  void replace(String& in, const char s, const char r);
};
