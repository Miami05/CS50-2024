from cs50 import get_float


def main():
    while True:
        n = get_float("Change: ")
        if n > 0:
            break
    n = round(n * 100)
    quarters = calculate_quarters(n)
    n = n - (quarters * 25)

    dimes = calculate_dimes(n)
    n = n - (dimes * 10)

    nickels = calculate_nickels(n)
    n = n - (nickels * 5)

    pennies = calculate_pennies(n)
    n = n - (pennies * 1)

    sum = quarters + dimes + nickels + pennies
    print(sum)


def calculate_quarters(n):
    count = 0
    while n >= 25:
        count += 1
        n -= 25
    return (count)


def calculate_dimes(n):
    count = 0
    while (n >= 10):
        count += 1
        n -= 10
    return (count)


def calculate_nickels(n):
    count = 0
    while (n >= 5):
        count += 1
        n -= 5
    return (count)


def calculate_pennies(n):
    count = 0
    while (n >= 1):
        count += 1
        n -= 1
    return (count)


main()
