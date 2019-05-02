#include "ap2.h"
#include "common.h"
#include "util.h"

#include <stdlib.h>
#include <string.h>

char* length_prefix_encoded_txtAirPlay(char **kvs, size_t kv_count, size_t *out_chars_written) {
  char *buf = malloc(sizeof(char));
  size_t chars_written = 0; // 1 to keep room for our null terminator
  for(size_t i = 0; i < kv_count; i++) {
    size_t kv_len = strlen(kvs[i]);
    buf = realloc(buf, chars_written + kv_len + 1);
    buf[chars_written] = (unsigned char)kv_len;
    chars_written++;
    memcpy(buf+chars_written, kvs[i], kv_len);
    chars_written += kv_len;
  }
  
  *out_chars_written = chars_written;
  return buf;
}

plist_t get_info_audio_latency(char *audio_type) {
  plist_t dict = plist_new_dict();

  if (audio_type != NULL) {
    plist_dict_set_item(dict, "audioType", plist_new_string(audio_type));
  }

  plist_dict_set_item(dict, "inputLatencyMicros", plist_new_uint(0));
  plist_dict_set_item(dict, "outputLatencyMicros", plist_new_uint(0));
  plist_dict_set_item(dict, "type", plist_new_uint(100));

  return dict;
}

plist_t get_info_dict(uint8_t *hw_addr, char* service_name) {
  plist_t root_dict = plist_new_dict();
  
  {
    plist_t audio_latencies = plist_new_array();
    plist_array_append_item(audio_latencies, get_info_audio_latency(NULL));
    plist_array_append_item(audio_latencies, get_info_audio_latency("default"));
    plist_array_append_item(audio_latencies, get_info_audio_latency("media"));
    plist_array_append_item(audio_latencies, get_info_audio_latency("telephone"));
    plist_dict_set_item(root_dict, "audioLatencies", audio_latencies);
  }

  plist_dict_set_item(root_dict, "deviceID", plist_new_string(render_hw_address(hw_addr, "", ":")));
  plist_dict_set_item(root_dict, "sourceVersion", plist_new_string("366.0"));
  plist_dict_set_item(root_dict, "protocolVersion", plist_new_string("1.1"));
  plist_dict_set_item(root_dict, "name", plist_new_string(service_name));
  plist_dict_set_item(root_dict, "sdk", plist_new_string("AirPlay;2.0.2"));
  plist_dict_set_item(root_dict, "manufacturer", plist_new_string("manufacturer=iostat/griff/mikebrady"));
  plist_dict_set_item(root_dict, "model", plist_new_string("ShairportSync"));
  plist_dict_set_item(root_dict, "statusFlags", plist_new_uint(4)); // aka flags=0x4
  plist_dict_set_item(root_dict, "keepAliveLowPower", plist_new_bool(1));
  plist_dict_set_item(root_dict, "keepAliveSendStatsAsBody", plist_new_bool(1));

  char pk_bytes[32] = { 0x27, 0x33, 0xc7, 0x5c, 0xa6, 0xce, 0x67, 0x52, 0x55, 0x0d, 0xa2, 0x26, 0x87, 0xad, 0xf9, 0xb2, 0x9b, 0x18, 0xe4, 0x6c, 0x0f, 0xce, 0x8a, 0x73, 0x69, 0x08, 0x3a, 0x08, 0x47, 0xdd, 0x87, 0xef };
  plist_dict_set_item(root_dict, "pk", plist_new_data(pk_bytes, 32));
  
  plist_dict_set_item(root_dict, "pi", plist_new_string("1698df64-e8c9-4e4f-9663-5797ee57dcef"));
  // if you look closely, its that weird hex number from the features bits
  // in the reverse order from how they appear on mDNS (and txtAirplay) ;)
  plist_dict_set_item(root_dict, "features", plist_new_uint(0x1C340445D0A00));


  // all airplay devices ive seen send these alphabetically, though that
  // might not strictly be necessary...
  char *txtAirPlay_records[] = {
    "acl=0",
    "model=ShairportSync",
    "manufacturer=iostat/griff/mikebrady",
    render_hw_address(hw_addr, "deviceid=", ":"),
    "features=0x445D0A00,0x1C340",
    "flags=0x4",
    "protovers=1.1",
    "srcvers=366.0",
    "pk=2733c75ca6ce6752550da22687adf9b29b18e46c0fce8a7369083a0847dd87ef",
    "gid=1698df64-e8c9-4e4f-9663-5797ee57dcef",
    "pi=1698df64-e8c9-4e4f-9663-5797ee57dcef",
    "gcgl=0",
    "rsf=0x0",
  };
  size_t txtAirPlay_length;
  char *txtAirPlay_lpe = length_prefix_encoded_txtAirPlay(txtAirPlay_records, sizeof(txtAirPlay_records) / sizeof(char*), &txtAirPlay_length);
  plist_dict_set_item(root_dict, "txtAirPlay", plist_new_data(txtAirPlay_lpe, txtAirPlay_length));

  return root_dict;
}

