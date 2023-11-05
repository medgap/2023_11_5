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

void PreThreadTree(TreeNode* t,TreeNode** pre){
    if(t){
        if(t->lchild == NULL){
            t->ltag = 1;
            t->lchild = *pre;
        }
        if(*pre != NULL && (*pre)->rchild == NULL){
            (*pre)->rtag = 1;
            (*pre)->rchild = t;
        }
        *pre = t;
        if(t->ltag == 0)
            PreThreadTree(t->lchild,pre);
        if(t->rtag == 0)
            PreThreadTree(t->rchild,pre);
    }
}

TreeNode* getNext(TreeNode* node){
    if (node->rtag == 1 || node->ltag == 1)
        return node->rchild;
    else
        return node->lchild;
}

int main(int argc,char* argv[]){
    TreeNode* t;
    TreeNode* pre = NULL;
    int index = 0;
    createTree(&t,argv[1],&index);
    PreThreadTree(t,&pre);
    pre->rtag = 1;
    pre->rchild = NULL;
    for(TreeNode* node = t; node != NULL; node = getNext(node)){
        printf("%c ",node->data);
    }
    printf("\n");
    return 0;
}