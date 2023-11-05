#include<stdio.h>
#include<stdlib.h>

typedef struct TreeNode
{
    char data;
    struct TreeNode* lchild;
    struct TreeNode* rchild;
    struct TreeNode* parent;
    int ltag;
    int rtag;
}TreeNode;

void createTree(TreeNode** t,char* data,int* index,TreeNode* parent){
    char ch = data[*index];
    *index += 1;
    if(ch == '#'){
        *t = NULL;
    }
    else{
        *t = (TreeNode*)malloc(sizeof(TreeNode));
        (*t)->data = ch;
        (*t)->ltag = 0;
        (*t)->rtag = 0;
        (*t)->parent = parent;
        createTree(&((*t)->lchild),data,index,*t);
        createTree(&((*t)->rchild),data,index,*t);
    }
}

void PostThreadTree(TreeNode* t,TreeNode** pre){
    if(t){
        PostThreadTree(t->lchild,pre);
        PostThreadTree(t->rchild,pre);
        if(t->lchild == NULL){
            t->ltag = 1;
            t->lchild = *pre;
        }
        if(*pre != NULL && (*pre)->rchild == NULL){
            (*pre)->rtag = 1;
            (*pre)->rchild = t;
        }
        *pre = t;
    }
}

TreeNode* getFirst(TreeNode* t){
    while(t->ltag == 0){
        t= t->lchild;
    }
    if(t->rtag == 0)
        return getFirst(t->rchild);
    return t;
}

TreeNode* getNext(TreeNode* t){
    if(t->rtag == 1)
        return t->rchild;
    else{
        //根节点
        if(t->parent == NULL)
            return NULL;
        //右孩子
        else if(t->parent->rchild == t)
            return t->parent;
        //左孩子
        else{
            //右孩子为空
            if(t->parent->rtag == 1)
                return t->parent;
            //右孩子不为空
            else
                return getFirst(t->parent->rchild);
        }
    }
}
int main(int argc,char* argv[]){
    TreeNode* t;
    TreeNode* pre = NULL;
    int index = 0;
    createTree(&t,argv[1],&index,NULL);
    PostThreadTree(t,&pre);
    for(TreeNode* node = getFirst(t); node != NULL; node = getNext(node)){
        printf("%c ",node->data);
    }
    printf("\n");
    return 0;
}