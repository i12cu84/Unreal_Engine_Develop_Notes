#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

//定义B+树节点结构体
struct BPlusNode{
    bool isLeaf; //是否为叶子节点
    vector<int> keys; //关键字列表
    BPlusNode *parent; //父节点指针
    vector<BPlusNode*> children; //子节点指针列表
    BPlusNode(bool leaf=false):isLeaf(leaf),parent(NULL){} //构造函数
};

//获取节点最左边的关键字
int getLeftmostKey(BPlusNode *node){
    if(node==NULL) return -1;
    if(node->isLeaf) return node->keys[0];
    return getLeftmostKey(node->children[0]);
}

//获取节点最右边的关键字
int getRightmostKey(BPlusNode *node){
    if(node==NULL) return -1;
    if(node->isLeaf) return node->keys[node->keys.size()-1];
    return getRightmostKey(node->children[node->children.size()-1]);
}

//获取节点中大于等于key的最小关键字位置
int getLowerBound(BPlusNode *node,int key){
    int l=0,r=node->keys.size()-1;
    while(l<=r){
        int mid=l+(r-l)/2;
        if(node->keys[mid]>=key) r=mid-1;
        else l=mid+1;
    }
    return l;
}

//获取节点中大于key的最小关键字位置
int getUpperBound(BPlusNode *node,int key){
    int l=0,r=node->keys.size()-1;
    while(l<=r){
        int mid=l+(r-l)/2;
        if(node->keys[mid]>key) r=mid-1;
        else l=mid+1;
    }
    return l;
}

//查找关键字所在的叶子节点
BPlusNode* searchLeafNode(BPlusNode *node,int key){
    if(node==NULL) return NULL;
    if(node->isLeaf) return node;
    int index=getLowerBound(node,key);
    return searchLeafNode(node->children[index],key);
}

//分裂叶子节点
void splitLeafNode(BPlusNode *node){
    int mid=node->keys.size()/2;
    BPlusNode *newNode=new BPlusNode(true);
    newNode->keys.assign(node->keys.begin()+mid,node->keys.end());
    node->keys.erase(node->keys.begin()+mid,node->keys.end());
    newNode->parent=node->parent;
    if(node->parent==NULL){
        node->parent=new BPlusNode(false);
        node->parent->children.push_back(node);
    }
    int index=getLowerBound(node->parent,newNode->keys[0]);
    node->parent->keys.insert(node->parent->keys.begin()+index,newNode->keys[0]);
    node->parent->children.insert(node->parent->children.begin()+index+1,newNode);
    for(int i=0;i<newNode->keys.size();i++){
        newNode->keys[i]=node->keys[i+mid];
    }
    newNode->children.push_back(node->children[node->children.size()-1]);
    node->children[node->children.size()-1]=newNode;
}

//分裂非叶子节点
void splitNonLeafNode(BPlusNode *node){
    int mid=node->keys.size()/2;
    BPlusNode *newNode=new BPlusNode(false);
    newNode->keys.assign(node->keys.begin()+mid+1,node->keys.end());
    node->keys.erase(node->keys.begin()+mid,node->keys.end());
    newNode->parent=node->parent;
    if(node->parent==NULL){
        node->parent=new BPlusNode(false);
        node->parent->children.push_back(node);
    }
    newNode->children.assign(node->children.begin()+mid+1,node->children.end());
    for(int i=0;i<newNode->children.size();i++){
        newNode->children[i]->parent=newNode;
    }
    node->children.erase(node->children.begin()+mid+1,node->children.end());
    int index=getLowerBound(node->parent,newNode->keys[0]);
    node->parent->keys.insert(node->parent->keys.begin()+index,newNode->keys[0]);
    node->parent->children.insert(node->parent->children.begin()+index+1,newNode);
}

//插入关键字
void insertKey(BPlusNode *node,int key){
    node->keys.insert(getLowerBound(node,key),key);
    if(node->keys.size()>2){
        if(node->isLeaf) splitLeafNode(node);
        else splitNonLeafNode(node);
    }
}

//插入关键字并调整B+树
void insert(BPlusNode *&root,int key){
    if(root==NULL){
        root=new BPlusNode(true);
        root->keys.push_back(key);
        return;
    }
    BPlusNode *leafNode=searchLeafNode(root,key);
    insertKey(leafNode,key);
}

//删除关键字
void deleteKey(BPlusNode *node,int key){
    int index=getLowerBound(node,key);
    if(index<node->keys.size() && node->keys[index]==key){
        node->keys.erase(node->keys.begin()+index);
    }
}

