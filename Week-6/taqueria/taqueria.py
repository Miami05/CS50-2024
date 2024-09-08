# Taqueriea Project
# This program is designed to simulate an order system for a taquerie (taco shop).
# Users can select items from the menu, and the program will track their order and calculate the total.
# It includes features like customizing tacos, adding/removing items, and calculating taxes.


menu = {
    "Baja Taco": 4.25,
    "Burrito": 7.50,
    "Bowl": 8.50,
    "Nachos": 11.00,
    "Quesadilla": 8.50,
    "Super Burrito": 8.50,
    "Super Quesadilla": 9.50,
    "Taco": 3.00,
    "Tortilla Salad": 8.00
}

def main():
    total = 0
    try:
        while True:
            items = input("Items: ").title()
            if items in menu:
                total += menu[items]
                print(f"Total: ${total:.2f}")
            else:
                pass
    except EOFError:
        print()

main()
