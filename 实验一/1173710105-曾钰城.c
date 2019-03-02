#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define NULL ((void *)0)

struct PolyNode
{
    float coef;//记录系数
    int exp;//记录指数
    struct PolyNode *next ;//记录下一节点的
};

typedef struct PolyNode* PolyPointer;
typedef struct PolyNode* Position;
PolyPointer PolyMult(PolyPointer a, PolyPointer b, PolyPointer available);// 乘法
PolyPointer New_PolyNode_avail(PolyPointer available);
PolyPointer Avail_Insert(float coef, int exp, Position c, PolyPointer available);
PolyPointer New_PolyNode();
PolyPointer Create_Polynomial(char *filename,PolyPointer available);
float calculate(float x, PolyPointer List);
PolyPointer PolyAdd (PolyPointer a, PolyPointer b, PolyPointer available);
PolyPointer PolySub (PolyPointer a, PolyPointer b, PolyPointer available);
void Delete_Poly(PolyPointer L);
void PolyDiv(PolyPointer quotient, PolyPointer remainder,PolyPointer a, PolyPointer b, PolyPointer available);
void Destroy_List(PolyPointer p);
void Print_Poly(PolyPointer p);
void recycle_avail(PolyPointer p, PolyPointer available);
void Write_Polynomial_To_File(char *filename,PolyPointer head);


int main()
{
    char *filename1 = "coef_exp1.txt";
    char *filename2 = "coef_exp2.txt";
    PolyPointer available = New_PolyNode();//用于存储可用空间
    PolyPointer head1 = Create_Polynomial(filename1,available);//加载多项式1
    PolyPointer head2 = Create_Polynomial(filename2,available);//加载多项式2
    float x0 = 0.0f;
    float result1 = calculate(x0,head1);
    float result2 = calculate(x0,head2);
    PolyPointer head3 = PolyAdd(head1,head2,available);
    PolyPointer head4 = PolySub(head1,head2,available);
    PolyPointer head5 = PolyMult(head1,head2,available);
    Write_Polynomial_To_File("coef_exp3.txt",head5);
    PolyPointer quotient = New_PolyNode_avail(available);
    PolyPointer remainder = New_PolyNode_avail(available);
    PolyDiv(quotient,remainder,head1,head2,available);
    printf("多项式1：");
    Print_Poly(head1);
    printf("多项式2：");
    Print_Poly(head2);
    printf("多项式1在点X=%.1f的值为：%.1f\n",x0,result1);
    printf("多项式2在点X=%.1f的值为：%.1f\n",x0,result2);
    printf("多项式1 + 多项式2 的值为：");
    Print_Poly(head3);
    printf("多项式1 - 多项式2 的值为：");
    Print_Poly(head4);
    printf("多项式1 * 多项式2 的值为：");
    Print_Poly(head5);
    printf("多项式1 / 多项式2 的值为：\n");
    printf("商  为：");
    Print_Poly(quotient);
    printf("余数为：");
    Print_Poly(remainder);

    //Write_Polynomial_To_File("coef_exp3.txt",head3);
    Destroy_List(head1);
    Destroy_List(head2);
    Destroy_List(head3);
    Destroy_List(head4);
    Destroy_List(head5);
    Destroy_List(quotient);
    Destroy_List(remainder);
    Destroy_List(available);//删除多余的可用空间

    return 0;
}

/*按降幂顺序创建多项式，多项式参数从文件中读取*/
PolyPointer Create_Polynomial(char *filename,PolyPointer available)
{
    FILE *fp;
    fp = fopen(filename,"r");
    if(fp==NULL)
    {
        printf("打开文件失败\n");
        return NULL;
    }
    PolyPointer head, p;
    head = New_PolyNode();//多项式头指针
    float coef;
    int exp;
    while(!feof(fp))
    {
        p = head;
        fscanf(fp,"%f\t%d\n",&coef,&exp);
        //printf("%f\t%d\n",coef,exp);
        while((p->next!=NULL)&&((p->next->exp)>=exp))//找到正确的插入位置
            p = p->next;
        Avail_Insert(coef,exp,p,available);//在指定位置插入一个节点
    }
    fclose(fp);
    return head;
}

/*创建一个新节点，并且将这个节点初始化*/
PolyPointer New_PolyNode()
{
    PolyPointer node = (PolyPointer)malloc(sizeof(struct PolyNode));
    node->coef = 0.0;
    node->exp = 0;
    node->next = NULL;
    return node;
}

/*将多项式写入到文件之中去*/
void Write_Polynomial_To_File(char *filename,PolyPointer head)
{
    FILE *fp;
    fp = fopen(filename,"w");
    if(fp==NULL)
    {
        printf("打开文件失败\n");
        return;
    }
    PolyPointer p = head;
    while(p->next)
    {
        fprintf(fp,"%.2f\t%d\n",p->next->coef,p->next->exp);
        p = p->next;
    }
    fclose(fp);
}
/*计算多项式在点x=x0的值*/
float calculate(float x, PolyPointer List)
{
    float result = 0;
    PolyPointer p;
    p = List;
    while(p->next)
    {
        result += (p->next->coef)*pow(x,p->next->exp);
        p = p->next;
    }
    return result;
}
/*比较两个节点的值*/
char  Compare (int x, int y)
{
    char c;
    if( x == y )
        c = '=';
    else if( x > y )
        c = '>';
    else
        c = '<';
    return c;
}

