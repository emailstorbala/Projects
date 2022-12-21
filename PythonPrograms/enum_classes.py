#!/usr/bin/env python
"""
Program to illustrate enum class
"""
import sys
from enum import Enum, auto
from dataclasses import dataclass

class Role(Enum):
    """
    Role - Enum class
    """

    MANAGER = auto()
    DEVELOPER = auto()
    INTERN = auto()

@dataclass
class Employee:
    """
    Employee class
    """
    name: str
    role: Role
    age: int

def main():
    """
    Main function
    """
    emp = Employee(name="Balamurugan", role=Role.DEVELOPER, age=39)
    print(emp)

if __name__ == '__main__':
    sys.exit(main())
