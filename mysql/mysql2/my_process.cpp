#include "my_process.h"

void my_match_images_insert(MYSQL *mysql, const char *src_name1, const char *src_name2,
                            const char *dst_name, int socket_id)
{
#define INSERT_SAMPLE "INSERT INTO \
                        match_images(src_name1,src_name2,dst_name, socket_id) \
                        VALUES(?,?,?,?)"
    MYSQL_STMT *stmt;
    MYSQL_BIND bind[4];
    my_ulonglong affected_rows;
    int param_count;
    unsigned long str_length1, str_length2, str_length3;

    /* Prepare an INSERT query with 3 parameters */
    /* (the TIMESTAMP column is not named; the server */
    /* sets it to the current date and time) */
    stmt = mysql_stmt_init(mysql);
    if (!stmt)
    {
        fprintf(stderr, " mysql_stmt_init(), out of memory\n");
        exit(0);
    }
    if (mysql_stmt_prepare(stmt, INSERT_SAMPLE, strlen(INSERT_SAMPLE)))
    {
        fprintf(stderr, " mysql_stmt_prepare(), INSERT failed\n");
        fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
        exit(0);
    }
    fprintf(stdout, " prepare, INSERT successful\n");
    /* Get the parameter count from the statement */
    param_count= mysql_stmt_param_count(stmt);
    fprintf(stdout, " total parameters in INSERT: %d\n", param_count);
    if (param_count != 4) /* validate parameter count */
    {
        fprintf(stderr, " invalid parameter count returned by MySQL\n");
        exit(0);
    }


    /* Bind the data for all 3 parameters */
    memset(bind, 0, sizeof(bind));
    /* INTEGER PARAM */
    /* This is a number type, so there is no need
    to specify buffer_length */
    bind[0].buffer_type= MYSQL_TYPE_STRING;
    bind[0].buffer= const_cast<char *>(src_name1);
    bind[0].buffer_length= strlen(src_name1);
    bind[0].is_null= 0;
    bind[0].length= &str_length1;

    bind[1].buffer_type= MYSQL_TYPE_STRING;
    bind[1].buffer= const_cast<char *>(src_name2);
    bind[1].buffer_length= strlen(src_name2);
    bind[1].is_null= 0;
    bind[1].length= &str_length2;

    bind[2].buffer_type= MYSQL_TYPE_STRING;
    bind[2].buffer= const_cast<char *>(dst_name);
    bind[2].buffer_length= strlen(dst_name);
    bind[2].is_null= 0;
    bind[2].length= &str_length3;

    bind[3].buffer_type= MYSQL_TYPE_LONG;
    bind[3].buffer= (void*)(&socket_id);
    bind[3].buffer_length= strlen(dst_name);
    bind[3].is_null= 0;
    bind[3].length= 0;

    /* Bind the buffers */
    if (mysql_stmt_bind_param(stmt, bind))
    {
        fprintf(stderr, " mysql_stmt_bind_param() failed\n");
        fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
        exit(0);
    }

    str_length1= strlen(src_name1);
    str_length2= strlen(src_name2);
    str_length3= strlen(dst_name);

    /* Execute the INSERT statement - 1*/
    if (mysql_stmt_execute(stmt))
    {
        fprintf(stderr, " mysql_stmt_execute(), 1 failed\n");
        fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
        exit(0);
    }
    /* Get the number of affected rows */
    affected_rows= mysql_stmt_affected_rows(stmt);
    fprintf(stdout, " total affected rows(insert 1): %lu\n",
    (unsigned long) affected_rows);
    if (affected_rows != 1) /* validate affected rows */
    {
        fprintf(stderr, " invalid affected rows by MySQL\n");
        exit(0);
    }

    printf("affect_rows: %d\n", affected_rows);
    /* Close the statement */
    if (mysql_stmt_close(stmt))
    {
        fprintf(stderr, " failed while closing the statement\n");
        fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
        exit(0);
    }
}


