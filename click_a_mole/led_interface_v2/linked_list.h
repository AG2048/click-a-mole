#ifndef LINKED_LIST_H
#define LINKED_LIST_H

struct AnimationObject;

class AnimationList {

private:
    struct Node {
        AnimationObject* data;
        Node* next;

        Node(AnimationObject* d) {
            data = d;
            next = nullptr;
        }
    };

    Node* head;
    Node* tail;
    int count;

public:
    AnimationList();
    ~AnimationList();

    void push_back(AnimationObject* value);
    bool erase(int index);
    int size();
    void clear();
    AnimationObject* get(int index);
    AnimationObject*& getRef(int index); 

};


#endif
