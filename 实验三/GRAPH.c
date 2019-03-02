#include <stdio.h>
#include <stdlib.h>
#define  INFINITY    1000
#define  MAX_VERTEX_NUM 20
#define NULL  ((void *)0)
//邻接矩阵
typedef enum {DG, DN, AG, AN} GraphKind;
typedef struct ArcCell
{
    int adj;
    int *info;
}ArcCell,AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

typedef struct
{
    int vex[MAX_VERTEX_NUM] ;
    AdjMatrix arcs;
    int vexnum, arcnum;
    GraphKind kind;
}MGraph;


//邻接表
typedef struct Vnode
{
    int data;  //自身节点数据
    struct Vnode *firstarc;//
}Vnode, AdjList[MAX_VERTEX_NUM];

typedef struct
{
    AdjList vertices;
    int vexnum; //顶点个数
    int kind; //图的类型
}ALGraph;

//队列
typedef struct queue
{
    int data[MAX_VERTEX_NUM];
    int front;
    int rear;
}QUEUE;

// 栈
typedef struct
{
    int data[MAX_VERTEX_NUM];
    int top;
}STACK;

void set_up_by_matrix(MGraph *G);
void print_matrix_graph(const MGraph *G);
Vnode *new_node(int data);
void print_link_graph(const ALGraph *G);
void set_up_by_link(ALGraph *G);
MGraph ALG2MG(const ALGraph *ALG);
ALGraph MG2ALG(const MGraph *G);
void analyse_space_complex_MG(const MGraph *MG);
void analyse_space_complex_ALG(const ALGraph *ALG);
ALGraph set_up_by_ALGraph_from_file(char *filename);
MGraph set_up_by_MGraph_from_file(char *filename);
void destroy_ALG(ALGraph *ALG);

Vnode *NextAdjVex_ALG(ALGraph *ALG,int w, int *visited);
void DFS_ALG(ALGraph *ALG , int v, int *visited,int *tree);
void DFSTravers_ALG(ALGraph *ALG);

int Front(QUEUE *Q);
void DeQueue(QUEUE *Q);
int Addone(int i);
int QueueEmpty(QUEUE *Q);
void EnQueue(QUEUE *Q,int v);
void InitQueue(QUEUE *Q);
void BFSTravers_ALG(ALGraph *ALG);


void DFSTravers_N_ALG(ALGraph *ALG);
void Push(STACK *S,int x);
int Pop(STACK *S);
int top (STACK *S);
int StackEmpty(STACK *S);
void init_stack(STACK *S);


void DFSTravers_MG(MGraph *MG);
void DFS_MG(MGraph *MG , int v, int *visited,int *tree);
int NextAdjVex_MG (MGraph *MG , int v, int *visited);
void DFSTravers_N_MG(MGraph *MG);
void BFSTravers_MG(MGraph *MG);
int menu();

void print_tree(int *tree);
void init_tree(int *tree);

