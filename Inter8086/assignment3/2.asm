DATA    SEGMENT
		YEAR DW 0, 0
		MONTH DB 0
		DAY DB 0 
		WEEK DB 0
		HOUR DB 0
		MINITE DB 0
		SECOND60 DB 0 
		SECOND100 DB 0
		PHRASES DB "Sunday   ", "$" , "Monday   ", "$" , "Tuesday  ", "$" , "Wednesday", "$" , "Thursday ", "$" , "Friday   ", "$" , "Saturday ", "$" 
		
DATA    ENDS

CODE    SEGMENT
        ASSUME CS:CODE,DS:DATA
START: 	MOV AX, DATA
        MOV DS, AX
        ;TO GET THE DATE
        MOV AH, 2AH
        INT 21H
        MOV YEAR, CX
        MOV MONTH, DH
        MOV DAY, DL
        MOV WEEK, AL
        ;TO GET THE TIME
        MOV AH, 2CH
        INT 21H
        MOV HOUR, CH
        MOV MINITE, CL
        MOV SECOND60, DH
        MOV SECOND100, DL  
        ;OUTPUT THE RESULT 
        ;YEAR
        ;FIRST
        MOV AX, YEAR
        XOR DX, DX
        MOV BX, 1000
        DIV BX 
        ;PROTECT THE REMAIN
        MOV CX, DX 
        ADD AL, 30H
        MOV DL, AL
        MOV AH, 02H
        INT 21H 
        ;SECOND
        MOV AX, CX
        XOR DX, DX
        MOV BL, 100
        DIV BL  
        MOV CL, AH
        ADD AL, 30H 
        MOV DL, AL 
        MOV AH, 02H
        INT 21H
        ;THERD
        MOV AL, CL
        MOV AH, 0
        MOV BL, 10
        DIV BL
        MOV CL, AH
        ADD AL, 30H
        MOV DL, AL
        MOV AH, 02H
        INT 21H
        ;FORTH
        MOV AL, CL
        ADD AL, 30H
        MOV AH, 02H
        MOV DL, AL
        INT 21H 
        ;FINISH THE YEAR AND FORM A GAP
        MOV DL, '.'
        MOV AH, 02H
        INT 21H
        ;MONTH
        ;FIRST
        MOV AL, MONTH
        MOV AH, 0
        MOV BL, 10
        DIV BL
        MOV CL, AH
        ADD AL, 30H
        MOV DL, AL
        MOV AH, 02H
        INT 21H
        ;SECOND
        MOV AL, CL
        ADD AL, 30H
        MOV AH, 02H
        MOV DL, AL
        INT 21H 
        ;FINISH THE MONTH AND FORM A GAP
        MOV DL, '.'
        MOV AH, 02H
        INT 21H
        ;DAY
        ;FIRST
        MOV AL, DAY
        MOV AH, 0
        MOV BL, 10
        DIV BL
        MOV CL, AH
        ADD AL, 30H
        MOV DL, AL
        MOV AH, 02H
        INT 21H
        ;SECOND
        MOV AL, CL
        ADD AL, 30H
        MOV AH, 02H
        MOV DL, AL
        INT 21H
        ;FINISH THE DAY AND FORM A GAP
        MOV DL, ' '
        MOV AH, 02H
        INT 21H 
        ;HOUR
        ;FIRST
        MOV AL, HOUR
        MOV AH, 0
        MOV BL, 10
        DIV BL
        MOV CL, AH
        ADD AL, 30H
        MOV DL, AL
        MOV AH, 02H
        INT 21H
        ;SECOND
        MOV AL, CL
        ADD AL, 30H
        MOV AH, 02H
        MOV DL, AL
        INT 21H
        ;FINISH THE HOUR AND FORM A GAP
        MOV DL, ':'
        MOV AH, 02H
        INT 21H
        ;MINITE
        ;FIRST
        MOV AL, MINITE
        MOV AH, 0
        MOV BL, 10
        DIV BL
        MOV CL, AH
        ADD AL, 30H
        MOV DL, AL
        MOV AH, 02H
        INT 21H
        ;SECOND
        MOV AL, CL
        ADD AL, 30H
        MOV AH, 02H
        MOV DL, AL
        INT 21H
        ;FINISH THE MINITE AND FORM A GAP
        MOV DL, ':'
        MOV AH, 02H
        INT 21H
        ;SECOND 
        ;FIRST
        MOV AL, SECOND60
        MOV AH, 0
        MOV BL, 10
        DIV BL
        MOV CL, AH
        ADD AL, 30H
        MOV DL, AL
        MOV AH, 02H
        INT 21H
        ;SECOND
        MOV AL, CL
        ADD AL, 30H
        MOV AH, 02H
        MOV DL, AL
        INT 21H
        ;FINISH THE SECONDE60 AND FORM A GAP
        MOV DL, '.'
        MOV AH, 02H
        INT 21H
        ;FIRST
        MOV AL, SECOND100
        MOV AH, 0
        MOV BL, 10
        DIV BL
        MOV CL, AH
        ADD AL, 30H
        MOV DL, AL
        MOV AH, 02H
        INT 21H
        ;SECOND
        MOV AL, CL
        ADD AL, 30H
        MOV AH, 02H
        MOV DL, AL
        INT 21H
        ;FINISH THE SECONDE100 AND FORM A GAP
        MOV DL, ' '
        MOV AH, 02H
        INT 21H
        ;WEEK
        MOV AL, WEEK  
        MOV BL, 10
        MUL BL
        XOR AH, AH 
        MOV DX, OFFSET PHRASES 
        ADD DX, AX
        MOV AH, 09H 
        INT 21H
        
SUN:	              
        
		MOV AX, 4C00H
        INT 21H
CODE    ENDS
        END START