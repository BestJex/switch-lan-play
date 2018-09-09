#ifndef _LAN_PLAY_H_
#define _LAN_PLAY_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pcap.h>
#include <stdint.h>
#include <time.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>
#include <base/llog.h>
#include <uv.h>

struct lan_play;
#include "packet.h"
#include "helper.h"
#include "config.h"
#include "arp.h"
#include "gateway.h"

struct lan_play {
    pcap_t *dev;

    struct packet_ctx packet_ctx;

    bool stop;
    uv_loop_t loop;
    uv_thread_t libpcap_thread;
    uv_async_t get_packet_handle;

    // lan_client
    uv_udp_t client;
    uv_timer_t client_keepalive_timer;
    struct sockaddr_in server_addr;

    struct gateway gateway;
};

void get_packet(struct packet_ctx *arg, const struct pcap_pkthdr * pkthdr, const u_char * packet);
int lan_client_init(struct lan_play *lan_play);
int lan_client_send_ipv4(struct lan_play *lan_play, void *dst_ip, const void *packet, uint16_t len);

#endif // _LAN_PLAY_H_
