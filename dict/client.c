#include "my.h"
// singal:1注册2登录3查询单词4查询历史记录5退出6联想
// return 0正常 -1异常
int cli_history(int sockfd)
{
    MSG msg = {0};
    msg.signal = 4;
    send(sockfd, &msg, sizeof(MSG), 0);
    puts("历史记录:");
    while (1)
    {
        if (msg.signal == -1)
        {
            printf("当前历史记录有%d条.", msg.len);
            return 0;
        }
        recv(sockfd, &msg, sizeof(MSG), 0);
        printf("%s\n", msg.data);
    }
}
// int cli_expend(int sockfd, MSG *msg)
// {
//     while (1)
//     {
//         recv(sockfd, &msg, sizeof(MSG), 0);
//         printf("其他单词:%s", msg->wordname);
//         if (msg->signal == -1)
//         {
//             break;
//         }
//     }
// }
int cli_search(int sockfd)
{
    MSG msg = {0};
    printf("查询单词,3返回上一级:");
    scanf("%s", msg.wordname);
    if (atoi(msg.wordname) == 3)
    {
        return -1;
    }

    msg.signal = 3;
    msg.len = strlen(msg.wordname);
    send(sockfd, &msg, sizeof(MSG), 0);
    while (1)
    {
        recv(sockfd, &msg, sizeof(MSG), 0);
        if (msg.signal == 0)
        {
            printf("单词:%s\n", msg.wordname);
            printf("释义:%s\n", msg.data);

            // cli_expend(sockfd, &msg);
            cli_search(sockfd);
            return 0;
        }
        else
        {
            puts("无此单词");

            // cli_expend(sockfd, &msg);
            cli_search(sockfd);
            return -1;
        }
    }
}
int cli_register(int sockfd)
{
    MSG msg = {0};
    printf("***注册***\n");
    printf("用户名:");
    scanf("%s", msg.username);
    printf("密码:");
    scanf("%s", msg.passwd);
    msg.signal = 1;
    send(sockfd, &msg, sizeof(MSG), 0);
    recv(sockfd, &msg, sizeof(MSG), 0);
    if (msg.signal == -1)
    {
        puts("注册失败");
        return -1;
    }
    puts("注册成功");
    return 0;
}
int cli_login(int sockfd)
{
    MSG msg = {0};
    printf("***登录***\n");
    printf("用户名:");
    scanf("%s", msg.username);
    printf("密码:");
    scanf("%s", msg.passwd);
    msg.signal = 2;
    send(sockfd, &msg, sizeof(MSG), 0);
    recv(sockfd, &msg, sizeof(MSG), 0);
    if (msg.signal == -1)
    {
        puts("登录失败");
        return -1;
    }
    puts("登录成功");
    return 0;
}
void firstmenu()
{
    printf("\n*************************************\n");
    printf("*            电子词典项目           *");
    printf("\n***************************************");
    printf("\n*       1.注册2登录3.退出            * \n");
    printf("\n***************************************");
    printf("\n*        请 输入您的 选 择:           *\n");
}
void secondmenu()
{
    printf("\n///////////////////////////////////////////");
    printf("\n*******************************************");
    printf("\n*      欢  迎  使  用  电  子  词  典      *\n");
    printf("\n*******************************************");
    printf("\n 1.査询单词 2.査询历史单词 3.返回上一级 4.退出 \n");
    printf("\n*******************************************");
    printf("\n///////////////////////////////////////////");
    printf("\n*             请 输入您的 选 择:           *\n");
}
void do_client(int scokfd)
{
    firstmenu();
    while (1)
    {
        int num;
        puts("选择:");
        scanf("%d", &num);
        switch (num)
        {
        case 1:
            cli_register(scokfd);
            return;
        case 2:
            if (!cli_login(scokfd))
            {
                while (1)
                {
                    secondmenu();
                    scanf("%d", &num);
                    switch (num)
                    {
                    case 1:
                        cli_search(scokfd);
                        break;
                    case 2:
                        cli_history(scokfd);
                        break;
                    case 3:
                        // break;
                        return;
                    case 4:
                        exit(0);
                    default:
                        break;
                    }
                }
                        }
            return;
            // break;
        case 3:
            exit(0);
        default:
            break;
        }
    }
}
int main(int argc, char const *argv[])
{
    int num;
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        perror("sockfd failed");
        exit(-1);
    }
    struct sockaddr_in client_addr = {0};
    client_addr.sin_family = AF_INET;
    // client_addr.sin_addr.s_addr = inet_addr("NET");
    client_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    client_addr.sin_port = htons(PORT);
    connect(sockfd, (struct sockaddr *)&client_addr, sizeof(client_addr));
    while (1)
    {
        // cli_register(sockfd);
        // cli_login(sockfd);
        // cli_search(sockfd);
        // cli_history(sockfd);
        do_client(sockfd);
    }

    return 0;
}
