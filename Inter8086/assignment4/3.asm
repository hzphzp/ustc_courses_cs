DATA    SEGMENT
		TABLE DB '  1', '  4','  9', ' 16',' 25',' 36',' 49',' 64',' 81','100','121','144','169','196','225'
DATA    ENDS

CODE    SEGMENT
        ASSUME CS:CODE,DS:DATA
START:  MOV AX, DATA
        MOV DS, AX
        ;INPUT
AGAIN:  MOV AH, 01H
        INT 21H 
        AND AL, 0FH
        MOV CL, 10
        MUL CL
        MOV CL, AL
        MOV AH, 01H
        INT 21H
        AND AL, 0FH
        ADD AL, CL
        CMP AL, 00H
        JZ 	FINAL  
        MOV CL, 03H
        MUL CL
        SUB AL, 3
        MOV CL, AL 
        MOV AH, 02H
        MOV DL, 1AH;AFTER THAT AL CHANGED
        INT 21H
        MOV AL, CL
        MOV BX, OFFSET TABLE
        XLAT
        MOV DL, AL
        MOV AH, 02H
        INT 21H
        MOV AL, CL
        INC AL
        MOV BX, OFFSET TABLE
        XLAT
        MOV DL, AL
        MOV AH, 02H
        INT 21H 
        MOV AL, CL
        INC AL
        INC AL
        MOV BX, OFFSET TABLE
        XLAT
        MOV DL, AL
        MOV AH, 02H
        INT 21H
        MOV DL, 0DH
        MOV AH, 02H
        INT 21H
        MOV DL, 0AH
        MOV AH, 02H
        INT 21H
        JMP AGAIN
FINAL:	MOV AX, 4C00H
        INT 21H
CODE    ENDS
        END START