//合并叶子节点
void mergeLeafNode(BPlusNode *node){
    BPlusNode *leftNode=node->parent->children[getLowerBound(node->parent,node->keys[0])-1];
    leftNode->keys.insert(leftNode->keys.end(),node->keys.begin(),node->keys.end());
    leftNode->children[node->children.size()-1]=node->children[node->children.size()-1];
    node->parent->keys.erase(node->parent->keys.begin()+getLowerBound(node->parent,node->keys[0]));
    node->parent->children.erase(node->parent->children.begin()+getLowerBound(node->parent,node->keys[0])+1);
    delete node;
}

//合并非叶子节点
void mergeNonLeafNode(BPlusNode *node){
    BPlusNode *leftNode=node->parent->children[getLowerBound(node->parent,node->keys[0])-1];
    leftNode->keys.push_back(node->parent->keys[getLowerBound(node->parent,node->keys[0])]);
    leftNode->keys.insert(leftNode->keys.end(),node->keys.begin(),node->keys.end());
    leftNode->children.insert(leftNode->children.end(),node->children.begin(),node->children.end());
    for(int i=0;i<node->children.size();i++){
        node->children[i]->parent=leftNode;
    }
    node->parent->keys.erase(node->parent->keys.begin()+getLowerBound(node->parent,node->keys[0]));
    node->parent->children.erase(node->parent->children.begin()+getLowerBound(node->parent,node->keys[0])+1);
    delete node;
}

//删除关键字并调整B+树
void remove(BPlusNode *&root,int key){
    if(root==NULL) return;
    BPlusNode *leafNode=searchLeafNode(root,key);
    deleteKey(leafNode,key);
    if(leafNode->keys.size()<1){
        if(leafNode->parent==NULL){
            root=NULL;
            delete leafNode;
            return;
        }
        if(leafNode->parent->children[0]==leafNode){
            BPlusNode *rightNode=leafNode->parent->children[1];
            if(rightNode->keys.size()>1){
                leafNode->keys.push_back(rightNode->keys[0]);
                rightNode->keys.erase(rightNode->keys.begin());
                leafNode->children[leafNode->children.size()-1]=rightNode->children[0];
                rightNode->children[0]->parent=leafNode;
                rightNode->children.erase(rightNode->children.begin());
                leafNode->parent->keys[0]=rightNode->keys[0];
            }
            else{
                mergeLeafNode(rightNode);
            }
        }
        else{
            BPlusNode *leftNode=leafNode->parent->children[getLowerBound(leafNode->parent,leafNode->keys[0])-1];
            if(leftNode->keys.size()>1){
                leafNode->keys.insert(leafNode->keys.begin(),leftNode->keys[leftNode->keys.size()-1]);
                leftNode->keys.erase(leftNode->keys.begin()+leftNode->keys.size()-1);
                leafNode->children.insert(leafNode->children.begin(),leftNode->children[leftNode->children.size()-1]);
                leftNode->children[leftNode->children.size()-1]->parent=leafNode;
                leftNode->children.erase(leftNode->children.begin()+leftNode->children.size()-1);
                leafNode->parent->keys[getLowerBound(leafNode->parent,leafNode->keys[0])-1]=leafNode->keys[0];
            }
            else{
                mergeLeafNode(leafNode);
            }
        }
    }
}

//中序遍历叶子节点
void inorderTraversalLeafNodes(BPlusNode *node){
    if(node==NULL) return;
    if(node->isLeaf){
        for(int i=0;i<node->keys.size();i++){
            cout<<node->keys[i]<<" ";
        }
    }
    else{
        for(int i=0;i<node->children.size();i++){
            inorderTraversalLeafNodes(node->children[i]);
        }
    }
}

//测试样例
int main(){
    BPlusNode *root=NULL;
    insert(root,10);
    insert(root,20);
    insert(root,30);
    insert(root,40);
    insert(root,50);
    insert(root,60);
    insert(root,70);
    insert(root,80);
    insert(root,90);
    insert(root,100);
    cout<<"Inorder traversal of the B+ tree is:"<<endl;
    inorderTraversalLeafNodes(root);
    cout<<endl;
    remove(root,30);
    remove(root,50);
    remove(root,70);
    cout<<"Inorder traversal of the B+ tree after deleting 30, 50, 70 is:"<<endl;
    inorderTraversalLeafNodes(root);
    cout<<endl;
    return 0;
}