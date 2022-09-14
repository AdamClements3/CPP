/*
 * Name:  Adam CLements
 * Date Submitted: 
 * Lab Section: 2121-001
 * Assignment Name: Infix to Postfix Conversion
 */

#include <iostream>
#include <string>
#include <stack>

using namespace std;

//Converts an infix arithmetic expression into postfix
//The function takes 3 parameters
//First parameter: array of strings for infix expression
//    each string is either an integer number or operator symbol
//Second parameter: number of strings in infix expression
//Third parameter: array of strings for postfix expression
//    generated by function, same format as first parameter
//    assumes that postfix is at least the size of postfix
//Return value: int, number of strings in postfix expression
//    Returns 0 if an error is encountered when converting expression
//    An error occurs with a mismatched parenthesis, e.g. ( ( ) or ( ) ) etc.
//Operator symbols:
// ( : left parenthesis, all operations between this and ")" take place first
// ) : right parenthesis, all op.s back to previous "(" take place first
// * : multiplication, higher precedence - takes place before "+" and "-"
// / : division, higher precedence - takes place before "+" and "-"
// % : remainder, higher precedence - takes place before "+" and "-"
// + : addition, lower precedence - takes place after "*" , "/" , "%"
// - : subtraction, lower precedence - takes place after "*" , "/" , "%"
//The function is not specified to work with any other operator symbols
//Any string in infix may be assumed to be an integer operand if none
// of the above symbols

int precedence(std::string str){
	if(str == "*" || str == "/" || str == "%"){
		return 2;
	}
	else if(str == "+" || str == "-"){
		return 1;
	}
	else{
		return 0;
	}
}

//reorder the infix expression as a properly formatted postfix expression, and return 
int infixToPostfix(string infix[], int length, string postfix[]){
	//variables used later (stack for operators, currentPos for filling postfix
	stack<std::string> temp;
	int currentPos = 0;
	//iterate through the input expression
	for(int i=0;i<length;i++){
		//if the current char is a number, send it to output
		if(infix[i] >= "0" && infix[i] <= "9"){
			postfix[currentPos++] = infix[i];
		}
		//if the current char is a parenthesis, send it to the stack, and keep sending operators to the stack until it encounters ")"
		else if(infix[i] == "("){
			temp.push(infix[i]);
		}
		//if the program encounters a ")" unload the stack until it finds the previous "("
		else if(infix[i] == ")"){
			while(temp.top() != "("){
				postfix[currentPos++] = temp.top();
				temp.pop();
			}
		}
		//if the current char is an operator, assign it a precedence value to make comparison easy ("*","/","%" = 2, "+","-" = 2), and check the operator stack
		if(infix[i] == "*" || infix[i] == "/" || infix[i] == "%" || infix[i] == "+" || infix[i] == "-"){
			//pop all of the operators from the stack that have a greater than or equal precedence value, unless a parenthetical is found in the stack in which case, push the current operator
			while(!temp.empty() && precedence(infix[i]) <= precedence(temp.top())){
				postfix[currentPos++] = temp.top();
				temp.pop();
			}
			temp.push(infix[i]);
		}
	}
	while(!temp.empty()){
		postfix[currentPos++] = temp.top();
		temp.pop();
	}
	return currentPos-1;
}

//Main function to test infixToPostfix()
//Should convert 2 + 3 * 4 + ( 5 - 6 + 7 ) * 8
//            to 2 3 4 * + 5 6 - 7 + 8 * +
int main()
{
    string infixExp[] = {"2", "+", "3", "*", "4", "+", "(",
                         "5", "-", "6", "+", "7", ")", "*",
                         "8"};
    string postfixExp[15];
    int postfixLength;

    cout << "Infix expression: ";
    for (int i=0; i<15; i++)
    {
        cout << infixExp[i] << " ";
    }
    cout << endl;
    cout << "Length: 15" << endl << endl;

    postfixLength = infixToPostfix(infixExp, 15, postfixExp);

    cout << "Postfix expression: ";
    for (int i=0; i<postfixLength; i++)
    {
        cout << postfixExp[i] << " ";
    }
    cout << endl;
    cout << "Length: " << postfixLength << endl;
    
    return 0;
}