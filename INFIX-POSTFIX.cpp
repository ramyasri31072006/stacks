#include<stdio.h>
#include<string.h>

char stack[30];
int top = -1;

void push(char c) {
    stack[++top] = c;
}

void pop() {
    if (top != -1) top--;
}

char Top() {
    if (top != -1) return stack[top];
    return '\0';
}

int precedence(char c) {
    if (c == '+' || c == '-') return 1;
    else if (c == '*' || c == '/') return 2;
    else if (c == '^') return 3;
    else return 0; // For non-operators
}

int isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

void infixToPostfix(char* infix, char* postfix) {
    int j = 0;
    for (int i = 0; infix[i] != '\0'; i++) {
        char c = infix[i];

        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9')) {
            // If operand, add to postfix
            postfix[j++] = c;
        } else if (c == '(') {
            // Push open parenthesis
            push(c);
        } else if (c == ')') {
            // Pop until open parenthesis
            while (Top() != '(') {
                postfix[j++] = Top();
                pop();
            }
            pop(); // Remove open parenthesis
        } else if (isOperator(c)) {
            // Pop while precedence is greater or equal
            while (top != -1 && precedence(Top()) >= precedence(c)) {
                postfix[j++] = Top();
                pop();
            }
            push(c);
        }
    }

    // Pop remaining operators
    while (top != -1) {
        postfix[j++] = Top();
        pop();
    }
    postfix[j] = '\0'; // Null-terminate postfix string
}

int main() {
    char infix[30], postfix[30];
    printf("Enter infix expression: ");
    scanf("%s", infix);

    infixToPostfix(infix, postfix);
    printf("Postfix expression: %s\n", postfix);

    return 0;
}
