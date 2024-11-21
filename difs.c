#include "myclib/string/mystring.h"
#include "difs.h"
#include <string.h>
#include <ctype.h>
#include <stdio.h>

int which_func(char* str) {
    char * FUNC_ARR[] = {"LOG","LN","SIN","COS","SQRT","TG","CTG","ARCSIN","ARCCOS","ARCTG","ARCCTG"};
    for(int i = 0; i < sizeof(FUNC_ARR)/sizeof(char *); i++) {
        if(strcmp(str,FUNC_ARR[i])) {
            return i;
        }
    }
    return -1;
}

bool is_number(string str) {
    char * digit = str.str;
    while(*digit != '\0') {
        if (!isdigit(*digit)) {
            return false;
        }
        digit++;
    }
    return true;
}

string delete_spaces(string str) {
    string new_string = string_new_empty(str.capacity);
    for (size_t i = 0; i < str.length; i++) {
        const char* digit = string_at_pos(&str,i);
        if (*digit != ' ') {
            string_push_back(&new_string, *digit);
        }
    }
    return new_string;
}

void plase_mult(string *str) {
    char prev = *string_at_pos(str,0);
    const char* cur = string_at_pos(str, 1);
    while(*cur != '\0') {
        if (isdigit(prev) && (isalpha(*cur) || *cur == '\\')) {
            string_insert(str,'*',cur-1-str->str);
        }
        else if (isalpha(prev) && isdigit(*cur)) {
            string_insert(str,'*',cur-1-str->str);
        }
        else if (prev == ')' && *cur == '(') {
            string_insert(str,'*',cur-1-str->str);
        }
        prev = *cur;
        cur++;
    }
}


string parse(string str) {
    string newstr = delete_spaces(str);
    plase_mult(&newstr);
    string_destroy(&str);
    return plus_minus(newstr);
}

string plus_minus(string str) {
    for (size_t i = 0; i < str.length ; i++) {
        const char* digit = string_at_pos(&str,i);
        if (*digit == LB) {
            digit++;
            i++;
            while(*digit != RB) {
                digit++;
                i++;
            }
        }
        if (*digit == PLUS || *digit == MINUS) {
            string left = mult(string_substr(&str, 0, i-1));
            string right = plus_minus(string_substr(&str, i+1, str.length-1));
            string_push_back(&left, *digit);
            string_concatinate_c_str(&left,right.str);

            string_destroy(&str);
            string_destroy(&right);
            return left;
        }

    }
    return mult(str);
}

string mult(string str) {
    for (size_t i = 0; i < str.length ; i++) {
        const char* digit = string_at_pos(&str,i);
        if (*digit == LB) {
            digit++;
            i++;
            while(*digit != RB) {
                digit++;
                i++;
            }
        }
        if (*digit == MUL || *digit == DIV) {
            string left = power(string_substr(&str,0,i-1));
            string right = mult(string_substr(&str,i+1,str.length-1));
            if(is_number(left) || is_number(right)) {
                string_push_back(&left,*digit);
                string_concatinate_c_str(&left,right.str);

                string_destroy(&right);
                string_destroy(&str);
                return left;
            }
        }
    }
    return power(str);
}

string power(string str) {
    for (size_t i = 0; i < str.length ; i++) {
        const char* digit = string_at_pos(&str,i);
        if (*digit == LB) {
            digit++;
            i++;
            while(*digit != RB) {
                digit++;
                i++;
            }
        }
        if (*digit == POW) {
            string left = brackets(string_substr(&str,0,i-1));
            string right = power(string_substr(&str,i+1,str.length-1));

            if (is_number(right)) {
                string_push_back(&left,POW);
                string_concatinate_c_str(&left,right.str);
                string_push_back(&left,MUL);
                string_concatinate_c_str(&left,right.str);

                string_destroy(&right);
                string_destroy(&str);
                return left;
            }

        }
    }
    return brackets(str);
}

string brackets(string str) {
    if (*string_at_pos(&str,0) == LB) {
        return plus_minus(string_substr(&str,1,str.length-2));
    }
    return function(str);
}

string function(string str) {
    const char* digit = string_at_pos(&str,0);

    string func = string_new_empty(10);
    if (*digit == '\\') {
        digit++;
        while(*digit != '{') {
            string_push_back(&func,*digit);
            digit++;
        }
    } else {
        string_destroy(&func);
        return str;
    }

    switch (which_func(func.str)) {
        case LOG:
        case LN:
            string_destroy(&func);
            return ln(string_substr(&str,digit-str.str+1,str.length-2));
        case SIN:
        case COS:
        case SQRT:
        case TG:
        case CTG:
        case ARCSIN:
        case ARCCOS:
        case ARCTG:
        case ARCCTG:
        default:
            break;
    }
}

string ln(string str) {
    string res = string_new("1/");
    string_concatinate_c_str(&res, plus_minus(str).str);

    return res;
}

/* node* sin(string str) { */

/* } */

/* node* cos(string str) { */

/* } */

/* node* sqrt(string str) { */

/* } */

/* node* tg(string str) { */

/* } */

/* node* ctg(string str) { */

/* } */

/* node* arcsin(string str) { */

/* } */

/* node* arccos(string str) { */

/* } */

/* node* arctg(string str) { */

/* } */

/* node* arcctg(string str) { */

/* } */
