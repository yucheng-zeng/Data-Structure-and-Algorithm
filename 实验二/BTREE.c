#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <math.h>
#include <string.h>
#define NULL ((void *)0)
#define  N  100
#define MAX 100
struct Node
{
    char data;
    struct Node *lchild;
    struct Node *rchild;
};
typedef struct Node * BTree;
typedef struct Node * LNode;
typedef struct Node * RNode;
typedef struct Node * HEAD;
typedef struct Node * NODE;
typedef char *string;
string Null(int x);
string Read_Tree(string filename);
void Extern_Str(string *str);
void Destroy(string S);
int Len(string S);
int Cal_Layer(string S);
void Cal_LeftNum(int k,int LeftNum[]);
string Sequence2In(string seqStr);
string CopyString(string S);
NODE New_Node();
void PreOrder(BTree BT,string result);
void PostOrder(BTree BT,string result);
void InOrder(BTree BT,string result);
BTree *Setup3(BTree *bt, int n,string *Str);
string Sequence2Pre(string *seqStr);
int IsNull(string S);
void InOrder_N(BTree head);
void PreOrder_N(BTree head);
void PostOrder_N(BTree root);
int check(BTree root);
void Write2File(string filename,string result);
void DestroyTree(BTree head);
void AddLeaves(string *S);


