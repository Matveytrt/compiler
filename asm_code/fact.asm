PUSH 4
POPR RAX

;;OP - _END_STATEMENT_

;;OP - _FUNC_DECLARE_
JMP :end_Fact_0x7c091cfe0090
:Fact
PUSHR RAX
PUSH 0
ADD
POPR AX
POPM [AX]
;popped in var [n]

;;OP - _END_STATEMENT_

;;OP - _IF_

;;OP - _MATH_EQUAL_

;;VAR - n, table_idx [0]
PUSHR RAX
PUSH 0
ADD
POPR AX
PUSHM [AX]
;pushed var [n]

;;NUM = 0
PUSH 0
JNE :end_if_0x7c091cfe0150

;;OP - _END_STATEMENT_

;;OP - _RETURN_

;;NUM = 1
PUSH 1
RET
:end_if_0x7c091cfe0150

;;OP - _END_STATEMENT_

;;OP - _ASSIGNMENT_

;;NUM = 1
PUSH 1
PUSHR RAX
PUSH 1
ADD
POPR AX
POPM [AX]
;popped in var [f]
;assign end

;;OP - _END_STATEMENT_

;;OP - _ASSIGNMENT_

;;OP - _MATH_MUL_

;;FUNC - Fact st_idx = 0, end_idx = 1

;;OP - _MATH_SUB_

;;VAR - n, table_idx [0]
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
PUSH 2
ADD
POPR RAX
CALL :Fact
PUSHR RAX
PUSH 2
SUB
POPR RAX

;;VAR - n, table_idx [0]
PUSHR RAX
PUSH 0
ADD
POPR AX
PUSHM [AX]
;pushed var [n]
MUL
PUSHR RAX
PUSH 1
ADD
POPR AX
POPM [AX]
;popped in var [f]
;assign end

;;OP - _END_STATEMENT_

;;OP - _RETURN_

;;VAR - f, table_idx [1]
PUSHR RAX
PUSH 1
ADD
POPR AX
PUSHM [AX]
;pushed var [f]
RET
:end_Fact_0x7c091cfe0090

;;OP - _END_STATEMENT_

;;OP - _ASSIGNMENT_

;;OP - _SCAN_
IN
PUSH 2
POPR AX
POPM [AX]
;popped in var [x]
;assign end

;;OP - _END_STATEMENT_

;;OP - _ASSIGNMENT_

;;FUNC - Fact st_idx = 0, end_idx = 1

;;VAR - x, table_idx [2]
PUSH 2
POPR AX
PUSHM [AX]
;pushed var [x]
CALL :Fact
PUSH 3
POPR AX
POPM [AX]
;popped in var [res]
;assign end

;;OP - _END_STATEMENT_

;;OP - _PRINT_

;;VAR - res, table_idx [3]
PUSH 3
POPR AX
PUSHM [AX]
;pushed var [res]
OUT
HLT