int main()
{
    int choice;
    int ALG_Flag = 0;
    int MG_Flag = 0;
    ALGraph ALG;
    MGraph MG;
    /*
    MGraph MG = set_up_by_MGraph_from_file("graph5.txt");
    ALG = set_up_by_ALGraph_from_file("graph5.txt");
    //DFSTravers_MG(&MG);
    //DFSTravers_ALG(&ALG);
    //DFSTravers_N_ALG(&ALG);
    DFSTravers_N_MG(&MG);
    */
    while(1)
    {
        choice = menu();
        switch(choice){
            case 1:
                set_up_by_matrix(&MG);
                MG_Flag = 1;
                printf("success!\n");
                system("pause");
                system("cls");
                break;
            case 2:
                set_up_by_link(&ALG);
                ALG_Flag = 1;
                printf("success!\n");
                system("pause");
                system("cls");
                break;
            case 3:
                if(ALG_Flag)
                {
                    MG = ALG2MG(&ALG);
                    MG_Flag = 1;
                    printf("success!\n");
                }
                else
                    printf("邻接链表未建立\n");
                system("pause");
                system("cls");
                break;
            case 4:
                if(MG_Flag)
                {
                    ALG = MG2ALG(&MG);
                    ALG_Flag = 1;
                }
                else
                    printf("邻接矩阵表未建立\n");
                system("pause");
                system("cls");
                break;
            case 5:
                printf("两种存储结构的空间复杂度分析：\n");
                if(ALG_Flag)
                    analyse_space_complex_ALG(&ALG);
                else
                    printf("邻接链表未建立\n");
                if(MG_Flag)
                    analyse_space_complex_MG(&MG);
                else
                    printf("邻接矩阵表未建立\n");
                system("pause");
                system("cls");
                break;
            case 6:
                if(MG_Flag)
                {
                    printf("深度优先搜索（邻接矩阵 递归）结果：");
                    DFSTravers_MG(&MG);
                    printf("\n");
                }
                else
                    printf("邻接矩阵表未建立\n");
                system("pause");
                system("cls");
                break;
            case 7:
                if(MG_Flag)
                {
                    printf("深度优先搜索（邻接矩阵 非递归）结果：");
                    DFSTravers_N_MG(&MG);
                    printf("\n");
                }
                else
                    printf("邻接矩阵表未建立\n");
                system("pause");
                system("cls");
                break;
            case 8:
                if(MG_Flag)
                {
                    printf("广度优先搜索（邻接矩阵）结果：");
                    BFSTravers_MG(&MG);
                    printf("\n");
                }
                else
                    printf("邻接矩阵表未建立\n");
                system("pause");
                system("cls");
                break;
            case 9:
                if(ALG_Flag)
                {
                    printf("深度优先搜索（邻接链表 递归）结果：");
                    DFSTravers_ALG(&ALG);
                    printf("\n");
                }
                else
                    printf("邻接链表表未建立\n");
                system("pause");
                system("cls");
                break;
            case 10:
                if(ALG_Flag)
                {
                    printf("深度优先搜索（邻接链表 非递归）结果：");
                    DFSTravers_N_ALG(&ALG);
                    printf("\n");
                }
                else
                    printf("邻接链表表未建立\n");
                system("pause");
                system("cls");
                break;
            case 11:
                if(ALG_Flag)
                {
                    printf("广度优先搜索（邻接链表）结果：");
                    BFSTravers_ALG(&ALG);
                    printf("\n");
                }
                else
                    printf("邻接链表表未建立\n");
                system("pause");
                system("cls");
                break;
            case 12:
                ALG = set_up_by_ALGraph_from_file("graph5.txt");
                MG = set_up_by_MGraph_from_file("graph5.txt");
                ALG_Flag = 1;
                MG_Flag = 1;
                printf("success!\n");
                system("pause");
                system("cls");
                break;
            case 13:
                if(MG_Flag)
                    print_matrix_graph(&MG);
                else
                    printf("邻接矩阵表未建立\n");
                system("pause");
                system("cls");
                break;
            case 14:
                if(ALG_Flag)
                    print_link_graph(&ALG);
                else
                    printf("邻接链表表未建立\n");
                system("pause");
                system("cls");
                break;
            case 15:
                destroy_ALG(&ALG);
                exit(0);
                break;
            default:
                break;

        }
    }

    return 0;
}
int menu()
{
    printf("本程序实现的功能：\n");
    printf("1、从键盘输入，建立邻接矩阵\n");
    printf("2、从键盘输入，建立邻接链表\n");
    printf("3、邻接矩阵转化为邻接链表\n");
    printf("4、邻接链表转化为邻接矩阵\n");
    printf("5、分析两种存储结构的空间占用情况\n");
    printf("6、深度优先搜索（邻接矩阵 递归）\n");
    printf("7、深度优先搜索（邻接矩阵 非递归）\n");
    printf("8、广度优先搜索（邻接矩阵）\n");
    printf("9、深度优先搜索（邻接链表 递归）\n");
    printf("10、深度优先搜索（邻接链表 非递归）\n");
    printf("11、广度优先搜索（邻接链表）\n");
    printf("12、从文件方式输入，建立邻接矩阵和邻接链表\n");
    printf("13、用连接矩阵表示图\n");
    printf("14、用连接链表表示图\n");
    printf("15、退出\n");
    printf("注：在执行其他操作之前，一定要先建立储存结构\n");
    printf("请输入你的选择：");
    int choice;
    scanf("%d",&choice);
    return choice;
}
void set_up_by_matrix(MGraph *G)
{
    printf("建立无向无权重图\n");
    printf("请输入顶点个数：");
    scanf("%d",&((*G).vexnum));
    //printf("%d",(*M).vexnum);
    int vexnum = (*G).vexnum;
    int i, j;
    int node;
    (*G).arcnum = 0;
    for(i=0;i<vexnum;i++)
    {
        printf("与顶点%d有一条边的顶点有：(输入-1则退出输入)\n",i);
        scanf(" %d",&node);
        while(node!=-1)
        {
            (*G).arcnum++;
            (*G).arcs[i][node].adj = 1;
            scanf("%d",&node);
        }
        for(j=0;j<vexnum;j++)
        {
            if((*G).arcs[i][j].adj != 1)
            {
                (*G).arcs[i][j].adj = 0;
            }
        }
    }

}
void print_matrix_graph(const MGraph *G)
{
    int vexnum = (*G).vexnum;
    int i, j, num;
    printf("邻接矩阵：\n");
    for(i=0;i<vexnum;i++)
    {
        for(j=0;j<vexnum;j++)
        {
            num = (*G).arcs[i][j].adj;
            printf("%d  ",num);
        }
        printf("\n");
    }
}

