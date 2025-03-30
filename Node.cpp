#include "Node.h"

Node::Node(char c, int f, Node *l, Node *r) : ch(c), freq(f), left(l), right(r) {}

Node::~Node() {
    delete left;
    delete right;
}

bool Compare::operator()(Node *l, Node *r) {
    return l->freq > r->freq;
}