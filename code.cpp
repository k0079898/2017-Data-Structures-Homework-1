#include <iostream>
#include <string>
#include <algorithm>
#include <cstdlib>
#include "function.h"

using namespace std;

class Implement : public Parenthesis {
    private:
        bool valid;
        string stackArr;
        string expression;
        string prefix;
        long long eval;

        void expresionCheck(string s) {
            unsigned long long i;

            valid = true;
            stackArr.clear();
            expression.clear();
            for(i=0;i<s.length();i++) {
                if(s[i]=='(' || s[i]=='{' || s[i]=='[') {
                    stackArr.push_back(s[i]);
                    expression.push_back(s[i]);
                }else if(s[i]==')') {
                    if(stackArr.back()=='(') {
                        stackArr.erase(stackArr.end()-1);
                        expression.push_back(s[i]);
                    }else if(stackArr.back()=='{') {
                        valid = false;
                        stackArr.erase(stackArr.end()-1);
                        expression.push_back('}');
                    }else if(stackArr.back()=='[') {
                        valid = false;
                        stackArr.erase(stackArr.end()-1);
                        expression.push_back(']');
                    }
                }else if(s[i]=='}') {
                    if(stackArr.back()=='(') {
                        valid = false;
                        stackArr.erase(stackArr.end()-1);
                        expression.push_back(')');
                    }else if(stackArr.back()=='{') {
                        stackArr.erase(stackArr.end()-1);
                        expression.push_back(s[i]);
                    }else if(stackArr.back()=='[') {
                        valid = false;
                        stackArr.erase(stackArr.end()-1);
                        expression.push_back(']');
                    }
                }else if(s[i]==']') {
                    if(stackArr.back()=='(') {
                        valid = false;
                        stackArr.erase(stackArr.end()-1);
                        expression.push_back(')');
                    }else if(stackArr.back()=='{') {
                        valid = false;
                        stackArr.erase(stackArr.end()-1);
                        expression.push_back('}');
                    }else if(stackArr.back()=='[') {
                        stackArr.erase(stackArr.end()-1);
                        expression.push_back(s[i]);
                    }
                }else {
                    expression.push_back(s[i]);
                }
            }
            while(!stackArr.empty()) {
                if(stackArr.back()=='(') {
                    stackArr.erase(stackArr.end()-1);
                    expression.push_back(')');
                }else if(stackArr.back()=='{') {
                    stackArr.erase(stackArr.end()-1);
                    expression.push_back('}');
                }else if(stackArr.back()=='[') {
                    stackArr.erase(stackArr.end()-1);
                    expression.push_back(']');
                }
            }
            if( valid == true ) cout << "True" << endl;
            else cout << "False" << endl << expression << endl;
        }
        void infix2Prefix() {
            unsigned long long i, len;

            stackArr.clear();
            prefix.clear();
            len = expression.length();
            for(i=1;i<=len;i++) {
                if(expression[len-i]>='0' && expression[len-i]<='9')
                {
                    prefix.push_back(expression[len-i]);
                }else if(expression[len-i]=='+' || expression[len-i]=='-' || expression[len-i]=='*' || expression[len-i]=='/')
                {
                    while( !stackArr.empty() && ( (stackArr.back()=='*' && expression[len-i]=='+') || (stackArr.back()=='*' && expression[len-i]=='-') || (stackArr.back()=='/' && expression[len-i]=='+') || (stackArr.back()=='/' && expression[len-i]=='-') ) )
                    {
                        prefix.push_back(stackArr.back());
                        stackArr.erase(stackArr.end()-1);
                    }
                    stackArr.push_back(expression[len-i]);
                }else if(expression[len-i]==')' || expression[len-i]=='}' || expression[len-i]==']')
                {
                    stackArr.push_back(expression[len-i]);
                }else if(expression[len-i]=='(')
                {
                    while(stackArr.back()!=')') {
                        prefix.push_back(stackArr.back());
                        stackArr.erase(stackArr.end()-1);
                    }
                    stackArr.erase(stackArr.end()-1);
                }else if(expression[len-i]=='{')
                {
                    while(stackArr.back()!='}') {
                        prefix.push_back(stackArr.back());
                        stackArr.erase(stackArr.end()-1);
                    }
                    stackArr.erase(stackArr.end()-1);
                }else if(expression[len-i]=='[')
                {
                    while(stackArr.back()!=']') {
                        prefix.push_back(stackArr.back());
                        stackArr.erase(stackArr.end()-1);
                    }
                    stackArr.erase(stackArr.end()-1);
                }
            }
            while(!stackArr.empty()) {
                prefix.push_back(stackArr.back());
                stackArr.erase(stackArr.end()-1);
            }
            reverse(prefix.begin(), prefix.end());
        }
        void evalPrefix() {
            unsigned long long i, n, len;
            long long op1, op2;
            long long *buffer;

            len = prefix.length();
            if(len==0) {
                eval = 0;
            }else {
                buffer = (long long*) calloc (len, sizeof(long long));
                n = 0;
                for(i=1;i<=len;i++) {
                    switch(prefix[len-i])
                    {
                        case '+':
                            op1 = buffer[n-1];
                            n--;
                            op2 = buffer[n-1];
                            n--;
                            buffer[n] = op1 + op2;
                            n++;
                            break;
                        case '-':
                            op1 = buffer[n-1];
                            n--;
                            op2 = buffer[n-1];
                            n--;
                            buffer[n] = op1 - op2;
                            n++;
                            break;
                        case '*':
                            op1 = buffer[n-1];
                            n--;
                            op2 = buffer[n-1];
                            n--;
                            buffer[n] = op1 * op2;
                            n++;
                            break;
                        case '/':
                            op1 = buffer[n-1];
                            n--;
                            op2 = buffer[n-1];
                            n--;
                            buffer[n] = op1 / op2;
                            n++;
                            break;
                        default:
                            buffer[n] = prefix[len-i] - '0';
                            n++;
                            break;
                    }
                }
                eval = buffer[0];
                free(buffer);
            }
            cout << eval << endl;
        }
    public:
        void isValid(string s) {
            expresionCheck(s);
            infix2Prefix();
            evalPrefix();
        }
};
