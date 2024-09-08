from pyfiglet import Figlet
import sys

# Figlet Project
# This project outputs text in different fonts using the FIGlet library.
# If no font is provided via command-line arguments, a random font is selected.
# If a font is provided (using -f or --font), it will display the text in the specified font.
# If invalid arguments are given, the program exits with an error message.


def main():
    figlet = Figlet()
    if len(sys.argv) == 1:
        s = input("Input: ")
        print("Output: ")
        print(figlet.renderText(s))
    elif len(sys.argv) == 3 and (sys.argv[1] == "-f" or sys.argv[1] == "--font"):
        f = sys.argv[2]
        avaible_fonts = figlet.getFonts()

        if f in avaible_fonts:
           f = figlet.setFont(font=f)
           s = input("Input: ")
           print(figlet.renderText(s))
        else:
            print("Invalid usage")
            sys.exit(1)
    else:
        print("Invalid usage")
        sys.exit(1)

main()
