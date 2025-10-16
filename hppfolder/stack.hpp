#pragma once
#include <iostream>
#include <vector>
#include <stdexcept>
#include <string>
using namespace std;
template <typename T>
class Stack {
private:
    vector<T> data;
public:
    Stack() = default;
    void push(const T& value) {
        data.push_back(value);
    }
    T pop() {
        if (isEmpty())
            throw runtime_error("Stack Underflow");
        T val = data.back();
        data.pop_back();
        return val;
    }
    T& top() {
        if (isEmpty())
            throw runtime_error("Stack is empty");
        return data.back();
    }
    bool isEmpty() const {
        return data.empty();
    }
    int size() const {
        return static_cast<int>(data.size());
    }
    void clear() {
        data.clear();
    }
};

struct LinkedList {
    vector<string> items;
    void insert(const string& item) {
        items.push_back(item);
    }
    void remove() {
        if (!items.empty()) items.pop_back();
    }
    void print() const {
        
        for (const auto& it : items) cout << it << " "<<endl;
        
    }
};

void Undo(Stack<string>& undoStack, Stack<string>& redoStack, LinkedList& list) {
    if (undoStack.isEmpty()) {
        cout << "Nothing to undo!" << endl;
        return;
    }
    string lastAction = undoStack.pop();
    redoStack.push(lastAction);
    if (lastAction.rfind("ADD:", 0) == 0) {
        list.remove();
        cout << "removed last added item." << endl;
    } else if (lastAction.rfind("DEL:", 0) == 0) {
        string restored = lastAction.substr(4);
        list.insert(restored);
        cout << "restored deleted item: " << restored << endl;
    }
}

void Redo(Stack<string>& redoStack, Stack<string>& undoStack, LinkedList& list) {
    if (redoStack.isEmpty()) {
        cout << "Nothing to redo!" << endl;
        return;
    }
    string lastAction = redoStack.pop();
    undoStack.push(lastAction);
    if (lastAction.rfind("ADD:", 0) == 0) {
        string val = lastAction.substr(4);
        list.insert(val);
        cout << "re-added item: " << val << endl;
    } else if (lastAction.rfind("DEL:", 0) == 0) {
        list.remove();
        cout << "re-deleted last item." << endl;
    }
}

