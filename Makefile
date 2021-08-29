linguagem-basica: linguagem-basica.y linguagem-basica.l linguagem-basica.h
	bison -o linguagem-basica.tab.c -d linguagem-basica.y
	flex -o linguagem-basica.lex.c linguagem-basica.l
	gcc linguagem-basica.tab.c linguagem-basica.lex.c linguagem-basica.c -lfl -lm -o $@ -g
	@echo Construcao concluida