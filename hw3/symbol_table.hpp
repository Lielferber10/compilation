#ifndef SYMTABLE_h
#define SYMTABLE_h
#include <vector>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <memory>
#include "Node.hpp"

using namespace std;

class Entry
{
    public:
    int offset;
    string id;
    Types ret_type;
    bool is_func;
    vector<Types> func_types;

    Entry(int off, string name, Types type)
    {
        offset = off;
        id = name;
        ret_type = type;
        is_func = false;
    };

    Entry(int off, string name, Types type, bool func, vector<Types> types)
    {
        offset = off;
        id = std::move(name);
        ret_type = type;
        is_func = func;
        func_types = std::move(types);
    };
};

class Table
{
    public:
    vector<Entry> table;
    int offset;

    Table(int offset) : offset(offset){};
};

class Symbol_Table
{
    public:
    vector<Table *> stack;
    vector<int> offset_stack;

    Symbol_Table();
    Entry *find_entry(string name);
    Entry *find_entry_in_last_table(string name);
    void insert_var(Entry entry);
    void open_table();
    void close_table();
    Table *top();
    void insert_node(Node *arg);

    void print();
};

string type_to_string(Types type);
vector<string> type_to_string_vec(vector<Types> &vec);
string typeListToString(const std::vector<string> &argTypes);
#endif /* SYMTABLE_h */
