/*
** Interface file for Scanner module
**
**
**
** exa
**
*/

#ifndef Scanner_Interface
#define Scanner_Interface 1

#include "General.hxx"
#include "Attribute.hxx"

enum Token { id, intnum, realnum, relop, addop, multop,
	     assigop, keyword, delimiter, eof };


enum State { s_init, s_id, s_num, s_fract, s_exp, s_exp2, s_less,
	     s_grt, s_col, s_dot, s_ws, s_comment, s_dead, s_error,
	     s_eq, s_ne, s_le, s_ge, s_dotdot, s_asg, s_add, s_sub,
	     s_tms, s_dvd, s_cm, s_sc, s_lb, s_rb, s_la, s_ra
	     };

struct TokenInfo {
  TokenInfo(Token t, Attribute& a, int l, int c)
    : token(t), attributevalue(a), linenumber(l), lineposition(c) {}
  Token token;
  Attribute& attributevalue;
  int linenumber, lineposition;
};


// Scanner reads tokens from a specified input stream
class Scanner {
public:

  struct EOFException {};

  Scanner(char *);

  int finished() { return (in.bad() || in.eof()); }
  int print_next_token(ostream&);
  TokenInfo scan();

private:

  string source_filename;
  ifstream in;			// input stream
  int line_number, column_number;
  int beg_ln, beg_cn;		// beginning line and column numbers
  char last_c;			// last character
  char c;			// next character
  State state;			// automaton state
  State prev_state;		// previous automaton state

  void reset_lexeme();
  char lexeme[256];
  int lexemesize;

  void read_next_char();
  void transition(State);
  void add_char();

  void scan_white_space();
  void scan_comment();

  TokenInfo handle_id();
  TokenInfo gen_quad(Token t, Attribute& a);

  void error(const string&);
  void warning(const string&);

  static char* token_names[];
  static char* keywords[];

  map<string, Token, less<string> > rw;// reserved words
};

#endif






