//
// Created by RudolfLee on 16/12/19.
//

#include "filesys.h"

int usernum() {
    int i;
    for (i = 0; i < PWDNUM; i++) {
        if(pwd[i].p_gid==0)
            return i;
    }
    return -1;
}


void useradd(int user_id,unsigned short username) {
    //��ŵ���4���������û�
    if (user[user_id].u_gid==4) {
        int num = usernum(),i;
        for (i = 0; i < PWDNUM; i++) {
            if(pwd[i].p_uid==username)
                break;
        }
        if (i==PWDNUM) {
            if (num >= 0) {
                pwd[num].p_uid = username;
                pwd[num].p_gid = 2;
                strcpy(pwd[num].password, "1234");
                printf("�û�%hu�����ɹ�����ʼ����Ϊ��1234����ʼ���Ϊ��2\n", username);
            } else
                printf("�û������������ޣ����ܼ������\n");
        }
        else
            printf("���û����ѱ�ʹ�ã������´���\n");
    }
    else
        printf("Ȩ�޲��㣬����ϵ����Ա����Ȩ��\n");
}

void userdel(int user_id,unsigned short username) {
    //��ŵ���4����ɾ���û�
    if (user[user_id].u_gid==4) {
        int i;
        if(user[user_id].u_uid==username) {
            printf("�㲻��ɾ���Լ���\n");
            return;
        }
        for (i = 0; i < PWDNUM; i++) {
            if (username == pwd[i].p_uid) {
                //pwd
                for (int j = i; j < PWDNUM; j++) {
                    pwd[j].p_uid = pwd[j + 1].p_uid;
                    pwd[j].p_gid = pwd[j + 1].p_gid;
                    strcpy(pwd[j].password, pwd[j + 1].password);
                }
                printf("ɾ�����\n");
                break;
            }
        }
        if (i == PWDNUM)
            printf("δ�ҵ����û�\n");
    } else
        printf("Ȩ�޲��㣬����ϵ����Ա����Ȩ��\n");
}

void userauth(int user_id,unsigned short username,unsigned short auth){
    if (user[user_id].u_gid==4) {
        int i;
        for (i = 0; i < PWDNUM; i++) {
            if (username == pwd[i].p_uid) {
                pwd[i].p_gid = auth;
                printf("�޸���ɹ�\n");
                break;
            }
        }
        if (i == PWDNUM)
            printf("δ�ҵ����û�\n");
    } else
        printf("Ȩ�޲��㣬����ϵ����Ա����Ȩ��\n");
}


void passwd(int user_id,char* passwd) {
    //�޸ĵ�ǰ�û����룬ÿ���û�ֻ�ܸ��Լ�������
    int i;
    for (i = 0; i < PWDNUM; ++i) {
        if(pwd[i].p_uid==user[user_id].u_uid) {
            printf("���ٴ������������룺\n");
            char repasswd[PWDSIZ];
            scanf("%s", repasswd);
            while (strcmp(repasswd, passwd)) {
                printf("�������һ�β�ͬ�����ٴ������������룺\n");
                scanf("%s", repasswd);
            };
            printf("�����޸ĳɹ�!\n");
            break;
        }
    }
    if (i==PWDNUM) {
        printf("ϵͳ��������ϵ��Ӫ��\n");
    }
}

void usershow(int user_id) {
    //��ŵ���4������ʾ�����û�
    if (user[user_id].u_gid==4) {
        printf("�û���\t����\t\tȨ��\n");
        for(int i = 0;i<usernum();i++){
            printf("%hu\t%s\t%hu\n",pwd[i].p_uid,pwd[i].password,pwd[i].p_gid);
        }
    }
    else
        printf("Ȩ�޲��㣬����ϵ����Ա����Ȩ��\n");
}

