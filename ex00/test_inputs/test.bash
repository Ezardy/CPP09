#!/bin/bash

echo 'NO ARGUMENTS'
../btc
echo

echo 'EXTRA ARGUMENTS'
../btc default.csv empty.csv
echo

echo 'NON-EXISTANT FILE'
../btc nonexistant.csv
echo

echo 'NO HEADER'
../btc no_header.csv
echo

echo 'INVALID HEADER DELIMETER'
../btc invalid_delimeter.csv
echo

echo 'SPACE BEFORE HEADER'
../btc space_before_header.csv
echo

echo 'SPACE AFTER HEADER'
../btc space_after_header.csv
echo

echo 'ERRORNESS ENTRIES'
../btc various_errorness_entries.csv
echo

echo 'TEST INPUT FROM THE EXERCISE'
../btc default.csv