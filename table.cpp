# include <bits/stdc++.h>
# include "table.h"
using namespace std;

Table::Table(int size, vector<int>* column_info, vector<int>* row_info): 
        _size(size), _column_info(column_info), _row_info(row_info), _completed(0)
{
    for (int i = 0; i < _size; i++){
        int sum1 = 0, sum2 = 0;
        for (auto elem: column_info[i])
            sum1 += elem;
        sum1 += column_info[i].size();
        for (auto elem: row_info[i])
            sum2 += elem;
        sum2 += row_info[i].size();
        if (sum1 - 1 > _size || sum2 - 1 > _size){
            cout << "This problem is self-contradictory!" << endl;
            exit(1);
        }
    }
    _arr = new state*[size];
    for (int i = 0; i < size; i++)
        _arr[i] = new state[size];
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            _arr[i][j] = undef;
    _possible_columns = new list<vector<state>>[_size];
    _possible_rows = new list<vector<state>>[_size];
    _row_completed = new int[_size];
    _column_completed = new int[_size];
    for (int i = 0; i < _size; i++)
        _row_completed[i] = _column_completed[i] = 0;
}

list<vector<state>> Table::FindAlternatives(vector<int> info, int length){
    int infolen = info.size();
    int infosum = 0;
    for (int i = 0; i < infolen; i++)
        infosum += info[i];

    if (info.empty()){
        vector<state> states;
        list<vector<state>> possibles;
        for (int i = 0; i < length; i++)
            states.push_back(empty);
        possibles.push_back(states);
        return possibles;
    }

    int gap = 0;
    list<vector<state>> possibles;
    if (infolen == 1)
        gap = 1;
    for (int i = 0; i <= length - infolen - infosum + 1; i++){
        vector<state> header;
        list<vector<state>> tails;
        for (int j = 0; j < i; j++)
            header.push_back(empty);
        for (int j = 0; j < info[0]; j++)
            header.push_back(state::fill);
        for (int j = 0; j < 1 - gap; j++)
            header.push_back(empty);
        if (gap){
            vector<state> temp;
            for (int j = 0; j < length - header.size(); j++)
                temp.push_back(empty);
            tails.push_back(temp);
        }
        else{
            vector<int> new_info;
            for (auto iter = info.begin() + 1; iter != info.end(); iter ++)
                new_info.push_back(*iter);
            tails = FindAlternatives(new_info, length - header.size());
        }
        for (auto tail_elems: tails){
            vector<state> full;
            for (auto head_elem: header)
                full.push_back(head_elem);
            for (auto tail_elem: tail_elems)
                full.push_back(tail_elem);
            possibles.push_back(full);
        }
    }
    return possibles;
        
}

void Table::FindColumnAlternatives(int n){
    _possible_columns[n] = FindAlternatives(_column_info[n], _size);
}

void Table::FindRowAlternatives(int n){
    _possible_rows[n] = FindAlternatives(_row_info[n], _size);
}

void Table::Fillin(list<vector<state>>* possibles, state* solution, int n){
    auto iter = possibles[n].begin();
    int counter = 0;
    for (int i = 0; i < _size; i++)
        solution[i] = (*iter)[i];
    iter++;
    
    for (; iter != possibles[n].end(); iter++)
        for (int i = 0; i < _size; i++){
            if (solution[i] != (*iter)[i] && solution[i] != undef){
                solution[i] = undef;
                counter++;
                if (counter == _size)
                    return;
            }
        }
}

void Table::FillinColumn(int n){
    state* solution = new state[_size];
    Fillin(_possible_columns, solution, n);
    for (int i = 0; i < _size; i++){
        if (_arr[i][n] != undef && solution[i] != undef && solution[i] != _arr[i][n]){
            cout << "This problem is self-contradictory!" << endl;
            exit(1);
        }
        if (_arr[i][n] == undef && solution[i] != undef){
            _arr[i][n] = solution[i];
            _completed++;
            _row_completed[i]++;
            _column_completed[n]++;            
        }
    }
}

void Table::FillinRow(int n){
    state* solution = new state[_size];
    Fillin(_possible_rows, solution, n);
    for (int i = 0; i < _size; i++){
        if (_arr[n][i] != undef && solution[i] != undef && solution[i] != _arr[n][i]){
            cout << "This problem is self-contradictory!" << endl;
            exit(1);
        }
        if (_arr[n][i] == undef && solution[i] != undef){
            _arr[n][i] = solution[i];
            _completed++;
            _row_completed[n]++;
            _column_completed[i]++;
        }
    }
}

void Table::Initialize(){
    for (int i = 0; i < _size; i++){
        FindColumnAlternatives(i);
        FindRowAlternatives(i);
    }
}

void Table::UpdateColumn(int n){
    for (auto iter = _possible_columns[n].begin(); iter != _possible_columns[n].end();){
        int flag = 0;
        for (int i = 0; i < _size; i++){
            if ((_arr[i][n] != undef) && (*iter)[i] != _arr[i][n]){
                _possible_columns[n].erase(iter++);
                flag = 1;
                break;
            }
        }
        if (flag == 0)
            iter++;
    }
    if (_possible_columns[n].size() == 0){
        cout << "This problem is self-contradictory!" << endl;
        exit(1);
    }
}

void Table::UpdateRow(int n){
    for (auto iter = _possible_rows[n].begin(); iter != _possible_rows[n].end();){
        int flag = 0;
        for (int i = 0; i < _size; i++){
            if ((_arr[n][i] != undef) && (*iter)[i] != _arr[n][i]){
                _possible_rows[n].erase(iter++);
                flag = 1;
                break;
            }
        }
        if (flag == 0)
            iter++;
    }
    if (_possible_rows[n].size() == 0){
        cout << "This problem is self-contradictory!" << endl;
        exit(1);
    }
}

void Table::printAnswer(){
    for (int i = 0; i < _size; i++){
        for (int j = 0; j < _size; j++){
            if (_arr[i][j] == state::fill)
                cout << "# ";
            else if (_arr[i][j] == state::empty)
                cout << "0 ";
            else
                cout << "? ";
        }
        cout << endl;
    }
}

void Table::solve(){
    Initialize();
    int old_completed = 0;
    while(old_completed < _size * _size){
        for (int i = 0; i < _size; i++){
            if (_column_completed[i] < _size)
                FillinColumn(i);
            if (_row_completed[i] < _size)
                FillinRow(i);
        }  
        for (int i = 0; i < _size; i++){
            if (_column_completed[i] < _size)
                UpdateColumn(i);
            if (_row_completed[i] < _size)
                UpdateRow(i);
        }
        if (_completed == old_completed)
            break;
        old_completed = _completed;   
    }
    if (_completed == _size * _size)
        printAnswer();
    else
        cout << "Sorry, the program cannot solve the problem!" << endl;
}