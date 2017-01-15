#include <iostream>
#include <mysql/mysql.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "my_process.h"

using namespace std;

int main()
{
    MYSQL *mysql;
    mysql = mysql_init(NULL);
//    mysql_options(&mysql,MYSQL_READ_DEFAULT_GROUP,"mysql2");
    if (mysql == NULL) {
      printf("Error %u: %s\n", mysql_errno(mysql), mysql_error(mysql));
      exit(1);
    }

    if (!mysql_real_connect(mysql,"localhost","root","root","matcher",0,NULL,0))
    {
        fprintf(stderr, "Failed to connect to database: Error: %s\n",
        mysql_error(mysql));
    }
    my_match_images_insert(mysql, "image1.jpg", "image2.jpg", "dst1.jpg", 1);
    my_image_sockets_insert(mysql, "219.216.87.20", 80);

    int socket_id;
    cout << my_image_sockets_has_ip_port(mysql, "219.216.87.20", 80, socket_id) << endl;
    cout << my_image_sockets_has_ip_port(mysql, "219.216.87.0", 90, socket_id) << endl;

//    transaction_test(mysql);

    mysql_close(mysql);
    return 0;
}

