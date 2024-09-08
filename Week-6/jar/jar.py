# Jar Management Project
# This program simulates managing a jar where users
# can add or remove coins and check the total value of coins in the jar.

class Jar:
    def __init__(self, capacity=12):
        self._capacity = capacity
        if capacity < 0:
            raise ValueError("Number can not be negative")
        self._cookies = 3
        return

    def __str__(self):
        return '🍪' * self._cookies

    def deposit(self, n):
        if self._cookies + n > self._capacity:
            raise ValueError("Too many cookies")
        self._cookies += n

    def withdraw(self, n):
        if n > self._cookies:
            raise ValueError("Too less cookies")
        self._cookies -= n

    @property
    def capacity(self):
        return self._capacity

    @property
    def size(self):
        return n


def main():
    jar = Jar()
    jar.deposit(2)
    print(str(jar))
    jar.withdraw(4)
    print(str(jar))


main()
