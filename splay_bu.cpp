#include<iostream>
#include<stack>
using namespace std;

class splaytree{
    private:
    struct node{
        node *left,*right,*parent;
        int key;
        node(int key){
            this->key=key;
            left=right=parent=NULL;
        }
    };
    node *root=NULL;
    int zig=0,zigzig=0,zigzag=0;
    
    void leftrotate(node *x){
        node *y=x->right;
        if(y){
            x->right=y->left;
            if(y->left) y->left->parent=x;
            y->parent=x->parent;
        }
        if(!x->parent) root=y;
        else if(x==x->parent->left) x->parent->left=y;
        else x->parent->right=y;
        if(y) y->left=x;
        x->parent=y;
    }
    
    void rightrotate(node *x){
        node *y=x->left;
        if(y){
            x->left=y->right;
            if(y->right) y->right->parent=x;
            y->parent=x->parent;
        }
        if(!x->parent) root=y;
        else if( x == x->parent->left ) x->parent->left = y;
        else x->parent->right = y;
        if(y) y->right = x;
        x->parent = y;
    }
    
    void splay(node *x){
        //bottom up splay
        while(x->parent){
            if(!x->parent->parent){
                zig++;
                if(x->parent->left==x) rightrotate(x->parent);
                else leftrotate(x->parent);
            }
            else if(x->parent->left==x &&x->parent->parent->left==x->parent){
                zigzig++;
                rightrotate(x->parent->parent);
                rightrotate(x->parent);
            }
            else if( x->parent->right == x && x->parent->parent->right == x->parent ) {
                zigzig++;
                leftrotate( x->parent->parent );
                leftrotate( x->parent );
            } 
            else if( x->parent->left == x && x->parent->parent->right == x->parent ) {
                zigzag++;
                rightrotate( x->parent );
                leftrotate( x->parent );
            } else 
            {
                zigzag++;
                leftrotate( x->parent );
                rightrotate( x->parent );
            }
        }
    }
    
    node* findmin(node *u){
        while(u->left) u=u->left;
        return u;
    }
    
    node* findmax(node *u){
        while(u->right) u=u->right;
        return u;
    }
    public:
    
    void insert(int key)
    {
    node *z = root;
    node *p = NULL;
    
    while(z) {
      p = z;
      if( key > z->key ) z = z->right;
      else if (key<z->key) z = z->left;
      else if(key==z->key) {
          splay(z);
          return;
      }
    }
    
    z = new node(key);
    z->parent = p;
    
    if(p==NULL) root = z;
    else{
	    if( p->key< z->key ) p->right = z;
	    else p->left = z;
	}
    splay( z );
    }
    
    void search(int key){
    	if(root==NULL || root->key==key) return;
    	
        node *current=root; node *p=NULL;
        while(current){
            p=current;
           if(key<current->key) current=current->left;
           else if (key>current->key) current=current->right;
           else if(current->key==key) {
				splay(current);
				return;
           }
        }
        //node not found
        splay(p);
        return;
    }
    
    void Delete(int key){
        if(root==NULL) return;
        search(key); //will bring last accessed node at root
        if(root->key!=key) return;
        
        node *L=root->left;
        node *R=root->right;
        delete(root);
        
        //Rmin
        if(R){
           R->parent=NULL;
           node *Rmin=findmin(R);
           splay(Rmin);
           R->left=L;
           if(L) L->parent=R;
           root=R;
        }
        else{
            if(L){
                L->parent=NULL;
                root=L;
            }
        }
     
    }
    
    void printops(){
        cout<<zig<<endl;
        cout<<zigzig<<endl;
        cout<<zigzag<<endl;
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
	    
    void traversals(){
        node *r=root;
        preorder(r);cout<<endl;
        inorder(r);cout<<endl;
        postorder(r);cout<<endl;
    }
};

int main()
{   
    splaytree T;
    int x,NQ;
    char op;
    cin>>NQ;
    while(NQ--){
        cin>>op>>x;
        if(op=='i') T.insert(x);
        else if (op=='d') T.Delete(x);
        else if(op=='s') T.search(x);
    }
    T.traversals();  
    T.printops();
}


