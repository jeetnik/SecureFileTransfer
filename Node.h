#pragma once

struct Node {
    char ch;
    int freq;
    Node *left, *right;

    Node(char c, int f, Node *l = nullptr, Node *r = nullptr);
    ~Node();
};

struct Compare {
    bool operator()(Node *l, Node *r);
};