int main()
{
    string filename = "BTree2.txt";
    string seqStr = Read_Tree(filename);
    printf("%s\n",seqStr);
    string preStr = Sequence2Pre(&seqStr);

    //构建树
    HEAD head;
    string s = preStr;
    ++s;
    Setup3(&head,0,&s);

    //递归遍历树
    printf("%s\n",preStr);
    int length = Len(preStr);
    string result1 = Null(length);
    string result2 = Null(length);
    string result3 = Null(length);

    printf("递归遍历树：");
    printf("\n先序：");
    PreOrder(head, result1);
    //printf("\n结果：%s\n",result1);
    printf("\n中序：");
    InOrder(head, result2);
    //printf("\n结果：%s\n",result2);
    printf("\n后序：");
    PostOrder(head, result3);
    //printf("\n结果：%s\n",result3);

    //非递归遍历树
    printf("\n非递归遍历树：");
    printf("\n先序：");
    PreOrder_N(head);
    printf("\n中序：");
    InOrder_N(head);
    printf("\n后序：");
    PostOrder_N(head);

    int j = check(head);
    printf("\n是否是完全树：");
    if(j)
        printf("是");
    else
        printf("否");
    DestroyTree(head);
    Destroy(result1);
    Destroy(result2);
    Destroy(result3);
    return 0;
}
string Read_Tree(string filename)
{
    FILE *fp;
    fp = fopen(filename,"r");
    if(fp==NULL)
    {
        printf("打开文件失败\n");
        return NULL;
    }
    char a = '\0';
    string S = Null(10);
    int length = _msize(S);
    int i = 1;
    S[0] = ' ';
    do
    {
        fscanf(fp,"%c",&a);
        if(a=='\n')
            break;
        S[i] = a;
        i++;
        if(i>=length-2)
        {
            S[i]='\0';
            Extern_Str(&S);
            length = _msize(S);
        }
    }while(1);
    S[i] = '\0';
    fclose(fp);
    return S;
}
void Extern_Str(string *str)
{
    int x = _msize(*str)*2;
    int i = 0;
    string new_str = (string)malloc(sizeof(char)*x);
    while((*str)[i]!='\0'&&i<x)
    {
        new_str[i] = (*str)[i];
        i++;
    }
    new_str[i] = '\0';
    Destroy(*str);
    *str = new_str;
}
string Null(int x)
{
    string str = (string)malloc(sizeof(char)*x);
    str[0]='\0';
    return str;
}
void Destroy(string S)
{
    free(S);
}
int Len(string S)
{
    int i=0;
    while(S[i]!='\0')
        i++;
    return i-1;
}
void AddLeaves(string *S)
{
    int layer = Cal_Layer(*S);
    int i;
    int shape_num = 1;
    for(i=1;i<=layer;i++)
    {
        shape_num *= 2;
    }
    int length = Len(*S);
    int total_length = length + shape_num;
    int maxlength = _msize(*S);
    for(i=length+1;i<=total_length;i++)
    {
        if(i>=maxlength-2)
        {
            (*S)[i]='\0';
            Extern_Str(S);
            maxlength = _msize(*S);
        }
        (*S)[i] = '#';
    }
    (*S)[i] = '\0';
}
string Sequence2Pre(string *seqStr)
{
    AddLeaves(seqStr);
    int layer = Cal_Layer(*seqStr);
    int LeftNumArray[layer+1];
    Cal_LeftNum(layer,LeftNumArray);
    int length = Len(*seqStr);
    int i = 0;
    string preStr = Null(128);
    preStr[i] = ' ';
    //初始化打点
    int semi = length;
    int maxlength = _msize(preStr);
    for(i=1;i<=length;i++)
    {
        if(i<=layer)
        {
            preStr[i] = (char)(i+'0');
            continue;
        }
        preStr[i] = '#';
        if(i>=maxlength-2)
        {
            preStr[i]='\0';
            Extern_Str(&preStr);
            maxlength = _msize(preStr);
        }
    }
    preStr[i] = '\0';
    //打点
    for(i=2;i<=layer;i++)
    {
        semi = semi/2;
        preStr[i+semi] = (char)(i+'0');
    }
    //printf("%s\n",preStr);

    //对称赋值
    int sharpLen, j;
    for(i=layer+1;i<=length;i++)
    {
        if(preStr[i]=='#')
        {
            sharpLen = 0;
            while(preStr[i+sharpLen]=='#')
            {
                sharpLen++;
            }
            for(j=0;j<sharpLen;j++)
            {
                preStr[i+j] = preStr[i-1-sharpLen+j];//对称赋值
            }
            i = i + sharpLen;
        }
    }
    string layer_string = CopyString(preStr);
    //printf("%s\n",preStr);
    for(i=1;i<=length;i++)
    {
        int layer_num = (int)(preStr[i]-'0');
        int left_num = (LeftNumArray[layer_num])++;
        preStr[i] = (*seqStr)[left_num];
    }
    preStr[i] = '\0';
    //printf("%s\n",preStr);
    //规范化
    int layer_dist;
    for(i=1;i<=length;i++)
    {
        if(preStr[i]=='#')
        {
            sharpLen = 0;
            while(preStr[sharpLen+i]=='#')
            {
                layer_dist = abs((int)(layer_string[i-1]-'0')-(int)(layer_string[i+sharpLen]-'0'));
                if(layer_dist>1)
                    preStr[i+sharpLen] = '*';
                sharpLen++;
            }
            i = i + sharpLen;
        }
    }
    //printf("%s\n",preStr);
    Destroy(layer_string);
    return preStr;
}
string Sequence2In(string seqStr)
{
    int layer = Cal_Layer(seqStr);
    int LeftNumArray[layer+1];
    Cal_LeftNum(layer,LeftNumArray);
    int length = Len(seqStr);
    int i=0;
    string inStr = Null(128);
    inStr[i] = ' ';
    int index = 1;
    int tag = 0;
    int maxlength = _msize(inStr);
    //初始化中跟序列节点
    for(i=1;i<=length;i++)
    {
        if(i>=maxlength-2)
        {
            inStr[i]='\0';
            Extern_Str(&inStr);
            maxlength = _msize(inStr);
        }
        if(i==index)
        {
            inStr[i] = (char)(layer-tag+'0');
            tag++;
            index = index * 2;
        }
        else
            inStr[i] = '#';
    }
    //为每一个节点标记一个其元素来自树的层数
    inStr[i] = '\0';
    tag = 1;
    for(i=1;i<=length+1/2;i++)
    {
        if(inStr[i]=='#')
        {
            inStr[i] = inStr[tag];
            tag++;
        }
        else
            tag = 1;
    }
    for(i=1;i<=length;i++)
    {
        int layer_num = (int)(inStr[i]-'0');
        int left_num = (LeftNumArray[layer_num])++;
        inStr[i] = seqStr[left_num];
    }
    return inStr;
}
int Cal_Layer(string S)
{
    int length = Len(S);
    int k = 0;
    int leaves_num = 1;
    while(leaves_num!=length)
    {
        k++;
        leaves_num = (1<<k) -1;
    }
    return k;
}

int IsNull(string S)
{
    int i=0;
    while(S[i]!='\0')
        i++;
    if(i==0)
        return 1;
    else
        return 0;
}
void Cal_LeftNum(int k,int LeftNum[])
{
    int i = 1;
    LeftNum[0] = 0;
    while(i<=k)
    {
        LeftNum[i] = pow(2,i-1);
        i++;
    }
}
string CopyString(string S)
{
    int x = _msize(S);
    int i = 0;
    string new_str = (string)malloc(sizeof(char)*x);
    while(S[i]!='\0'&&i<x)
    {
        new_str[i] = S[i];
        i++;
    }
    new_str[i] = '\0';
    return new_str;
}


