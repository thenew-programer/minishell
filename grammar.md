<program>           ::= <statement-list>

<statement-list>    ::= <statement> (';' <statement)*

<logical_or>        ::= <statement_list> ('||' <statement_list>)+

<logical_and>       ::= <logical_or> ('&&' <logical_or>)+

<statement>         ::= <command>
                      | <pipeline>
                      | <if_statement>
                      | <while_statement>
                      | <assignment>
                      | <function_def>

<command>           ::= '$' '(' <compound_list> ')' // subshell
                      | WORD <argument_list>? redirection_list?

<argument_list>     ::= WORD*

<redirection_list>  ::= <redirection>*

<redirection>       ::= ('>' | '<' | '<<' | '>>' | '<<-' | '2>' | '2>>' | '1>' | '1>>' | '&>' | '>&' | '2&>1') WORD

<assignment>        ::= NAME '=' WORD

<pipeline>          ::= <command> ('|' <command>)+

<if_statement>      ::= 'if' <compound_list> 'then' <compound_list> ('elif' <compound_list> 'then' <compound_list>)* ('else' <compound_list>)? 'fi'

<while_statement>   ::= 'while' <compound_list> 'do' <compound_list> 'done'

<compound_list>     ::= <statement_list>

<function_def>      ::= NAME '(' ')' ,compound_list>












<program>          ::= <compound_list>

<compound_list>    ::= <list> ('\n' <list>)*

<list>             ::= <pipeline> ((';' | '&' | '\n') <pipeline>)*

<logical_expr>     ::= <pipeline> (('&&' | '||') <pipeline>)*

<pipeline>         ::= <command> ('|' <command>)*

<command>          ::= <simple_command>
                     | <compound_command>
                     | <function_def>

<simple_command>   ::= <assignments>? <word> <arguments>? <redirections>?

<assignments>      ::= <assignment>+

<assignment>       ::= NAME '=' WORD

<arguments>        ::= WORD+

<redirections>     ::= <redirection>+

<redirection>      ::= ('>' | '<' | '<<' | '>>' | '<<-' | '2>' | '2>>' | '1>' | '1>>' | '&>' | '>&' | '2>&1') WORD

<compound_command> ::= <subshell>
                     | <group>
                     | <if_statement>
                     | <while_statement>
                     | <until_statement>
                     | <for_statement>
                     | <case_statement>

<subshell>         ::= '(' <compound_list> ')'

<group>            ::= '{' <compound_list> '}'

<if_statement>     ::= 'if' <compound_list> 'then' <compound_list> ('elif' <compound_list> 'then' <compound_list>)* ('else' <compound_list>)? 'fi'

<while_statement>  ::= 'while' <compound_list> 'do' <compound_list> 'done'

<until_statement>  ::= 'until' <compound_list> 'do' <compound_list> 'done'

<for_statement>    ::= 'for' NAME ('in' <word_list>)? ';'? 'do' <compound_list> 'done'

<word_list>        ::= WORD+

<case_statement>   ::= 'case' WORD 'in' <case_clause>+ 'esac'

<case_clause>      ::= <pattern_list> ')' <compound_list> ';;'

<pattern_list>     ::= WORD ('|' WORD)*

<function_def>     ::= NAME '(' ')' <compound_command>
