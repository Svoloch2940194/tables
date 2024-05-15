#pragma once

template<class Key, class Value>
class AVL_tree
{
    struct node
    {
        pair<Key,Value> data;
        int h;
        node* left, * right; 
    };

    node* root;

    node* insert(pair<Key,Value> x, node* head)
    {
        if (head == nullptr)
        {
            head = new node;
            head->data = x;
            head->h = 0;
            head->left = head->right = nullptr;
        }
        else
        {
            if (x.first < head->data.first)
            {
                head->left = insert(x, head->left);
                if (height(head->left) - height(head->right) == 2)
                {
                    if (x.first < head->left->data.first) head = single_right_rotate(head);
                    else head = double_right_rotate(head);
                }
            }
            else
            {
                if (x.first > head->data.first)
                {
                    head->right = insert(x, head->right);
                    if (height(head->right) - height(head->left) == 2)
                    {
                        if (x.first > head->right->data.first) head = single_left_rotate(head);
                        else head = double_left_rotate(head);
                    }
                }
            }
            head->h = max(height(head->left), height(head->right)) + 1;
        }
        return head;
    }

    node* single_right_rotate(node*& x)
    {
        if (x == nullptr || x->left == nullptr) return x;

        node* y = x->left;
        x->left = y->right;
        y->right = x;
        x->h = max(height(x->left), height(x->right)) + 1;
        y->h = max(height(y->left), x->h) + 1;
        return y;
    }

    node* single_left_rotate(node*& x)
    {
        if (x == nullptr || x->right == nullptr) return x;

        node* y = x->right;
        x->right = y->left;
        y->left = x;
        x->h = max(height(x->left), height(x->right)) + 1;
        y->h
            = max(height(x->right), x->h) + 1;
        return y;
    }

    node* double_left_rotate(node*& x)
    {
        x->right = single_right_rotate(x->right);
        return single_left_rotate(x);
    }

    node* double_right_rotate(node*& x)
    {
        x->left = single_left_rotate(x->left);
        return single_right_rotate(x);
    }

    int height(node* x) {return (x == nullptr) ? -1 : x->h; }

    node* find_min(node* x)
    {
        if (x == nullptr) return nullptr;
        else
        {
            if (x->left == nullptr) return x;
            else return find_min(x->left);
        }
    }

    node* find_max(node* t)
    {
        if (t == nullptr) return nullptr;
        else
        {
            if (t->right == nullptr)  return t;
            else return find_max(t->right);
        }
    }

    node* erase(pair<Key,Value> x, node* head)
    {
        node* temp;

        if (head == nullptr) return nullptr;
        else
        {
            if (x.first < head->data.first) head->left = erase(x, head->left);
            else
            {
                if (x.first > head->data.first) head->right = erase(x, head->right);
                else
                {
                    if (head->left && head->right)
                    {
                        temp = find_min(head->right);
                        head->data = temp->data;
                        head->right = erase(head->data, head->right);
                    }
                    else
                    {
                        temp = head;
                        if (head->left == nullptr) head = head->right;
                        else if (head->right == nullptr)  head = head->left;
                        delete temp;
                    }
                }
            }
        }

        if (head == nullptr) return head;

        head->h = max(height(head->left), height(head->right)) + 1;

        if (height(head->left) - height(head->right) == 2)
        {
            if (height(head->left->left) - height(head->left->right) == 1) return single_left_rotate(head);
            else return double_left_rotate(head);
        }
        else if (height(head->right) - height(head->left) == 2)
        {
            if (height(head->right->right) - height(head->right->left) == 1) return single_right_rotate(head);
            else return double_right_rotate(head);
        }
        return head;
    }

    void inorder(node* t)
    {
        if (t == nullptr) return;
        inorder(t->left);
        std::cout << t->data.first<< " ";
        inorder(t->right);
    }

public:

    AVL_tree() { root = nullptr; }

    void insert(pair<Key,Value> x) { root=insert(x,root); }
    void erase(pair<Key,Value> x) { root=erase(x, root); }
    void display(){ inorder(root); std::cout << std::endl; }
};