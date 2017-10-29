#include <iostream>
#include <string>
#include <vector>
#include "code.cpp"

using namespace std;

int main(int argc, char const *argv[])
{
    Implement paren;
    string input;

	while(getline(cin, input)){
		paren.isValid(input);
	}
	return 0;
}
