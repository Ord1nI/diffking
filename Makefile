# @file
# @version 0.1
run:
	clang main.c parser.c myclib/string/mystring.c dif.c tree.c -o dif.out -lm -fsanitize=address
	./gen_graph.sh
	./dif.out



# end
