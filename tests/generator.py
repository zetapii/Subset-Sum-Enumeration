import random

def generate_test_case(n, k, max_value):
    # Generate an array of n random integers between 1 and max_value
    array = [random.randint(1, max_value) for _ in range(n)]
    
    return array, k

def write_test_case_to_file(filename, test_case):
    array, k = test_case
    # with open(filename, 'w') as f:
    with open(filename,'a') as f:
        f.write(f"{len(array)} {k}\n")
        f.write(' '.join(map(str, array)) + '\n')
        f.write('\n')

for i in range(100):
    n = random.randint(10, 15)
    k = random.randint(10, 15)
    max_value = random.randint(10, 18)

    test_case = generate_test_case(n, k, max_value)

    # write_test_case_to_file('test_case.txt', test_case)
    write_test_case_to_file('tests/input.txt',test_case)