#ifndef PROCESS_H
#define PROCESS_H
#include <iostream>
#include <mysql/mysql.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

void my_match_images_insert(MYSQL *mysql, const char *src_name1, const char *src_name2,
                            const char *dst_name, int socket_id);
void my_image_sockets_insert(MYSQL *mysql, const char *ip, unsigned short port);

bool my_image_sockets_has_ip_port(MYSQL *mysql, const char *ip, unsigned port, int &socket_id);

void transaction_test(MYSQL *mysql);

#endif // PROCESS_H
