#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 10

typedef struct {
  int top;
  int data[SIZE];
} Stack;

void push(Stack *, int);
int pop(Stack *);
int isBalanced(char *);
int isEmpty(Stack *);
int isFull(Stack *);
char peek(Stack, int);
char stackTop(Stack);
int isOperand(char);
int myPow(int, int);
int OutStackPrecedence(char);
int InStackPrecedence(char);
void InfixToPrefix(char *);
void InfixToPostfix(char *);
char *reverseString(char *);
void reverse(char *);
int EvaluatePrefix(char *);
int EvaluatePostfix(char *);
void printStep(int, char, Stack, char *);
void printPrefixStep(int, char, Stack, char *);

char prefix[100], postfix[100];
int main() {
  int choice;
  int res;
  char expression[100];

  do {
    printf("\n********************Welcome to Expression Evaluation "
           "Program******************\n");
    printf("\n1.Infix to Prefix Conversion");
    printf("\n2.Infix to Postfix Conversion");
    printf("\n3.Check whether Expression is Balanced or Not");
    printf("\n4.Exit");

    printf("\nEnter your choice : ");
    if (scanf("%d", &choice) != 1) {
      printf("\nInvalid Choice");
      return 0;
    }

    switch (choice) {
    case 1:
      printf("\nEnter expression: ");
      if (scanf("%s", expression) != 1) {
        printf("\nInvalid Expressions");
        return 0;
      }
      if (!(isBalanced(expression))) {
        printf("\nAN EXPRESSION IS NOT BALANCED");
      } else {
        printf("\nStep \tChar Scan \tStack Content \t\tDisplay\n");
        printf("-------------------------------------------------------\n");
        InfixToPrefix(expression);
        printf("\nRes: %s", prefix);
        res = EvaluatePrefix(prefix);
        printf("\nEvaluated Value : %d", res);
        memset(prefix, 0, sizeof(prefix));
      }
      break;
    case 2:
      printf("\nEnter expression: ");
      if (scanf("%s", expression) != 1) {
        printf("\nInvalid Expressions");
        return 0;
      }
      if (!(isBalanced(expression))) {
        printf("\nAN EXPRESSION IS NOT BALANCED");
      } else {
        printf("\nStep \tChar Scan \tStack Content \t\tDisplay\n");
        printf("------------------------------------------------------\n");
        InfixToPostfix(expression);
        res = EvaluatePostfix(postfix);
        printf("\nEvaluated Value : %d", res);
        memset(prefix, 0, sizeof(prefix));
      }
      break;
    case 3:
      printf("\nEnter expression: ");
      if (scanf("%s", expression) != 1) {
        printf("\nInvalid Expressions");
        return 0;
      }
      if (isBalanced(expression)) {
        printf("\nAn EXPRESSION is BALANCED");
      } else {
        printf("\nEXPRESSION IS NOT BALANCED");
      }
      break;
    case 4:
      printf("\nEXIT");
      exit(0);
      break;
    default:
      printf("\nInvalid Choice\n");
    }
  } while (choice != 4);
  return 0;
}

void push(Stack *st, int tok) {
  if (st->top == SIZE - 1) {
    printf("\nStack Overflow\n");
  } else {
    st->top++;
    st->data[st->top] = tok;
  }
}

int pop(Stack *st) {
  if (st->top == -1) {
    printf("\nStack is Underflow");
    return -1;
  } else {
    int val = st->data[st->top];
    st->top--;
    return val;
  }
}

char peek(Stack st, int pos) {
  if (pos < 1 || pos > st.top + 1) {
    printf("\nInvalid Position");
    return '\0';
  } else {
    return st.data[st.top - pos + 1];
  }
}

int isEmpty(Stack *st) { return st->top == -1; }

int isFull(Stack *st) { return st->top == SIZE - 1; }

char stackTop(Stack st) {
  if (st.top == -1) {
    return -1;
  } else {
    return st.data[st.top];
  }
}

int myPow(int base, int exponent) {
  if (exponent == 0) {
    return 1;
  } else if (exponent < 0) {
    return 1 / myPow(base, -exponent);
  } else {
    int result = 1;
    for (int i = 0; i < exponent; i++) {
      result *= base;
    }
    return result;
  }
}

