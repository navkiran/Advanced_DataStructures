#include<iostream>
#define RED 'R'
#define BLACK 'B'
using namespace std;

class rbtree{
	private:
		struct node{
			int key;
			char color;
			node *left,*right,*parent;
			node(int key){
				this->key=key;
				left=right=parent=NULL;
				color=RED;
			}
			
			bool onLeft(){
				//node is on left of its parent
				if(parent) return this==parent->left;
			}
			bool hasRedChild(){
				return (left&&left->color==RED)||(right&&right->color==RED);
			}
			node* uncle(){
				if(!parent||!parent->parent) return NULL;
				if(parent->onLeft()) return parent->parent->right;
				else  return parent->parent->left;
			}
			node* sibling(){
				if(!parent) return NULL;
				
				if(onLeft()) return parent->right;
				else return parent->left;
			}
	};
	node *root=NULL;
		void preorder(node *root){
			if(root){
				cout<<root->key<<" "<<root->color<<" ";
				preorder(root->left);
				preorder(root->right);
			}
		}
		
		void inorder(node *root){
			if(root){
				inorder(root->left);
				cout<<root->key<<" "<<root->color<<" ";
				inorder(root->right);
			}
		}
		
		void postorder(node *root){
			if(root){
				postorder(root->left);
				postorder(root->right);
				cout<<root->key<<" "<<root->color<<" ";
			}
		}
		void leftrotate(node *x){
			node *y=x->right;
			if(y){
				x->right=y->left;
				if(y->left) y->left->parent=x;
				y->left=x;
				y->parent=x->parent;
			}
			if(!x->parent) root=y;
			else if(x->onLeft()) x->parent->left=y;
			else x->parent->right=y;
			
			x->parent=y;
		}
		
		void rightrotate(node *x){
			node *y=x->left;
			if(y){
				x->left=y->right;
				if(y->right) y->right->parent=x;
				y->right=x;
				y->parent=x->parent;
			}
			if(!x->parent) root=y;
			else if(x->onLeft()) x->parent->left=y;
			else x->parent->right=y;
			
			x->parent=y;
		}
		
		void swapColors(node *a,node *b){
			char temp=a->color;
			a->color=b->color;
			b->color=temp;
		}
		
		void swapValues(node *a,node *b){
			int temp=a->key;
			a->key=b->key;
			b->key=temp;
		}
		
		void fixRedRed(node *x){
			if(root==x){
				x->color=BLACK;
				return;
			}
			
			node *parent=x->parent;
			node *grandparent=(parent)?x->parent->parent:NULL;
			node *uncle=x->uncle();
			
			if(parent->color==RED){
				if(uncle&&uncle->color==RED){
					//push red up
					parent->color=BLACK;
					uncle->color=BLACK;
					grandparent->color=RED;
					fixRedRed(grandparent);
				}
				else{
					//uncle black or NULL
					if(parent->onLeft()){
						if(x->onLeft()){
							//skewed shape
							swapColors(parent,grandparent);
						}
						else{
							//angular shape
							leftrotate(parent);
							swapColors(x,grandparent);
						}
						rightrotate(grandparent);
					}
					else{
						if(!x->onLeft()){
							//right right skewed
							swapColors(parent,grandparent);
						}
						else{
							rightrotate(parent);
							swapColors(x,grandparent);
						}
						leftrotate(grandparent);
					}
				}
			}
		}
		
		node* successor(node *n){
			while(n->left) n=n->left;
			return n;
		}
		
