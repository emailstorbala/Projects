#!/usr/bin/env python3
import logging


class TestCase:
    logger = logging.getLogger(__name__)


class TestSample(TestCase):
    def setup_class(self):
        self.logger.info("Oneoff Setup before suite ...")

    def teardown_class(self):
        self.logger.info("Oneoff teardown after suite ...")

    def setup_method(self, method):
        self.logger.info("Setup before each test ...")

    def teardown_method(self, method):
        self.logger.info("Teardown after each test ...")

    def test_addition(self):
        self.logger.info("I am inside test_addition")
        # Print logs for debugging
        assert 1 + 1 == 2

    def test_subtraction(self):
        self.logger.info("I am inside test_subtraction")
        assert 3 - 1 == 2
