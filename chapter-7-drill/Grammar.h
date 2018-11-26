#pragma once

/*
Calculation:
    Statement
    Print
    Quit
    Calculation Statement
Statement:
    Declaration
    Expression
Declaration:
    "let" Name "=" Expression
Expression:
    Expression + Term
    Expression - Term
	Term
Term:
    Primary
    Term * Primary
    Term / Primary
    Term % Primary
Primary:
    Number
    "(" Expression ")"
    - Primary
    + Primary
    sqrt(Expression)
    pow(Expression, Expression)
Number:
    floating-point-literal
*/