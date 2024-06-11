#pragma once

#ifdef HOST
#define substring(start, end) substr(start, (end - start))
#define indexOf(...) find(__VA_ARGS__)
#define isEmpty(...) empty(__VA_ARGS__)
#endif

#include <string>

typedef std::string String;

void delay(int);

#include "WiFiS3.h"
class IPAddress;
class HardwareSerial {
 public:
  void print(String);
  void print(int);
  void println(IPAddress);
  void println(String);
  void println(int);
};

extern HardwareSerial Serial;