void set_up_by_link(ALGraph *G)
{
    printf("建立无向无权重图\n");
    printf("请输入顶点个数：");
    scanf("%d",&((*G).vexnum));
    //printf("%d",(*M).vexnum);
    int vexnum = (*G).vexnum;
    int i;
    int node;
    Vnode *p;
    for(i=0;i<vexnum;i++)
    {
        printf("与顶点%d有一条边的顶点有：(输入-1则退出输入)\n",i);
        scanf(" %d",&node);
        (*G).vertices[i].firstarc = NULL;
        p = &((*G).vertices[i]);
        p->data = i;
        while(node!=-1)
        {
            p->firstarc = new_node(node);
            scanf("%d",&node);
            p = p->firstarc;
        }
    }
}
Vnode *new_node(int data)
{
    Vnode * node = (Vnode *)malloc(sizeof(Vnode));
    node->data = data;
    node->firstarc = NULL;
    return node;
}
void print_link_graph(const ALGraph *G)
{
    int vexnum = (*G).vexnum;
    int i;
    Vnode *p;
    printf("邻接链表：\n");
    for(i=0;i<vexnum;i++)
    {
        p = &((*G).vertices[i]);
        while(p!=NULL)
        {
            printf("%d  ",p->data);
            p = p->firstarc;
        }
        printf("\n");
    }
}
MGraph ALG2MG(const ALGraph *ALG)
{
    MGraph MG;
    int vexnum = (*ALG).vexnum;
    MG.vexnum = vexnum;
    int i, j;
    Vnode *p;
    for(i=0;i<vexnum;i++)
    {
        p = &((*ALG).vertices[i]);
        p = p->firstarc;
        while(p!=NULL)
        {
            j = p->data;
            MG.arcs[i][j].adj = 1;
            p = p->firstarc;
        }
        for(j=0;j<vexnum;j++)
        {
            if(MG.arcs[i][j].adj != 1)
            {
                MG.arcs[i][j].adj = 0;
            }
        }
    }
    return MG;
}
ALGraph MG2ALG(const MGraph *G)
{
    ALGraph ALG;
    int i, j;
    int vexnum = (*G).vexnum;
    ALG.vexnum = vexnum;
    Vnode *p;
    for(i=0;i<vexnum;i++)
    {
        ALG.vertices[i].data = i;
        ALG.vertices[i].firstarc = NULL;
        p = &(ALG.vertices[i]);
        for(j=0;j<vexnum;j++)
        {
            if((*G).arcs[i][j].adj != 0)
            {
                p->firstarc = new_node(j);
                p = p->firstarc;
            }
        }
    }
    return ALG;
}

