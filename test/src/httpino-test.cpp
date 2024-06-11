#include "httpino/httpino.hpp"
#include "Arduino.h"

#include <Hashtable.h>
#include <catch.hpp>

TEST_CASE("parseQueryString") {
  HttpIno http;

  SECTION("Single key value") {
    Hashtable<String, String>* actual = http.parseQueryString("hello?abc=1");
    REQUIRE(actual->elements() == 1);
    REQUIRE(*actual->get("abc") == "1");
    delete actual;
  }

  SECTION("Multiple key values") {
    Hashtable<String, String>* actual =
        http.parseQueryString("hello?abc=1&qwer=world&onemore=yesyes");
    REQUIRE(actual->elements() == 3);
    REQUIRE(*actual->get("abc") == "1");
    REQUIRE(*actual->get("qwer") == "world");
    REQUIRE(*actual->get("onemore") == "yesyes");
    delete actual;
  }

  SECTION("Handles spaces") {
    Hashtable<String, String>* actual =
        http.parseQueryString("hello?full+name=Jose+Shanchez");
    REQUIRE(actual->elements() == 1);
    REQUIRE(*actual->get("full name") == "Jose Shanchez");
    delete actual;
  }

  SECTION("Skips when no equal sign is found") {
    Hashtable<String, String>* actual =
        http.parseQueryString("hello?asdf&abc=1");
    REQUIRE(actual->elements() == 1);
    REQUIRE(*actual->get("abc") == "1");
    delete actual;
  }
}
