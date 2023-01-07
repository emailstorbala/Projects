#!/usr/bin/env python3
"""
Program to illustrate data classes
"""
import sys
from dataclasses import dataclass

@dataclass
class Person:
    """
    Person class
    """
    name: str
    age: int
    address: str

def main():
    """
    Main function
    """
    person = Person(name="Balamurugan", age=39, address="Tamilnadu")
    print(person)

if __name__ == '__main__':
    sys.exit(main())
