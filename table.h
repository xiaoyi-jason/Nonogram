# pragma once
# include <bits/stdc++.h>
using namespace std;

enum state {undef, fill, empty};

class Table{
    int _size;
    int _completed;
    state **_arr;
    int* _column_completed;
    int* _row_completed;
    vector<int>* _column_info;
    vector<int>* _row_info;
    list<vector<state>>* _possible_columns;
    list<vector<state>>* _possible_rows;
    list<vector<state>> FindAlternatives(vector<int> info, int length);
    void FindColumnAlternatives(int n);
    void FindRowAlternatives(int n);
    void Initialize();
    void Fillin(list<vector<state>>* possibles, state* solution, int n);
    void FillinColumn(int n);
    void FillinRow(int n);
    void UpdateColumn(int n);
    void UpdateRow(int n);
public:
    Table(int size, vector<int>* column_info, vector<int>* row_info);
    void printAnswer();
    void solve();
};