void my_image_sockets_insert(MYSQL *mysql, const char *ip, unsigned short port)
{
#define INSERT_SAMPLE "INSERT INTO \
                        image_sockets(ip, port) \
                        VALUES(?,?)"
    MYSQL_STMT *stmt;
    MYSQL_BIND bind[2];
    my_ulonglong affected_rows;
    int param_count;
    unsigned long str_length;

    /* Prepare an INSERT query with 3 parameters */
    /* (the TIMESTAMP column is not named; the server */
    /* sets it to the current date and time) */
    stmt = mysql_stmt_init(mysql);
    if (!stmt)
    {
        fprintf(stderr, " mysql_stmt_init(), out of memory\n");
        exit(0);
    }
    if (mysql_stmt_prepare(stmt, INSERT_SAMPLE, strlen(INSERT_SAMPLE)))
    {
        fprintf(stderr, " mysql_stmt_prepare(), INSERT failed\n");
        fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
        exit(0);
    }
    fprintf(stdout, " prepare, INSERT successful\n");
    /* Get the parameter count from the statement */
    param_count= mysql_stmt_param_count(stmt);
    fprintf(stdout, " total parameters in INSERT: %d\n", param_count);
    if (param_count != 2) /* validate parameter count */
    {
        fprintf(stderr, " invalid parameter count returned by MySQL\n");
        exit(0);
    }

    /* Bind the data for all 3 parameters */
    memset(bind, 0, sizeof(bind));
    /* INTEGER PARAM */
    /* This is a number type, so there is no need
    to specify buffer_length */
    bind[0].buffer_type= MYSQL_TYPE_STRING;
    bind[0].buffer= const_cast<char *>(ip);
    bind[0].buffer_length= strlen(ip);
    bind[0].is_null= 0;
    bind[0].length= &str_length;

    bind[1].buffer_type= MYSQL_TYPE_SHORT;
    bind[1].buffer= &port;
    bind[1].buffer_length= sizeof(port);
    bind[1].is_null= 0;
    bind[1].length= 0;

    /* Bind the buffers */
    if (mysql_stmt_bind_param(stmt, bind))
    {
        fprintf(stderr, " mysql_stmt_bind_param() failed\n");
        fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
        exit(0);
    }

    str_length= strlen(ip);

    /* Execute the INSERT statement - 1*/
    if (mysql_stmt_execute(stmt))
    {
        fprintf(stderr, " mysql_stmt_execute(), 1 failed\n");
        fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
        exit(0);
    }
    /* Get the number of affected rows */
    affected_rows= mysql_stmt_affected_rows(stmt);
    fprintf(stdout, " total affected rows(insert 1): %lu\n",
    (unsigned long) affected_rows);
    if (affected_rows != 1) /* validate affected rows */
    {
        fprintf(stderr, " invalid affected rows by MySQL\n");
        exit(0);
    }

    printf("affect_rows: %d\n", affected_rows);
    /* Close the statement */
    if (mysql_stmt_close(stmt))
    {
        fprintf(stderr, " failed while closing the statement\n");
        fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
        exit(0);
    }
}


bool my_image_sockets_has_ip_port(MYSQL *mysql, const char *ip, unsigned port, int &socket_id)
{
    char cmd[100];
    sprintf(cmd, "select socket_id from image_sockets where ip=\"%s\" and port=%d", ip, port);

    if(mysql_query(mysql, cmd))
    {
        printf("Error %u: %s\n", mysql_errno(mysql), mysql_error(mysql));
        exit(1);
    }

    MYSQL_RES *result = mysql_store_result(mysql);
    if(NULL != result && mysql_num_rows(result))
    {
        MYSQL_ROW row;
        row = mysql_fetch_row(result);
        socket_id = atoi(row[0]);
        return true;
    }
    else if(0 == mysql_errno(mysql))
    {
        return false;
    }
    else
    {
        printf("Error %u: %s\n", mysql_errno(mysql), mysql_error(mysql));
        exit(1);
    }
}

unsigned int get_image_sockets_id(MYSQL_RES *result)
{
    
}

void my_image_sockets_process_result(MYSQL_RES *result)
{
    MYSQL_ROW    row;
    MYSQL_FIELD  *field;
    unsigned int i;
    unsigned int row_count= 0;

    if (!result)
        return;

    while ((row= mysql_fetch_row(result)) != NULL)
    {
        mysql_field_seek(result, 0);
        for(i= 0; i< mysql_num_fields(result); i++)
        {
            field= mysql_fetch_field(result);
            if (row[i] == NULL)
            fprintf(stdout, " %-*s |", (int) field->max_length, "NULL");
            else if (IS_NUM(field->type))
            fprintf(stdout, " %*s |", (int) field->max_length, row[i]);
            else
            fprintf(stdout, " %-*s |", (int) field->max_length, row[i]);
        }
        row_count++;
    }
}



void transaction_test(MYSQL *mysql)
{
    int error = 0;
    mysql_autocommit(mysql, false);

    if(mysql_query(mysql, "insert into image_sockets (ip, port)\
                   values(\"219.216.87.25\", 100)"))
    {
            printf("Error %u: %s\n", mysql_errno(mysql), mysql_error(mysql));
            error = 1;
    }
    if(mysql_query(mysql, "inser intert into image_sockets (ip, prot)\
                   values(\"219.216.87.25\")"))
    {
            printf("Error %u: %s\n", mysql_errno(mysql), mysql_error(mysql));
            error = 1;
    }

    if(1 == error)
    {
       mysql_rollback(mysql);
    }
       else
    {
       mysql_commit(mysql);
    }

     mysql_autocommit(mysql, true);
}
