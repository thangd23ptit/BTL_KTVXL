#include <stdio.h>
#include <stdint.h>

// Khai bao ham Assembly
// Truyen vao dia chi mang (R0) va so luong phan tu (R1)
extern void FIND_MAX_VALUES(uint32_t *arr, uint32_t n);

// Gia su ket qua tra ve duoc luu vao cac bien toan cuc de de kiem tra
uint32_t max1_result; // Tuong ung R5
uint32_t max2_result; // Tuong ung R6

int main(void) {
    // Khoi tao mang tai vung nho (mo phong dia chi 0x20008000)
    uint32_t n = 512; // 2048 bytes / 4 bytes moi phan tu
    uint32_t arr[512];
    
    // Dien du lieu mau vao mang
    for (int i = 0; i < n; i++) {
        arr[i] = i * 2; // Ví d?: 0, 2, 4, ..., 1022
    }
    // Ghi de mot so gia tri de kiem tra Max
    arr[10] = 5000; 
    arr[50] = 4000;

    // Goi ham Assembly
    FIND_MAX_VALUES(arr, n);

    // Sau khi chay xong, R5 va R6 se chua ket qua (co the quan sat qua Debugger)
    while(1);
    return 0;
}