#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <sstream>
#include <cstring>
using namespace std;

struct Node{
    int Value;
    Node* left;
    Node* right;
    int height;
};

int getHeight(Node* r){
    if(r!=NULL)
        return r->height;
    else
        return 0;
}

Node* getr(Node* node , int val){
    node = new Node();
    node->Value = val;
    node->left,node->right = NULL;
    node->height = 1;
    return node;
}

Node* max(Node* r){
    Node* var = r;
    while(var->right!=NULL)
        var = var->right;
    return var;
}

int getBalance(Node* r){
	if(r != NULL){
		if(r->left == NULL && r->right == NULL)
			return 0;
		else if(r->left == NULL && r->right !=NULL)
			return 0-getHeight(r->right);
		else if(r->left !=NULL && r->right == NULL)
			return getHeight(r->left)-0;
		else
			return (getHeight(r->left)- getHeight(r->right));
	}
	return 0;
}

Node* rotate_right(Node* r){
	Node* right_l = r->left;
	Node* left_r = right_l->right;

	right_l->right = r;
	r->left = left_r;

	if(r!=NULL || r->left!=NULL || r->right!=NULL)
		r->height = ((getHeight(r->left) > getHeight(r->right)) ? getHeight(r->left) : getHeight(r->right))+1;

	if(right_l!=NULL || right_l->left!=NULL || right_l->right!=NULL)
		right_l->height = ((getHeight(right_l->left) > getHeight(right_l->right)) ? getHeight(right_l->left) : getHeight(right_l->right))+1;

	return right_l;
}

Node* rotate_left(Node* r){
	Node* right_r = r->right;
	Node* right_left = right_r->left;

	right_r->left = r;
	r->right = right_left;

	if(r!=NULL || r->left!=NULL || r->right!=NULL)
		r->height = ((getHeight(r->left) > getHeight(r->right)) ? getHeight(r->left) : getHeight(r->right))+1;

	if(right_r!=NULL || right_r->left!=NULL || right_r->right!=NULL)
		right_r->height = ((getHeight(right_r->left) > getHeight(right_r->right)) ? getHeight(right_r->left) :  getHeight(right_r->right))+1;

	return right_r;
}

Node* rotate_final(Node* r, int balance_height, int key, char in_del){
	if(in_del == 'A'){
		if(balance_height >1 && key < r->left->Value){
			return rotate_right(r);
		}
		if(balance_height >1 && key > r->left->Value){
			r->left = rotate_left(r->left);
			return rotate_right(r);
		}
		if(balance_height < -1 && key > r->right->Value){
			return rotate_left(r);
		}
		if(balance_height < -1 && key < r->right->Value){
			r->right = rotate_right(r->right);
			return rotate_left(r);
		}

	}else if(in_del == 'D'){
		if(balance_height >1 && getBalance(r->left)>=0){
			return rotate_right(r);
		}
		if(balance_height >1 &&  getBalance(r->left)<0){
			r->left = rotate_left(r->left);
			return rotate_right(r);
		}
		if(balance_height < -1 && getBalance(r->right)<=0){
			return rotate_left(r);
		}
		if(balance_height < -1 && getBalance(r->right)>0){
			r->right = rotate_right(r->right);
			return rotate_left(r);
		}

	}
	return r;
}

Node* insertion(Node* r, int val){
    if(r==NULL){
        return (getr(r , val));
    }
    if(val<r->Value){
        r->left = insertion(r->left,val);
    }
    else if(val > r->Value){
        r->right = insertion(r->right , val);
    }
    else{
        return r;
    }

    if(r!=NULL){
        r->height = ((getHeight(r->left) > getHeight(r->right))? getHeight(r->left) : getHeight(r->right))+1;
    }

    int balanceHeight = getBalance(r);

    return rotate_final(r,balanceHeight,val,'A');

}

Node* deletion(Node* r , int val){

    if(r==NULL){
        return r;
    }

    if(val < r->Value)
        r->left = deletion(r->left , val);
    else if(val > r->Value)
        r->right = deletion(r->right , val);
    else if(val==r->Value){
        if(r->left ==NULL && r->right ==NULL)
            r = NULL;
        else if(r->left==NULL && r->right!=NULL)
            r = r->right;
        else if(r->left!=NULL && r->right==NULL)
            r = r->left;

        else{
            Node* var = max(r->left);
            r->Value = var->Value;
            r->left = deletion(r->left , var->Value);
        }
    }
    if(r!=NULL)
        r->height = ((getHeight(r->left) > getHeight(r->right))? getHeight(r->left) : getHeight(r->right))+1;

    int balanceHeight = getBalance(r);
    return rotate_final(r,balanceHeight, val,'D');

}

void in_order(Node *r) {
  if (r!=NULL){
    in_order(r->left);
    cout << r->Value << " ";
    in_order(r->right);
  }
}

void pre_order(Node *r){
  if (r!=NULL){
    cout << r->Value << " ";
    pre_order(r->left);
    pre_order(r->right);
  }
}

void post_order(Node *r){
  if (r!=NULL){
    post_order(r->left);
    post_order(r->right);
    cout << r->Value << " ";
  }
}


int main(){
    string final,traversal;
    int key;
    Node* r = NULL;
    char enter[1000];
    vector<char*> v;
    cin.getline(enter, 1000);
	char* enter_string = strtok(enter, " ");
    while(enter_string)
    {
        v.push_back(enter_string);
		enter_string = strtok(NULL, " ");
    }
	for(unsigned int i=0;i<v.size()-1;i++){
		final=v[i];
		key = stoi(final.substr(1, final.size()-1));
		if(final[0]== 'A'){
			r= insertion(r, key);
		}else{
			r = deletion(r, key);
		}
	}
	traversal = v[v.size()-1];
    if(r==NULL){
        cout<<"EMPTY";
    }
    else{
        if(traversal=="IN")
            in_order(r);
        else if(traversal == "PRE")
            pre_order(r);
        else if(traversal=="POST")
            post_order(r);
    }
}