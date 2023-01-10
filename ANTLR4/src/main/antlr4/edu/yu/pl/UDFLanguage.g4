grammar UDFLanguage;

/* Start Variable */
userField : numExpr  # NumExpression
          | strExpr  # StrExpression
          | boolExpr # BoolExpression
          | EOF      # EndOfInput
          ;

// Possible expressions in order of precedence
numExpr : '-' numExpr                              # NegNumExpr
        | left=numExpr op=('*'|'/') right=numExpr  # MulDiv
        | left=numExpr op=('+'|'-') right=numExpr  # AddSub
        | '(' numExpr ')'                          # ParensNumExpr
        | 'ABS' '(' numExpr ')'                    # AbsValue
        | FIELD_NAME                               # NumField
        | NUMBER_CONSTANT                          # NumConstant
        ;

strExpr : left=strExpr '+' right=strExpr                          # Concat
        | '(' strExpr ')'                                         # ParensStrExpr
        | 'STR' '(' numExpr ')'                                   # StrValue
        | 'JOIN' '(' delim=('-'|'/') ',' strExpr ',' listExpr ')' # JoinValue
        | 'IF' '(' boolExpr ',' true=strExpr ',' false=strExpr ')'# IfValue
        | STRING_CONSTANT                                         # StrConstant
        | FIELD_NAME                                              # StrField
        ;

boolExpr : left=boolExpr 'AND' right=boolExpr                         # AndOp
         | left=boolExpr 'OR' right=boolExpr                          # OrOp
         | left=numExpr op=('<'|'<='|'<>'|'='|'>='|'>') right=numExpr # NumCompare
         | left=strExpr op=('<'|'<='|'<>'|'='|'>='|'>') right=strExpr # StrCompare
         | strExpr 'IN' '(' listExpr ')'                              # InValue
         | 'NOT' '(' boolExpr ')'                                     # NotValue
         | BOOLEAN_CONSTANT                                           # BoolConstant
         ;

listExpr : strExpr ',' listExpr                    # ListHead
         | strExpr                                 # ListTail
         ;

/* Tokens */
NUMBER_CONSTANT : [0-9]+ ('.' [0-9]+)?;
STRING_CONSTANT : '\'' [a-zA-Z0-9_][a-zA-Z0-9_]* '\'';
BOOLEAN_CONSTANT: 'TRUE'|'True'|'true'|'FALSE'|'False'|'false';
FIELD_NAME      : [0-9_]*[a-zA-Z_][a-zA-Z0-9_]*;                // variable field name

COMMENT : '//' ~[\r\n]* -> skip;    // skip the rest of the line after comment (//)
WHITE_SPACE: [ \t\n]+ -> skip;      // skip spaces, tabs and newline characters