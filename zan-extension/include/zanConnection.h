/*
  +----------------------------------------------------------------------+
  | Zan                                                                  |
  +----------------------------------------------------------------------+
  | Copyright (c) 2016-2017 Zan Group <https://github.com/youzan/zan>    |
  +----------------------------------------------------------------------+
  | This source file is subject to version 2.0 of the Apache license,    |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.apache.org/licenses/LICENSE-2.0.html                      |
  | If you did not receive a copy of the Apache2.0 license and are unable|
  | to obtain it through the world-wide-web, please send a note to       |
  | zan@zanphp.io so we can mail you a copy immediately.                 |
  +----------------------------------------------------------------------+
  |         Zan Group   <zan@zanphp.io>                                  |
  +----------------------------------------------------------------------+
*/

#ifndef _ZAN_CONNECTION_H_
#define _ZAN_CONNECTION_H_

#include "swoole.h"
#include "swPipe.h"
#include "swMemory/memoryPool.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _zanConnection
{
    /**
     * file descript
     */
    int fd;

    /**
     * session id
     */
    uint32_t session_id;

    /**
     * socket type, SW_SOCK_TCP or SW_SOCK_UDP
     */
    uint8_t socket_type;

    /**
     * fd type, SW_FD_TCP or SW_FD_PIPE or SW_FD_TIMERFD
     */
    uint8_t fdtype;

    int events;

    /**
     * is active
     * system fd must be 0. en: timerfd, signalfd, listen socket
     */
    uint8_t active;

    uint8_t connect_notify;

    /**
     * for SWOOLE_BASE mode.
     */
    uint8_t close_notify;

    uint8_t recv_wait;
    uint8_t send_wait;

    uint8_t direct_send;
    uint8_t ssl_send;

    /**
     * protected connection, cannot be closed by heartbeat thread.
     */
    uint8_t protect;

    uint8_t close_wait;
    uint8_t closed;
    uint8_t closing;
    uint8_t close_force;
    uint8_t close_reset;
    uint8_t event_trigger;
    uint8_t removed;			//// 是否从reactor 中移除
    uint8_t overflow;

    uint8_t tcp_nopush;
    uint8_t tcp_nodelay;

    uint8_t ssl_want_read;
    uint8_t ssl_want_write;

    uint8_t http_upgrade;
    uint8_t http2_stream;

    /**
     * ReactorThread id
     */
    uint8_t from_id;

    /**
     * from which socket fd, 由哪个监听套接字accepte 出来
     */
    uint8_t from_fd;

    uint8_t from_net_id;  //networker_id

    /**
     * socket address
     */
    swSocketAddress info;

    /**
     * link any thing, for kernel, do not use with application.
     */
    void *object;

    /*
     * used for user context data
     */
    void *user_data;


    /**
     * input buffer
     */
    struct _swBuffer *in_buffer;

    /**
     * output buffer
     */
    struct _swBuffer *out_buffer;

    /**
     * connect time(seconds)
     */
    time_t connect_time;

    /**
     * received time with last data，可以用于检测连接空闲
     */
    time_t last_time;

    /**
     * bind uid
     */
    long uid;

    /**
     * memory buffer size;
     */
    int buffer_size;

    /**
     *  upgarde websocket
     */
    uint8_t websocket_status;

#ifdef SW_USE_OPENSSL
    SSL *ssl;
    uint32_t ssl_state;
    swString ssl_client_cert;
#endif
    sw_atomic_t lock;
}zanConnection;

int zanReactor_onAccept(swReactor *reactor, swEvent *event);
void zanReactor_enableAccept(swReactor *reactor);

#ifdef __cplusplus
}
#endif

#endif   //_ZAN_CONNECTION_H_