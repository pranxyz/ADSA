#include <iostream>
#include <cmath>
#include <regex>
#include <cassert>
using namespace std;

string schoolSum(string x,string y,int b) {
    int num1 = x.size() ;
    int num2 = y.size() ;
    string ans;
    while(num2>num1) {
        x.insert(x.begin(),'0');
        num1++ ;
    }
    while(num1>num2) {
        y.insert(y.begin(),'0');
        num2++ ;
    }
    int i;
    int Nnum1, Nnum2, ansNnum;
    bool cary = 0;
    for(i = num1-1; i >= 0; i--) {
        Nnum1 = x[i]-'0';
        Nnum2 = y[i]-'0';
        ansNnum = cary + Nnum1 + Nnum2;
        if(ansNnum >= b) {
            cary = 1;
            ansNnum -= b;
        } else {
            cary = 0;
        }
        int p = ans.size() ;

        if(p==0) {
            ans.push_back(ansNnum+'0');
        } else {
            ans.insert(ans.begin(),ansNnum+'0');
        }
    }
    if(cary == 0)
    return (ans);
    ans.insert(ans.begin(),'1');
    return ans;
}
string schoolSub(string y, string x, int C) {
   if(x.size() > y.size())
   swap(x, y);

   int n = x.size();
   int difference = y.size() - x.size();
   string ans;
   int carry = 0;
   for(int i = n-1; i > -1; i--){
       int differenceDigit = (y[i + difference] - '0') - (x[i] - '0') - carry;
       carry = (differenceDigit < 0);
       differenceDigit += C * carry;
       ans.push_back(differenceDigit + '0');
   }
   for(int i = difference - 1; i > -1; i--){
       int differenceDigit = (y[i] - '0') - carry;
       carry = (differenceDigit < 0);
       differenceDigit += C * carry;
       ans.push_back(differenceDigit + '0');
   }
   assert(carry == 0);
   reverse(ans.begin(), ans.end());
   return ans;
}

string removeZeros(string x) {
   for(int i = 0; i < x.size(); i++){
       if(x[i] != '0')
           return x.substr(i, x.size() - i);
   }
   return "0";
}

string singleDigitMultiplication(string y, char x, int C) {
   string ans;
   int digit = x - '0', carry = 0;
   for(int i = y.size() - 1; i > -1; i--){
       int multiDigit = (y[i] - '0') * digit + carry;
       carry = multiDigit / C;
       ans.push_back(multiDigit % C + '0');
   }
   if(carry) ans.push_back(carry + '0');
   reverse(ans.begin(), ans.end());
   return ans;
}

string karatsubaMultiplication(string x, string y, int C) {

   if(x.size() > y.size())
   swap(x, y);

   int X = x.size(), Y = y.size();

   if(X == 1)
   return singleDigitMultiplication(y, x[0], C);

   string copy_X, copy_Y;
   if(Y&1){
       copy_Y.push_back('0');
       Y += 1;
   }
   for(int i = 0; i < Y - X; i++){
       copy_X.push_back('0');
   }
   copy_X = copy_X + x;
   copy_Y = copy_Y + y;

   string X_l, X_r, Y_l, Y_r;
   X_l = copy_X.substr(0, Y/2);
   X_r = copy_X.substr(Y/2, Y/2);
   Y_l = copy_Y.substr(0, Y/2);
   Y_r = copy_Y.substr(Y/2, Y/2);

   string A_1 = karatsubaMultiplication(X_l, Y_l, C);
   string A_2 = karatsubaMultiplication(X_r, Y_r, C);
   string A_3 = karatsubaMultiplication(schoolSum(X_l, X_r, C), schoolSum(Y_l, Y_r,C), C);
   string sum_A1_A2 = schoolSum(A_1, A_2,C);

   A_3 = schoolSub(A_3, sum_A1_A2, C);

   A_1 += string(Y, '0');
   A_3 += string(Y/2, '0');
   string A_4 = schoolSum(A_3, schoolSum(A_1, A_2, C),C);

   return removeZeros(A_4);
}

int main() {
    string x , y;
    int B;
    cin >> x >> y >> B;
    cout<<schoolSum(x,y,B)<< " " <<karatsubaMultiplication(x,y,B)<< " " << "0" <<endl;
    return 0;
}