void analyse_space_complex_ALG(const ALGraph *ALG)
{
    int vnode_space = sizeof(Vnode);
    int vexnumALG = (*ALG).vexnum;
    int i;
    int sum = 0;
    Vnode *p;
    for(i=0;i<vexnumALG;i++)
    {
        p = &((*ALG).vertices[i]);
        p = p->firstarc;
        while(p!=NULL)

        {
            sum++;
            p = p->firstarc;
        }
    }
    int ALG_SPACE = sizeof(*ALG) + sum*vnode_space - (MAX_VERTEX_NUM-vexnumALG)*sizeof(Vnode);
    printf("邻接链表的空间占用情况为：%d字节\n",ALG_SPACE);
}

void analyse_space_complex_MG(const MGraph *MG)
{
    int vexnumMG = (*MG).vexnum;
    int MG_SPACE = sizeof(*MG) - (sizeof(ArcCell)*((MAX_VERTEX_NUM*MAX_VERTEX_NUM)-(vexnumMG*vexnumMG)));
    MG_SPACE -= sizeof(int)*(MAX_VERTEX_NUM-vexnumMG);
    printf("邻接矩阵的空间占用情况为：%d字节\n",MG_SPACE);
}

ALGraph set_up_by_ALGraph_from_file(char *filename)
{
    FILE *fp;
    fp = fopen(filename,"r");
    if(fp==NULL)
    {
        printf("打开文件失败\n");
        exit(1);
    }
    ALGraph ALG;
    ALG.vexnum = 0;
    //Vnode **p;
    Vnode *p;
    int node;
    int parent = -1;
    int preparent = -1;
    int child;
    fscanf(fp," %d",&node);
    while(node!=-1)
    {
        ALG.vexnum++;
        ALG.vertices[node].data = node;
        ALG.vertices[node].firstarc = NULL;
        fscanf(fp," %d",&node);
    }
    while(!feof(fp))
    {
        fscanf(fp,"%d-%d\n",&parent,&child);
        if(parent!=preparent)
        {
            p = &(ALG.vertices[parent]);
            while(p->firstarc)
            {
                p = p->firstarc;
            }
        }
        p->firstarc =  new_node(child);
        p = p->firstarc;
        preparent = parent;
    }
    return ALG;
}
MGraph set_up_by_MGraph_from_file(char *filename)
{
    FILE *fp;
    fp = fopen(filename,"r");
    if(fp==NULL)
    {
        printf("打开文件失败\n");
        exit(1);
    }
    MGraph MG;
    MG.vexnum = 0;
    //Vnode **p;
    int row, col;
    int node;
    int vexnum = 0;
    fscanf(fp," %d",&node);
    while(node!=-1)
    {
        vexnum++;
        MG.vex[node] = 1;
        fscanf(fp,"%d",&node);
    }
    MG.vexnum = vexnum;
    int i, j;
    for(i=0;i<vexnum;i++)
    {
        for(j=0;j<vexnum;j++)
        {
            MG.arcs[i][j].adj = 0;
        }
    }
    while(!feof(fp))
    {
        fscanf(fp,"%d-%d\n",&row,&col);
        MG.arcs[row][col].adj = 1;
    }
    return MG;
}
void destroy_ALG(ALGraph *ALG)
{
    int vexnum = (*ALG).vexnum;
    int i;
    Vnode *p;
    Vnode *q;
    for(i=0;i<vexnum;i++)
    {
        p = &((*ALG).vertices[i]);
        p = p->firstarc;
        while(p!=NULL)
        {
            q = p->firstarc;
            free(p);
            p = q;
        }
        (*ALG).vertices[i].firstarc = NULL;
    }
}

//邻接表DFS
void DFSTravers_ALG(ALGraph *ALG)
{
    int vexnum = (*ALG).vexnum;
    int visited[MAX_VERTEX_NUM] = {0};
    int v;
    int tree[MAX_VERTEX_NUM];
    for(v = 0; v < vexnum ; v++)
        if(!visited[v])
        {
            printf("\n");
            printf("根节点：%d",v);
            printf("\t树边：");
            init_tree(&tree);
            DFS_ALG(ALG, v, &visited,&tree);
            print_tree(&tree);
        }
}

