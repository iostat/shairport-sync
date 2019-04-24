#include "ap2.h"
#include "util.h"

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

  return root_dict;
}
