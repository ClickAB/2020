#include <stdio.h>
#include <stdlib.h>
struct num
{
    int number;
    struct num* next;
};
int getnumber(int m, int n);
int getnumber1(int m, int n);
int main()
{
    int m, n;
    scanf("%d%d", &m, &n);
    printf("循环链表：猴王编号为:%d\n\n\n", getnumber(m, n));
    printf("单向链表：猴王编号为:%d\n", getnumber1(m, n));
    return 0;
}
int getnumber(int m, int n)
{
    struct num* p, * p1, * head, * temp;
    int i = 0, flag;
    p = (struct num*)malloc(sizeof(struct num));
    head = p;
    while (i < m)
    {
        p1 = p;
        p->number = i + 1;
        p = (struct num*)malloc(sizeof(struct num));
        p1->next = p;
        i++;
    }
    p1->next = head;     //形成环状列表
    free(p);
    temp = p1; //temp当前指针的前驱
    i = 1;
    while (i < m)
    {
        flag = 1;     //计数器
        //查找要删除的编号的指针
        while (flag < n)
        {
            temp = head;
            head = head->next;
            flag++;
        }
        temp->next = head->next;
        printf("删除猴子的编号:%d\n", head->number);
        free(head);
        head = temp->next;
        i++;
    }
    return head->number;
}
int getnumber1(int m, int n)
{
    struct num* p, * p1, * head, * temp;
    int i = 0, flag;
    p = (struct num*)malloc(sizeof(struct num));
    head = p;
    if (n == 1)
        return m;
    while (i < m)
    {
        p1 = p;
        p->number = i + 1;
        p = (struct num*)malloc(sizeof(struct num));
        p1->next = p;
        i++;
    }
    p1->next = NULL;   //形成单向链表
    p = head;
    i = 0;
    flag = 0;
    while (i != m - 1)
    {
        if (flag == n - 1)
        {
            printf("删除猴子的编号:%d\n", p->number);
            if (p == head)   //当删除的节点位于节点头时
            {
                head = head->next;
                p = head;
            }
            else if (p->next == NULL) //当初节点位于节点尾时
            {
                temp->next = NULL;
                p = head;
            }
            else                   //位于中间
            {
                temp->next = p->next;
                p = p->next;
            }
            i++;
            flag = 0;
        }

        //当指针到达链表尾部是，使其指向头指针。

        if (p->next == NULL)
        {
            p = head;
        }
        else
        {
            temp = p;
            p = p->next;
        }
        flag++;
    }
    return head->number;
}