extern int yylineno;
void yyerror(char *s, ...);

struct symbol {
  char *name;
  double value;
  struct ast *func;
  struct symlist *syms;
};

#define NHASH 9997
struct symbol symtab[NHASH];

struct symbol *lookup(char *);

struct symlist {
  struct symbol *sym;
  struct symlist *next;
};

struct symlist *newsymlist(struct symbol *sym, struct symlist *next);
void symlistfree(struct symlist *sl);

/* tipos de nós
  + - * /
  0-7 operadores de comparação, 04 igual, 02 menpr que, 01 maior que
  L expressao ou lista de comandos
  I comando IF
  W comando WHILE
  N symbol de referencia
  = atribuicao
  S lista de simbolos
  F chamada de função pre-definida
  C chamada de função definida pelo usuário
*/

// funções pré-definidas
enum bifs {
  B_sqrt = 1,
  B_exp,
  B_log,
  B_print
};

struct ast {
  int nodetype;
  struct ast *l;
  struct ast *r;
};

struct fncall {
  int nodetype;  // F
  struct ast *l;
  enum bifs functype;
};

struct ufncall {
  int nodetype;  // C
  struct ast *l;
  struct symbol *s;
};

struct flow {
  int nodetype;  // I ou W
  struct ast *cond;
  struct ast *tl;
  struct ast *el;
};

struct numval {
  int nodetype;  // K
  double number;
};

struct symref {
  int nodetype;  // N
  struct symbol *s;
};

struct symasgn {
  int nodetype;  // =
  struct symbol *s;
  struct ast *v;
};

struct ast *newast(int nodetype, struct ast *l, struct ast *r);
struct ast *newcmp(int cmptype, struct ast *l, struct ast *r);
struct ast *newfunc(int functype, struct ast *l);
struct ast *newcall(struct symbol *s, struct ast *l);
struct ast *newref(struct symbol *s);
struct ast *newasgn(struct symbol *s, struct ast *v);
struct ast *newnum(double d);
struct ast *newflow(int nodetype, struct ast *cond, struct ast *tl, struct ast *tr);

void dodef(struct symbol *name, struct symlist *syms, struct ast *stmts);

double eval(struct ast *);
void treefree(struct ast *);