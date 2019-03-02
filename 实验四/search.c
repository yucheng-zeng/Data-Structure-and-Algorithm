#include <stdio.h>
#include <stdlib.h>
#define NULL ((void *)0)
#define TRUE 1
#define FALSE 0
#define MAX 1025
//结点
struct node
{
    int data; //关键字
    struct node *lchild;  //左子树
    struct node *rchild;  //右子树
};
//根节点
typedef struct
{
    struct node * child; //根节点
}ROOT;
typedef struct node NODE;
typedef struct node AVLT;
typedef int boolean;
typedef NODE *BST;



NODE *new_Node(int R);
void AVLInsert(AVLT **PT ,int R);
void set_up_BST_TREE(ROOT *root,char *filename);
ROOT new_Root();
void PreOrder(AVLT *BT);
NODE *search(int k, AVLT *F,int *depth);
void Delete(int k ,AVLT **F);
void delete_Node(NODE *node);
int DeleteMin(AVLT **F);
int Depth(AVLT *T);  //求二叉树的深度
boolean IsAVL(AVLT *T);   //判断平衡二叉树
void Adjust_BF(AVLT **T);
void Adjust_Tree(AVLT **T);
void AVL_Delete(int R, ROOT *root);
void InOrder(AVLT *BT);
void destory_tree(AVLT *BT);

int set_up_Binary(char *filename,int **array);
void SelectSort_increase(int max,int **array);
int Binary_Search(int k, int max, int *depth, int *array);

void analyse_btree_search(AVLT *BT, char *filename);
void analyse_binary_search(int *array,int max, char *filename);
int menu();

int analyse_btree_search_failure(AVLT *BT,int depth);




