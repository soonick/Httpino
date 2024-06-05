#include "httpino.h"

#include <Hashtable.h>

Hashtable<String, String> HttpIno::parseQueryString(const String& line) {
  Hashtable<String, String> dictionary;

  int start = line.indexOf("?") + 1;
  int end = line.indexOf(" ", start);
  String queryString = line.substring(start, end);
  replace(queryString, '+', ' ');

  long unsigned int currentStart = 0;
  while (currentStart < queryString.length()) {
    int currentEnd = queryString.indexOf("&", currentStart);
    if (currentEnd == -1) {
      currentEnd = queryString.length();
    }

    String currentPair = queryString.substring(currentStart, currentEnd);
    int equalPos = currentPair.indexOf("=");
    if (equalPos != -1) {
      // If there is no equal sign, we skip adding it to the result
      String key = currentPair.substring(0, equalPos);
      String value = currentPair.substring(equalPos + 1, currentPair.length());
      dictionary.put(key, value);
    }

    currentStart = currentEnd + 1;
  }

  return dictionary;
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
