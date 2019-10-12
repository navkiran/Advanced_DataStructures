#include<iostream>
using namespace std;

struct node{
	int key,height;
	node *left,*right;

node(int key){
	this->key=key;
	left=right=NULL;
	height=1;
}
};

int max(int a,int b){
	return a>b?a:b;
}

int height(node *root){
	if(root==NULL) return 0;
	else return root->height;
}

int balfactor(node *root){
	return height(root->left)-height(root->right);
}


node* leftrotate(node *root){
	node *temp=root->right;
	root->right=temp->left;
	temp->left=root;
	root->height=1+max(height(root->left),height(root->right));
	temp->height=1+max(height(temp->left),height(temp->right));
	return temp;
}

node* rightrotate(node *root){
	node *temp=root->left;
	root->left=temp->right;
	temp->right=root;
	root->height=1+max(height(root->left),height(root->right));
	temp->height=1+max(height(temp->left),height(temp->right));
	return temp;
}



node* insertion(node *root,int key){
	if(root==NULL) return new node(key);
	
	if(key<root->key) root->left=insertion(root->left,key);
	else if(key>root->key) root->right=insertion(root->right,key);
	else return root;
	
	root->height=1+max(height(root->left),height(root->right));
	int bal=balfactor(root);
	if(bal>1||bal<-1) cout<<root->key<<endl;
	if(bal>1){
		if(key<root->left->key) return rightrotate(root);
		
		if(key>root->left->key){
			root->left=leftrotate(root->left);
			return rightrotate(root);
		}
	}
	if(bal<-1){

		if(key>root->right->key) return leftrotate(root);

		if(key<root->right->key){
			root->right=rightrotate(root->right);
			return leftrotate(root);
		}
	}

return root;
}
node* successor(node *root){
	
	while(root->left){
		root=root->left;
	}
	return root;
}

node* deleteNode(node *root,int key){
	if(root==NULL) return NULL;

	if(key<root->key) root->left=deleteNode(root->left,key);
	else if(key>root->key) root->right=deleteNode(root->right,key);

	else{
		if(!root->left&&!root->right){
			delete root;
			return NULL;
		}
		else if(root->left&&!root->right){
			node *temp=root->left;
			delete root;
			return temp;
		}
		else if(root->right&&!root->left){
			node *temp=root->right;
			delete root;
			return temp;
		}
		else if(root->right&&root->left){
			node *temp=successor(root->right);
			root->key=temp->key;
			root->right=deleteNode(root->right,temp->key);
		}
	}

	root->height=1+max(height(root->left),height(root->right));
	int bal=balfactor(root);
	if(bal>1||bal<-1) cout<<root->key<<endl;

	if(bal>1){

		if(balfactor(root->left)>=0) return rightrotate(root);

		if(balfactor(root->left)<0){
			root->left=leftrotate(root->left);
			return rightrotate(root);
		}
	}
	if(bal<-1){

		if(balfactor(root->right)<=0) return leftrotate(root);

		if(balfactor(root->right)>0){
			root->right=rightrotate(root->right);
			return leftrotate(root);
		}
	}

return root;
}
void preorder(node *root){
	if(root){
		cout<<root->key<<" ";
		preorder(root->left);
		preorder(root->right);
	}
}

void inorder(node *root){
	if(root){
		inorder(root->left);
		cout<<root->key<<" ";
		inorder(root->right);
	}
}

void postorder(node *root){
	if(root){
		postorder(root->left);
		postorder(root->right);
		cout<<root->key<<" ";
	}
}


int main()
{   
    node *root=NULL;
    int x,NQ;
    char op;
    cin>>NQ;
    while(NQ--){
        cin>>op>>x;
        if(op=='i') root=insertion(root,x);
        else if (op=='d') root=deleteNode(root,x);
    }
    preorder(root);cout<<endl;
    inorder(root);cout<<endl;
    postorder(root);cout<<endl;
}
