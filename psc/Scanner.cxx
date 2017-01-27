/*
** Implementation file for Scannermodule
**
**
**
** exa
**
*/

#include "Scanner.hxx"

char* Scanner::token_names[]=
{"id", "intnum", "realnum", "relop", "addop", "multop",
 "assigop", "keyword", "delimiter", "eof"};

char* Scanner::keywords[]=
{ "program", "begin", "end", "integer", "real", "boolean",
  "function", "procedure", "if", "then", "else", "while", "for", "repeat",
  "until", "do", "not", "array", "var", "const", "type", "of" };

// constructor
Scanner::Scanner(char* source)
  : in(source), line_number(1), column_number(0)
  , source_filename(source), state(s_init), prev_state(s_dead)
  , lexemesize(0)
{
  for (int i=0; i<256; i++)
    lexeme[i]=0;
  try {
    read_next_char();
  }
  catch (EOFException e) {
    error("File empty");
    exit(0);
  }
  for (int i=0; i<22; i++)
    rw[keywords[i]] = keyword;

  rw["or"] = addop;
  rw["div"] = multop;
  rw["mod"] = multop;
  rw["and"] = multop;
}

// pretty print quadruple of next token in the row
int Scanner::print_next_token(ostream& out) {

  TokenInfo quad = scan();
  out << '(' << token_names[quad.token] << ", '"
      << quad.attributevalue.lexeme << "', "
      << quad.linenumber << ", " << quad.lineposition << ')' << endl;
  //out << "TOKEN: " << lexeme << endl;
}

// The core routine used by the scanner
TokenInfo Scanner::scan() {

  if ((state!=s_init) || (prev_state==s_error)) {
    try {
      read_next_char();
    }
    catch (EOFException e) {
      // we may have a valid token up to the end of input
    }
  }
  else if (finished())
    return gen_quad(eof, *new Attribute);

  //cout << state << ",<" << lexeme << "> " << endl; // debug

  // State transitions
  switch (state) {

    // initial state
  case s_init: {

    reset_lexeme();		// start new lexeme
     // beginning position of lexeme
    beg_ln = line_number;
    beg_cn = column_number;

    // transition from s_init
    switch (c) {

      // white space
    case '\n':
    case ' ':
    case '\t': transition(s_ws); scan_white_space(); break;

      // beginning of a comment
    case '{': transition(s_comment); scan_comment(); break;

      // prefix '<'
    case '<': transition(s_less); break;

      // prefix '>'
    case '>': transition(s_grt); break;

      // prefix ':'
    case ':': transition(s_col); break;

      // prefix ','
    case '.': transition(s_dot); break;

      // singletons
    case '=': transition(s_eq); break;
    case '+': transition(s_add); break;
    case '-': transition(s_sub); break;
    case '*': transition(s_tms); break;
    case '/': transition(s_dvd); break;
    case ',': transition(s_cm); break;
    case ';': transition(s_sc); break;
    case '(': transition(s_lb); break;
    case ')': transition(s_rb); break;
    case '[': transition(s_la); break;
    case ']': transition(s_ra); break;
    default: {
      if (isalpha(c))
	transition(s_id);
      else if (isdigit(c))
	transition(s_num);
      else {
        string msg;
	msg=string("Skipping character <");
	if (!iscntrl(c))
	  msg += c;
	else
	  msg += "control-character";
	msg += string(">, it cannot constitute any token");
	error(msg);
	try {
	  read_next_char();
	}
	catch (EOFException e)
	  {}
	transition(s_init);	// unable to match a token
	return scan();
     }
    } break;
    }
  }
  break;

  // scanning white space
  case s_ws: {
    switch (c) {
    case '\n':
    case ' ':
    case '\t': break;
    default: {
	transition(s_init);
    } break;
    }
  }
  break;

  // scanning identifiers and keywords
  case s_id: {
    if (!isalnum(c)) {
      transition(s_init);
      return handle_id();
    }
  } break;
  break;

  // scanning numbers
  case s_num: {
    if ((c=='.'))
      transition(s_fract);
    else if ((c=='e'))
      transition(s_exp2);
    else if (!isdigit(c)) {
      transition(s_init);
      return gen_quad(intnum, *new IntNum(lexeme));
    }
  } break;
  break;

  // scanning fraction or dotdot
  case s_fract: {
    if ((c=='e'))
      transition(s_exp);
    else if (!isdigit(c)) {
      if (last_c=='.') {
	lexeme[lexemesize-1] = 0;// trim last character;
	if (c=='.') {		// some hacking :<
	  TokenInfo t = gen_quad(intnum, *new IntNum(lexeme));
	  strcpy(lexeme, "..");
	  lexemesize = 2;
	  beg_ln=line_number;
	  beg_cn=column_number-1;
	  transition(s_dotdot);
	  return t;
	}
	error("Digit expected for fraction part of real literal");
	transition(s_init);
	return gen_quad(realnum, *new RealNum(lexeme));
      }
      transition(s_init);
      return gen_quad(realnum, *new RealNum(lexeme));
    }
  } break;
  break;

  // scanning optional exponent
  case s_exp: {
    if (! ((isdigit(c)) || (c=='+') || (c=='-')) ) {
      error("Digit, + or - expected for exponent part of real literal");
      lexeme[lexemesize-1] = 0;// trim last character;
      transition(s_init);
      return gen_quad(realnum, *new RealNum(lexeme));
    }
    transition(s_exp2);
  } break;
  break;

  // scanning optional exponent's value
  case s_exp2: {
    if (!isdigit(c))
      if (!isdigit(last_c)) {
	error("Digit expected at the end of exponent part");
	lexeme[lexemesize-1] = 0;// trim last character;
	transition(s_init);
	return gen_quad(realnum, *new RealNum(lexeme));
      }
      else {
	transition(s_init);
	return gen_quad(realnum, *new RealNum(lexeme));
      }
  } break;
  break;

  // scanning prefix '<'
  case s_less: {
    switch (c) {
    case '>': transition(s_ne); break;
    case '=': transition(s_le); break;
    default: transition(s_init); return gen_quad(relop, *new RelOp); break;
    }
  }
  break;
  case s_ne: transition(s_init); return gen_quad(relop, *new RelOp); break;
  case s_le: transition(s_init); return gen_quad(relop, *new RelOp); break;

  // scanning prefix '>'
  case s_grt: {
    switch (c) {
    case '=': transition(s_ge); break;
    default: transition(s_init); return gen_quad(relop, *new RelOp); break;
    }
  }
  break;
  case s_ge: transition(s_init); return gen_quad(relop, *new RelOp); break;

  // scanning prefix '.'
  case s_dot: {
    switch (c) {
    case '.': transition(s_dotdot); break;
    default: transition(s_init); return gen_quad(delimiter, *new Delimiter); break;
    }
  }
  break;
  case s_dotdot: transition(s_init); return gen_quad(delimiter, *new Delimiter); break;

  // scanning prefix ':'
  case s_col: {
    switch (c) {
    case '=': transition(s_asg); break;
    default: transition(s_init); return gen_quad(delimiter, *new Delimiter); break;
    }
  }
  break;
  case s_asg: transition(s_init); break;

  case s_eq: transition(s_init); return gen_quad(relop, *new RelOp);
  case s_add: transition(s_init); return gen_quad(addop, *new AddOp);
  case s_sub: transition(s_init); return gen_quad(addop, *new AddOp);
  case s_tms: transition(s_init); return gen_quad(multop, *new MultOp);
  case s_dvd: transition(s_init); return gen_quad(multop, *new MultOp);
  case s_cm: transition(s_init); return gen_quad(delimiter, *new Delimiter);
  case s_sc: transition(s_init); return gen_quad(delimiter, *new Delimiter);
  case s_lb: transition(s_init); return gen_quad(delimiter, *new Delimiter);
  case s_rb: transition(s_init); return gen_quad(delimiter, *new Delimiter);
  case s_la: transition(s_init); return gen_quad(delimiter, *new Delimiter);
  case s_ra: transition(s_init); return gen_quad(delimiter, *new Delimiter);

  case s_error: transition(s_init);

  } // end of switch(state)

  add_char();
  
  return scan();
}

