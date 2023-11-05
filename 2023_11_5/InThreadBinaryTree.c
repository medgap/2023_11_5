#include<stdio.h>
#include<stdlib.h>

typedef struct TreeNode{
    char data;
    struct TreeNode* lchild;
    struct TreeNode* rchild;
    int ltag;
    int rtag;
}TreeNode;

void createTree(TreeNode** t,char* data,int* index){
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
        createTree(&((*t)->lchild),data,index);
        createTree(&((*t)->rchild),data,index);
    }
}

void InTread(TreeNode* t,TreeNode** pre){
    if(t){
        InTread(t->lchild,pre);
        //do sth.
        if(t->lchild == NULL){
            t->ltag = 1;
            t->lchild = *pre;
        }
        if(*pre != NULL && (*pre)->rchild == NULL){
            (*pre)->rtag = 1;
            (*pre)->rchild = t;
        }
        *pre = t;
        InTread(t->rchild,pre);
    }
}

TreeNode* getFirst(TreeNode* t){
    while(t->ltag == 0)
        t = t->lchild;
    return t;
}

TreeNode* getNext(TreeNode* t){
    if(t->rtag)
        return t->rchild;
    else
        return getFirst(t->rchild);
}

int main(int argc,char* argv[]){
    TreeNode* t;
    TreeNode* pre = NULL;
    int index = 0;
    createTree(&t,argv[1],&index);
    InTread(t,&pre);
    pre->rtag = 1;
    pre->rchild = NULL;
    for(TreeNode* node = getFirst(t); node != NULL; node = getNext(node)){
        printf("%c ",node->data);
    }
    printf("\n");
    return 0;
}