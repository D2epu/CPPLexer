///////////////////////////////////////////////////////////
// C++ Language Lexer
// version 1.0, author: DeepuKumar
// Copyright (C) DeepuKumar, All rights reserved
// For more info see documentation
///////////////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <ctype.h>
#include <stdio.h>

class Lexer
{
    private:
        enum
        {
            SYNTAX_ERROR = 1,
            INVALID_TOKEN,
            UNBAL_SQUOTE,
            UNBAL_DQUOTE
        };
        std::list<std::string> KwdTable;
        char*  pProgram;
        int    currLine;
    public:
        Lexer () : currLine ( 1 )
        {
        }
        ~Lexer ()
        {
            delete [] pProgram;
        }
        bool CPP_IsDigit ( char c )
        {
            return ( c >= '0' && c <= '9' );
        }
        bool CPP_IsAlnum ( char c )
        {
            return ( ( c >= 'A' && c <= 'Z' ) || ( c >= 'a' && c <= 'z' ) || ( c >= '0' && c <= '9' ) );
        }
        bool CPP_IsAlpha ( char c )
        {
            return ( ( c >= 'A' && c <= 'Z' ) || ( c >= 'a' && c <= 'z' ) );
        }
        void CPP_BuildupKeywordTable ( void )
        {
            KwdTable.push_back ( "alignas"          );
            KwdTable.push_back ( "alignof"          );
            KwdTable.push_back ( "and"              );
            KwdTable.push_back ( "and_eq"           );
            KwdTable.push_back ( "asm"              );
            KwdTable.push_back ( "atomic_cancel"    );
            KwdTable.push_back ( "atomic_commit"    );
            KwdTable.push_back ( "atomic_nonexcept" );
            KwdTable.push_back ( "auto"             );
            KwdTable.push_back ( "bitand"           );
            KwdTable.push_back ( "bitor"            );
            KwdTable.push_back ( "bool"             );
            KwdTable.push_back ( "break"            );
            KwdTable.push_back ( "case"             );
            KwdTable.push_back ( "catch"            );
            KwdTable.push_back ( "char"             );
            KwdTable.push_back ( "char16_t"         );
            KwdTable.push_back ( "char32_t"         );
            KwdTable.push_back ( "class"            );
            KwdTable.push_back ( "compl"            );
            KwdTable.push_back ( "concept"          );
            KwdTable.push_back ( "const"            );
            KwdTable.push_back ( "constexpr"        );
            KwdTable.push_back ( "const_cast"       );
            KwdTable.push_back ( "continue"         );
            KwdTable.push_back ( "decltype"         );
            KwdTable.push_back ( "default"          );
            KwdTable.push_back ( "delete"           );
            KwdTable.push_back ( "do"               );
            KwdTable.push_back ( "double"           );
            KwdTable.push_back ( "dynamic_cast"     );
            KwdTable.push_back ( "else"             );
            KwdTable.push_back ( "enum"             );
            KwdTable.push_back ( "explicit"         );
            KwdTable.push_back ( "export"           );
            KwdTable.push_back ( "extern"           );
            KwdTable.push_back ( "false"            );
            KwdTable.push_back ( "float"            );
            KwdTable.push_back ( "for"              );
            KwdTable.push_back ( "friend"           );
            KwdTable.push_back ( "goto"             );
            KwdTable.push_back ( "if"               );
            KwdTable.push_back ( "import"           );
            KwdTable.push_back ( "inline"           );
            KwdTable.push_back ( "int"              );
            KwdTable.push_back ( "long"             );
            KwdTable.push_back ( "module"           );
            KwdTable.push_back ( "mutable"          );
            KwdTable.push_back ( "namespace"        );
            KwdTable.push_back ( "new"              );
            KwdTable.push_back ( "noexcept"         );
            KwdTable.push_back ( "not"              );
            KwdTable.push_back ( "not_eq"           );
            KwdTable.push_back ( "nullptr"          );
            KwdTable.push_back ( "operator"         );
            KwdTable.push_back ( "or"               );
            KwdTable.push_back ( "or_eq"            );
            KwdTable.push_back ( "private"          );
            KwdTable.push_back ( "protected"        );
            KwdTable.push_back ( "public"           );
            KwdTable.push_back ( "register"         );
            KwdTable.push_back ( "reinterpret_cast" );
            KwdTable.push_back ( "requires"         );
            KwdTable.push_back ( "returns"          );
            KwdTable.push_back ( "short"            );
            KwdTable.push_back ( "signed"           );
            KwdTable.push_back ( "sizeof"           );
            KwdTable.push_back ( "static"           );
            KwdTable.push_back ( "static_assert"    );
            KwdTable.push_back ( "static_cast"      );
            KwdTable.push_back ( "struct"           );
            KwdTable.push_back ( "switch"           );
            KwdTable.push_back ( "synchronized"     );
            KwdTable.push_back ( "template"         );
            KwdTable.push_back ( "this"             );
            KwdTable.push_back ( "thread_local"     );
            KwdTable.push_back ( "throw"            );
            KwdTable.push_back ( "true"             );
            KwdTable.push_back ( "try"              );
            KwdTable.push_back ( "typedef"          );
            KwdTable.push_back ( "typeid"           );
            KwdTable.push_back ( "typename"         );
            KwdTable.push_back ( "union"            );
            KwdTable.push_back ( "unsigned"         );
            KwdTable.push_back ( "using"            );
            KwdTable.push_back ( "virtual"          );
            KwdTable.push_back ( "void"             );
            KwdTable.push_back ( "volatile"         );
            KwdTable.push_back ( "wchar_t"          );
            KwdTable.push_back ( "while"            );
            KwdTable.push_back ( "xor"              );
            KwdTable.push_back ( "xor_eq"           );
        }
        bool CPP_IsKeyword ( const std::string & key )
        {
            std::list<std::string>::iterator itr = KwdTable.begin ();

            while ( itr != KwdTable.end () )
            {
                if ( *itr == key ) return true;
                itr++;
            }

            return false;
        }
        void CPP_CommandLine ( int argc, char ** argv )
        {
            if ( argc < 2 ) CPP_Printusage ();
        }
        void CPP_ProgramLoader ( const std::string & fname )
        {
            std::ifstream in ( fname, std::ios::in | std::ios::binary );

            if ( ! in )
            {
                std::cout << "Error : Can't Open" << fname;
                exit ( EXIT_FAILURE );
            }

            in.seekg ( 0, std::ios::end );

            int isize = ( int ) in.tellg ();

            in.seekg ( 0, std::ios::beg );

            pProgram = new char[isize + 1];

            if ( ! pProgram )
            {
                std::cout << "Error : OUT of MEMORY\n";
                exit ( EXIT_FAILURE );
            }

            char currChar;

            for ( int i = 0; i < isize; i++ )
            {
                currChar = in.get ();

                if ( currChar == 13 )
                {
                    in.get ();
                    --isize;
                    pProgram[i] = '\n';
                }
                else pProgram[i] = currChar;
            }

            pProgram[isize] = '\0';

            in.close ();
        }
        void CPP_Printusage ( void )
        {
            std::cout << "\nC++17 Lexer, written by DeepuKumar\n";
            std::cout << "Copyright (C) DeepuKumar, All Rights Reserved\n\n";
            std::cout << "Usage: CLEX [ Filename.cpp ]\n\n";
            
            exit ( EXIT_FAILURE );
        }
        void CPP_Lexer ()
        {
            std::ofstream out ( "lex_output.txt" );
            
            char * progPtr = pProgram, c;

            while ( *progPtr )
            {
                c = *progPtr++;

                switch ( c )
                {
                    case ' ' :
                    case '\t':
                    {
                        while ( *progPtr == ' ' || *progPtr == '\t' ) progPtr++;
                        break;
                    }
                    case '\n':
                    {
                        out << "NEWLINE :\t" << ++currLine << "\n";
                        break;
                    }
                    case '(':
                    {
                        out << "LPAREN :\t" << "(\n";
                        break;
                    }
                    case ')':
                    {
                        out << "RPAREN :\t" << ")\n";
                        break;
                    }
                    case '{':
                    {
                        out << "LBRACE :\t" << "{\n";
                        break;
                    }
                    case '}':
                    {
                        out << "RBRACE :\t" << "}\n";
                        break;
                    }
                    case '[':
                    {
                        out << "LBRACKET :\t" << "[\n";
                        break;
                    }
                    case ']':
                    {
                        out << "RBRACKET :\t" << "]\n";
                        break;
                    }
                    case ',':
                    {
                        out << "COMMA :\t" << ",\n";
                        break;
                    }
                    case '?':
                    {
                        out << "OPERATOR :\t" << "?\n";
                        break;
                    }
                    case ';':
                    {
                        out << "SEMICOLON :\t" << ";\n";
                        break;
                    }
                    case '.':
                    {
                        if ( progPtr[0] == '.' && progPtr[1] == '.' )
                        {
                            out << "OPERATOR :\t" << "...\n";
                            progPtr += 2;
                        }
                        else if ( CPP_IsDigit ( progPtr[0] ) )
                        {

                        }
                        else out << "DOT :\t" << ".\n";

                        break;
                    }
                    case '=':
                    {
                        if ( progPtr[0] == '=' )
                        {
                            out << "OPERATOR :\t" << "==\n";
                            progPtr++;
                        }
                        else out << "OPERATOR :\t" << "=\n";

                        break;
                    }
                    case '+':
                    {
                        if ( progPtr[0] == '+' )
                        {
                            out << "OPERATOR :\t" << "++\n";
                            progPtr++;
                        }
                        else if ( progPtr[0] == '=' )
                        {
                            out << "OPERATOR :\t" << "+=\n";
                            progPtr++;
                        }
                        else out << "OPERATOR :\t" << "+\n";

                        break;
                    }
                    case '-':
                    {
                        if ( progPtr[0] == '-' )
                        {
                            out << "OPERATOR :\t" << "--\n";
                            progPtr++;
                        }
                        else if ( progPtr[0] == '=' )
                        {
                            out << "OPERATOR :\t" << "-=\n";
                            progPtr++;
                        }
                        else if ( progPtr[0] == '>' )
                        {
                            out << "OPERATOR :\t" << "->\n";
                            progPtr++;
                        }
                        else out << "OPERATOR :\t" << "-\n";

                        break;
                    }
                    case '*':
                    {
                        if ( progPtr[0] == '=' )
                        {
                            out << "OPERATOR :\t" << "*=\n";
                            progPtr++;
                        }
                        else out << "OPERATOR :\t" << "*\n";

                        break;
                    }
                    case '%':
                    {
                        if ( progPtr[0] == '=' )
                        {
                            out << "OPERATOR :\t" << "%=\n";
                            progPtr++;
                        }
                        else out << "OPERATOR :\t" << "%\n";

                        break;
                    }
                    case '~':
                    {
                        if ( progPtr[0] == '=' )
                        {
                            out << "OPERATOR :\t" << "~=\n";
                            progPtr++;
                        }
                        else out << "OPERATOR :\t" << "~\n";

                        break;
                    }
                    case '#':
                    {
                        out << "NUMBER :\t" << "#\n";
                        break;
                    }
                    case '!':
                    {
                        if ( progPtr[0] == '=' )
                        {
                            out << "OPERATOR :\t" << "!=\n";
                            progPtr++;
                        }
                        else out << "OPERATOR :\t" << "!\n";

                        break;
                    }
                    case '&':
                    {
                        if ( progPtr[0] == '&' )
                        {
                            out << "OPERATOR :\t" << "&&\n";
                            progPtr++;
                        }
                        else out << "OPERATOR :\t" << "&\n";

                        break;
                    }
                    case '^':
                    {
                        if ( progPtr[0] == '=' )
                        {
                            out << "OPERATOR :\t" << "^=\n";
                            progPtr++;
                        }
                        else out << "OPERATOR :\t" << "^\n";

                        break;
                    }
                    case '<':
                    {
                        if ( progPtr[0] == '<' && progPtr[1] == '=' )
                        {
                            out << "OPERATOR :\t" << "<<=\n";
                            progPtr += 2;
                        }
                        else if ( progPtr[0] == '<' )
                        {
                            out << "OPERATOR :\t" << "<<\n";
                            progPtr++;
                        }
                        else if ( progPtr[0] == '=' )
                        {
                            out << "OPERATOR :\t" << "<=\n";
                            progPtr++;
                        }
                        else out << "OPERATOR :\t" << "<\n";

                        break;
                    }
                    case '>':
                    {
                        if ( progPtr[0] == '>' && progPtr[1] == '=' )
                        {
                            out << "OPERATOR :\t" << ">>=\n";
                            progPtr += 2;
                        }
                        else if ( progPtr[0] == '>' )
                        {
                            out << "OPERATOR :\t" << ">>\n";
                            progPtr++;
                        }
                        else if ( progPtr[0] == '=' )
                        {
                            out << "OPERATOR :\t" << ">=\n";
                            progPtr++;
                        }
                        else out << "OPERATOR :\t" << ">\n";

                        break;
                    }
                    case '|':
                    {
                        if ( progPtr[0] == '|' )
                        {
                            out << "OPERATOR :\t" << "||\n";
                            progPtr++;
                        }
                        else if ( progPtr[0] == '=' )
                        {
                            out << "OPERATOR :\t" << "|=\n";
                            progPtr++;
                        }
                        else out << "OPERATOR :\t" << "|\n";

                        break;
                    }
                    case '/':
                    {
                        if ( progPtr[0] == '/' )
                        {
                            out << "SINGLE_LINE_COMMENT\n"; progPtr++;

                            while ( *progPtr && *progPtr != '\n' ) progPtr++;
                        }
                        else if ( progPtr[0] == '*' )
                        {
                            out << "MULTI_LINE_COMMENT\n"; progPtr++;

                            while ( *progPtr && *progPtr != '*' ) progPtr++;

                            if ( *progPtr != '*' ) CPP_Error ( SYNTAX_ERROR );

                            else if ( progPtr[1] != '/' ) CPP_Error ( SYNTAX_ERROR );

                            else progPtr += 2;
                        }
                        else out << "OPERATOR :\t" << "/\n";

                        break;
                    }
                    case '\'':
                    {
                        out << "CHRLIT :\t";

                        if ( *progPtr == '\\' )
                        {
                            switch ( *++progPtr )
                            {
                                case 'a' : out << "'\a'\n"; progPtr++; break;
                                case 'b' : out << "'\b'\n"; progPtr++; break;
                                case 'n' : out << "'\n'\n"; progPtr++; break;
                                case 'r' : out << "'\r'\n"; progPtr++; break;
                                case 't' : out << "'\t'\n"; progPtr++; break;
                                case '\\': out << "'\\'\n"; progPtr++; break;
                                case '\'': out << "\'\n";   progPtr++; break;
                                case '"' : out << "\"\n";   progPtr++; break;
                            }
                        }
                        else
                        {
                            out << *progPtr << "\n";
                            progPtr++;
                        }

                        if ( *progPtr == '\'' )
                            progPtr++;
                        else CPP_Error ( UNBAL_SQUOTE );

                        break;
                    }
                    case '"':
                    {
                        while ( *progPtr && *progPtr != '"' ) out << *progPtr++;

                        if ( *progPtr == '"' )
                            progPtr++;
                        else CPP_Error ( UNBAL_DQUOTE );

                        break;
                    }
                    default:
                    {
                        if ( CPP_IsDigit ( c ) )
                        {
                            progPtr--; char *p = progPtr; int ival; float fval; long lval;

                            while ( CPP_IsDigit ( *p ) ) p++;

                            if ( *p == '.' || *p == 'e' || *p == 'E' )
                            {
                                out << "FLTLIT :\t";

                                int dot = 0, num = 0, e = 0, sign = 0, i = 0; char *temp = progPtr;

                                while ( *temp )
                                {
                                    if ( *temp == '.' )
                                    {
                                        if ( dot ) break;
                                        dot++; temp++;
                                    }
                                    else if ( *temp == 'e' || *temp == 'E' )
                                    {
                                        if ( ! ( dot || num ) || e ) break;
                                        e++; temp++;
                                    }
                                    else if ( *temp == '+' || *temp == '-' )
                                    {
                                        if ( e != 1 || sign ) break;
                                        sign++; temp++;
                                    }
                                    else if ( CPP_IsDigit ( *temp ) )
                                    {
                                        num++; temp++;
                                        if (e) e++;
                                    }
                                    else break;
                                }

                                char *p = progPtr, buf[256];

                                while ( p < temp )
                                    buf[i++] = *p++;
                                buf[i] = '\0';

                                fval = atof ( buf );

                                out << fval << "\n";

                                progPtr = temp;
                            }
                            else
                            {
                                int IsDone = false;

                                if ( *progPtr++ == '0' )
                                {
                                    if ( CPP_IsDigit ( *progPtr ) )
                                    {
                                        sscanf ( progPtr, "%o", &ival );

                                        while ( CPP_IsDigit ( *progPtr ) ) progPtr++;

                                        out << "OCTLIT :\t" << ival << "\n";

                                        IsDone = true;
                                    }
                                    else if ( *progPtr == 'x' || *progPtr == 'X' )
                                    {
                                        sscanf ( ++progPtr, "%x", &ival );

                                        while ( isxdigit ( *progPtr ) ) progPtr++;

                                        out << "HEXLIT :\t" << ival << "\n";

                                        IsDone = true;
                                    }
                                }

                                if ( ! IsDone )
                                {
                                    progPtr--;

                                    ival = atoi ( progPtr );
                                    lval = atol ( progPtr );

                                    while ( CPP_IsDigit ( *progPtr ) ) progPtr++;

                                    if ( *progPtr == 'U' ) progPtr++;

                                    if ( *progPtr == 'l' || *progPtr == 'L' )
                                    {
                                        progPtr++;

                                        out << "LNGLIT :\t" << lval << "\n";
                                    }
                                    else out << "INTLIT :\t" << ival << "\n";
                                }
                            }
                        }
                        else if ( CPP_IsAlpha ( c ) || c == '_' )
                        {
                            progPtr--; char str[256], *pstr; pstr = str; std::string s;

                            while ( CPP_IsAlnum ( *progPtr ) || *progPtr == '_' )
                                *pstr++ = *progPtr++;
                            *pstr = '\0';

                            s = str;

                            if ( CPP_IsKeyword ( s ) )
                            {
                                out << "KEYWORD : " << s << "\n";
                            }
                            else
                            {
                                out << "IDENTIFIER : " << s << "\n";
                            }
                        }
                        else CPP_Error ( INVALID_TOKEN );
                    }
                }
            }
        }
        void CPP_Error ( int err )
        {
            switch ( err )
            {
                case SYNTAX_ERROR:
                     std::cout << "error : syntax error on line : " << currLine << "\n";
                     break;
                case UNBAL_SQUOTE:
                     std::cout << "error : unbalanced single quotes on line : " << currLine << "\n";
                     break;  
                case UNBAL_DQUOTE:
                     std::cout << "error : unbalanced double quotes on line : " << currLine << "\n";
                     break;
                case INVALID_TOKEN:
                     std::cout << "error : invalid character in source file on line : " << currLine << "\n";
                     break;
            }
            
            exit ( EXIT_FAILURE );
        }
};

int main ( int argc, char ** argv )
{
    Lexer lexer;

    lexer.CPP_CommandLine ( argc, argv );

    lexer.CPP_BuildupKeywordTable ();

    lexer.CPP_ProgramLoader ( argv[1] );

    lexer.CPP_Lexer ();

    return EXIT_SUCCESS;
}
