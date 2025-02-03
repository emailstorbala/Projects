#!/usr/bin/env python3

import pytest
import logging

def setup_function(function):
    print("setting up...", function)

def teardown_function(function):
    print("teardown ...", function)

def test_func1():
    assert False