		node* BSTreplace(node *x){
			if(x->left&&x->right) return successor(x->right);
			if(!x->left&&!x->right) return NULL;
			else if (x->right) return x->right;
			else return x->left;
		}
		void deleteNode(node *v) { 
			node *u = BSTreplace(v); 
			bool uvBlack = ((u == NULL or u->color == BLACK) && (v->color == BLACK)); 
			node *parent = v->parent; 
		
			if (u == NULL) { 
			 
			if (v == root) { 
				
				root = NULL; 
			} else { 
				if (uvBlack) { 
				fixDoubleBlack(v); 
				} else { 
				if (v->sibling() != NULL) 
					
					v->sibling()->color = RED; 
				} 
				if (v->onLeft()) { 
				parent->left = NULL; 
				} else { 
				parent->right = NULL; 
				} 
			} 
			delete v; 
			return; 
			} 
		
			if (v->left == NULL || v->right == NULL) { 
			
			if (v == root) { 
				
				v->key = u->key; 
				v->left = v->right = NULL; 
				delete u; 
			} else { 
				
				if (v->onLeft()) { 
				parent->left = u; 
				} else { 
				parent->right = u; 
				} 
				delete v; 
				u->parent = parent; 
				if (uvBlack) { 
				 
				fixDoubleBlack(u); 
				} else { 
			
				u->color = BLACK; 
				} 
			} 
			return; 
			} 
		
			swapValues(u, v); 
			deleteNode(u); 
		} 
		
		void fixDoubleBlack(node *x) { 
			if (x == root)  
			return; 
		
			node *sibling = x->sibling(), *parent = x->parent; 
			if (sibling == NULL) { 
			 
			fixDoubleBlack(parent); 
			} else { 
			if (sibling->color == RED) { 
				 
				parent->color = RED; 
				sibling->color = BLACK; 
				if (sibling->onLeft()) { 
				 
				rightrotate(parent); 
				} else { 
				
				leftrotate(parent); 
				} 
				fixDoubleBlack(x); 
			} else { 
					 
					if (sibling->hasRedChild()) { 
					
					if (sibling->left != NULL && sibling->left->color == RED) { 
						if (sibling->onLeft()) { 
						 
						sibling->left->color = sibling->color; 
						sibling->color = parent->color; 
						rightrotate(parent); 
						} else { 
						 
						sibling->left->color = parent->color; 
						rightrotate(sibling); 
						leftrotate(parent); 
						} 
					} else { 
						if (sibling->onLeft()) { 
						
						sibling->right->color = parent->color; 
						leftrotate(sibling); 
						rightrotate(parent); 
						} else { 
						sibling->right->color = sibling->color; 
						sibling->color = parent->color; 
						leftrotate(parent); 
						} 
					} 
					parent->color = BLACK; 
					} else { 
				
					sibling->color = RED; 
					if (parent->color == BLACK) 
						fixDoubleBlack(parent); 
					else
						parent->color = BLACK; 
					} 
				} 
			} 
	} 

	
	public:
		rbtree(){
			root=NULL;
		}
		
		node *search(int key){
			node *z=root;
			node *p=NULL;
			while(z){
				p=z;
				if(key<z->key) z=z->left;
				else if (key>z->key) z=z->right;
				else return z;
			}
			//node not found, return last accessed node
			return p;
		}
		
		void insert(int key){
			node *newNode=new node(key);
			if(root==NULL){
				root=newNode;
				root->color=BLACK;
			}
			else{
				node *n=search(key); //either n is the correct leaf or key already present
				if(n->key==key) return;
				else{
					newNode->parent=n;
					if(key<n->key) n->left=newNode;
					else n->right=newNode;
				}
				fixRedRed(newNode); 
			}		
		}
		void Delete(int key){
			if(!root) return;
			node *v=search(key);
			if(v->key!=key) return;
			deleteNode(v);
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
	/*
	16
	i 7
	i 3
	i 18
	i 10
	i 22
	i 8
	i 11
	i 26
	i 2
	i 6
	i 13
	d 18
	d 11
	d 3
	d 10
	d 22
	*/
	rbtree T;
    int x,NQ;
    char op;
    cin>>NQ;
    while(NQ--){
        cin>>op>>x;
        if(op=='i') T.insert(x);
        else if (op=='d') T.Delete(x);
    }
    T.traversals();  
	return 0;
}
