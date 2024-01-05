#include<iostream>
using namespace std;

//定义AVL节点结构体
struct AVLNode{
    int key; //节点关键字
    int height; //节点高度
    AVLNode *left; //左子节点
    AVLNode *right; //右子节点
    AVLNode(int k):key(k),height(1),left(NULL),right(NULL){} //构造函数
};

//获取节点高度
int getHeight(AVLNode *node){
    if(node==NULL) return 0;
    return node->height;
}

//获取节点平衡因子
int getBalance(AVLNode *node){
    if(node==NULL) return 0;
    return getHeight(node->left)-getHeight(node->right);
}

//更新节点高度
void updateHeight(AVLNode *node){
    node->height=max(getHeight(node->left),getHeight(node->right))+1;
}

//左旋
AVLNode* leftRotate(AVLNode *node){
    AVLNode *r=node->right;
    AVLNode *rl=r->left;
    r->left=node;
    node->right=rl;
    updateHeight(node);
    updateHeight(r);
    return r;
}

//右旋
AVLNode* rightRotate(AVLNode *node){
    AVLNode *l=node->left;
    AVLNode *lr=l->right;
    l->right=node;
    node->left=lr;
    updateHeight(node);
    updateHeight(l);
    return l;
}

//插入节点
AVLNode* insertNode(AVLNode *node,int key){
    if(node==NULL) return new AVLNode(key);
    if(key<node->key) node->left=insertNode(node->left,key);
    else node->right=insertNode(node->right,key);
    updateHeight(node);
    int balance=getBalance(node);
    if(balance>1 && key<node->left->key) return rightRotate(node);
    if(balance>1 && key>node->left->key){
        node->left=leftRotate(node->left);
        return rightRotate(node);
    }
    if(balance<-1 && key>node->right->key) return leftRotate(node);
    if(balance<-1 && key<node->right->key){
        node->right=rightRotate(node->right);
        return leftRotate(node);
    }
    return node;
}

//查找节点
AVLNode* searchNode(AVLNode *node,int key){
    if(node==NULL || node->key==key) return node;
    if(key<node->key) return searchNode(node->left,key);
    else return searchNode(node->right,key);
}

//删除节点
AVLNode* deleteNode(AVLNode *node,int key){
    if(node==NULL) return node;
    if(key<node->key) node->left=deleteNode(node->left,key);
    else if(key>node->key) node->right=deleteNode(node->right,key);
    else{
        if(node->left==NULL || node->right==NULL){
            AVLNode *temp=node->left?node->left:node->right;
            if(temp==NULL){
                temp=node;
                node=NULL;
            }
            else *node=*temp;
            delete temp;
        }
        else{
            AVLNode *temp=node->right;
            while(temp->left!=NULL) temp=temp->left;
            node->key=temp->key;
            node->right=deleteNode(node->right,temp->key);
        }
    }
    if(node==NULL) return node;
    updateHeight(node);
    int balance=getBalance(node);
    if(balance>1 && getBalance(node->left)>=0) return rightRotate(node);
    if(balance>1 && getBalance(node->left)<0){
        node->left=leftRotate(node->left);
        return rightRotate(node);
    }
    if(balance<-1 && getBalance(node->right)<=0) return leftRotate(node);
    if(balance<-1 && getBalance(node->right)>0){
        node->right=rightRotate(node->right);
        return leftRotate(node);
    }
    return node;
}

//中序遍历
void inorderTraversal(AVLNode *node){
    if(node==NULL) return;
    inorderTraversal(node->left);
    cout<<node->key<<" ";
    inorderTraversal(node->right);
}

//测试样例
int main(){
    AVLNode *root=NULL;
    root=insertNode(root,10);
    root=insertNode(root,20);
    root=insertNode(root,30);
    root=insertNode(root,40);
    root=insertNode(root,50);
    root=insertNode(root,25);
    cout<<"Inorder traversal of the AVL tree is:"<<endl;
    inorderTraversal(root);
    cout<<endl;
    root=deleteNode(root,30);
    cout<<"Inorder traversal of the AVL tree after deleting 30 is:"<<endl;
    inorderTraversal(root);
    cout<<endl;
    return 0;
}