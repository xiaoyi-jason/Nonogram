# include "table.h"
# include <bits/stdc++.h>
# include <unistd.h>
using namespace std;

void readInfo(vector<int>* x, int n){
    for (int i = 0; i < n; i++){
        string sentence;
        getline(cin, sentence);
        stringstream str;
        str << sentence;
        int temp;
        while(str >> temp){
            if (!temp)
                break;
            x[i].push_back(temp);
        }
    }
}

int readNumber(){
    string temp;
    getline(cin, temp);
    stringstream str;
    str << temp;
    int x;
    str >> x;
    return x;
}

void print_help_info(){
    cout << "This program is developed to solve simple \"nonograms\". " << endl;
    cout << "You should first input the size of the model you're going to solve, " << endl;
    cout << "then you should enter the row and column info of your model in sequence." << endl;
    sleep(5);
    cout << "For example, given the model below:" << endl;
    cout << "               2" << endl;
    cout << "       4 2 2 1 2" << endl;
    cout << "     2 * * * * *" << endl;
    cout << "   1 1 * * * * *" << endl;
    cout << "     1 * * * * *" << endl;
    cout << "   3 1 * * * * *" << endl;
    cout << "   3 1 * * * * *" << endl;
    sleep(5);
    cout << "Your input should be: " << endl;
    cout << "5" << endl;
    cout << "4" << endl;
    cout << "2" << endl;
    cout << "2" << endl;
    cout << "1" << endl;
    cout << "2 2" << endl;
    cout << "2" << endl;
    cout << "1 1" << endl;
    cout << "1" << endl;
    cout << "3 1" << endl;
    cout << "3 1" << endl;
    sleep(5);
    cout << "The output will be a solved model marked with \"#\" and \"0\": " << endl;
    cout << "0 0 0 # #" << endl;
    cout << "# 0 0 0 #" << endl;
    cout << "# 0 0 0 0" << endl;
    cout << "# # # 0 #" << endl;
    cout << "# # # 0 #" << endl;
    cout << "\"#\" stands for \"filled\", \"0\" stands for \"empty\"." << endl;
    sleep(5);
    cout << "If your input model is self-contradictory, the program will send out an error message." << endl;
    cout << "Since the program is only capable of solving models with single solutions, " << endl;
    cout << "If your input model has different feasible solutions or is too complicated, " << endl;
    cout << "then the program may fail to solve it and send out an error message." << endl;
    sleep(10);
    cout << endl;
    cout << "So, it's your turn!" << endl;
}

int main(int argc, char *argv[]){
    int o;
    const char *optstring = "h";

    while ((o = getopt(argc, argv, optstring)) != -1) {
        switch (o) {
            case 'h':
                print_help_info();
                break;
            case '?':
                printf("error optopt: %c\n", optopt);
                printf("error opterr: %d\n", opterr);
                break;
        }
    }

    int n;
    cout << "Please input the size of your matrix:" << endl;
    n = readNumber();
    vector<int>* column_info = new vector<int>[n];
    vector<int>* row_info = new vector<int>[n];
    cout << "Please input the column infomation of your matrix:" << endl;
    readInfo(column_info, n);
    cout << "Please input the row infomation of your matrix:" << endl;
    readInfo(row_info, n);

    Table myTable(n, column_info, row_info);
    myTable.solve();
    return 0;
}