DATA	SEGMENT
	A DB 07H
	B DB 0
DATA	ENDS

CODE	SEGMENT
	ASSUME CS:CODE,DS:DATA
START:	MOV AX, DATA
	MOV DS, AX
	MOV SI, OFFSET A
	MOV DI, OFFSET B
	MOV AL, [SI]
	MUL AL
	MOV [DI], AL
	MOV DL, [DI]
	AND DL, 0F0H
	ROR DL, 4
	ADD DL, 30H
	MOV AH, 02H
	INT 21H
	MOV DL, [DI]
	AND DL, 0FH
	ADD DL, 30H
	MOV AH, 02H
	INT 21H
	MOV DL, 48H
	MOV AH, 02H
	INT 21H
	MOV AX, 4C00H
	INT 21H
CODE	ENDS
	END START