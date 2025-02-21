#!/bin/bash

# Compile my program 
make

# Run Tests
echo "Tests commencing..."

run_test(){
    input="$1"
    expected_output="$2"
    actual_output=$(echo "$input" | ./number_to_words)

    if [ "$actual_output" == "$expected_output" ]; then
        echo "SUCCESS"
    else 
        echo "FAILED: Input '$input' provided incorrect output."
        echo "Expected: $expected_output"
        echo "Got:      $actual_output"
    fi
}

# Single Test Cases 
run_test "77777" "77777 = seven hundred seventy-seven dollars and seventy-seven cents"
run_test "15" "15 = fifteen cents"
run_test "199" "199 = one dollar and ninety-nine cents"
run_test "100" "100 = one dollar"
run_test "155021" "155021 = one thousand five hundred fifty dollars and twenty-one cents"
run_test "10000" "10000 = one hundred dollars"
run_test "100000000" "100000000 = one million dollars"
run_test "100000000000" "100000000000 = one billion dollars"

echo "Tests completed."