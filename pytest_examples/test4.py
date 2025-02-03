#!/usr/bin/env python3

class TestExample:
    def setup_class(self):
        print("Oneoff Setup before suite ...")

    def teardown_class(self):
        print("Oneoff teardown after suite ...")

    def setup_method(self, method):
        print("Setup before each test ...")

    def teardown_method(self, method):
        print("Teardown after each test ...")

    def test_addition(self):
        assert 1 + 1 == 2

    def test_subtraction(self):
        assert 3 - 1 == 2
