#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <sstream>
using namespace std;

class hash_node{
  public:
    string node[26];
    hash_node(){
      int x = 0;
      while(x<26){
        node[x] = "never used";
        x++;}}
        int idx(char letter){
          int idx_temp = (int)letter-97;
        return idx_temp;}
        char key(string str){
        return str.back();}
        string key_loc(string k){
          int idx_i = idx(key(k));
          string not_used = "";
            if(node[idx_i] == k){
              return node[idx_i];}
            else{
            int x = idx_i+1;
            while(x != idx_i){
              if(x == 26){
                x = 0;}
                if(node[x] == k){
                  return node[x];}
          else if(node[x] == "never used"){
            return not_used;}
          x++;}
        return not_used;}}

    void insertion(string k){
      if(key_loc(k) != ""){
        return;}
      int idx_i = idx(key(k));
      if(node[idx_i] == "never used" || node[idx_i] == "tombstone"){
        node[idx_i] = k;}
      else{
        int x = idx_i+1;
        while(x != idx_i){
          if(x == 26){
            x = 0;}
          if(node[x] == "never used" || node[x] == "tombstone"){
            node[x] = k;
            return;}
          x++;}}}

    void deletion(string k){
      int idx_i = idx(key(k));
      if(node[idx_i] == k){
        node[idx_i] = "tombstone";
		    return;}
      else{
        int x = idx_i+1;
        while(x != idx_i){
          if(x == 26){
            x = 0;}
          if(node[x] == k){
            node[x] = "tombstone";
            return;}
          else if(node[x] == "never used"){
            return;}
            x++;}
          return;}}

    void display(){
      int x = 0;
	  while(x<26){
		if(node[x] != "never used" && node[x] != "tombstone"){
		  string temp = node[x];
          cout<<temp<<" ";}
          x++;}
      cout<<endl;}};

int main(void) {
    hash_node node;
    string entered;
    getline( cin, entered );
    istringstream is( entered );
    vector<string> input((istream_iterator<string>(is)),
    istream_iterator<string>());
    int x = 0;
    while(x < input.size()){
	  (input[x].front() == 'A')
	  ? node.insertion(input[x].substr(1))
	  : node.deletion(input[x].substr(1));
	  x++;}
    node.display();
    return 0;
}