import pytest
import logging


@pytest.hookimpl(tryfirst=True)
def pytest_runtest_setup(item):
    """Set up a unique log file for each test."""
    test_name = item.nodeid.replace("/", "_").replace("::", "_")  # Unique name
    log_file = f"logs/{test_name}.log"

    # Configure a test-specific logger
    logger = logging.getLogger()
    logger.handlers = []  # Clear existing handlers to avoid duplicates

    file_handler = logging.FileHandler(log_file, mode="w")
    formatter = logging.Formatter("%(asctime)s [%(levelname)s] %(message)s")
    file_handler.setFormatter(formatter)
    file_handler.setLevel(logging.DEBUG)  # Capture all levels

    logger.addHandler(file_handler)

    # Ensure logs are captured in pytest
    logging.getLogger().setLevel(logging.DEBUG)