NODE New_Node()
{
    NODE node = (struct Node*)malloc(sizeof(struct Node));
    node->data = '\0';
    node->lchild = NULL;
    node->rchild = NULL;
    return node;
}

//根据先序遍历和中序遍历创建二叉树
BTree *Setup3(BTree *bt, int n,string *Str)        //交互问答方式创建二叉树
{
    while(**Str=='*')
        (*Str)++;
    char ch = **Str;
    (*Str)++;
    if(n==0)
        printf("");
    if(ch!='#')
    {
       n=1;
       (*bt)=New_Node();
       (*bt)->data=ch;
       (*bt)->lchild = Setup3(&((*bt)->lchild),n,Str);
       (*bt)->rchild=Setup3(&((*bt)->rchild),n,Str);
    }
    return(*bt);
}
void InOrder (BTree BT,string result)
{
    if (BT)
    {
        InOrder(BT->lchild,result);
        printf("%c ",BT->data);
        Attach(BT->data,result);
        InOrder(BT->rchild,result);
    }
    else
        Attach('#',result);
}
void PostOrder(BTree BT,string result)

{
    if (BT)
    {
        PostOrder(BT->lchild,result);
        PostOrder(BT->rchild,result);
        printf("%c ",BT->data);
        Attach(BT->data,result);
    }
    else
        Attach('#',result);
}
void PreOrder(BTree BT,string result)
{
    if (BT)
    {
        printf("%c ",BT->data);
        Attach(BT->data,result);
        PreOrder(BT->lchild,result);
        PreOrder(BT->rchild,result);
    }
    else
        Attach('#',result);
}
void Attach(char c, string result)
{
    int length = Len(result) + 1;
    result[length] = c;
    result[length+1] = '\0';
}
void InOrder_N (BTree head)
{
    BTree stack[MAX];
    BTree root = head;
    int top=0;
    do{
        while(root!=NULL)
        {
            top++;
            if(top>MAX)
                printf("栈满!\n");
            else
                stack[top]=root;
            root = root->lchild;
        }
        if(top!=0)
        {
            root=stack[top];
            top--;
            printf("%c ",root->data);
            root = root->rchild;
        }
    }while((top!=0)||(root!=NULL));
}
void PreOrder_N(BTree head)
{
    BTree stack[MAX];
    int top=0;
    BTree root = head;
    do{
        while(root!=NULL)
        {
            printf("%c ",root->data);
            top++;
            if(top>MAX)
                printf("栈满!\n");
            else
                stack[top]=root;
            root=root->lchild;
        }
        if(top!=0)
        {
            root=stack[top];
            top--;
            root=root->rchild;
        }
    }while((top!=0)||(root!=NULL));
}
void PostOrder_N(BTree head)//后序遍历，非递归
{
    BTree stack[MAX];
    BTree p;
    BTree root = head;
    int top=0;
    int b;
    do{
        while(root!=NULL)
        {
            top++;
            if(top>MAX)
                printf("栈满!\n");
            else
                stack[top]=root;
            root = root->lchild;
        }
        p=NULL;
        b=1;
        while((top!=0)&&b)  //右子树不存在或已访问
        {
            root=stack[top];
            if(root->rchild==p)
            {
                printf("%c ",root->data);//访问根结点
                top--;
                p=root;//p指向刚访问
            }
            else
            {
                root=root->rchild;
                b=0;
            }
        }
    }while(top!=0);
}
int check(BTree root)
{
    if(root==NULL)
        return 0;
    else if(root->lchild==NULL&&root->rchild==NULL)
        return 1;
    else if(root->lchild==NULL&&root->rchild!=NULL)
        return 0;
    else if(root->lchild!=NULL&&root->rchild==NULL)
        return 1;
    else
        return check(root->lchild)&&check(root->rchild);
}
void Write2File(string filename,string result)
{
    FILE *fp;
    fp = fopen(filename,"w");
    if(fp==NULL)
    {
        printf("打开文件失败\n");
        return;
    }
    int i = 0;
    while(result[i]!='\0')
    {
        fprintf(fp,"%c",result[i]);
        i++;
    }
    fprintf(fp,"\n");
    fclose(fp);
}
void DestroyTree(BTree head)
{
    BTree root = head;
    if(root!=NULL&&root->lchild!=NULL)
        DestroyTree(root->lchild);
    if(root!=NULL&&root->rchild!=NULL)
        DestroyTree(root->rchild);
    free(root);
}
