#ifndef _MDNS_H
#define _MDNS_H

#include "config.h"
#include <player.h>
#include <stdint.h>

extern int mdns_pid;

void mdns_unregister(void);
void mdns_register(void);
void mdns_dacp_monitor_start();
void mdns_dacp_monitor_stop(void);
void mdns_dacp_monitor_set_id(const char *dacp_id);

void mdns_ls_backends(void);

typedef struct {
  char *name;
  int (*mdns_register)(char *apname, int port);
  void (*mdns_unregister)(void);
  void (*mdns_dacp_monitor_start)();
  void (*mdns_dacp_monitor_set_id)(const char *);
  void (*mdns_dacp_monitor_stop)();
} mdns_backend;

#ifdef CONFIG_METADATA

#define METADATA_EXPRESSION config.get_coverart ? "md=0,1,2" : "md=0,2"

/*
 #define MDNS_RECORD_WITH_METADATA \
  "tp=UDP", "sm=false", "ek=1", "et=0,1", "cn=0,1", "ch=2", METADATA_EXPRESSION, "ss=16",          \
      "sr=44100", "vn=3", "txtvers=1", config.password ? "pw=true" : "pw=false"
*/
#define MDNS_RECORD_WITH_METADATA                                                                  \
  "sf=0x4", "fv=76400.10", "am=ShairportSync", "vs=105.1", "tp=TCP,UDP", "vn=65537",               \
      METADATA_EXPRESSION, "ss=16", "sr=44100", "da=true", "sv=false", "et=0,1", "ek=1", "cn=0,1", \
      "ch=2", "txtvers=1", config.password ? "pw=true" : "pw=false"

#endif

#ifdef CONFIG_AIRPLAY_2
#define AP2_MDNS_RECORD "acl=0", "flags=0x4", "protovers=1.1", "srcvers=366.0", "features=0x40180200,0x300", config.airplay_device_id
#endif
/*
 #define MDNS_RECORD_WITHOUT_METADATA \
  "tp=UDP", "sm=false", "ek=1", "et=0,1", "cn=0,1", "ch=2", METADATA_EXPRESSION, "ss=16",
 "sr=44100", "vn=3",           \
      "txtvers=1", config.password ? "pw=true" : "pw=false"
*/

#define MDNS_RECORD_WITHOUT_METADATA                                                               \
  "sf=0x4", "fv=76400.10", "am=ShairportSync", "vs=105.1", "tp=TCP,UDP", "vn=65537", "ss=16",      \
      "sr=44100", "da=true", "sv=false", "et=0,1", "ek=1", "cn=0,1", "ch=2", "txtvers=1",          \
      config.password ? "pw=true" : "pw=false"

#endif // _MDNS_H
