import os
import subprocess

def compile_cpp_program(source_file, output_file):
    compile_command = ["g++", source_file, "-std=c++20","-o", output_file]
    result = subprocess.run(compile_command, capture_output=True, text=True)
    
    if result.returncode != 0:
        print("Compilation failed:")
        print(result.stderr)
        return False
    return True

def run_cpp_program(executable_file, input_file, output_file):
    with open(input_file, 'r') as infile, open(output_file, 'w') as outfile:
        result = subprocess.run([f"./{executable_file}"], stdin=infile, stdout=outfile, stderr=subprocess.PIPE, text=True)
    
    if result.returncode != 0:
        print("Execution failed:")
        print(result.stderr)
        return False
    return True

def compare_output(output_file, expected_output_file):
    """
    Compares the output of the C++ program with the expected output.
    """
    with open(output_file, 'r') as outfile, open(expected_output_file, 'r') as expectedfile:
        output_content = outfile.read()
        expected_content = expectedfile.read()
        
        if output_content == expected_content:
            print("Test passed: Output matches the expected output.")
            return True
        else:
            print("Test failed: Output does not match the expected output.")
            print("Expected Output:")
            print(expected_content)
            print("Actual Output:")
            print(output_content)
            return False

def main(source_file = "main.cpp"):
    
    executable_file = "a.out"
    input_file = "tests/input.txt"
    output_file = "program_output.txt"
    expected_output_file = "tests/output.txt"
    
    if not compile_cpp_program(source_file, executable_file):
        return
    
    if not run_cpp_program(executable_file, input_file, output_file):
        return
    
    compare_output(output_file, expected_output_file)

if __name__ == "__main__":
    filename = input("Enter the filename to test: ")
    main(filename)