int isBalanced(char *exp) {
  int x = 0;
  Stack temp;
  temp.top = -1;
  for (int i = 0; exp[i] != '\0'; i++) {
    if (exp[i] == '(' || exp[i] == '[' || exp[i] == '{') {
      push(&temp, exp[i]);
    } else if (exp[i] == ')' || exp[i] == ']' || exp[i] == '}') {
      if (peek(temp, 1) == '(' && exp[i] == ')') {
        pop(&temp);
      }

      if (peek(temp, 1) == '[' && exp[i] == ']') {
        pop(&temp);
      }

      if (peek(temp, 1) == '{' && exp[i] == '}') {
        pop(&temp);
      }
    }
    x = isEmpty(&temp);
  }
  return x;
}

int isOperand(char exp) {
  return !(exp == '+' || exp == '-' || exp == '*' || exp == '/' || exp == '%' ||
           exp == '^' || exp == '$' || exp == '(' || exp == ')');
}

int OutStackPrecedence(char operator) {
  switch (operator) {
  case '+':
  case '-':
    return 1;
  case '*':
  case '/':
  case '%':
    return 3;
  case '^':
  case '$':
    return 6;
  case '(':
    return 7;
  case ')':
    return 0;
  default:
    return -1;
  }
}

int InStackPrecedence(char operator) {
  switch (operator) {
  case '+':
  case '-':
    return 2;
  case '*':
  case '/':
  case '%':
    return 4;
  case '^':
  case '$':
    return 5;
  case '(':
    return 0;
  default:
    return -1;
  }
}

void printPrefixStep(int step, char charScan, Stack st, char *display) {
  printf("%-5d \t %-10c \t ", step, charScan);
  if (st.top == -1) {
    printf("(empty)\t");
  } else {
    for (int i = st.top; i >= 0; i--) {
      printf("%c", st.data[i]);
    }
    printf("\t\t");
  }
  printf("%20s\n", reverseString(display));
}

void printStep(int step, char charScan, Stack st, char *display) {
  printf("%-5d \t %-10c \t ", step, charScan);
  if (st.top == -1) {
    printf("(empty)\t");
  } else {
    for (int i = st.top; i >= 0; i--) {
      printf("%c", st.data[i]);
    }
    printf("\t\t");
  }
  printf("%20s\n", display);
}

void reverse(char *exp) {
  int i = 0, j = strlen(exp) - 1;
  while (i < j) {
    char c = exp[i];
    exp[i] = exp[j];
    exp[j] = c;
    i++;
    j--;
  }
}

char *reverseString(char *exp) {
  int len = strlen(exp);
  char *rev = (char *)malloc((len + 1) * sizeof(char));
  int start = 0;
  int end = len - 1;

  while (end >= 0) {
    rev[start++] = exp[end--];
  }
  rev[end] = '\0';
  return rev;
}

void fixBrackets(char *exp) {
  for (int i = 0; exp[i] != '\0'; i++) {
    if (exp[i] == '(') {
      exp[i] = ')';
    } else if (exp[i] == ')') {
      exp[i] = '(';
    }
  }
}

void InfixToPrefix(char *exp) {
  reverse(exp);
  fixBrackets(exp);
  Stack temp;
  temp.top = -1;
  int i = 0, j = 0, step = 1;
  char c;

  while (exp[i] != '\0') {
    if (isalnum(exp[i])) {
      while (isalnum(exp[i])) {
        prefix[j++] = exp[i++];
      }
      prefix[j++] = ' ';
    } else if (isdigit(exp[i])) {

      while (isdigit(exp[i])) {
        prefix[j++] = exp[i++];
      }
      prefix[j++] = ' ';
    } else {
      if (OutStackPrecedence(exp[i]) >= InStackPrecedence(stackTop(temp))) {
        push(&temp, exp[i++]);
      } else {
        c = pop(&temp);
        if (!(c == '(' || c == ')' || c == '[' || c == ']' || c == '{' ||
              c == '}')) {
          prefix[j++] = c;
          prefix[j++] = ' ';
        }
      }
    }
    printPrefixStep(step++, exp[i], temp, prefix);
  }

  while (!isEmpty(&temp)) {
    c = pop(&temp);
    if (!(c == '(' || c == ')' || c == '[' || c == ']' || c == '{' ||
          c == '}')) {
      prefix[j++] = c;
      prefix[j++] = ' ';
    }
    printPrefixStep(step++, ' ', temp, prefix);
  }

  prefix[j] = '\0';
  reverse(prefix);
  printf("\nPrefix: %s", prefix);
}