/*在列表尾部附加一个节点*/
/*PolyPointer Attch(float coef, int exp, PolyPointer d)
{
    PolyPointer x;
    x = New_PolyNode();
    x->coef = coef;
    x->exp = exp;
    d->next= x;
    return  x;
}*/
/*两个多项式相加*/
PolyPointer PolyAdd (PolyPointer a, PolyPointer b, PolyPointer available)
{
    PolyPointer p, q, d, c;
    float y ;
    p = a->next;
    q = b->next;
    c = New_PolyNode_avail(available);
    d = c;
    while ((p!=NULL)&&(q!=NULL))
    {
        switch (Compare(p->exp,q->exp))
        {
            case '=' :
                y = p->coef + q->coef ;
                if(fabs(y)>0.01)//如果多项式幂次相等两项系数相加不等于0，则将这项附加到表尾
                    d = Avail_Insert(y,p->exp,d,available);
                p = p->next;
                q = q->next;
                break;
            case '>':
                d = Avail_Insert(p->coef, p->exp, d, available);
                p = p->next;
                break;
            case '<':
                d = Avail_Insert(q->coef, q->exp, d, available);
                q = q->next;
                break;
        }
    }
    //如果多项式1还有项未附加完成，则继续进行附加操作
    while (p!=NULL)
    {
        d = Avail_Insert( p->coef, p->exp, d, available);
        p = p->next ;
    }
    //如果多项式2还有项未附加完成，则继续进行附加操作
    while (q !=NULL)
    {
        d = Avail_Insert(q->coef, q->exp, d, available);
        q = q->next ;
    }
    d->next = NULL;
    //当相加等于0时，只有表头，不能参与后续运算，这时加上一个0X^0
    if(c->next==NULL)
    {
        c->next = New_PolyNode_avail(available);
    }
    return c;
}
/*两个多项式相减*/
PolyPointer PolySub (PolyPointer a, PolyPointer b,PolyPointer available)
{
    PolyPointer p, q, d, c;
    float y ;
    p = a->next;
    q = b->next;
    c = New_PolyNode_avail(available);
    d = c;
    while ((p!=NULL)&&(q!=NULL))
    {
        switch (Compare(p->exp,q->exp))
        {
            case '=' :
                y = p->coef - q->coef ;
                if(fabs(y)>0.01)//如果多项式幂次相等两项系数相减不等于0，则将这项附加到表尾
                    d = Avail_Insert(y, p->exp, d, available);
                p = p->next;
                q = q->next;
                break;
            case '>':
                d = Avail_Insert(p->coef, p->exp, d, available);
                p = p->next;
                break;
            case '<':
                d = Avail_Insert(-q->coef, q->exp, d,available);
                q = q->next;
                break;
        }
    }
    //如果多项式1还有项未附加完成，则继续进行附加操作
    while (p!=NULL)
    {
        d = Avail_Insert(p->coef, p->exp, d, available);
        p = p->next ;
    }
    //如果多项式2还有项未附加完成，则继续进行附加操作
    while (q !=NULL)
    {
        d = Avail_Insert(-q->coef,q->exp,d, available);
        q = q->next ;
    }
    d->next = NULL;
    //当相减等于0时，只有表头，不能参与后续运算，这时加上一个0X^0
    if(c->next==NULL)
    {
        c->next = New_PolyNode_avail(available);
    }
    return c;
}

