#!/usr/bin/env python3
import logging
import os


class TestCase:
    def setup_logger(cls_name: str):
        """Logger for setup phase (one-off setup before tests)."""
        logger = logging.getLogger("setup_logger")
        logger.setLevel(logging.INFO)

        # Ensure logs directory exists
        os.makedirs("logs", exist_ok=True)

        # Setup log file handler
        oneoff_setup_file = f"logs/{cls_name}_oneoff_setup.log"
        file_handler = logging.FileHandler(oneoff_setup_file, mode="w")
        formatter = logging.Formatter("%(asctime)s [%(levelname)s] [ONEOFF SETUP] %(message)s")
        file_handler.setFormatter(formatter)

        # Attach handler
        logger.addHandler(file_handler)
        return logger

    def teardown_logger(cls_name: str):
        """Logger for setup phase (one-off teardown before tests)."""
        logger = logging.getLogger("teardown_logger")
        logger.setLevel(logging.INFO)

        # Setup log file handler
        oneoff_teardown_file = f"logs/{cls_name}_oneoff_teardown.log"
        file_handler = logging.FileHandler(oneoff_teardown_file, mode="w")
        formatter = logging.Formatter("%(asctime)s [%(levelname)s] [ONEOFF TEARDOWN] %(message)s")
        file_handler.setFormatter(formatter)

        # Attach handler
        logger.addHandler(file_handler)
        return logger

    def get_testlogger(self, method_name):
        """Logger for individual tests."""
        logger = logging.getLogger("test_logger")
        logger.setLevel(logging.DEBUG)

        log_file = f"logs/{self.__class__.__name__}_{method_name}.log"

        # Remove existing handlers to prevent duplicate logs
        for handler in logger.handlers[:]:
            logger.removeHandler(handler)

        # Create new file handler
        file_handler = logging.FileHandler(log_file, mode="a")
        formatter = logging.Formatter("%(asctime)s [%(levelname)s] [TEST] %(message)s")
        file_handler.setFormatter(formatter)

        # Attach handler
        logger.addHandler(file_handler)
        return logger


class TestSample(TestCase):
    def setup_class(self):
        logger = self.setup_logger(self.__name__)
        logger.info("Oneoff Setup before suite ...")

    def teardown_class(self):
        logger = self.teardown_logger(self.__name__)
        logger.info("Oneoff teardown after suite ...")

    def setup_method(self, method):
        self.test_logger = self.get_testlogger(method.__name__)
        self.test_logger.info("Setup before each test ...")

    def teardown_method(self, method):
        self.test_logger.info("Teardown after each test ...")

    def test_addition(self):
        self.test_logger.info("I am inside test_addition")
        # Print logs for debugging
        assert 1 + 1 == 2

    def test_subtraction(self):
        self.test_logger.info("I am inside test_subtraction")
        assert 3 - 1 == 2
