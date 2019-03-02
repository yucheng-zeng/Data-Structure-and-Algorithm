#include <stdio.h>
#include <stdlib.h>
#define NULL ((void *)0)
#define TRUE 1
#define FALSE 0
struct node
{
    int data; //关键字
    int bf; //平行因子
    struct node *lchild;  //左子树
    struct node *rchild;  //右子树
};
typedef struct
{
    struct node * child;
}ROOT;
typedef struct node NODE;
typedef struct node AVLT;
typedef int boolean;
typedef NODE *BST;


NODE *new_Node(int R);
void RightRotation(AVLT **PT, int *unbalanced);
void LeftRotation (AVLT **PT, int *unbalanced);
void AVLInsert(AVLT **PT ,int R, int *unbalanced);
void set_up_AVL_TREE(ROOT *root,char *filename);
ROOT new_Root();
void PreOrder(AVLT *BT);
NODE *search(int k, AVLT *F);
void Delete(int k ,AVLT **F);
void delete_Node(NODE *node);
int DeleteMin(AVLT **F);
int Depth(AVLT *T);  //求二叉树的深度
boolean IsAVL(AVLT *T);   //判断平衡二叉树
void Adjust_BF(AVLT **T);
void Adjust_Tree(AVLT **T);
void AVL_Delete(int R, ROOT *root);
void InOrder(AVLT *BT);


int main()
{
    ROOT root = new_Root();
    set_up_AVL_TREE(&root,"btree.txt");
    /*
    int k;
    printf("请输入要查找节点信息：");
    scanf("%d",&k);
    NODE *node = search(k,root.child);
    if(node)
        printf("已找到节点:%d",node->data);
    else
        printf("无该节点信息");
    */
    printf("排序结果：");
    InOrder(root.child);
    return 0;
}

