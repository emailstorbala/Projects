#!/usr/bin/env python3
import logging


class TestExample:
    logger = logging.getLogger(__name__)

    def setup_class(self):
        print("Oneoff Setup before suite ...")

    def teardown_class(self):
        print("Oneoff teardown after suite ...")

    def setup_method(self, method):
        print("Setup before each test ...")

    def teardown_method(self, method):
        print("Teardown after each test ...")

    def test_addition(self):
        self.logger.info("I am inside test_addition")
        # Print logs for debugging
        assert 1 + 1 == 2

    def test_subtraction(self):
        self.logger.info("I am inside test_subtraction")
        assert 3 - 1 == 2
