#include <iostream>
#include <cctype>
#include <regex>
#include<map>
#include <stack>
#include<string.h>
#include <ctype.h>
using namespace std;
string postfix(string pp){
    map<char,int> preced;
    preced['*']=2;
    preced['/']=2;
    preced['-']=1;
    preced['+']=1;
    stack<char> st;
    string fin;
    //cout<<pp<<endl;
    reverse(pp.begin(), pp.end()); 
    for(auto x:pp){
        if(x=='*'||x=='/'||x=='+'||x=='-'){
            if(st.empty()==true){
                st.push(x);
            }
            else{
                int a = preced[st.top()];
                int b = preced[x];
                if(a>b){
                    fin=fin+st.top();
                    st.pop();
                    st.push(x);
                }
                else if(a<=b){
                    st.push(x);
                }
            }

        }
        else{
        fin=fin+x;
        }
    }
    while(st.empty()==false){
    fin=fin+st.top();
    st.pop();
    }
    //cout<<fin<<endl;
    return fin;
}
int eval(string s,map<string,int> finall){
    stack<float> st;
    for(auto x:s){
         if(x=='*'){
             float a = st.top();
             st.pop();
             float b = st.top();
             st.pop();
             st.push(a*b);
         }
        else if(x=='/'){
             float a = st.top();
             st.pop();
             float b = st.top();
             st.pop();
             st.push(a/b);
         }
        else if(x=='-'){
             float a = st.top();
             st.pop();
             float b = st.top();
             st.pop();
             st.push(a-b);
         }
        else if(x=='+'){
             float a = st.top();
             st.pop();
             float b = st.top();
             st.pop();
             st.push(a+b);
         }
        else{
        string p;
        p.push_back(x);
        if(isdigit(x)){
            st.push(stoi(p));
            continue;
        }
        //cout<<finall[p]<<endl;
        st.push(finall[p]);
        }
    }
    //cout<<"value"<<"-->"<<st.top()<<endl;
    return st.top();

}
void parser(map<pair<int,string>,string> expr,int n,vector<int> check,map<string,int> &finall){   
stack<string> ss;
int iter = 1;
auto vt = expr.begin();
string pp; 
for(;vt!=expr.end();vt++){
//first
if((vt->first).second=="let"&&check[iter]==4){
for(int z=1;z<=4;z++){
if((vt->second)=="keyword"){
    vt++;
}
else if(vt->second=="identifier"){
    auto kk = (vt->first).second;
    ss.push(kk);
    vt++;
}
else if(vt->second=="equalsign"){
    vt++;
}
else if(vt->second=="value"){
    auto l = (vt->first).second;
    int pp=stoi(l);
    auto top = ss.top();
    ss.pop();
    finall[top]=pp;
}
}
}
//second
else if((vt->first).second=="print"){
    for(int z=1;z<=2;z++){
    if((vt->first).second=="print"){
    vt++; 
    }
    else {
        if((vt->second)=="direct"){
            cout<<(vt->first).second<<endl;
            continue;
        }
        if((vt->second)=="directto"){
            auto z = (vt->first).second;
            string mm;
            string a;
            string b;
            int flag=0;
            for(auto ll:z){
                if(ll=='*'){
                    a=mm;
                    if(finall.find(mm) != finall.end()){
                    a=to_string(finall[mm]);
                    }
                    mm="";
                    flag=1;
                    continue;
                }
                else if(ll=='/'){
                    a=mm;
                    if(finall.find(mm) != finall.end()){
                    a=to_string(finall[mm]);
                    }                    
                    mm="";
                    flag=2;
                    continue;
                }
                else if(ll=='+'){
                    a=mm;
                    if(finall.find(mm) != finall.end()){
                    a=to_string(finall[mm]);
                    }                   
                    mm="";
                    flag=3;
                    continue;
                }
                else if(ll=='-'){
                    a=mm;
                    if(finall.find(mm) != finall.end()){
                    a=to_string(finall[mm]);
                    }
                    mm="";
                    flag=4;
                    continue;
                }
               mm=mm+ll;
            }
            b=mm;
            if(flag==1){
                int xx=stoi(a);
                int yy=stoi(b);
                cout<<(xx*yy)<<endl;
            }
            if(flag==2){
                int xx=stoi(a);
                int yy=stoi(b);
                cout<<(xx/yy)<<endl;
            }
            if(flag==3){
                int xx=stoi(a);
                int yy=stoi(b);
                cout<<(xx+yy)<<endl;
            }
            if(flag==3){
                int xx=stoi(a);
                int yy=stoi(b);
                cout<<(xx-yy)<<endl;
            }
            continue;
        }
        else{
        cout<<finall[(vt->first).second]<<endl;
        }
    }
    }
}
//third
else if((vt->first).second=="let"&&check[iter]>4){
for(int z=1;z<=check[iter];z++){
if((vt->second)=="keyword"){
    vt++;
}
else if(vt->second=="identifier"&&z<=2){
    auto kk = (vt->first).second;
    ss.push(kk);
    vt++;
}
else if(vt->second=="equalsign"){
    vt++;
}
else{
  pp=pp+(vt->first).second;
  if(z==check[iter]){
      pp=postfix(pp);
      int kl = eval(pp,finall);
      auto top = ss.top();
      ss.pop();
      finall[top]=kl;
      continue;
  }
  vt++;
}
}
}
//fourth
iter++;
}

}
int main() {
    map<pair<int,string>,string> expr;
    int ll;
    string s;
    string para;
    vector<int> check;
    map<string,int> finall;
    while(getline(cin,s)){
        para=para+s+" ";
    }
    string word;
    int i=0;
    int z=0;
    string zzz;
    //basically here i am tokenizing for difffernt tokenz
    for(auto x:para){
        if(x==' '){
                i++;
                if((word.find('0') != string::npos || word.find('1') != string::npos ||word.find('2') != string::npos ||word.find('3') != string::npos ||word.find('4') != string::npos ||word.find('5') != string::npos ||word.find('6') != string::npos ||word.find('7') != string::npos ||word.find('8') != string::npos ||word.find('9') != std::string::npos)){
                if(zzz=="print"){
                expr[(make_pair(i,word))]="directto";
                }
                }
                if(word.find_first_not_of("0123456789") == string::npos){
                expr[(make_pair(i,word))]="value";
                zzz="value";
                }
                else if(word.find("\"")!=string::npos){
                expr[(make_pair(i,word))]="direct";
                zzz="direct";
                }
                else if(word=="LET"||word=="let"||word=="print"||word=="println"||word=="PRINT"||word=="PRINTLN"||word=="print"){
                expr[(make_pair(i,word))]="keyword";
                check.push_back((i-z));
                z=i;
                ll=z;
                if(word=="print"){
                zzz="print";
                }
                else{
                    zzz="random";
                }
                 }
                else if(regex_match(word,regex("^[A-Za-z]+$"))&&word.length()==1){
                expr[(make_pair(i,word))]="identifier";
                zzz="identifier;";
                 }
                else if(word=="/"||word=="*"||word=="+"||word=="-"){
                expr[(make_pair(i,word))]="operator";
                zzz="operator";
                }
                else if(word=="="){
                expr[(make_pair(i,word))]="equalsign";
                zzz="equalsign";
                }
                word="";
            continue;
        }
        word=word+x;
    }
    check[0]=0;
    check.push_back((i-ll+1));
    i=i+1;
    expr[(make_pair(i,"END"))]="END";

    //basically sending to parser which will take care of everything
    parser(expr,i,check,finall);

    return 0;
}


