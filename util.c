#include "util.h"

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

// render a mac address in the form of "$prefix($HEX_BYTE$separator){6}"
// hw_address must be exactly 6 long
char* render_hw_address(uint8_t *hw_addr, char* prefix, char *separator) {
  size_t prefix_length = strlen(prefix);
  size_t separator_length = strlen(separator);

  // 12 hex nibbles in 6 byte mac address, 1 for NULL terminator
  size_t total_length = prefix_length + (5 * separator_length) + 13;   
  char *dest = calloc(total_length, sizeof(char));
  char *p = dest;

  strcpy(p, prefix);
  p += prefix_length;

  // copy first byte without separator,
  // we tack on the separator at the start
  // of each subsequent loop to avoid
  // an extra copy and rewind
  sprintf(p, "%02X", hw_addr[0]);
  p += 2;

  for (int i = 1; i < 6; i++) {
    strcpy(p, separator);
    p += separator_length;
    sprintf(p, "%02X", hw_addr[i]);
    p += 2;
  }

  return dest;
}
