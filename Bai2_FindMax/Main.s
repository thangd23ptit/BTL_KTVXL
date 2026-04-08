        AREA RESET, CODE, READONLY
        ENTRY

START
        LDR     R0, =0x20008000
        MOV     R1, #512

        LDR     R5, [R0]
        MOV     R6, R5

        ADD     R0, R0, #4
        SUB     R1, R1, #1

LOOP
        CMP     R1, #0
        BEQ     DONE

        LDR     R2, [R0]

        CMP     R2, R5
        BGT     UPDATE1

        CMP     R2, R6
        BGT     UPDATE2

NEXT
        ADD     R0, R0, #4
        SUB     R1, R1, #1
        B       LOOP

UPDATE1
        MOV     R6, R5
        MOV     R5, R2
        B       NEXT

UPDATE2
        MOV     R6, R2
        B       NEXT

DONE
        B       DONE

        END