void AVL_Delete(int R, ROOT *root)
{
    Delete(R,&(root->child));
    boolean flag = IsAVL(root->child);
    Adjust_Tree(&(root->child));
}
void Adjust_Tree(AVLT **T)
{
    int unbalance = TRUE;
    if((*T)==NULL)
    {
        return;
    }
    else if((*T)->lchild==NULL&&(*T)->rchild==NULL)
    {
        (*T)->bf = 0;
    }
    else if((*T)->lchild&&(*T)->rchild==NULL)
    {
        Adjust_Tree(&((*T)->lchild));
        int left = Depth((*T)->lchild);
        (*T)->bf = left;
        if(left==2)
            LeftRotation(T,&unbalance);
    }
    else if((*T)->rchild&&(*T)->lchild==NULL)
    {
        Adjust_Tree(&((*T)->rchild));
        int right = -Depth((*T)->rchild);
        (*T)->bf = right;
        if(right==-2)
            RightRotation(T,&unbalance);
    }
    else
    {
        Adjust_Tree(&((*T)->lchild));
        Adjust_Tree(&((*T)->rchild));
        //(*T)->bf = Depth((*T)->lchild) - Depth((*T)->rchild);
        int ldepth = Depth((*T)->lchild);
        int rdepth = Depth((*T)->rchild);
        int diff = ldepth - rdepth;
        (*T)->bf = diff;
        if(diff==2)
        {
            LeftRotation(T,&unbalance);
        }
        else if(diff==-2)
        {
            RightRotation(T,&unbalance);
        }
    }
}
void Adjust_BF(AVLT **T)
{
    int unbalance = TRUE;
    if((*T)==NULL)
    {
        return;
    }
    else if((*T)->lchild==NULL&&(*T)->rchild==NULL)
    {
        (*T)->bf = 0;
    }
    else if((*T)->lchild&&(*T)->rchild==NULL)
    {
        Adjust_BF(&((*T)->lchild));
        (*T)->bf = Depth((*T)->lchild);

    }
    else if((*T)->rchild&&(*T)->lchild==NULL)
    {
        Adjust_BF(&((*T)->rchild));
        (*T)->bf = -Depth((*T)->rchild);
    }
    else
    {
        Adjust_BF(&((*T)->lchild));
        Adjust_BF(&((*T)->rchild));
        //(*T)->bf = Depth((*T)->lchild) - Depth((*T)->rchil
        (*T)->bf = Depth((*T)->lchild) - Depth((*T)->rchild);
    }
}
void PreOrder(AVLT *BT)
{
    if(BT)
    {
        printf("%d\t%d\t",BT->data,BT->bf);
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
void set_up_AVL_TREE(ROOT *root,char *filename)
{
    FILE *fp;
    fp = fopen(filename,"r");
    if(fp==NULL)
    {
        printf("打开文件失败\n");
        exit(1);
    }
    int num;
    int unbalanced = FALSE;
    while(!feof(fp))
    {
        fscanf(fp," %d",&num);
        AVLInsert(&(root->child),num,&unbalanced);
    }
}
void AVLInsert(AVLT **T ,int R, int *unbalanced)
{
    if(!(*T)) //向空二叉树中插入元素
    {
        (*unbalanced) = TRUE ;
        (*T) = new_Node(R);
    }
    else if(R<(*T)->data) //在左子树上插入
    {
        AVLInsert(&((*T)->lchild), R, unbalanced);
        if(*unbalanced)
        {
            switch((*T)->bf)
            {
                case -1:
                    (*T)->bf = 0;
                    (*unbalanced) = FALSE;
                    break;
                case 0:
                    (*T)->bf = 1;
                    break;
                case 1:
                    LeftRotation(T,unbalanced);
                    break;
            }
        }
    }
    else if(R>(*T)->data)     //在右子树上插入
    {
        AVLInsert(&((*T)->rchild), R, unbalanced) ;
        if(*unbalanced)
        {
            switch ((*T)->bf)
            {
                case 1:
                    (*T)->bf  =  0;
                    (*unbalanced) = FALSE;
                    break ;
                case 0:
                    (*T)->bf  =  -1 ;
                    break ;
                case -1:
                    RightRotation(T, unbalanced);
            }
          }
    }
   else
        *unbalanced = FALSE;
}

void LeftRotation(AVLT **T , int *unbalanced)
{
    AVLT *gc, *lc;
    lc = (*T)->lchild;
    if(lc->bf==1)    //LL旋转
    {
        printf("\nLL\n");
        (*T)->lchild = lc->rchild;
        lc->rchild = (*T);
        (*T)->bf = 0;
        (*T) = lc;
    }
    else // LR旋转
    {
        printf("\nLR\n");
        gc = lc->rchild;
        lc->rchild = gc->lchild;
        gc->lchild = lc ;
        (*T)->lchild  = gc->rchild;
        gc->rchild = (*T);
        switch(gc->bf)
        {
            case 1:
                (*T)->bf  = -1;
                lc->bf = 0;
                break ;
            case 0:
                (*T)->bf = 0;
                lc->bf = 0;
                break ;
            case -1:
                (*T)->bf  = 0;
                lc->bf = 1;
        }
        (*T) = gc;
    }
    (*T)->bf = 0;
    *unbalanced = FALSE;
}
void RightRotation(AVLT **T, int *unbalanced)
{
    AVLT *gc, *rc;
    rc = (*T)->rchild;
    if(rc->bf==-1)                   //RR旋转
    {
        printf("\nRR\n");
        (*T)->rchild = rc->lchild;
        rc->lchild = (*T);
        (*T)->bf = 0;
        (*T) = rc;
    }
    else//RL旋转
    {
        printf("\nRL\n");
        gc = rc->lchild ;
        rc->lchild=gc->rchild ;
        gc->rchild=rc;
        (*T)->rchild=gc->lchild ;
        gc->lchild=(*T);
        switch(gc->bf)
        {      //调整平衡因子
            case -1:
                (*T)->bf=1;
                rc->bf=0 ;
                break ;
            case 0:
                (*T)->bf=0;
                rc->bf = 0;
                break ;
            case 1:
                (*T)->bf =0;
                rc->bf=-1;
                break;
        }
        (*T) = gc;
    }
    (*T)->bf = 0;
    *unbalanced = FALSE;
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
    node->bf = 0;
    node->data = R;
    node->lchild = NULL;
    node->rchild = NULL;
    return node;
}
NODE *search(int k, AVLT *F)
{
    NODE *p = F;
    if ( p == NULL )
        return NULL ;
    else if( k == p->data)
        return p;
    else if( k < p->data)
        return(search(k, p->lchild));
    else if( k > p->data)
        return(search(k, p->rchild));
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
            if ((*F)->rchild == NULL)
                (*F) = (*F)->lchild;
            else if((*F)->lchild == NULL)
                (*F) = (*F)->rchild;
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
boolean IsAVL(AVLT *T)   //判断平衡二叉树
{
    boolean hl,hr;
    if(T==NULL)
        return(1);
    else
    {
        hl=Depth(T->lchild);
        hr=Depth(T->rchild);
        if(abs(hl-hr)<=1)
        {
            if(IsAVL(T->lchild))
                return(IsAVL(T->rchild));
        }
        else
            return(0);
    }
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
