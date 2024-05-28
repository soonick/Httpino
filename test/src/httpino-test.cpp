#include "httpino.h"
#include <catch.hpp>

TEST_CASE("parseQueryString") {
  HttpIno http;

  SECTION("Single key value") {
    String actual = http.parseQueryString("hello?abc=1");
    REQUIRE(actual == "abc=1");
  }

  SECTION("Multiple key values") {
    String actual = http.parseQueryString("hello?abc=1&qwer=world");
    REQUIRE(actual == "abc=1,qwer=world");
  }

  SECTION("Handles spaces") {
    String actual = http.parseQueryString("hello?full+name=Jose+Shanchez");
    REQUIRE(actual == "full name=Jose Shanchez");
  }
}
