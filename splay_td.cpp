#include<iostream>
using namespace std;
int reassembles=0;
struct node{
	int key,height;
	node *left,*right;

node(int key){
	this->key=key;
	left=right=NULL;
}
node(){
    left=right=NULL;
}
};
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

node* splay(node *t,int i){
    node N, *l, *r, *y;
    if (t == NULL) return t;
    N.left = N.right = NULL;
    l = r = &N;

    for (;;) {
	if (i < t->key) {
	    if (t->left == NULL) break;
	    if (i < t->left->key) {
		y = t->left;                           /* rotate right */
		t->left = y->right;
		y->right = t;
		t = y;
		if (t->left == NULL) break;
	    }
	    r->left = t;                               /* link right */
	    r = t;
	    t = t->left;
	} else if (i > t->key) {
	    if (t->right == NULL) break;
	    if (i > t->right->key) {
		y = t->right;                          /* rotate left */
		t->right = y->left;
		y->left = t;
		t = y;
		if (t->right == NULL) break;
	    }
	    l->right = t;                              /* link left */
	    l = t;
	    t = t->right;
	} else {
	    break;
	}
    }
    reassembles++;
    l->right = t->left;                                /* assemble */
    r->left = t->right;
    t->left = N.right;
    t->right = N.left;
    return t;
    }
node* findmin(node *root){
    while(root->left){
        root=root->left;
    }
    return root;
}
node* deleteNode(node *root,int i){
    if(root==NULL) return NULL;
    root=splay(root,i);
    if(root->key!=i) return root;
    
    node *L=root->left;
    node *R=root->right;
    delete root;
    if(L&&R){
        node *Rmin=findmin(R);
        Rmin=splay(R,Rmin->key);
        Rmin->left=L;
        return Rmin;
    }
    else if(L&&!R){
        return L;
    }
    else if(R&&!L){
        return R;
    }
    else return NULL;
}
node* insert(node *root, int i){
    node *newNode=new node(i);
    if(root==NULL) return newNode;
    else{
        //splay at value to be inserted
        root=splay(root,i);
        if(i<root->key){
            newNode->right=root;
            newNode->left=root->left;
            root->left=NULL;
            return newNode;
        }
        else if(i>root->key){
            newNode->left=root;
            newNode->right=root->right;
            root->right=NULL;
            return newNode;
        }
        else{
            delete newNode;
            return root;
        }
    }
    
    
}
node* search(node *root,int key){
	root=splay(root,key);
	return root;
}


int main()
{   
  node *root=NULL;
    int x,NQ;
    char op;
    cin>>NQ;
    while(NQ--){
        cin>>op>>x;
        if(op=='i') root=insert(root,x);
        else if (op=='d') root=deleteNode(root,x);
        else if(op=='s') root=search(root,x);
    }
    preorder(root);cout<<endl;
    inorder(root);cout<<endl;
    postorder(root);cout<<endl;  
    cout<<reassembles<<endl;
}