/*两多项式相乘，思路：依次将多项式1中的每一项依次乘以多项式2，
然后将结果按降幂次序添加到新的多项式*/
PolyPointer PolyMult(PolyPointer a, PolyPointer b, PolyPointer available)// 乘法
{
    /*
    多创建一个列表，用于存储相乘求和之后，系数为0的淘汰项，以便后来复用
    */
    PolyPointer p, q, c2, avail;
    PolyPointer c = New_PolyNode_avail(available); //用于存储相乘之后多项式的结果
    int acoef, aexp, bcoef, bexp;
    int AB_Coef, AB_Exp;
    p = a;//多项式1的节点指针
    q = b;//多项式2的节点指针
    c2 = c;//相乘之后多项式节点指针
    avail = available;//可用空间节点指针
    while(p->next!=NULL)//遍历多项式一
    {
        acoef = p->next->coef;
        aexp  = p->next->exp;
        q = b;
        p = p->next;
        while(q->next!=NULL)//遍历多项式2
        {
            bcoef = q->next->coef;
            bexp  = q->next->exp;
            AB_Coef = acoef*bcoef;
            q = q->next;
            if(AB_Coef==0)
                continue;
            AB_Exp = aexp+bexp;
            c2 = c;
            //初始化新的多项式
            if(c2->next==NULL)
            {
                Avail_Insert(AB_Coef,AB_Exp,c2,available);
                continue;
            }

            while(c2->next!=NULL)
            {
                //按降幂顺序将结果附加到新的多项式
                if((c2->next->exp)>AB_Exp)
                {
                    c2 = c2->next;
                    if(c2->next==NULL)
                    {
                        Avail_Insert(AB_Coef,AB_Exp,c2,available);//相乘结果是这新多项式中幂次最小的，故附加到末尾
                        break;
                    }
                    continue;
                }
                //若相乘结果项的幂次在多项式已经存在，则只需在新的多项式中将结果合并
                if(c2->next->exp==AB_Exp)
                {
                    int Temp_Coef = c2->next->coef+AB_Coef;
                    //若果合并结果项的系数为0，则在新的多项式中去除该节点，将该节点回收到可用空间
                    if(Temp_Coef==0)
                    {
                        avail->next = c2->next;
                        avail = avail->next;
                        c2->next = avail->next;
                        avail->next = NULL;
                    }
                    else
                    {
                        //若果合并结果项的系数不为0，则只需修改该项系数
                        c2->next->coef = Temp_Coef;
                    }
                    break;
                }
                else
                {
                    //如果相乘结果项的幂次不为最值，且未曾出现，则在按降幂次序在相应位置插入该结果项
                    Avail_Insert(AB_Coef,AB_Exp,c2,available);
                    break;
                }
            }

        }
    }
    return c;
}
/*销毁列表*/
void Destroy_List(PolyPointer p)
{
    Position q;
    while(p)
    {
        q = p->next;
        free(p);
        p = q;
    }
}

/*利用多余的节点空间创建新节点，完成插入元素操作*/
PolyPointer Avail_Insert(float coef, int exp, Position c, PolyPointer available)
{

    PolyPointer new_node = New_PolyNode_avail(available);
    new_node->coef = coef;
    new_node->exp  = exp;
    new_node->next = c->next;
    c->next = new_node;
    return new_node;
}
/*多项式除法
1、将分子的第一项除以分母的最高次项得到首商
2、将分母乘以首商
3、从分子的相应项中减去刚得到的乘积
4、把第一余式当作新的被除式，重复前三步，得到次商与第二余式
5、重复第四步，得到三商与第三余式。余式小于除式次数，运算结束。
*/
void PolyDiv(PolyPointer quotient, PolyPointer remainder,PolyPointer a, PolyPointer b, PolyPointer available)
{
    PolyPointer nodeheader = New_PolyNode_avail(available);//用于储存首商的节点头
    PolyPointer node = New_PolyNode_avail(available);//用于储存首商
    PolyPointer a1, b1, quo;
    PolyPointer temp1, temp2;
    temp1 = NULL;//用于记录首商*除数
    temp2 = NULL;//用于记录新的被除数 = 被除数 - 首商*除数
    nodeheader->next = node;
    a1 = a;//用于记录被除数
    b1 = b;//用于记录除数
    quo = quotient;
    while((a1->next->exp)>=(b1->next->exp))
    {
        quo->next = New_PolyNode_avail(available);//用于记录除数结果
        quo = quo->next;
        node->coef = a1->next->coef/b1->next->coef;
        node->exp  = a1->next->exp - b1->next->exp;
        quo->coef = node->coef;
        quo->exp  = node->exp;
        temp1 = PolyMult(nodeheader,b,available);//获取首商*除数
        if(temp2)
            recycle_avail(temp2,available);//回收内存空间到可用空间
        temp2 = PolySub(a1,temp1,available);//用于获取新的被除数 = 被除数 - 首商*除数
        if(temp1)
            recycle_avail(temp1,available);//回收内存空间到可用空间
        a1 = temp2;//更新被除数
    }
    remainder->next = a1->next;//获得余数
    recycle_avail(nodeheader,available);//回收首商节点
}
/*打印多项式*/
void Print_Poly(PolyPointer q)
{
    PolyPointer p = q;
    while(p->next)
    {
        printf("%.1fX^%d",p->next->coef,p->next->exp);
        p = p->next;
        if(p->next)
        {
            if(p->next->coef>0)
                printf("+");
        }
    }
    printf("\n");
}
/*利用可用空间创建新节点*/
PolyPointer New_PolyNode_avail(PolyPointer available)
{
    PolyPointer new_node;
    if(available->next!=NULL)//判断可用空间是否还有可用空间
    {
        new_node = available->next;
        available->next = new_node->next;
        new_node->coef = 0.0;
        new_node->exp = 0;
        new_node->next = NULL;
    }
    else
    {
        new_node = New_PolyNode();
    }
    return new_node;
}
/*回收链表的节点到可用空间*/
void recycle_avail(PolyPointer p, PolyPointer available)
{
    PolyPointer avail = available;
    while(avail->next)
    {
        avail = avail->next;
    }
    while(p)
    {
        avail->next = p;
        avail = avail->next;
        p = p->next;
        avail->next = NULL;
    }
}
