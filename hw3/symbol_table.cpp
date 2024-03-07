#include "symbol_table.hpp"
#include "hw3_output.hpp"
#include "Node.hpp"
#include <vector>
#include <string>
#include <iostream>
#include <sstream>

using namespace std;
using namespace output;

Symbol_Table::Symbol_Table()
{

    stack.push_back(new Table(0));
    vector<Types> vec;
    vec.push_back(STRING);
    Entry print(0, "print", VOID, true, vec);
    stack.back()->table.push_back(print);
    vec.clear();
    vec.push_back(INT);
    Entry printi(0, "printi", VOID, true, vec);
    stack.back()->table.push_back(printi);
    Entry readi(0, "readi", INT, true, vec);
    stack.back()->table.push_back(readi);
}

Entry *Symbol_Table::find_entry(string name)
{
    for (int table_num = stack.size() - 1; table_num >= 0; --table_num)
    {
        Table &table = *stack[table_num];
        for (int entry_num = table.table.size() - 1; entry_num >= 0; --entry_num)
        {
            Entry &entry = table.table[entry_num];
            if (entry.id == name)
                return &entry;
        }
    }
    return nullptr;
}

Entry *Symbol_Table::find_entry_in_last_table(string name)
{
    unsigned long table_num = stack.size() - 1;
    Table &table = *stack[table_num];
    for (int entry_num = table.table.size() - 1; entry_num >= 0; --entry_num)
    {
        Entry &entry = table.table[entry_num];
        if (entry.id == name)
            return &entry;
    }
    return nullptr;
}

void Symbol_Table::insert_var(Entry entry)
{
    if (find_entry(entry.id) != nullptr)
    {
        cout << "already exists" << endl; // need to replace that
        exit(0);
    }

    stack.back()->table.push_back(entry);
}

void Symbol_Table::open_table()
{
    Table &table = *stack.back();
    offset_stack.push_back(table.offset);
    stack.push_back(new Table(table.offset));
}

void Symbol_Table::close_table()
{
    endScope();

    Table &table = *stack.back();
    if (&table == nullptr)
        return;
    for (auto entry : table.table)
    {
        if (entry.is_func)
        {
            vector<string> arg_types = type_to_string_vec(entry.func_types);
            string type = type_to_string(entry.ret_type);
            string to_print = makeFunctionType(typeListToString(arg_types), type);
            printID(entry.id, entry.offset, to_print);
        }
        else
            printID(entry.id, entry.offset, type_to_string(entry.ret_type));
    }
    stack.pop_back();
    offset_stack.pop_back();
}

Table *Symbol_Table::top()
{
    return stack.back();
}

void Symbol_Table::insert_node(Node *arg)
{
    Table &table = *stack.back();
    Entry entry(table.offset, std::move(arg->text), arg->type);
    insert_var(entry);
    table.offset++;
}

void Symbol_Table::print()
{
    for (int table_num = stack.size() - 1; table_num >= 0; --table_num)
    {
        Table &table = *stack[table_num];
        cout << "table num " << table_num << endl;
        for (int entry_num = table.table.size() - 1; entry_num >= 0; --entry_num)
        {
            Entry &entry = table.table[entry_num];
            cout << "entry num " << entry_num << " id " << entry.id << endl;
        }
    }
}

string type_to_string(Types type)
{
    switch (type)
    {
    case BOOL:
        return "BOOL";
    case BYTE:
        return "BYTE";
    case INT:
        return "INT";
    case VOID:
        return "VOID";
    case STRING:
        return "STRING";
    default:
        return "error";
    };
}

vector<string> type_to_string_vec(vector<Types> &vec)
{
    vector<string> res;
    for (int i = 0; i < vec.size(); ++i)
    {
        res.push_back(type_to_string(vec[i]));
    }
    return res;
}

string typeListToString(const std::vector<string> &argTypes)
{
    stringstream res;
    // res << "(";
    for (int i = 0; i < argTypes.size(); ++i)
    {
        res << argTypes[i];
        if (i + 1 < argTypes.size())
            res << ",";
    }
    // res << ")";
    return res.str();
}
