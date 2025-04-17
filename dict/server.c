#include "my.h"
// singal:0成功结束-1错误6联系
// return 0正常 -1异常
sqlite3 *db;
int ser_history(int new_sockfd, MSG *msg)
{
    int row, column;
    db = NULL;
    errmsg = NULL;
    char **resultp = NULL;
    char sql[512] = {0};
    // char sql[512] = "select * from history ;";
    sprintf(sql, "select * from history where username='%s';", username);
    ret = sqlite3_open("./dict.db", &db);
    if (ret < 0)
    {
        perror("sqlite3_open failed");
        exit(-1);
    }
    ret = sqlite3_get_table(db, sql, &resultp, &row, &column, &errmsg);
    // if (ret != 0)
    // {
    //     perror("sqlite3_open failed 1");
    // }
    msg->len = row;
    if (row == 0)
    {
        msg->signal = 0;
        send(new_sockfd, msg, sizeof(MSG), 0);
        return 0;
    }

    for (int i = 0; i < row; i++)
    {
        msg->signal = 0;
        strcpy(msg->data, resultp[3 * i + 4]);
        strcat(msg->data, "         ");
        strcat(msg->data, resultp[3 * i + 5]);
        send(new_sockfd, msg, sizeof(MSG), 0);
        memset(msg->data, 0, sizeof(msg->data));
    }
    msg->signal = -1;
    send(new_sockfd, msg, sizeof(MSG), 0);
    return 0;
}
int create_history(MSG *msg)
{
    printf("%s\n", msg->username);
    errmsg = NULL;
    db = NULL;
    char sql[256] = {0};
    time_t t;
    struct tm *nowtime;
    time(&t);
    nowtime = localtime(&t);
    ret = sqlite3_open("./dict.db", &db);
    if (ret < 0)
    {
        perror("sqlite3_open failed");
        return -1;
    }
    sprintf(sql, "insert into history values('%s','%s','%d-%d-%d %d:%d');", username, msg->wordname, nowtime->tm_year + 1900, nowtime->tm_mon + 1, nowtime->tm_mday, nowtime->tm_hour, nowtime->tm_min);
    ret = sqlite3_exec(db, sql, NULL, NULL, &errmsg);
    if (ret != 0)
    {
        puts("插入历史数据失败");
        return -1;
    }
    puts("插入历史数据成功");
    return 0;
}

