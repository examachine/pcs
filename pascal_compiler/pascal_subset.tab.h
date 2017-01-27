typedef union {
	int		integer;
	double		floating;
	Symbol		*symbol;
	SymbolList	*symbol_list;
	Type		*type;
	TypeList	*type_list;
	Variable	*variable;
	Constant	*constant;
	Expression	*expression;
	ExprList	*expr_list;
	ConstantExpression *const_expr;
	Statement	*statement;
	Context		*context;
} YYSTYPE;
#define	LP	258
#define	RP	259
#define	LB	260
#define	RB	261
#define	COM	262
#define	COL	263
#define	SC	264
#define	DOT	265
#define	DOTDOT	266
#define	PROGRAM	267
#define	VAR	268
#define	ARRAY	269
#define	OF	270
#define	INTEGER	271
#define	REAL	272
#define	FUNCTION	273
#define	PROCEDURE	274
#define	BLOCK_BEG	275
#define	BLOCK_END	276
#define	IF	277
#define	THEN	278
#define	ELSE	279
#define	WHILE	280
#define	DO	281
#define	L_INT	282
#define	L_FLOAT	283
#define	ID	284
#define	ASSIGN	285
#define	OR	286
#define	AND	287
#define	XOR	288
#define	NOT	289
#define	EQ	290
#define	NE	291
#define	LT	292
#define	LE	293
#define	GT	294
#define	GE	295
#define	ADD	296
#define	SUB	297
#define	MUL	298
#define	DIV	299
#define	DIV2	300
#define	MOD	301
#define	UMINUS	302
#define	UPLUS	303


extern YYSTYPE yylval;
