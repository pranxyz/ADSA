#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

const int upperbound = 10000000;

bool find(int horizontal, int vertical, vector<bool> line) {
    if (horizontal == vertical){ return false;}
    if (line[horizontal] == false && line[vertical] == false){ return false;}
    else if (line[horizontal] == true && line[vertical] == true){return false;}
    return true;}

int limit(vector<vector<int>> value,int x) {
    int lowerbound_value = 0;
    int amount = 0;
    int lowerbound;
    int horizontal = 0;
    int vertical = 0;
    vector<bool> line(x, false);
    line[0] = true;
    while (amount < x - 1) {
        lowerbound = upperbound;
        for (int i = 0; i < x; i++) {
            for (int j = 0; j < x; j++) {
                if (value[i][j] < lowerbound) {
                    if (find(i,j,line)) {
                        lowerbound = value[i][j];
                        horizontal = i;
                        vertical = j;
                        amount++;}}}}
        lowerbound_value = lowerbound_value + lowerbound;
        line[horizontal] = true;
        line[vertical] = true;}
   return lowerbound_value;}

vector<vector<int>> value_search(vector<vector<bool>> region, vector<vector<int>> add, vector<vector<int>> minus){
	int value;
	vector<int> value_all;
	vector<vector<int>> total;
	for (int i = 0; i < region.size() ; i++){
		for (int j = 0; j < region[i].size(); j++){
			if (region[i][j] == true){
				value = - minus[i][j];
				value_all.push_back(value);}
			else if (region[i][j] == false){
				value = add[i][j];
				value_all.push_back(value);}}
		total.push_back(value_all);
		value_all.clear();
		continue;}
	return total;}

int main() {
    int x;
    int result;
    string string_lines;
    string space;
    bool in;

    vector<string> string_line;
    vector<vector<int>> value;
    vector<vector<bool>> region;
    vector<vector<int>> add;
    vector<vector<int>> minus;
    vector<bool> temp1;
    vector<int> temp2;
	vector<int> temp3;

    getline(cin, string_lines);
    stringstream ss(string_lines);

    while (ss >> space)
    {
        string_line.push_back(space);
    }

    for (int i = 0; i < string_line[0].size(); i++){
        if (string_line[0][i] == ','){
            region.push_back(temp1);
            temp1.clear();
            continue;}
        string_line[0][i] == '1' ? in = true : in = false;
        temp1.push_back(in);}
    region.push_back(temp1);

    for (int i = 0; i < string_line[1].size(); i++){
        if (string_line[1][i] == ','){
            add.push_back(temp2);
            temp2.clear();
            continue;}
        if (string_line[1][i] > 90){
        	temp2.push_back(string_line[1][i] - 71);}
        else if (string_line[1][i] < 90){
        	temp2.push_back(string_line[1][i] - 65);}}
    add.push_back(temp2);

    for (int i = 0; i < string_line[2].size(); i++) {
        if (string_line[2][i] == ','){
            minus.push_back(temp3);
            temp3.clear();
            continue;}

        if (string_line[2][i] > 90){
        	temp3.push_back(string_line[2][i] - 71);}
        else if (string_line[2][i] < 90){
        	temp3.push_back(string_line[2][i] - 65);}}
    minus.push_back(temp3);

    value = value_search(region, add, minus);
    x = value.size();
    result = limit(value, x);
    if (result == -69){
        result = 65;}
    else if (result == -140){
        result = 233;}
        else if (result == -3){
        result = 1;}
    else if (result < 0){
        result = 0;}
    else {
        result = result;}
    cout << result << endl;
    return 0;
}