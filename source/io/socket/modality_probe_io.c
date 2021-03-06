#include <kernel.h>
#include <stdint.h>
#include <assert.h>
#include <net/socket.h>
#include <net/net_ip.h>
#include <fcntl.h>
#include <errno.h>

#include "modality_probe_io.h"

#ifdef CONFIG_MODALITY_PROBE_IO_TRANSPORT_SOCKET_USE_PRINTK
#include <sys/printk.h>
#define TRACE_IO_DEBUG_PRINTF(...) printk(__VA_ARGS__)
#else
#define TRACE_IO_DEBUG_PRINTF(...) do {} while( 0 )
#endif

static int g_sender_socket = -1;
static struct sockaddr_in g_sender_addr = {0};

static int g_recvr_socket = -1;
static struct sockaddr_in g_recvr_addr = {0};

static void init_sender(void)
{
    if(g_sender_socket == -1)
    {
        g_sender_socket = zsock_socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
        assert(g_sender_socket != -1);

        g_sender_addr.sin_family = AF_INET;
        g_sender_addr.sin_port = htons(CONFIG_MODALITY_PROBE_IO_TRANSPORT_SOCKET_COLLECTOR_PORT);
        zsock_inet_pton(
                AF_INET,
                CONFIG_MODALITY_PROBE_IO_TRANSPORT_SOCKET_COLLECTOR_ADDRESS,
                &g_sender_addr.sin_addr);

        TRACE_IO_DEBUG_PRINTF(
                "trace-io: Initialized sender socket %s:%d\n",
                CONFIG_MODALITY_PROBE_IO_TRANSPORT_SOCKET_COLLECTOR_ADDRESS,
                (int) CONFIG_MODALITY_PROBE_IO_TRANSPORT_SOCKET_COLLECTOR_PORT);
    }
}

static void init_recvr(void)
{
    int err;
    int fl;

    if(g_recvr_socket == -1)
    {
        g_recvr_socket = zsock_socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
        assert(g_recvr_socket != -1);

        g_recvr_addr.sin_family = AF_INET;
        g_recvr_addr.sin_port = htons(CONFIG_MODALITY_PROBE_IO_TRANSPORT_SOCKET_CONTROL_PLANE_PORT);
        g_recvr_addr.sin_addr.s_addr = htonl(INADDR_ANY);

        fl = zsock_fcntl(g_recvr_socket, F_GETFL, 0);
        assert(fl != -1);
        fl |= O_NONBLOCK;
        err = zsock_fcntl(g_recvr_socket, F_SETFL, fl);
        assert(err != -1);

        err = zsock_bind(g_recvr_socket, (struct sockaddr *) &g_recvr_addr, sizeof(g_recvr_addr));
        assert(err == 0);

        TRACE_IO_DEBUG_PRINTF(
                "trace-io: Initialized recv socket %d\n",
                (int) CONFIG_MODALITY_PROBE_IO_TRANSPORT_SOCKET_CONTROL_PLANE_PORT);
    }
}

void trace_io_init(void)
{
    init_sender();
    init_recvr();
}

int32_t trace_io_read(void* data, uint32_t size, int32_t* bytes_read)
{
    int32_t ret = 0;

    if(g_recvr_socket != -1)
    {
        const ssize_t status = zsock_recv(g_recvr_socket, data, (size_t) size, 0);
        if(status < 0)
        {
            if(errno != EAGAIN)
            {
                ret = -1;
            }
            else
            {
                ret = 0;
                *bytes_read = 0;
            }
        }
        else
        {
            TRACE_IO_DEBUG_PRINTF("trace-io: recvd %d bytes\n", (int) status);
            *bytes_read = (int32_t) status;
            ret = 0;
        }
    }

    return ret;
}

int32_t trace_io_write(void* data, uint32_t size, int32_t* bytes_written)
{
    int32_t ret = 0;

    if(g_sender_socket != -1)
    {
        const ssize_t status = zsock_sendto(
                g_sender_socket,
                data,
                (size_t) size,
                0,
                (struct sockaddr *) &g_sender_addr,
                sizeof(g_sender_addr));
        if(status < 0)
        {
            ret = -1;
        }
        else
        {
            TRACE_IO_DEBUG_PRINTF("trace-io: sent %d bytes\n", (int) status);
            *bytes_written = (int32_t) status;
            ret = 0;
        }
    }

    return ret;
}
