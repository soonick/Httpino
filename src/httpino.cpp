#include "httpino.h"

String HttpIno::parseQueryString(const String& line) {
  int start = line.indexOf("?") + 1;
  int end = line.indexOf(" ", start);
  String queryString = line.substring(start, end);
  replace(queryString, '+', ' ');

  String result = "";
  long unsigned int currentStart = 0;
  while (currentStart < queryString.length()) {
    if (currentStart != 0) {
      result += ",";
    }

    int currentEnd = queryString.indexOf("&", currentStart);
    if (currentEnd == -1) {
      currentEnd = queryString.length();
    }

    String currentPair = queryString.substring(currentStart, currentEnd);
    result += currentPair;

    currentStart = currentEnd + 1;
  }

  return result;
}

void HttpIno::renderHtml(WiFiClient& client, const String& content) {
  client.println("HTTP/1.1 200 OK");
  client.println("Content-type:text/html");
  client.println();
  client.print(content);
  client.println();  // The HTTP response ends with another blank line:
}

void HttpIno::replace(String& in, const char f, const char r) {
  for (long unsigned int i = 0; i < in.length(); i++) {
    if (in[i] == f) {
      in[i] = r;
    }
  }
}
