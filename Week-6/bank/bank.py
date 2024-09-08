def main():
    s = input("Greeting: ")
    s = s.lower()
    if s == "hey" or s == "how you doing?":
        print("$20")
    elif s == "what's happening?" or s == "what's up?":
        print("$100")
    else:
        print("$0")

main()
