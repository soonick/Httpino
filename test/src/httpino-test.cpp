#include "httpino/httpino.hpp"
#include "Arduino.h"

#include <Hashtable.h>
#include <catch.hpp>

TEST_CASE("parseQueryString") {
  HttpIno http;

  SECTION("Single key value") {
    Hashtable<String, String> actual = http.parseQueryString("hello?abc=1");
    REQUIRE(actual.elements() == 1);
    REQUIRE(*actual.get("abc") == "1");
  }

  SECTION("Multiple key values") {
    Hashtable<String, String> actual =
        http.parseQueryString("hello?abc=1&qwer=world");
    REQUIRE(actual.elements() == 2);
    REQUIRE(*actual.get("abc") == "1");
    REQUIRE(*actual.get("qwer") == "world");
  }

  SECTION("Handles spaces") {
    Hashtable<String, String> actual =
        http.parseQueryString("hello?full+name=Jose+Shanchez");
    REQUIRE(actual.elements() == 1);
    REQUIRE(*actual.get("full name") == "Jose Shanchez");
  }

  SECTION("Skips when no equal sign is found") {
    Hashtable<String, String> actual =
        http.parseQueryString("hello?asdf&abc=1");
    REQUIRE(actual.elements() == 1);
    REQUIRE(*actual.get("abc") == "1");
  }
}
