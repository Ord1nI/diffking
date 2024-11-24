# @file
# @version 0.1
run:
	clang main.c parser.c myclib/string/mystring.c -o dif.out
	./dif.out
	dot -Tpng *.gv -o file.png

# end
