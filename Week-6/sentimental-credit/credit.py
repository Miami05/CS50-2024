from cs50 import get_int


def main():
    while True:
        num = get_int("Number: ")
        if (num > 0):
            break
    credit = calculate_checksum(num)
    if (credit == 0):
        card_type(num)
    else:
        print("INVALID")


def calculate_checksum(num):
    sum_even = 0
    sum_odd = 0
    is_even_position = False
    while num > 0:
        digit = num % 10
        if is_even_position:
            digit *= 2
            if digit > 9:
                digit = (digit // 10) + (digit % 10)
            sum_even += digit
        else:
            sum_odd += digit
        num //= 10
        is_even_position = not is_even_position
    total_sum = sum_even + sum_odd
    if total_sum % 10 == 0:
        return (0)
    return (1)


def card_type(num):
    length = card_len(num)

    if length < 13:
        print("INVALID")
        return

    first_two_digits = card_digits(num, 2)
    first_digit = first_two_digits // 10

    if length == 16 and 51 <= first_two_digits <= 55:
        print("MASTERCARD")
        return

    if length == 15 and (first_two_digits == 34 or first_two_digits == 37):
        print("AMEX")
        return

    if (length == 13 or length == 16) and first_digit == 4:
        print("VISA")
        return

    print("INVALID")


def card_len(num):
    len = 0
    while num != 0:
        len += 1
        num //= 10
    return (len)


def card_digits(num, n):
    while num >= 10 ** n:
        num //= 10
    return (num)


main()
