#include <gtk/gtk.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 10

typedef struct {
    int top;
    int data[SIZE];
} Stack;

void push(Stack *st, int tok);
int pop(Stack *st);
int isEmpty(Stack *st);
char stackTop(Stack st);
int myPow(int base, int exponent);
int isBalanced(char *exp);
int isOperand(char exp);
int OutStackPrecedence(char operator);
int InStackPrecedence(char operator);
void InfixToPrefix(char *exp);
void InfixToPostfix(char *exp);
char *reverseString(char *exp);
void reverse(char *exp);
int EvaluatePrefix(char *exp);
int EvaluatePostfix(char *exp);
void printPrefixStep(int step, char charScan, Stack st, char *display);
void printStep(int step, char charScan, Stack st, char *display);

char prefix[100], postfix[100];


GtkWidget *output_text_view;


void update_output(const char *text) {
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(output_text_view));
    gtk_text_buffer_set_text(buffer, text, -1);
}


void on_infix_to_prefix_clicked(GtkWidget *widget, gpointer data) {
    const char *expression = gtk_entry_get_text(GTK_ENTRY(data));
    if (!(isBalanced((char *)expression))) {
        update_output("The expression is not balanced.");
        return;
    }
    memset(prefix, 0, sizeof(prefix));
    printf("\nStep \tChar Scan \tStack Content \t\tDisplay\n");
    printf("-------------------------------------------------------\n");
    InfixToPrefix((char *)expression);
    int result = EvaluatePrefix(prefix);
    char result_text[256];
    snprintf(result_text, sizeof(result_text), "Prefix: %s\nEvaluated Value: %d", reverseString(prefix), result);
    update_output(result_text);
}


void on_infix_to_postfix_clicked(GtkWidget *widget, gpointer data) {
    const char *expression = gtk_entry_get_text(GTK_ENTRY(data));
    if (!(isBalanced((char *)expression))) {
        update_output("The expression is not balanced.");
        return;
    }
    memset(postfix, 0, sizeof(postfix));
    printf("\nStep \tChar Scan \tStack Content \t\tDisplay\n");
    printf("-------------------------------------------------------\n");
    InfixToPostfix((char *)expression);
    int result = EvaluatePostfix(postfix);
    char result_text[256];
    snprintf(result_text, sizeof(result_text), "Postfix: %s\nEvaluated Value: %d", postfix, result);
    update_output(result_text);
}


void on_check_balance_clicked(GtkWidget *widget, gpointer data) {
    const char *expression = gtk_entry_get_text(GTK_ENTRY(data));
    if (isBalanced((char *)expression)) {
        update_output("The expression is balanced.");
    } else {
        update_output("The expression is not balanced.");
    }
}


int main(int argc, char *argv[]) {
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *entry;
    GtkWidget *button_infix_to_prefix;
    GtkWidget *button_infix_to_postfix;
    GtkWidget *button_check_balance;
    GtkCssProvider *cssProvider;
    GdkDisplay *display;
    GdkScreen *screen;



    gtk_init(&argc, &argv);

    cssProvider = gtk_css_provider_new();
    gtk_css_provider_load_from_path(cssProvider, "style.css", NULL);
    display = gdk_display_get_default();
    screen = gdk_display_get_default_screen(display);
    gtk_style_context_add_provider_for_screen(screen, GTK_STYLE_PROVIDER(cssProvider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);





    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Expression Evaluator");
    gtk_window_set_default_size(GTK_WINDOW(window), 500, 500);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    printf("\n************Welcome to Expression Evaluation "
           "Program************\n");
    
 
    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    entry = gtk_entry_new();
    gtk_widget_set_name(entry, "entry");
    gtk_grid_attach(GTK_GRID(grid), entry, 0, 0, 3, 1);

    button_infix_to_prefix = gtk_button_new_with_label("Infix to Prefix");
    gtk_widget_set_name(button_infix_to_prefix, "button_infix_to_prefix");
    gtk_grid_attach(GTK_GRID(grid), button_infix_to_prefix, 0, 1, 1, 1);
    g_signal_connect(button_infix_to_prefix, "clicked", G_CALLBACK(on_infix_to_prefix_clicked), entry);

    button_infix_to_postfix = gtk_button_new_with_label("Infix to Postfix");
     gtk_widget_set_name(button_infix_to_postfix, "button_infix_to_postfix");
    gtk_grid_attach(GTK_GRID(grid), button_infix_to_postfix, 1, 1, 1, 1);
    g_signal_connect(button_infix_to_postfix, "clicked", G_CALLBACK(on_infix_to_postfix_clicked), entry);

    button_check_balance = gtk_button_new_with_label("Check Balance");
    gtk_widget_set_name(button_check_balance, "button_check_balance");
    gtk_grid_attach(GTK_GRID(grid), button_check_balance, 2, 1, 1, 1);
    g_signal_connect(button_check_balance, "clicked", G_CALLBACK(on_check_balance_clicked), entry);

    output_text_view = gtk_text_view_new();
    gtk_widget_set_name(output_text_view, "output_text_view");
    gtk_grid_attach(GTK_GRID(grid), output_text_view, 0, 2, 3, 1);

    gtk_widget_show_all(window);

    gtk_main();

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
        printf("\nStack Underflow\n");
        return -1;
    } else {
        return st->data[st->top--];
    }
}

int isEmpty(Stack *st) {
    return st->top == -1;
}

