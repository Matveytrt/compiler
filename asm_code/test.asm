PUSH 11
POPR RAX

;;OP - _END_STATEMENT_

;;OP - _FUNC_DECLARE_
JMP :end_Main_0x7bc6e0fe0090
:Main

;;OP - _END_STATEMENT_

;;OP - _ASSIGNMENT_

;;FUNC - Myaufunc st_idx = 1, end_idx = 5

;;OP - _COMMA_

;;OP - _COMMA_

;;OP - _COMMA_

;;NUM = 2
PUSH 2

;;NUM = 4
PUSH 4

;;NUM = 2
PUSH 2

;;NUM = 3
PUSH 3
PUSHR RAX
PUSH 5
ADD
POPR RAX
CALL :Myaufunc
PUSHR RAX
PUSH 5
SUB
POPR RAX
PUSHR RAX
PUSH 0
ADD
POPR AX
POPM [AX]
;popped in var [res]
;assign end

;;OP - _END_STATEMENT_

;;OP - _PRINT_

;;VAR - res, table_idx [0]
PUSHR RAX
PUSH 0
ADD
POPR AX
PUSHM [AX]
;pushed var [res]
OUT

;;OP - _END_STATEMENT_

;;OP - _RETURN_

;;VAR - res, table_idx [0]
PUSHR RAX
PUSH 0
ADD
POPR AX
PUSHM [AX]
;pushed var [res]
RET
:end_Main_0x7bc6e0fe0090

;;OP - _END_STATEMENT_

;;OP - _FUNC_DECLARE_
JMP :end_Myaufunc_0x7bc6e0fe05d0
:Myaufunc
PUSHR RAX
PUSH 0
ADD
POPR AX
POPM [AX]
;popped in var [a]
PUSHR RAX
PUSH 1
ADD
POPR AX
POPM [AX]
;popped in var [b]
PUSHR RAX
PUSH 2
ADD
POPR AX
POPM [AX]
;popped in var [c]
PUSHR RAX
PUSH 3
ADD
POPR AX
POPM [AX]
;popped in var [d]

;;OP - _END_STATEMENT_

;;OP - _ASSIGNMENT_

;;OP - _MATH_SUB_

;;OP - _MATH_ADD_

;;VAR - a, table_idx [1]
PUSHR RAX
PUSH 0
ADD
POPR AX
PUSHM [AX]
;pushed var [a]

;;VAR - b, table_idx [2]
PUSHR RAX
PUSH 1
ADD
POPR AX
PUSHM [AX]
;pushed var [b]
ADD

;;OP - _MATH_MUL_

;;VAR - c, table_idx [3]
PUSHR RAX
PUSH 2
ADD
POPR AX
PUSHM [AX]
;pushed var [c]

;;VAR - d, table_idx [4]
PUSHR RAX
PUSH 3
ADD
POPR AX
PUSHM [AX]
;pushed var [d]
MUL
SUB
PUSHR RAX
PUSH 4
ADD
POPR AX
POPM [AX]
;popped in var [f]
;assign end

;;OP - _END_STATEMENT_

;;OP - _RETURN_

;;VAR - f, table_idx [5]
PUSHR RAX
PUSH 4
ADD
POPR AX
PUSHM [AX]
;pushed var [f]
RET
:end_Myaufunc_0x7bc6e0fe05d0

;;OP - _END_STATEMENT_

;;OP - _FUNC_DECLARE_
JMP :end_Fact_0x7bc6e0fe0bd0
:Fact
PUSHR RAX
PUSH 0
ADD
POPR AX
POPM [AX]
;popped in var [n]

;;OP - _END_STATEMENT_

;;OP - _IF_

;;OP - _MATH_EQ_

;;VAR - n, table_idx [6]
PUSHR RAX
PUSH 0
ADD
POPR AX
PUSHM [AX]
;pushed var [n]

;;NUM = 0
PUSH 0
JNE :end_if_0x7bc6e0fe0c90

;;OP - _END_STATEMENT_

;;OP - _RETURN_

;;NUM = 1
PUSH 1
RET
:end_if_0x7bc6e0fe0c90

;;OP - _END_STATEMENT_

;;OP - _ELSE_
JE :end_else_0x7bc6e0fe0e90

;;OP - _END_STATEMENT_

;;OP - _ASSIGNMENT_

;;NUM = 2
PUSH 2
PUSHR RAX
PUSH 1
ADD
POPR AX
POPM [AX]
;popped in var [a]
;assign end
:end_else_0x7bc6e0fe0e90

;;OP - _END_STATEMENT_

;;OP - _ASSIGNMENT_

;;NUM = 1
PUSH 1
PUSHR RAX
PUSH 2
ADD
POPR AX
POPM [AX]
;popped in var [f]
;assign end

;;OP - _END_STATEMENT_

;;OP - _ASSIGNMENT_

;;OP - _MATH_MUL_

;;FUNC - Fact st_idx = 6, end_idx = 8

;;OP - _MATH_SUB_

;;VAR - n, table_idx [6]
PUSHR RAX
PUSH 0
ADD
POPR AX
PUSHM [AX]
;pushed var [n]

;;NUM = 1
PUSH 1
SUB
PUSHR RAX
PUSH 3
ADD
POPR RAX
CALL :Fact
PUSHR RAX
PUSH 3
SUB
POPR RAX

;;VAR - n, table_idx [6]
PUSHR RAX
PUSH 0
ADD
POPR AX
PUSHM [AX]
;pushed var [n]
MUL
PUSHR RAX
PUSH 2
ADD
POPR AX
POPM [AX]
;popped in var [f]
;assign end

;;OP - _END_STATEMENT_

;;OP - _RETURN_

;;VAR - f, table_idx [8]
PUSHR RAX
PUSH 2
ADD
POPR AX
PUSHM [AX]
;pushed var [f]
RET
:end_Fact_0x7bc6e0fe0bd0

;;OP - _END_STATEMENT_

;;OP - _ASSIGNMENT_

;;OP - _SCAN_
IN
PUSH 9
POPR AX
POPM [AX]
;popped in var [x]
;assign end

;;OP - _END_STATEMENT_

;;OP - _ASSIGNMENT_

;;FUNC - Fact st_idx = 6, end_idx = 8

;;VAR - x, table_idx [9]
PUSH 9
POPR AX
PUSHM [AX]
;pushed var [x]
CALL :Fact
PUSH 10
POPR AX
POPM [AX]
;popped in var [res]
;assign end

;;OP - _END_STATEMENT_

;;OP - _PRINT_

;;VAR - res, table_idx [10]
PUSH 10
POPR AX
PUSHM [AX]
;pushed var [res]
OUT
HLT
