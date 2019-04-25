#ifndef _AP2_H
#define _AP2_H

#include "common.h"
#include "plist/plist.h"

#include <stdint.h>

//char* base64_encode(char *data, size_t length);
//char* length_prefix_encoded_txtAirplay(char **kvs, size_t kv_count);
plist_t get_info_dict(uint8_t *hw_address, char *device_name);

#endif /* _AP2_H */
