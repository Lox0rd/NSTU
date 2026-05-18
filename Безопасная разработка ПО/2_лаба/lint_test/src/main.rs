//#![allow(warnings)]
use std::collections::HashSet;

fn main() {
    let numbers = [1, 2, 3, 4, 5, 5, 6, 7, 8, 9, 10];

    let mut has_duplicates = false;
    for i in 0..numbers.len() {
        for j in (i + 1)..numbers.len() {
            if numbers[i] == numbers[j] {
                has_duplicates = true;
                break;
            }
        }
        if has_duplicates {
            break;
        }
    }

    if has_duplicates {
        println!("Массив содержит дубликаты");
    } else {
        println!("Дубликатов нет");
    }

    let useless = 42;
    println!("Значение бесполезной переменной: {}", useless_variable);

    let sum: i32 = 0;
    for num in &numbers {
        //let num_as_i32: i32 = *num as i32;
        sum += num_as_i32;
    }

    println!("Сумма элементов: {}", sum);

    let is_empty = numbers.is_empty();
    if is_empty == true {
        println!("Массив пуст");
    } else {
        println!("Массив не пуст");
    }

    let user_input = "admin'; DROP TABLE users; --";
    let sql_query = format!(
        "SELECT * FROM users WHERE username = '{}'",
        user_input
    );

    println!("SQL‑запрос: {}", sql_query);
}