int ser_expend(FILE *fp, int new_sockfd, MSG *msg, char *word)
{
    while (fgets(word, sizeof(word), fp) != NULL)
    {
        if (strncmp(msg->wordname, word, msg->len) == 0)
        {

            int result = sscanf(word, "%49s %[^\n]", msg->wordname, msg->data);
            msg->signal = 6;
            send(new_sockfd, msg, sizeof(MSG), 0);
        }
    }
    msg->signal = -1;
    send(new_sockfd, msg, sizeof(MSG), 0);
}
int ser_search(int new_sockfd, MSG *msg)
{
    char word[256] = {0};
    FILE *fp = fopen("/home/linux/dict/dict.txt", "r");
    if (fp == NULL)
    {
        perror("fopen failed");
        return -1;
    }
    while (fgets(word, sizeof(word), fp) != NULL)
    {

        // if (word[strlen(word) - 1] == '\n')
        // {
        //     if (strncmp(msg->wordname, word, msg->len) == 0)
        //     {
        //         deal_space(new_sockfd, msg, word);
        //         return 0;
        //     }
        // }
        if (word[strlen(word) - 1] == '\n')
        {
            int result = sscanf(word, "%49s %[^\n]", msg->wordname, msg->data);
            if (msg->len == strlen(msg->wordname))
            {
                msg->signal = 0;
                send(new_sockfd, msg, sizeof(MSG), 0);
                puts("查询单词成功");
                return 0;
            }
            else
            {
                msg->signal = -1;
                send(new_sockfd, msg, sizeof(MSG), 0);
                puts("查询单词失败");
                return -1;
            }
            // if (strncmp(msg->wordname, word, msg->len) == 0)
            // {
            // ser_expend(fp, new_sockfd, msg, word);
            //     return 0;
            // }
        }
    }
}
// 0注册成功-1注册失败
int ser_register(int new_sockfd, MSG *msg)
{
    puts("注册中");
    int row = 0, column = 0;
    char sql[1024] = {0};
    char **resultp = NULL;
    sprintf(sql, "select * from user_info where username='%s'and passwd='%s';", msg->username, msg->passwd);
    ret = sqlite3_get_table(db, sql, &resultp, &row, &column, &errmsg);
    if (ret < 0)
    {
        printf("%s\n", errmsg);
    }
    if (row > 0)
    {

        msg->signal = -1;
        send(new_sockfd, msg, sizeof(MSG), 0);
        puts("注册失败");
        return -1;
    }
    else
    {

        memset(sql, 0, sizeof(sql));
        sprintf(sql, "insert into user_info values('%s','%s');", msg->username, msg->passwd);
        sqlite3_exec(db, sql, NULL, NULL, &errmsg);
        msg->signal = 0;
        send(new_sockfd, msg, sizeof(MSG), 0);
        puts("注册成功");
        return 0;
    }
}
int ser_login(int new_sockfd, MSG *msg)
{
    puts("登录中");
    int row = 0, column = 0;
    char sql[1024] = {0};
    char **resultp = NULL;
    ret = sqlite3_open("./dict.db", &db);
    if (ret < 0)
    {
        perror("sqlite3_open failed");
        exit(-1);
    }
    sprintf(sql, "select * from user_info where username='%s'and passwd='%s';", msg->username, msg->passwd);
    ret = sqlite3_get_table(db, sql, &resultp, &row, &column, &errmsg);
    if (ret < 0)
    {
        printf("%s\n", errmsg);
    }
    if (row == 1)
    {
        msg->signal = 0;
        send(new_sockfd, msg, sizeof(MSG), 0);
        strcpy(username, msg->username);
        puts("登录成功");
        return 0;
    }
    else
    {
        msg->signal = -1;
        send(new_sockfd, msg, sizeof(MSG), 0);
        puts("登录失败");
        return -1;
    }
}
void init_sqlite()
{
    errmsg = NULL;
    db = NULL;
    ret = sqlite3_open("./dict.db", &db);
    if (ret < 0)
    {
        perror("sqlite3_open failed");
        exit(-1);
    }

    char sql1[256] = "create table if not exists user_info(username varchar(20),passwd varchar(20));";
    ret = sqlite3_exec(db, sql1, NULL, NULL, &errmsg);
    if (ret)
    {
        printf("%s\n", errmsg);
        exit(-1);
    }
    char sql2[256] = "create table if not exists history(username varchar(20),word varchar(50),time varchar(50));";
    ret = sqlite3_exec(db, sql2, NULL, NULL, &errmsg);
    if (ret)
    {
        printf("%s\n", errmsg);
        exit(-1);
    }
    puts("数据库启动成功");
}
void *server(void *arg)
{
    MSG msg = {0};
    int new_sockfd = *((int *)arg);
    while (1)
    {
        ret = recv(new_sockfd, &msg, sizeof(MSG), 0);

        if (ret <= 0)
        {
            puts("客户端断开连接.");
            close(new_sockfd);
            pthread_exit(NULL);
            exit(-1);
        }
        switch (msg.signal)
        {
        case 1:
            ser_register(new_sockfd, &msg);

            break;
        case 2:
            ser_login(new_sockfd, &msg);
            break;
        case 3:
            if (!ser_search(new_sockfd, &msg))
            {
                create_history(&msg);
            }

            break;
        case 4:
            ser_history(new_sockfd, &msg);
            break;
        case 5:
            /* code */
            break;

        default:
            break;
        }
    }
}
int main(int argc, char const *argv[])
{
    init_sqlite(); // 创建数据库
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        perror("socket failed");
        exit(-1);
    }
    struct sockaddr_in server_addr = {0};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    // server_addr.sin_addr.s_addr = inet_addr("NET");
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    int ret = bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    listen(sockfd, 5);
    while (1)
    {
        int new_sockfd = accept(sockfd, NULL, NULL);
        pthread_t tid;
        pthread_create(&tid, NULL, server, &new_sockfd);
    }

    return 0;
}
