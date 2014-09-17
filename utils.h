#include <iostream>
#include <stdlib.h>
#include <stdio.h>

#define DEBUG 1

// This is gcc specific.
#define debug_print(fmt, ...) \
                do { if (DEBUG) fprintf(stderr, fmt, ##__VA_ARGS__); } while (0)

#define debug_cout(x) do { \
      if (DEBUG) { std::cerr << x << std::endl; } \
} while (0)
