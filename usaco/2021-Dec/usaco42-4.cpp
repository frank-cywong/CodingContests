#include <iostream>

using namespace std;

struct treenode {
	// bool prevhilo = false; // false = lo, true = hi
	bool curhilo = false; // false = lo, true = hi
	bool haschild = false; // has children nodes?
	treenode * l = nullptr;
	treenode * r = nullptr;
	treenode* parent = nullptr;
	int hilocount = 0;
	int switchnumber = 0; // if x < this, l; otherwise, r
	int childcount = 0;
};

int N;

treenode root = *new treenode();

void updatetree(int x) {
	treenode * curnode = &root;
	while ((*curnode).haschild) {
		if (x < (*curnode).switchnumber) {
			curnode = ((*curnode).l);
		}
		else {
			curnode = ((*curnode).r);
		}
	}
	bool hilo = (*curnode).curhilo;
	(*curnode).haschild = true;
	treenode * newl = new treenode();
	treenode * newr = new treenode();
	newl->curhilo = true;
	newr->curhilo = false;
	newl->parent = curnode;
	newr->parent = curnode;
	newl->hilocount = (*curnode).hilocount;
	newr->hilocount = (hilo ? (*curnode).hilocount + 1 : (*curnode).hilocount);
	(*curnode).switchnumber = x;
	curnode -> l = newl;
	curnode -> r = newr;
	curnode->childcount+=2;
	childbalance(curnode);
}

void childbalance(treenode* curnode) {
	while (curnode->parent != nullptr) {
		curnode = curnode->parent;
		curnode->childcount = (curnode->l->childcount + curnode->r->childcount + 2);
	}
	curnode->childcount = (curnode->l->childcount + curnode->r->childcount + 2);
	checkselfbalancing();
}

void checkselfbalancing() {
	int childcountl = root.l->childcount;
	int childcountr = root.r->childcount;
	if (childcountl > (childcountr * 2)) {

	}
	if (childcountr > (childcountl * 2)) {

	}
}

void traversetree(treenode * curnode) {
	if (!(*curnode).haschild) {
		cout << (*curnode).hilocount << endl;
		return;
	}
	traversetree((*curnode).l);
	traversetree((*curnode).r);
}

int main() {
	cin >> N;
	int temp;
	for (int i = 0; i < N; i++) {
		cin >> temp;
		updatetree(temp);
	}
	traversetree(&root);
	return 0;
}