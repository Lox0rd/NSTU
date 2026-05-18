#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ND 10
#define NOK 12252240  //НОК для финальной проверки



// long long FindNok(long long a, long long b) {
//     long long temp, gcd;
//     long long orig_a = a, orig_b = b;
//     while (b != 0) {
//         temp = b;
//         b = a % b;
//         a = temp;
//     }
//     gcd = a;
//     return (orig_a * orig_b) / gcd;
// }


// long long FindNok_in_range(long long start, long long end) {
//     if (start > end) {
//         long long temp = start;
//         start = end;
//         end = temp;
//     }

//     long long result = start;
//     for (long long i = start + 1; i <= end; i++) {
//         result = FindNok(result, i);
//     }
//     return result;
// }


long long Nok(long long x, long long y) {
    if (y == 0) {
        return x;
    }
    return Nok(y, x % y);
}

long long Nok_two(long long x, long long y) {
    return (x / Nok(x, y)) * y;
}

long long Nok_range(int a, int b) {
    if (a == b) {
        return a;
    }
    
    long long prev_lcm = Nok_range(a, b - 1);
    return Nok_two(prev_lcm, b);
}




//Генерации перестановок
void generatePer(int digits[], int start, int end, long long *result) {
    if (start == end) {
        //Преобразуем массив цифр в число
        long long num = 0;
        for (int i = 0; i < ND; i++) {
            num = num * 10 + digits[i];
        }
        

        if (digits[0] != 0 && num % Nok_range(2, 18) == 0) {
            *result = num;
            return;
        }
    } else {
        for (int i = start; i <= end; i++) {
            //Меняем местами цифры
            int temp = digits[start];
            digits[start] = digits[i];
            digits[i] = temp;
            
            //Рекурсивный вызов
            generatePer(digits, start + 1, end, result);
            
            //Возвращаем цифры на место
            temp = digits[start];
            digits[start] = digits[i];
            digits[i] = temp;
        }
    }
}

int main() {
    int digits[ND] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    long long result = -1;
    
    printf("Поиск числа из цифр 0-9, делящегося на все числа от 2 до 18...\n");
    printf("Найденый НОК: %lld\n", Nok_range(2, 18));
    generatePer(digits, 0, ND - 1, &result);
    
    if (result != -1) {
        printf("Найдено число: %lld\n", result);
        //Доп проверка ручной НОК
        printf("Результат деления на НОК: %lld %% %lld = %lld",result, Nok_range(2, 18), result % NOK);
    } else {
        printf("Число не найдено.\n");
    }
    
    return 0;
}