void DFS_ALG(ALGraph *ALG , int v, int *visited,int *tree)
{
    visited[v] = 1;
    Vnode *w = &(ALG->vertices[v]);
    w = w->firstarc;
    while(w)
    {
        if (!visited[w->data])
        {
            tree[w->data] = v;
            DFS_ALG(ALG,w->data,visited,tree);
        }
        w = NextAdjVex_ALG(ALG,v,visited);
    }
}
Vnode *NextAdjVex_ALG(ALGraph *ALG, int w, int *visited)
{
    Vnode *p = &(ALG->vertices[w]);
    while(p!=NULL)
    {
        if(visited[p->data])
            p = p->firstarc;
        else
            break;
    }
    return p;
}

void BFSTravers_ALG(ALGraph *ALG)
{
    int visited[MAX_VERTEX_NUM] = {0};
    QUEUE Q;
    InitQueue(&Q);
    int vexnum = ALG->vexnum;
    int v;
    int front;
    Vnode *w;
    for(v=0;v<vexnum;v++)
    {
        if(!visited[v])
        {
            EnQueue(&Q,v);
            visited[v] = 1;
            printf("\n");
            printf("根节点：%d",v);
            printf("\t树边：");
            while(!QueueEmpty(&Q))
            {
                front = Front(&Q);
                w = NextAdjVex_ALG(ALG ,front, &visited);
                while(w)
                {
                    printf("%d->%d  ",front,w->data);
                    visited[w->data] = 1 ;
                    EnQueue(&Q,w->data);
                    w = NextAdjVex_ALG(ALG ,front, &visited);
                }
                DeQueue(&Q);
            }
        }
    }
}
void InitQueue(QUEUE *Q)
{
    int i;
    for(i=0;i<MAX_VERTEX_NUM;i++)
    {
        Q->data[i] = -1;
    }
    Q->front = 0;
    Q->rear = 0;
}
void EnQueue(QUEUE *Q,int v)
{
    if(Addone(Q->rear)==Q->front)
        printf("队列满");
    else
    {
        Q->data[Q->rear] = v;
        Q->rear = Addone(Q->rear);
    }
}
int QueueEmpty(QUEUE *Q)
{
    if (Q->front==Q->rear)
        return 1;
    else
        return 0;
}
int Addone(int i)
{
    return ((i+1)%MAX_VERTEX_NUM);
}
void DeQueue(QUEUE *Q)
{
    if (QueueEmpty(Q))
    {
        return;
    }
    else
    {
        Q->data[Q->front] = -1;
        Q->front = Addone(Q->front);
    }
}
int Front(QUEUE *Q)
{
    if(!QueueEmpty(Q))
        return (Q->data[Q->front]);
    else
        return NULL;
}
void DFSTravers_N_ALG(ALGraph *ALG)
{
    STACK stack;
    init_stack(&stack);
    int visited[MAX_VERTEX_NUM] = {0};
    int v;
    int node;
    int parent;
    int vexnum = ALG->vexnum;
    int tree[MAX_VERTEX_NUM];
    Vnode *w;
    for(v=0;v<vexnum;v++)
    {
        if(visited[v])
            continue;
        Push(&stack,v);
        visited[v] = 1;
        init_tree(&tree);
        printf("\n根节点：%d\t",v);
        node = v;
        do
        {
            parent = node;
            w = NextAdjVex_ALG(ALG,node,&visited);
            if(w)
            {
                node = w->data;
                Push(&stack,node);
                visited[node] = 1;
                tree[node] = parent;
            }
            else
            {
                node = top(&stack);
                w = NextAdjVex_ALG(ALG,node,&visited);
                if(w==NULL)
                {
                    Pop(&stack);
                    node = top(&stack);
                }
            }
        }while(node!=-1);
        printf("树边：");
        print_tree(&tree);
    }
}

