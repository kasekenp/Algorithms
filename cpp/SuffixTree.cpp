#include <bits/stdc++.h>
using namespace std;

struct End {
    int end;
    End(int x) : end(x) {}
};

class SuffixNode {
   private:
    static const int TOTAL = 256;

   public:
    int start, index;
    End* end;
    SuffixNode* suffixLink;
    SuffixNode* child[TOTAL];

    static SuffixNode* createNode(int start, End* end) {
        auto node = new SuffixNode();
        node->start = start;
        node->end = end;
        return node;
    }
};

struct Active {
    int edge, length;
    SuffixNode* node;

    Active(SuffixNode* node) : edge(-1), length(0), node(node) {}
};

class EndOfPathException : exception {};

class SuffixTree {
   private:
    static const char UNIQUE_CHAR = '$';
    string input;
    SuffixNode* root;
    Active* active;
    int remainingSuffixCount = 0;
    End* end;

    void build() {
        root = SuffixNode::createNode(1, new End(0));
        root->index = -1;
        active = new Active(root);
        this->end = new End(-1);
        for (int i = 0; i < (int)input.length(); i++) {
            startPhase(i);
        }
        assert(remainingSuffixCount == 0);
        setIndexUsingDfs(root, 0, input.size());
    }

    void startPhase(int i) {
        SuffixNode* lastCreatedInternalNode = NULL;
        end->end++;
        remainingSuffixCount++;
        while (remainingSuffixCount > 0) {
            if (active->length == 0) {
                if (selectNode(i) != NULL) {
                    active->edge = selectNode(i)->start;
                    active->length++;
                    break;
                }
                root->child[input.at(i)] = SuffixNode::createNode(i, end);
                remainingSuffixCount--;
                continue;
            }

            try {
                const auto ch = nextChar(i);
                if (ch == input.at(i)) {
                    if (lastCreatedInternalNode != NULL)
                        lastCreatedInternalNode->suffixLink = selectNode();
                    walkDown(i);
                    break;
                }
                const auto node = selectNode();
                const auto oldStart = node->start;
                node->start = node->start + active->length;
                const auto newInternalNode = SuffixNode::createNode(
                    oldStart, new End(oldStart + active->length - 1));
                const auto newLeafNode = SuffixNode::createNode(i, this->end);
                newInternalNode
                    ->child[input.at(newInternalNode->start + active->length)] =
                    node;
                newInternalNode->child[input.at(i)] = newLeafNode;
                newInternalNode->index = -1;
                active->node->child[input.at(newInternalNode->start)] =
                    newInternalNode;
                if (lastCreatedInternalNode != NULL) {
                    lastCreatedInternalNode->suffixLink = newInternalNode;
                }
                lastCreatedInternalNode = newInternalNode;
                newInternalNode->suffixLink = root;
                if (active->node != root) {
                    active->node = active->node->suffixLink;
                } else {
                    active->edge++;
                    active->length--;
                }
                remainingSuffixCount--;
            } catch (const EndOfPathException* e) {
                const auto node = selectNode();
                node->child[input.at(i)] = SuffixNode::createNode(i, end);
                if (lastCreatedInternalNode != NULL)
                    lastCreatedInternalNode->suffixLink = node;
                lastCreatedInternalNode = node;
                if (active->node != root) {
                    active->node = active->node->suffixLink;
                } else {
                    active->edge++;
                    active->length--;
                }
                remainingSuffixCount--;
            }
        }
    }

    void walkDown(int i) {
        const auto node = selectNode();
        if (diff(node) < active->length) {
            active->node = node;
            active->length = active->length - diff(node);
            active->edge = node->child[input.at(i)]->start;
        } else {
            active->length++;
        }
    }

    char nextChar(int i) {
        const auto node = selectNode();
        if (diff(node) >= active->length) {
            return input.at(active->node->child[input.at(active->edge)]->start +
                            active->length);
        }
        if (diff(node) + 1 == active->length) {
            if (node->child[input.at(i)] != NULL) return input.at(i);
        } else {
            active->node = node;
            active->length = active->length - diff(node) - 1;
            active->edge = active->edge + diff(node) + 1;
            return nextChar(i);
        }
        throw new EndOfPathException();
    }

    SuffixNode* selectNode() {
        return active->node->child[input.at(active->edge)];
    }

    SuffixNode* selectNode(int i) { return active->node->child[input.at(i)]; }

    int diff(SuffixNode* node) { return node->end->end - node->start; }

    void setIndexUsingDfs(SuffixNode* root, int val, int size) {
        if (root == NULL) return;
        val += root->end->end - root->start + 1;
        if (root->index != -1) {
            root->index = size - val;
            return;
        }
        for (const auto node : root->child) {
            setIndexUsingDfs(node, val, size);
        }
    }

    void dfs(SuffixNode* root) {
        if (root == NULL) return;
        cout << root->start << ' ' << root->end->end + 1 << endl;
        for (const auto node : root->child) {
            dfs(node);
        }
    }

   public:
    SuffixTree(string s) : input(s) { build(); }

    void dfs() {
        for (const auto node : root->child) {
            dfs(node);
        }
    }
};

int main() {
    string s;
    cin >> s;
    for (int i = 0; i < (int)(2 * s.size() - 1); i++) {
        int x;
        cin >> x;
    }
    auto st = new SuffixTree(s);
    cout << s << endl;
    st->dfs();
}
