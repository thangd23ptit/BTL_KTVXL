.text
.global FIND_MAX_VALUES    @ Khai bao nhan de file C co the goi den

FIND_MAX_VALUES:
@ Y tuong: Duyet mang 1 lan (Linear Scan). O(n)
@ R0: Chua dia chi bat dau cua mang (arr)
@ R1: So luong phan tu (512)
@ R5: Luu Max 1 (Ket qua 1)
@ R6: Luu Max 2 (Ket qua 2)

    MOV R5, #0             @ Khoi tao Max 1 = 0
    MOV R6, #0             @ Khoi tao Max 2 = 0
    MOV R2, R0             @ Sao chep dia chi bat dau vao R2 (con tro i)
    MOV R11, R1            @ Dung R11 lam bien dem so lan lap

LOOP:
    CMP R11, #0            @ Kiem tra xem da duyet het mang chua
    BEQ END_FUNC           @ Neu R11 == 0 thi thoat
    
    LDR R3, [R2], #4       @ Load gia tri arr[i] vao R3 va tang con tro R2 len 4
    
    CMP R3, R5             @ So sanh gia tri hien tai (R3) voi Max 1 (R5)
    BLS CHECK_MAX2         @ Neu R3 <= R5, nhay den kiem tra Max 2
    
    @ Neu R3 > R5:
    MOV R6, R5             @ Max 2 cu = Max 1 cu
    MOV R5, R3             @ Max 1 moi = R3
    B NEXT_ITER

CHECK_MAX2:
    CMP R3, R6             @ So sanh R3 voi Max 2 (R6)
    BLS NEXT_ITER          @ Neu R3 <= R6, bo qua
    MOV R6, R3             @ Neu R3 > R6, cap nhat Max 2 moi = R3

NEXT_ITER:
    SUB R11, R11, #1       @ Giam bien dem
    B LOOP                 @ Quay lai vong lap

END_FUNC:
    BX LR                  @ Quay ve ham main trong C
