#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class AcNode
{
public:
	char data;
	bool isEnding = false;
	vector<AcNode*> children;
	int length = -1;
	AcNode* fail = nullptr;

public:
	AcNode(char data) {
		this->data = data;
		children.resize(26);
	}
};

class Ac
{
public:
	void insert(string text) {
		AcNode* p = root;
		for (int i = 0; i < text.size(); ++i) {
			int index = text[i] - 'a';
			if (p->children[index] == nullptr) {
				p->children[index] = new AcNode(text[i]);
			}
			p = p->children[index];
		}
		p->isEnding = true;
		p->length = text.size();
	}
	
	void buildFail() {
		queue<AcNode*> q;
		q.push(root);
		while (!q.empty()) {
			AcNode* p = q.front();
			
			q.pop();
			for (int i = 0; i < 26; ++i) {
				AcNode* pc = p->children[i];

				if (pc == nullptr) {
					continue;
				}
				
				if (p == root) {
					pc->fail = root;
				}
				else {
					AcNode* pp = p->fail;
					while (pp != nullptr) {
						AcNode* ppc = pp->children[pc->data - 'a'];
						if (ppc != nullptr) {
							pc->fail = ppc;
							break;
						}
						pp = pp->fail;
					}
					if (pp == nullptr) {
						pc->fail = root;
					}
				}
				q.push(pc);
			}
		}
	}

	void match(string text) {
		int n = text.size();
		AcNode* p = root;
		for (int i = 0; i < n; ++i) {
			int index = text[i] - 'a';
			while (p->children[index] == nullptr && p != root) {
				p = p->fail;
			}
			p = p->children[index];
			if (p == nullptr) p = root;
			AcNode* tmp = p;
			while (tmp != root) {
				if (tmp->isEnding) {
					int pos = i - tmp->length + 1;
					cout << "start : " << pos << "; len : " << tmp->length << endl;
				}
				tmp = tmp->fail;
			}
		}
	}
	void print() {
		cout << root->data << endl;

	}
private:
	AcNode* root = new AcNode('1');
};

int main() {
	cout << "--------------start--------------" << endl;
	Ac ac;
	ac.insert("abc");
	ac.insert("as");
	ac.insert("afg");
	ac.insert("cd");
	ac.insert("ba");
	ac.insert("dfg");

	cout << "--------------------insert end ------------------" << endl;

	ac.buildFail();

	cout << "--------------------build end ------------------" << endl;

	ac.match("abcdfg");

	cout << "---------------end---------------" << endl;

	return 0;
}