void init_stack(STACK *S)
{
    int i;
    for(i=0;i<MAX_VERTEX_NUM;i++)
    {
        S->data[i] = -1;
    }
    S->top = 0;
}
int StackEmpty(STACK *S)
{
    if(S->top<1)
        return 1;
    else
        return 0;
}
int top (STACK *S)
{
    if(StackEmpty(S))
        return -1;
    else
        return S->data[S->top];
}
int Pop(STACK *S)
{
    if(StackEmpty(S))
    {
        return -1;
    }
    else
    {
        int data = S->data[S->top];
        S->top = S->top - 1;
        return data;
    }
}
void Push(STACK *S,int x)
{
    if(S->top==MAX_VERTEX_NUM-1)
        printf("栈满");
    else
    {
        S->top = S->top + 1;
        S->data[S->top] = x;
    }
}

//邻接矩阵深度邮箱搜索算法
void DFSTravers_MG(MGraph *MG)
{
    int vexnum = (*MG).vexnum;
    int visited[MAX_VERTEX_NUM] = {0};
    int v;
    int tree[MAX_VERTEX_NUM];
    for(v = 0; v < vexnum ; v++)
        if(!visited[v])
        {
            printf("\n");
            printf("根节点：%d",v);
            printf("\t树边:");
            init_tree(&tree);
            DFS_MG(MG, v, &visited,&tree);
            print_tree(&tree);
        }

}
void DFS_MG(MGraph *MG , int v, int *visited,int *tree)
{
    visited[v] = 1;
    int w = NextAdjVex_MG(MG,v,visited);
    while(w!=-2)
    {
        if (!visited[w])
        {
            tree[w] = v;
            DFS_MG(MG,w,visited,tree);
        }
        w = NextAdjVex_MG(MG,v,visited);

    }

}
void init_tree(int *tree)
{
    int i;
    for(i=0;i<MAX_VERTEX_NUM;i++)
        tree[i] = -1;
}
void print_tree(int *tree)
{
    int i;
    for(i=0;i<MAX_VERTEX_NUM;i++)
    {
        if(tree[i]!=-1)
        {
            printf("%d->%d  ",tree[i],i);
        }
    }
}
int NextAdjVex_MG(MGraph *MG , int v, int *visited)
{
    int vexnum = MG->vexnum;
    int j;
    int flag;
    for(j=0;j<vexnum;j++)
    {
        flag = MG->arcs[v][j].adj;
        if(flag!=0&&visited[j]!=1)
        {
            return j;
        }
    }
    return -2;
}
void DFSTravers_N_MG(MGraph *MG)
{
    STACK stack;
    init_stack(&stack);
    int visited[MAX_VERTEX_NUM] = {0};
    int v, w;
    int vexnum = MG->vexnum;
    int tree[MAX_VERTEX_NUM];
    int parent;
    for(v=0;v<vexnum;v++)
    {
        if(visited[v])
            continue;
        Push(&stack,v);
        visited[v] = 1;
        w = v;
        init_tree(&tree);
        printf("\n根节点：%d\t",v);
        do
        {
            parent = w;
            w = NextAdjVex_MG(MG,w,&visited);
            if(w!=-2)
            {
                Push(&stack,w);
                visited[w] = 1;
                tree[w] = parent;
            }
            else
            {
                w = top(&stack);
                if(NextAdjVex_MG(MG,w,&visited)==-2)
                {
                    Pop(&stack);
                    w = top(&stack);
                }
            }
        }while(w!=-1);
        printf("树边：");
        print_tree(&tree);
    }
}
void BFSTravers_MG(MGraph *MG)
{
    int visited[MAX_VERTEX_NUM] = {0};
    QUEUE Q;
    InitQueue(&Q);
    int vexnum = MG->vexnum;
    int v, w;
    int front;
    for(v=0;v<vexnum;v++)
    {
        if(!visited[v])
        {
            EnQueue(&Q,v);
            visited[v] = 1;
            printf("\n");
            printf("根节点：%d",v);
            printf("\t树边：");
            while(!QueueEmpty(&Q))
            {
                front = Front(&Q);
                w = NextAdjVex_MG(MG,front,&visited);
                while(w!=-2)
                {
                    printf("%d->%d  ",front,w);
                    visited[w] = 1;
                    EnQueue(&Q,w);
                    w = NextAdjVex_MG(MG ,front, &visited);
                }
                DeQueue(&Q);
            }
          }
    }
}
