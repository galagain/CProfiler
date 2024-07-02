import os  # Imports the os module for interacting with the operating system
import re  # Imports the re module for regular expressions
import argparse  # Imports the argparse module for parsing command-line arguments


def add_profiling_macro(file_path: str, macro_type: str) -> None:
    """
    Adds a profiling macro to functions in the specified file.

    Args:
        file_path (str): The path to the file to be processed.
        macro_type (str): The type of profiling macro to add (PROFILE_FUNCTION or PROFILE_FUNCTION_TO_FILE).
    """
    # Read the file contents
    with open(file_path, "r") as file:
        lines: list[str] = file.readlines()

    # Regular expressions for detecting function definitions and declarations
    func_def_regex = re.compile(r"^\s*[\w:~<>]+\s+[\w:~<>]+\s*\(.*\)\s*(const)?\s*{")
    func_decl_regex = re.compile(r"^\s*[\w:~<>]+\s+[\w:~<>]+\s*\(.*")
    open_brace_regex = re.compile(r"{")
    profile_macro_regex = re.compile(
        r"\bPROFILE_FUNCTION\(\);|\bPROFILE_FUNCTION_TO_FILE\(\);"
    )

    # Check if the file already includes "Timer.h"
    include_present: bool = any('#include "Timer.h"' in line for line in lines)

    new_lines: list[str] = []
    # Add the include for "Timer.h" if not present and not the Timer.h file itself
    if not include_present and not file_path.endswith("Timer.h"):
        new_lines.append('#include "Timer.h"\n')

    inside_function: bool = False
    brace_level: int = 0
    profile_function_added: bool = False

    i: int = 0
    while i < len(lines):
        line: str = lines[i]

        if not inside_function:
            if func_def_regex.match(line):
                # Start of a function definition
                new_lines.append(line)
                inside_function = True
                brace_level = 1  # Function body starts with the opening brace
                profile_function_added = profile_macro_regex.search(line) is not None
            elif func_decl_regex.match(line):
                # Function declaration (possibly multi-line)
                new_lines.append(line)
                i += 1
                while i < len(lines) and not open_brace_regex.search(lines[i]):
                    new_lines.append(lines[i])
                    i += 1
                if i < len(lines) and open_brace_regex.search(lines[i]):
                    new_lines.append(lines[i])
                    inside_function = True
                    brace_level = 1  # Function body starts with the opening brace
                    profile_function_added = (
                        profile_macro_regex.search(lines[i]) is not None
                    )
                else:
                    new_lines.append(line)
            else:
                new_lines.append(line)
        else:
            if brace_level == 1 and not profile_function_added:
                # Add the profiling macro after the opening brace of the function
                new_lines.append(f"    {macro_type}();\n")
                profile_function_added = True

            new_lines.append(line)
            # Update the brace level to track the function's scope
            brace_level += line.count("{") - line.count("}")
            if brace_level == 0:
                # End of function
                inside_function = False

        i += 1

    # Write the modified contents back to the file
    with open(file_path, "w") as file:
        file.writelines(new_lines)


def process_directory(directory: str, macro_type: str) -> None:
    """
    Processes all .cpp and .h files in the specified directory,
    adding profiling macros to their functions.

    Args:
        directory (str): The path to the directory to be processed.
        macro_type (str): The type of profiling macro to add (PROFILE_FUNCTION or PROFILE_FUNCTION_TO_FILE).
    """
    for root, _, files in os.walk(directory):
        for file in files:
            if file.endswith(".cpp") or file.endswith(".h"):
                file_path = os.path.join(root, file)
                print(f"Processing file: {file_path}")
                add_profiling_macro(file_path, macro_type)


if __name__ == "__main__":
    # Set up argument parser
    parser = argparse.ArgumentParser(
        description="Add profiling macros to C++ source files."
    )
    parser.add_argument(
        "-d",
        "--directory",
        type=str,
        default="./src",
        help="The path to the directory to be processed (default: ./src).",
    )
    parser.add_argument(
        "-m",
        "--macro",
        type=str,
        choices=["PROFILE_FUNCTION", "PROFILE_FUNCTION_TO_FILE"],
        default="PROFILE_FUNCTION",
        help="The type of profiling macro to add (default: PROFILE_FUNCTION).",
    )
    args = parser.parse_args()

    # Process the directory to add profiling macros
    process_directory(args.directory, args.macro)
    print("Profiling macros and #include added to all functions in source files.")