void InfixToPostfix(char *exp) {
  Stack temp;
  temp.top = -1;
  int i = 0, j = 0, step = 1;
  char c;

  while (exp[i] != '\0') {
    if (isalnum(exp[i])) {
      while (isalnum(exp[i])) {
        postfix[j++] = exp[i++];
      }
      postfix[j++] = ' ';
    } else if (isdigit(exp[i])) {

      while (isdigit(exp[i])) {
        postfix[j++] = exp[i++];
      }
      postfix[j++] = ' ';
    } else {
      if (OutStackPrecedence(exp[i]) > InStackPrecedence(stackTop(temp))) {
        push(&temp, exp[i++]);
      } else {
        c = pop(&temp);
        if (!(c == '(' || c == ')' || c == '[' || c == ']' || c == '{' ||
              c == '}')) {
          postfix[j++] = c;
          postfix[j++] = ' ';
        }
      }
    }
    printStep(step++, exp[i], temp, postfix);
  }

  while (!isEmpty(&temp)) {
    c = pop(&temp);
    if (!(c == '(' || c == ')' || c == '[' || c == ']' || c == '{' ||
          c == '}')) {
      postfix[j++] = c;
      postfix[j++] = ' ';
    }
    printStep(step++, ' ', temp, postfix);
  }

  postfix[j] = '\0';
  printf("\nPostfix: %s", postfix);
}

int EvaluatePrefix(char *exp) {
  Stack temp;
  temp.top = -1;

  for (int i = strlen(exp) - 1; i >= 0; i--) {
    if (isdigit(exp[i])) {
      int num = 0, multiplier = 1;
      while (i >= 0 && isdigit(exp[i])) {
        num += (exp[i] - '0') * multiplier;
        multiplier *= 10;
        i--;
      }
      push(&temp, num);
      i++;
    } else if (exp[i] == ' ') {
      continue;
    } else {
      int x1 = pop(&temp);
      int x2 = pop(&temp);
      int res;

      switch (exp[i]) {
      case '+':
        res = x1 + x2;
        break;
      case '-':
        res = x1 - x2;
        break;
      case '*':
        res = x1 * x2;
        break;
      case '/':
        if (x2 == 0) {
          printf("\nDivision by zero error");
          return -1;
        }
        res = x1 / x2;
        break;
      case '%' :
       res = x1 % x2;
       break;
      case '^':
      case '$':
        res = myPow(x1, x2);
        break;
      default:
        printf("Error: Unexpected character in prefix expression: %c\n",
               exp[i]);
        return -1;
      }
      push(&temp, res);
    }
  }
  prefix[0] = '\0';
  return pop(&temp);
}

int EvaluatePostfix(char *exp) {
  Stack temp;
  temp.top = -1;
  for (int i = 0; exp[i] != '\0';) {
    if (isalnum(exp[i])) {
      if (isdigit(exp[i])) {
        int num = 0;

        while (isdigit(exp[i])) {
          num = num * 10 + (exp[i] - '0');
          i++;
        }
        push(&temp, num);
      } else {
        return -1;
      }

    } else if (exp[i] == ' ') {
      i++;
    } else {
      int x2 = pop(&temp);
      int x1 = pop(&temp);
      int res;
      switch (exp[i]) {
      case '+':
        res = x1 + x2;
        break;
      case '-':
        res = x1 - x2;
        break;
      case '*':
        res = x1 * x2;
        break;
      case '/':
        if (x2 == 0) {
          printf("\nDivision by zero error");
        } else {
          res = x1 / x2;
        }
        break;
      case '%' :
       res = x1 % x2;
       break;
      case '^':
      case '$':
        res = myPow(x1, x2);
        break;
      default:
        printf("Error: Unexpected character in postfix expression: %c\n",
               exp[i]);
        return -1;
      }
      push(&temp, res);
      i++;
    }
  }
  postfix[0] = '\0';
  return pop(&temp);
}