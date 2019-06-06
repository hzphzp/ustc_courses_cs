DATA    SEGMENT 
		STA DW 8720H
DATA    ENDS
                                              
                                              
CODE    SEGMENT
        ASSUME CS:CODE,DS:DATA
START:  MOV AX, DATA
        MOV DS, AX
        MOV AX, 0B000H
        MOV ES, AX
        MOV SI, STA 
        MOV ES:[SI], 'X'
AGAIN:	MOV AH, 0H
		INT 16H
		CMP AH, 48H
		JZ UP
		CMP AH, 50H
		JZ DOWN
		CMP AH, 4DH
		JZ RIGHT
		CMP AH, 4BH
		JZ LEFT
		CMP AH, 1CH
		JZ FINAL
		JMP NEXT
UP:		SUB SI, 0A0H
		MOV ES:[SI], 'X'
		JMP NEXT
DOWN:	ADD SI, 0A0H
		MOV ES:[SI], 'X'
		JMP NEXT
RIGHT:	ADD SI, 02H
		MOV ES:[SI], 'X'
		JMP NEXT
LEFT:	SUB SI, 02H
		MOV ES:[SI], 'X'
NEXT:	JMP AGAIN
FINAL:	MOV AX, 4C00H
        INT 21H
CODE    ENDS
        END START