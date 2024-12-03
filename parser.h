#ifndef _PARSER_H_
#define _PARSER_H_

#include "myclib/string/mystring.h"

#include <stdio.h>

#include "tree.h"



int which_func(char* str);

void delete_spaces(string str);
void plase_mult(string str);

node* parse(string str);
node* plus_minus(char** str);
node* mult(char** str);
node* division(char** str);
node* brackets(char** str);
node* power(char** str);
node* function(char** str);
node* getvar(char** str);
node* getnum(char** str);


static void sup_to_graph(FILE* f, node* n);
void to_graph(node* n, char* file_path);

#endif // _PARSER_H_
