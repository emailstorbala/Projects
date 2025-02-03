#!/usr/bin/env python3
import logging

logger = logging.getLogger(__name__)


def my_function():
    logger.debug("Debugging info")
    logger.info("Function started")
    logger.warning("This is a warning message")
    logger.error("Something went wrong!")


class TestExample:
    def setup_class(self):
        print("Oneoff Setup before suite ...")

    def teardown_class(self):
        print("Oneoff teardown after suite ...")

    def setup_method(self, method):
        print("Setup before each test ...")

    def teardown_method(self, method):
        print("Teardown after each test ...")

    def test_addition(self, caplog):
        with caplog.at_level(logging.INFO):  # Capture logs at INFO level and above
            my_function()
        # Print logs for debugging
        print(caplog.text)
        assert 1 + 1 == 2

    def test_subtraction(self, caplog):
        with caplog.at_level(logging.INFO):  # Capture logs at INFO level and above
            my_function()
        print(caplog.text)
        assert 3 - 1 == 2
