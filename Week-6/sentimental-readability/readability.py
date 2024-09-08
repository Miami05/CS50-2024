def main():
    str = input("Text: ")
    letters = letters_count(str)
    words = words_count(str)
    sentences = sentences_count(str)
    L = letters / words * 100
    S = sentences / words * 100
    result = round(0.0588 * L - 0.296 * S - 15.8)
    print_grades(result)


def letters_count(str):
    count = 0
    for char in str:
        if char.isalpha():
            count += 1
    return (count)


def words_count(str):
    count = 0
    words = 0
    for i in str:
        if not i.isspace():
            if not words:
                count += 1
                words = 1
        else:
            words = 0
    return (count)


def sentences_count(str):
    count = 0
    for i in str:
        if i == "?" or i == "!" or i == ".":
            count += 1
    return (count)


def print_grades(result):
    if result < 1:
        print("Before Grade 1")
    elif result == 1:
        print("Grade 1")
    elif result == 2:
        print("Grade 2")
    elif result == 3:
        print("Grade 3")
    elif result == 4:
        print("Grade 4")
    elif result == 5:
        print("Grade 5")
    elif result == 6:
        print("Grade 6")
    elif result == 7:
        print("Grade 7")
    elif result == 8:
        print("Grade 8")
    elif result == 9:
        print("Grade 9")
    elif result == 10:
        print("Grade 10")
    elif result == 11:
        print("Grade 11")
    elif result == 12:
        print("Grade 12")
    elif result == 13:
        print("Grade 13")
    elif result == 14:
        print("Grade 14")
    elif result == 15:
        print("Grade 15")
    elif result > 15:
        print("Grade 16+")


main()