// clear lexeme
void Scanner::reset_lexeme()
{
  for (int i=0; i<lexemesize; i++)		// starting new lexeme
    lexeme[i]=0;
  lexemesize = 0;
}

// read next character from the input stream
void Scanner::read_next_char() {
  if (finished()) {
    cerr << "Already at the end of the input" << endl;
    throw EOFException();
  }

  // read next character from the input stream
  last_c = c;
  c = in.get();
  if (finished()) {
    // return 0
    //throw EOFException();
  }

  // update current line and column number
  if (c=='\n') {
    line_number += 1;
    column_number = 0;
  }
  else
    if (c=='\t')
      column_number += 8;
    else
      column_number += 1;

  if (isalpha(c))
    c = tolower(c);

}

// perform state transition
void Scanner::transition(State ns) {
  prev_state = state;
  state = ns;
}

void Scanner::add_char() {
  // append new character to the lexeme
  if (state!=s_init) {
    lexeme[lexemesize++] = c;
    if (lexemesize==65)
      error("Lexeme too long");
  }
}

void Scanner::scan_white_space() {}

// scan past comments
void Scanner::scan_comment()
{
  //int err = 0;
  do {
    try {
      read_next_char();
    }
    catch (EOFException e) {
      error("comment delimiter '}' expected at the end of file");
      transition(s_init);
      return;
    }
  } while ( (c!='}') );
  transition(s_init);
  try {
    read_next_char();
  }
  catch (EOFException e) {}
}

// handle identifiers and reserved words through a reserved word table
TokenInfo Scanner::handle_id()
{
  string id_name(lexeme);

  // is it an identifier?
  if (rw.find(lexeme)==rw.end())
    return gen_quad(id, *new ID);
  else {
    // if it is a reserved word find out its type
    Token tkn = rw[lexeme];
    if (tkn==keyword)
      return gen_quad(keyword, *new Keyword);
    else if (tkn==multop)
      return gen_quad(multop, *new MultOp);
    else
      return gen_quad(addop, *new AddOp);
  }
}

// Generate appropriate quadruple for the token t with attr value a
TokenInfo Scanner::gen_quad(Token t, Attribute& a)
{
  a.lexeme = string(lexeme);
  reset_lexeme();
  a.state = prev_state; // accepting state
  return TokenInfo(t,a,beg_ln,beg_cn);
}

// Give error message
void Scanner::error(const string& s) {
  cerr << source_filename << ":L" << line_number << ":C" << column_number
       << " Error: " << s << endl;
}

// Give warning message
void Scanner::warning(const string& s) {
  cerr << source_filename << ":L" << line_number << ":C" << column_number
       << " Warning: " << s << endl;
}

