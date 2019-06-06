DATA    SEGMENT 
		BUFF DB "I am HUANGzp", "$"
		COUNT EQU $-BUFF
DATA    ENDS

CODE    SEGMENT 
MAIN	PROC FAR
        ASSUME CS:CODE,DS:DATA
START:  MOV AX, DATA
        MOV DS, AX
        MOV SI, OFFSET BUFF 
        MOV CX, COUNT
AGAIN:	MOV AL, [SI]
		CALL TOLA
		MOV [SI], AL
		INC SI
		LOOP AGAIN 
		MOV AH, 09H
		MOV DX, OFFSET BUFF
		INT 21H
		MOV AX, 4C00H
		INT 21H
MAIN	ENDP
        
;这个程序判断AL里面的ASIIC字符是否是小写字符,如果是小写，则将它改成大写
;使用了寄存器:AL
;入口:AL		出口:AL 
TOLA	PROC FR
		PUSHF
		CMP AL, 'a'
		JL FINAL
		CMP AL, 'z'
		JG FINAL
		SUB AL, 20H
FINAL:	POPF
		RET
TOLA	ENDP 

CODE	ENDS
		END MAIN
		