#!/bin/bash

cd build && cmake .. && make && cd .. && build/src/blocks
