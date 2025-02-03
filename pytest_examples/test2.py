#!/usr/bin/env python3
import pytest

class TestExample:
    def setup_method(self, method):
        print("Setup before each test method")
    
    def teardown_method(self, method):
        print("Teardown after each test method")
    
    def test_addition(self):
        assert 1 + 1 == 2
    
    def test_subtraction(self):
        assert 3 - 1 == 2
