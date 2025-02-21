# Tests cases for number_to_words.c (Converts dollar/cent amount integer into words)

# Test Case 1: Command Line Arguments After the Program Name

### Description: 
A test to verify that program will not accept any command line arguments

### Input: 
./number_to_words

./number_to_words 1

### Expected Output: 
Indicates that arguments are not expected and terminates the program. 

### Actual Output
Unexpected argument provided


# Test Case 2: Program Accepts Valid Integers

### Description: 
A test to verify that input must be integers. Any non-integer inputs will be ignored

### Input: 
./number_to_words
100a
a100
100.1
0.01
100
9999


### Expected Output: 
Program rejects any input which is not an integer. 

### Actual Output
100a
Failed to provide a valid integer
a100
Failed to provide a valid integer
100.1
Failed to provide a valid integer
0.01
Failed to provide a valid integer
100
100 = one dollar
9999
9999 = ninety-nine dollars and ninety-nine cents


# Test Case 3: Program Outputs the Correct Value of Dollar and Cents Amount in Words 

### Description: 
A test to verify that the correct output is displayed

### Input: 
1111
125345602


### Expected Output: 
1111 = eleven dollars and eleven cents
125345602 = one million two hundred fifty-three thousand four hundred fifty-six dollars and two cents

### Actual Output: 
1111 = eleven dollars and eleven cents
125345602 = one million two hundred fifty-three thousand four hundred fifty-six dollars and two cents


# Test Case 4: Program Can Handle Very Large Numbers 

### Description: 
A test to verify that the program can handle numbers in the billions

### Input: 
./number_to_words
99999999999999

### Expected Output: 
99999999999999 = nine hundred ninety-nine billion nine hundred ninety-nine million nine hundred ninety-nine thousand nine hundred ninety-nine dollars and ninety-nine cents

### Actual Output 
99999999999999 = nine hundred ninety-nine billion nine hundred ninety-nine million nine hundred ninety-nine thousand nine hundred ninety-nine dollars and ninety-nine cents


# Test Case 5: Values up to $1500 (150000) are Memoized

### Description: 
A test to verify that values up to $1500 are memoized

### Input
11445
137
150000
150100
150001
100000000
149999

### Expected Result 
Memoized dollar values are 1, 114, 137, 1499, 1500
Memoized cent values are 1, 37, 45, 98, 99

Not memoized: 1501, 1000000

### Actual Output
CACHE CONTENT
Dollar 1: [one dollar]
Dollar 114: [one hundred fourteen dollars]
Dollar 1499: [one thousand four hundred ninety-nine dollars]
Dollar 1500: [one thousand five hundred dollars]
Cent 1: [one cent]
Cent 37: [thirty-seven cents]
Cent 45: [forty-five cents]
Cent 98: [ninety-eight cents]
Cent 99: [ninety-nine cents]


