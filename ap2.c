#include "ap2.h"
#include "util.h"

#include <stdlib.h>
#include <string.h>
#include <openssl/pem.h>

// from https://stackoverflow.com/a/16511093/1763937 with love
char *base64_encode (const void *b64_encode_this, size_t encode_this_many_bytes) {
    BIO *b64_bio, *mem_bio;      //Declares two OpenSSL BIOs: a base64 filter and a memory BIO.
    BUF_MEM *mem_bio_mem_ptr;    //Pointer to a "memory BIO" structure holding our base64 data.
    b64_bio = BIO_new(BIO_f_base64());                      //Initialize our base64 filter BIO.
    mem_bio = BIO_new(BIO_s_mem());                           //Initialize our memory sink BIO.
    BIO_push(b64_bio, mem_bio);            //Link the BIOs by creating a filter-sink BIO chain.
    BIO_set_flags(b64_bio, BIO_FLAGS_BASE64_NO_NL);  //No newlines every 64 characters or less.
    BIO_write(b64_bio, b64_encode_this, encode_this_many_bytes); //Records base64 encoded data.
    BIO_flush(b64_bio);   //Flush data.  Necessary for b64 encoding, because of pad characters.
    BIO_get_mem_ptr(mem_bio, &mem_bio_mem_ptr);  //Store address of mem_bio's memory structure.
    BIO_set_close(mem_bio, BIO_NOCLOSE);   //Permit access to mem_ptr after BIOs are destroyed.
    BIO_free_all(b64_bio);  //Destroys all BIOs in chain, starting with b64 (i.e. the 1st one).
    BUF_MEM_grow(mem_bio_mem_ptr, (*mem_bio_mem_ptr).length + 1);   //Makes space for end null.
    (*mem_bio_mem_ptr).data[(*mem_bio_mem_ptr).length] = '\0';  //Adds null-terminator to tail.
    return (*mem_bio_mem_ptr).data; //Returns base-64 encoded data. (See: "buf_mem_st" struct).
}

char* length_prefix_encoded_txtAirPlay(char **kvs, size_t kv_count, size_t *out_chars_written) {
  char *buf = NULL;
  size_t chars_written = 0;
  for(size_t i = 0; i < kv_count; i++) {
   size_t kv_len = strlen(kvs[i]);
   buf = realloc(buf, chars_written + kv_len + 1);
   buf[chars_written] = (char)kv_len;
   strcpy(buf+chars_written+1, kvs[i]);
   chars_written += 1 + kv_len;
  }

  buf[chars_written] = 0;

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
  plist_dict_set_item(root_dict, "model", plist_new_string("ShairportSync"));
  plist_dict_set_item(root_dict, "statusFlags", plist_new_uint(4)); // aka flags=0x4
  plist_dict_set_item(root_dict, "keepAliveLowPower", plist_new_bool(1));
  plist_dict_set_item(root_dict, "keepAliveSendStatsAsBody", plist_new_bool(0)); // setting this to false cause i have a feeling this might make it harder

  // if you look closely, that weird hex number the features bits
  // in the reverse order from how they appear on mDNS (and txtAirplay) ;)
  plist_dict_set_item(root_dict, "features", plist_new_uint(0x30040180200));


  // all airplay devices ive seen send these alphabetically, though that
  // might not strictly be necessary...
  char *txtAirPlay_records[] = {
    "acl=0",
    "am=ShairportSync",
    render_hw_address(hw_addr, "deviceid=", ":"),
    "features=0x40180200,0x300",
    "flags=0x4",
    "protovers=1.1",
    "srcvers=366.0",
  };
  size_t txtAirPlay_length;
  char *txtAirPlay_lpe = length_prefix_encoded_txtAirPlay(txtAirPlay_records, 7, &txtAirPlay_length);
  plist_dict_set_item(root_dict, "txtAirPlay", plist_new_data(txtAirPlay_lpe, txtAirPlay_length));

  return root_dict;
}