int main()
{
    int choice;
    ROOT root = new_Root();
    int *array;
    int max;
    int tree_flag = 0;
    int array_flag = 0;
    int data;
    int depth=0;
    NODE *node;

    while(1)
    {
        choice = menu();
        switch(choice)
        {
        case 1:
            set_up_BST_TREE(&root,"increase.txt");
            tree_flag = 1;
            printf("建立查找二叉树成功\n");
            system("pause");
            system("cls");
            break;
        case 2:
            array = (int *)malloc(sizeof(int)*MAX);
            max = set_up_Binary("increase.txt",&array);
            array_flag = 1;
            printf("建立折半查找列表成功\n");
            system("pause");
            system("cls");
            break;
        case 3:
            if(tree_flag)
            {
                printf("请输入你要插入的节点信息：");
                scanf("%d",&data);
                AVLInsert(&(root.child),data);
                printf("插入节点成功\n");
            }
            else
                printf("错误：查找二叉树未建立\n");
            system("pause");
            system("cls");
            break;
        case 4:
            if(tree_flag)
            {
                printf("请输入你要删除的节点信息：");
                scanf("%d",&data);
                Delete(data,&(root.child));
                printf("删除节点成功\n");
            }
            else
                printf("错误：查找二叉树未建立\n");
            system("pause");
            system("cls");
            break;
        case 5:
            if(tree_flag)
            {
                printf("请输入你要查找的节点信息：");
                scanf("%d",&data);
                depth = 0;
                node = search(data,root.child,&depth);
                if(node)
                {
                    printf("已找到，该节点信息为：%d\n",node->data);
                    printf("深度为%d\n",depth);
                }
                else
                {
                    printf("无该节点信息\n");
                    printf("深度为%d\n",depth);
                }
            }
            else
                printf("错误：查找二叉树未建立\n");
            system("pause");
            system("cls");
            break;
        case 6:
            if(tree_flag)
            {
                printf("\n排序结果：\n");
                InOrder(root.child);
            }
            else
                printf("错误：查找二叉树未建立\n");
            system("pause");
            system("cls");
            break;
        case 7:
            if(tree_flag)
            {
                printf("\n查找二叉树时间性能分析结果：");
                printf("\n随机序列作输入的结果：\n");
                destory_tree(root.child);
                root.child = NULL;
                set_up_BST_TREE(&root,"random.txt");
                analyse_btree_search(root.child,"increase.txt");
                set_up_BST_TREE(&root,"random.txt");
                int failure = analyse_btree_search_failure(root.child,1);
                printf("查找失败平均查找长度=%.3f\n",((float)failure)/(MAX-1));
                destory_tree(root.child);
                root.child = NULL;
                set_up_BST_TREE(&root,"increase.txt");
                printf("\n顺序序列作输入的结果：\n");
                analyse_btree_search(root.child,"increase.txt");
                failure = analyse_btree_search_failure(root.child,1);
                printf("查找失败平均查找长度=%.3f\n",((float)failure)/(MAX-1));
            }
            else
                printf("错误：查找二叉树未建立\n");
            system("pause");
            system("cls");
            break;
        case 8:
            if(array_flag)
            {
                printf("\n折半查找时间性能分析结果：\n");
                analyse_binary_search(array,max,"random.txt");
            }
            else
                printf("错误：折半查找列表未建立\n");
            system("pause");
            system("cls");
            break;
        case 9:
            free(array);
            destory_tree(root.child);
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
    int choice;
    printf("本程序实现的功能:\n");
    printf("1.建立二叉查找树\n");
    printf("2.建立折半查找列表\n");
    printf("3.在查找二叉树中插入节点\n");
    printf("4.在查找二叉树中删除节点\n");
    printf("5.用查找二叉树查找一个节点\n");
    printf("6.用查找二叉树排序\n");
    printf("7.分析两种输入序列的查找二叉树的查找时间性能\n");
    printf("8.分析折半查找的查找时间性能\n");
    printf("9.退出\n");
    printf("请输入你的选择:");
    scanf(" %d",&choice);
    return choice;
}
void PreOrder(AVLT *BT)
{
    if(BT)
    {
        printf("%d\t",BT->data);
        if(BT->lchild)
            printf("%d->%d\t",BT->data,BT->lchild->data);
        else
            printf("\t");
        if(BT->rchild)
            printf("%d->%d\t",BT->data,BT->rchild->data);
        else
            printf("\t");
        printf("\n");
        PreOrder(BT->lchild);
        PreOrder(BT->rchild);
    }
}
void InOrder(AVLT *BT)
{
    if(BT)
    {
        InOrder(BT->lchild);
        printf("%d ",BT->data);
        InOrder(BT->rchild);
    }
}
void set_up_BST_TREE(ROOT *root,char *filename)
{
    FILE *fp;
    fp = fopen(filename,"r");
    if(fp==NULL)
    {
        printf("打开文件失败\n");
        exit(1);
    }
    int num;
    while(!feof(fp))
    {
        fscanf(fp,"%d\n",&num);
        AVLInsert(&(root->child),num);
    }
    fclose(fp);
}
void AVLInsert(AVLT **T ,int R)
{
    //两节点信息相同，不作处理
    if(!(*T)) //向空二叉树中插入元素
    {
        (*T) = new_Node(R);
    }
    else if(R<(*T)->data) //在左子树上插入
    {
        AVLInsert(&((*T)->lchild), R);
    }
    else if(R>(*T)->data)     //在右子树上插入
    {
        AVLInsert(&((*T)->rchild), R) ;
    }
}
ROOT new_Root()
{
    ROOT root;
    root.child = NULL;
    return root;
}
NODE *new_Node(int R)
{
    NODE *node = (NODE*)malloc(sizeof(NODE));
    node->data = R;
    node->lchild = NULL;
    node->rchild = NULL;
    return node;
}
void analyse_btree_search(AVLT *BT, char *filename)
{
    FILE *fp;
    fp = fopen(filename,"r");
    if(fp==NULL)
    {
        printf("打开文件失败\n");
        exit(1);
    }
    int num;
    int succee_depth;
    int succee_mean = 0;
    while(!feof(fp))
    {
        fscanf(fp,"%d\n",&num);
        succee_depth = 0;
        search(num,BT,&succee_depth);
        succee_mean += succee_depth;
    }
    fclose(fp);
    printf("查找成功平均查找长度=%.3f\n",((float)succee_mean)/((float)(MAX-1)));
}
void analyse_binary_search(int *array,int max, char *filename)
{
    FILE *fp;
    fp = fopen(filename,"r");
    if(fp==NULL)
    {
        printf("打开文件失败\n");
        exit(1);
    }
    int num;
    int succee_depth;
    int failure_depth;
    int succee_mean = 0;
    int failure_mean = 0;
    while(!feof(fp))
    {
        fscanf(fp,"%d\n",&num);
        succee_depth = 0;
        failure_depth = 0;
        Binary_Search(num,max,&succee_depth,array);
        succee_mean += succee_depth;
        //Binary_Search(num-1,max,&failure_depth,array);
        failure_mean+=succee_depth+1;
    }
    fclose(fp);
    printf("查找成功平均查找长度=%.3f\n",((float)succee_mean)/((float)(MAX-1)));
    printf("查找失败平均查找长度=%.3f\n",((float)failure_mean)/((float)(MAX-1)));

}
int analyse_btree_search_failure(AVLT *BT,int depth)
{
    if(BT->lchild==NULL&&BT->rchild==NULL)
    {
        return depth*2;
    }
    else if(BT->lchild==NULL&&BT->rchild!=NULL)
    {
        return depth + analyse_btree_search_failure(BT->rchild,depth+1);
    }
    else if(BT->lchild!=NULL&&BT->rchild==NULL)
    {
        return depth + analyse_btree_search_failure(BT->lchild,depth+1);
    }
    else
    {
        return analyse_btree_search_failure(BT->lchild,depth+1) + analyse_btree_search_failure(BT->rchild,depth+1);
    }
}
NODE *search(int k, AVLT *F,int *depth)
{
    NODE *p = F;
    if ( p == NULL )
    {
        (*depth)++;
        return NULL;
    }
    else if( k == p->data)
    {
        (*depth)++;
        return p;
    }
    else if( k < p->data )
    {
        (*depth)++;
        return search(k, p->lchild,depth);
    }
    else if( k > p->data)
    {
        (*depth)++;
        return search(k, p->rchild,depth);
    }
}
void Delete(int k ,AVLT **F)
{
    if((*F) != NULL)
    {
        if (k < (*F)->data)
            Delete(k, &((*F)->lchild)) ;
        else if(k > (*F)->data)
            Delete(k, &((*F)->rchild));
        else
        {
            NODE *node;
            if ((*F)->rchild == NULL)
            {
                node = *F;
                (*F) = (*F)->lchild;
                delete_Node(node);
            }
            else if((*F)->lchild == NULL)
            {
                node = *F;
                (*F) = (*F)->rchild;
                delete_Node(node);

            }
            else
            {
                (*F)->data = DeleteMin(&((*F)->rchild));
            }
        }
    }
}
int DeleteMin(AVLT **F)
{
    int temp;
    AVLT *p;
    if((*F)->lchild == NULL )
    {
        p = *F;
        temp = (*F)->data;
        (*F) = (*F)->rchild;
        delete_Node(p);
        return temp;
    }
    else
    {
        temp = DeleteMin(&((*F)->lchild));
        return temp;
    }
}
void delete_Node(NODE *node)
{
    free(node);
}
int Depth(AVLT *T)  //求二叉树的深度
{
    int ldepth,rdepth;
    if(T==NULL)
        return(0);
    else
    {
        ldepth=Depth(T->lchild);
        rdepth=Depth(T->rchild);
        if(ldepth>rdepth)
            return(ldepth+1);
        else
            return(rdepth+1);
   }
}
int set_up_Binary(char *filename,int **array)
{
    FILE *fp;
    fp = fopen(filename,"r");
    if(fp==NULL)
    {
        printf("打开文件失败\n");
        exit(1);
    }
    int num;
    int max = 0;
    while(!feof(fp))
    {
        fscanf(fp,"%d\n",&num);
        (*array)[max] = num;
        max++;
    }
    fclose(fp);
    SelectSort_increase(max,array);
    return max;
}
void SelectSort_increase(int max,int **array)
{
    int i, j, minindex, min, tempmin,temp;
    for(i=0;i<max-1;i++)
    {
        minindex = i;
        min = (*array)[minindex];
        for(j=i+1;j<max;j++)
        {
            tempmin = (*array)[j];
            if(tempmin<min)
            {
                minindex = j;
                min = tempmin;
            }
        }
        if(minindex!=i)
        {
            temp = (*array)[i];
            (*array)[i] = (*array)[minindex];
            (*array)[minindex] = temp;
        }
    }
}
int Binary_Search(int k, int max, int *depth, int *array)
{
    int  low , up , mid ;
    low = 0;
    up = max;
    while(low<=up)
    {
        mid = (up-low)/2 + low;
        if ( array[mid] == k)
        {
            (*depth)++;
            return mid ;
        }
        else if ( array[mid] > k )
        {
            (*depth)++;
            up = mid - 1 ;
        }
        else
        {
            (*depth)++;
            low = mid + 1 ;
        }
    }
    return -1;
}
void destory_tree(AVLT *BT)
{
    if(BT==NULL)
        return;
    else if(BT->lchild==NULL&&BT->rchild==NULL)
    {
        delete_Node(BT);
    }
    else
    {
        destory_tree(BT->lchild);
        destory_tree(BT->rchild);
        delete_Node(BT);
    }
}
