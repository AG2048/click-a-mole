#include "linked_list.h"

// complete
AnimationList::AnimationList()
{
    head = nullptr;
    tail = nullptr;
    count = 0;
}

// complete
AnimationList::~AnimationList()
{
    clear();
}

// complete
void AnimationList::push_back(AnimationObject *value)
{
    Node *n = new Node(value);

    if (tail != nullptr)
    {
        tail->next = n; // attach new node
    }

    tail = n; // update tail

    if (head == nullptr)
    {
        head = n; // first node added
    }

    count++;
}

// complete
bool AnimationList::erase(int index)
{

    if (index < 0 || index >= count)
    {
        return false;
    }

    Node *p = head;
    Node *prev = nullptr;

    for (int i = 0; i < index; i++)
    {
        prev = p;
        p = p->next;
    }

    if (prev == nullptr)
    {
        head = p->next;
    }
    else
    {
        prev->next = p->next;
    }

    // if deleting last element → update tail
    if (p->next == nullptr)
    {
        tail = prev;
    }

    delete p;
    count--;
    return true;
}

// complete
int AnimationList::size()
{
    return count;
}

// complete
// deletes nodes; doesn't delete the AnimationObject*
void AnimationList::clear()
{
    Node *p = head;

    while (p != nullptr)
    {
        Node *n = p->next;
        delete p;
        p = n;
    }

    head = nullptr;
    tail = nullptr;
    count = 0;
}

// complete, creates a copy of the AnimationObject pointer
AnimationObject *AnimationList::get(int index)
{
    Node *p = head;

    for (int i = 0; i < index; i++)
    {
        p = p->next;
    }

    return p->data;
}

// complete
// function exists in case
// we want to replace the data in a Node
// with a new dynamically allocated AnimationOobject
AnimationObject *&AnimationList::getRef(int index)
{
    Node *p = head;

    for (int i = 0; i < index; i++)
    {
        p = p->next;
    }

    return p->data;
}