DATA    SEGMENT
        V1 DB 31H
        V2 DB 02H
DATA    ENDS

CODE    SEGMENT
MAIN    PROC FAR
        ASSUME CS:CODE, DS,DATA
START:  MOV AL, V1
        ADD AL, V2
        MOV DL, AL
        MOV AH, 02H
        INT 21H
        RET
MAIN    ENDP
CODE    ENDS
        END MAIN