char stackTop(Stack st) {
    if (st.top == -1) {
        return -1;
    } else {
        return st.data[st.top];
    }
}

int myPow(int base, int exponent) {
    int result = 1;
    while (exponent > 0) {
        result *= base;
        exponent--;
    }
    return result;
}

int isBalanced(char *exp) {
    Stack temp;
    temp.top = -1;
    for (int i = 0; exp[i] != '\0'; i++) {
        if (exp[i] == '(' || exp[i] == '[' || exp[i] == '{') {
            push(&temp, exp[i]);
        } else if (exp[i] == ')' || exp[i] == ']' || exp[i] == '}') {
            if ((exp[i] == ')' && stackTop(temp) == '(') ||
                (exp[i] == ']' && stackTop(temp) == '[') ||
                (exp[i] == '}' && stackTop(temp) == '{')) {
                pop(&temp);
            } else {
                return 0;
            }
        }
    }
    return isEmpty(&temp);
}

int isOperand(char exp) {
    return !(exp == '+' || exp == '-' || exp == '*' || exp == '/' || exp == '%' || exp == '^' || exp == '$' || exp == '(' || exp == ')');
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

void reverse(char *exp) {
    int i = 0, j = strlen(exp) - 1;
    while (i < j) {
        char temp = exp[i];
        exp[i] = exp[j];
        exp[j] = temp;
        i++;
        j--;
    }
}

char *reverseString(char *exp) {
    int len = strlen(exp);
    char *rev = (char *)malloc((len + 1) * sizeof(char));
    for (int i = 0; i < len; i++) {
        rev[i] = exp[len - i - 1];
    }
    rev[len] = '\0';
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

void InfixToPrefix(char *exp) {
    Stack st;
    st.top = -1;
    char rev[strlen(exp) + 1];
    strcpy(rev, exp);
    reverse(rev);
    fixBrackets(rev);

    int j = 0, step = 1;
    for (int i = 0; rev[i] != '\0'; i++) {
        char charScan = rev[i];
        if (isOperand(charScan)) {
            prefix[j++] = charScan;
        } else if (charScan == '(') {
            push(&st, charScan);
        } else if (charScan == ')') {
            while (!isEmpty(&st) && stackTop(st) != '(') {
                prefix[j++] = pop(&st);
            }
            pop(&st);  
        } else {
            while (!isEmpty(&st) && OutStackPrecedence(charScan) < InStackPrecedence(stackTop(st))) {
                prefix[j++] = pop(&st);
            }
            push(&st, charScan);
        }
        printPrefixStep(step++, exp[i], st, prefix);
    }
    while (!isEmpty(&st)) {
        prefix[j++] = pop(&st);
        printStep(step++, ' ', st, prefix);
    }
    prefix[j] = '\0';
    reverse(prefix);
}

void InfixToPostfix(char *exp) {
    Stack st;
    st.top = -1;

    int j = 0, step = 1;
    for (int i = 0; exp[i] != '\0'; i++) {
        char charScan = exp[i];
        if (isOperand(charScan)) {
            postfix[j++] = charScan;
        } else if (charScan == '(') {
            push(&st, charScan);
        } else if (charScan == ')') {
            while (!isEmpty(&st) && stackTop(st) != '(') {
                postfix[j++] = pop(&st);
            }
            pop(&st);  
        } else {
            while (!isEmpty(&st) && OutStackPrecedence(charScan) <= InStackPrecedence(stackTop(st))) {
                postfix[j++] = pop(&st);
            }
            push(&st, charScan);
        }
        printStep(step++, exp[i], st, postfix);
    }
    while (!isEmpty(&st)) {
        postfix[j++] = pop(&st);
        printStep(step++, ' ', st, postfix);
    }
    postfix[j] = '\0';
}

int EvaluatePrefix(char *exp) {
    Stack st;
    st.top = -1;
    reverse(exp);

    for (int i = 0; exp[i] != '\0'; i++) {
        if (isdigit(exp[i])) {
            push(&st, exp[i] - '0');
        } else {
            int op1 = pop(&st);
            int op2 = pop(&st);
            switch (exp[i]) {
                case '+':
                    push(&st, op1 + op2);
                    break;
                case '-':
                    push(&st, op1 - op2);
                    break;
                case '*':
                    push(&st, op1 * op2);
                    break;
                case '/':
                    push(&st, op1 / op2);
                    break;
                case '^':
                    push(&st, myPow(op1, op2));
                    break;
                case '$':
                    push(&st, myPow(op1, op2));
                    break;
                default:
                    break;
            }
        }
    }
    return pop(&st);
}

int EvaluatePostfix(char *exp) {
    Stack st;
    st.top = -1;

    for (int i = 0; exp[i] != '\0'; i++) {
        if (isdigit(exp[i])) {
            push(&st, exp[i] - '0');
        } else {
            int op2 = pop(&st);
            int op1 = pop(&st);
            switch (exp[i]) {
                case '+':
                    push(&st, op1 + op2);
                    break;
                case '-':
                    push(&st, op1 - op2);
                    break;
                case '*':
                    push(&st, op1 * op2);
                    break;
                case '/':
                    push(&st, op1 / op2);
                    break;
                case '^':
                    push(&st, myPow(op1, op2));
                    break;
                case '$':
                    push(&st, myPow(op1, op2));
                    break;
                default:
                    break;
            }
        }
    }
    return pop(&st);
}

