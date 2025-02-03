#!/usr/bin/env python3
import pytest

class TestExample:
    @classmethod
    def setup_class(self):
        print("Oneoff Setup before suite ...")
    
    @classmethod
    def teardown_class(self):
        print("Oneoff teardown after suite ...")
    
    def test_addition(self):
        assert 1 + 1 == 2
    
    def test_subtraction(self):
        assert 3 - 1 == 2
