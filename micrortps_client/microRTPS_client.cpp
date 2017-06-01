#include <px4_config.h>
#include <px4_tasks.h>
#include <px4_posix.h>
#include <unistd.h>
#include <stdio.h>
#include <poll.h>
#include <string.h>
#include <termios.h>
#include <ctime>

#include <microcdr/microCdr.h>
#include <uORB/uORB.h>

#include "UART_node.h"

#include <uORB/topics/sensor_combined.h>

#define BUFFER_SIZE 256
#define POLL_TIME_MS 1000
#define UPDATE_TIME_MS 1000
#define LOOPS 20
#define USLEEP_MS 2000

extern "C" __EXPORT int micrortps_client_main(int argc, char *argv[]);

int micrortps_client_main(int argc, char *argv[])
{
    int update_time = UPDATE_TIME_MS;
    if (argc > 1) update_time = atoi(argv[1]);

    int poll_time = POLL_TIME_MS;
    if (argc > 2) poll_time = atoi(argv[2]);

    int loops = LOOPS;
    if (argc > 3) loops = atoi(argv[3]);

    int usleep_ms = USLEEP_MS;
    if (argc > 4) usleep_ms = atoi(argv[4]);

    printf("update: %dms poll: %dms loops: %d usleep_ms: %d\n", update_time, poll_time, loops, usleep_ms);
    usleep(2000000);

    UART_node m_uartNode;
    if (0 != m_uartNode.init_uart("/dev/ttyACM0"))
    {
        printf("ERROR UART INIT, EXITING...\n");
        return -1;
    }

    char data_buffer[BUFFER_SIZE] = {};
    char rx_buffer[BUFFER_SIZE] = {};
    uint32_t rx_buff_pos = 0u;

    /* subscribe to topics */
    px4_pollfd_struct_t fds[1];

    // orb_set_interval statblish an update interval period in milliseconds.
    fds[0].fd = orb_subscribe(ORB_ID(sensor_combined));
    orb_set_interval(fds[0].fd, update_time);
    fds[0].events = POLLIN;

    /* advertise topics */
    struct sensor_combined_s sensor_combined_data;
    memset(&sensor_combined_data, 0, sizeof(sensor_combined_data));
    //orb_advert_t sensor_combined_pub = orb_advertise(ORB_ID(sensor_combined), &sensor_combined_data);

    // microBuffer to serialized using the user defined buffer
    struct microBuffer microBufferWriter;
    initStaticAlignedBuffer(data_buffer, BUFFER_SIZE, &microBufferWriter);
    // microCDR structs for managing the microBuffer
    struct microCDR microCDRWriter;
    initMicroCDR(&microCDRWriter, &microBufferWriter);

    // microBuffer to deserialized using the user defined buffer
    struct microBuffer microBufferReader;
    initDeserializedAlignedBuffer(data_buffer, BUFFER_SIZE, &microBufferReader);
    // microCDR structs for managing the microBuffer
    struct microCDR microCDRReader;
    initMicroCDR(&microCDRReader, &microBufferReader);

    //int error_counter = 0;
    uint32_t length = 0;
    //uint32_t sent = 0, received = 0;
    //uint64_t total_send_lenght = 0;
    double total_latency = 0;
    int lat_count = 0;


    struct timespec begin, latency_begin;
    clock_gettime(0, &begin);
    latency_begin = begin;
    int i = 0;
    for (i = 0; i < loops; ++i)
    {
        int poll_ret = px4_poll(fds, 1, poll_time);

        if (poll_ret < 0)
        {
            //++error_counter;
        }
        else
        {
            if (fds[0].revents & POLLIN)
            {
                // obtained data for the file descriptor
                struct sensor_combined_s data;
                // copy raw data into local buffer
                orb_copy(ORB_ID(sensor_combined), fds[0].fd, &data);
                data.baro_temp_celcius = i;
                serialize_sensor_combined(&data, data_buffer, &length, &microCDRWriter);
                m_uartNode.writeToUART((char)58, data_buffer, length);
                clock_gettime(0, &latency_begin);
                //printf("[%d]>> %llu\n", 58, data.timestamp);
                //++sent;
                //total_send_lenght += (length + 9);

                //usleep(usleep_ms);

                char topic_ID = 255;
                bool waiting = true;
                int waited = 0;
                while (waiting && waited < 1000000)
                {
                    if(0 < m_uartNode.readFromUART(&topic_ID, data_buffer, rx_buffer, rx_buff_pos, BUFFER_SIZE))
                    {
                        struct timespec latency;
                        clock_gettime(0, &latency);
                        double elapsed_secs2 = double(latency.tv_sec - latency_begin.tv_sec) + double(latency.tv_nsec - latency_begin.tv_nsec)/double(1000000000);
                        printf("LATENCY, LOOP %03d: %.02f ms, estimated latency %.02f ms\n",
                                i, elapsed_secs2*double(1000), elapsed_secs2*double(500));
                        total_latency += elapsed_secs2*double(500);
                        ++lat_count;

                        switch (topic_ID)
                        {
                            case 58:
                                deserialize_sensor_combined(&sensor_combined_data, data_buffer, &microCDRReader);
                                //orb_publish(ORB_ID(sensor_combined), sensor_combined_pub, &sensor_combined_data);
                                if (int(sensor_combined_data.baro_temp_celcius) == i)
                                {
                                    //printf("                >>[%d] %d\n", 58, i);
                                    waiting = false;
                                }
                                //++received;
                            break;
                        }
                    }
                    else
                    {
                        ++waited;
                    }
                }
            }
        }
    }

    /*struct timespec end;
    clock_gettime(0, &end);
    double elapsed_secs2 = double(end.tv_sec - begin.tv_sec) + double(end.tv_nsec - begin.tv_nsec)/double(1000000000);
    printf("\nSENT: %d RECEIVED: %d in %d LOOPS\n%llu bytes in %.03f seconds sent %.02fKB/s\n",
            sent, received, i, total_send_lenght, elapsed_secs2, (double)total_send_lenght/(1000*elapsed_secs2));*/

    printf("\n          AVERAGE LATENCY %.02f ms\n\n", total_latency/double(lat_count));

    PX4_INFO("exiting");
    fflush(stdout);
    return 0;
}
