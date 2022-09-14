"""Usage:
python3 base64_python.py encode <inputFile> <outputFile>

python3 base64_python.py decode <inputFile> <outputFile>
"""

import base64
import argparse


def _main():
    """Main function"""

    parser = argparse.ArgumentParser(description="Encode / decode base64")
    parser.add_argument(
        "command", type=str, choices=["encode", "decode"], help="a command to execute"
    )
    parser.add_argument("input_file", type=str, help="input file")
    parser.add_argument("output_file", type=str, help="output file")
    args = parser.parse_args()

    command = args.command.lower()
    input_file = args.input_file
    output_file = args.output_file

    if command == "encode":
        _encode(input_file, output_file)
    elif command == "decode":
        _decode(input_file, output_file)


def _encode(input_file: str, output_file: str):
    """Decode"""
    with open(input_file, "rb") as file:
        encoded = base64.b64encode(file.read())
    with open(output_file, "wb") as file:
        file.write(encoded)
        print(f"Finished writing to {output_file}")


def _decode(input_file: str, output_file: str):
    with open(input_file, "rb") as file:
        decoded = base64.b64decode(file.read())
    with open(output_file, "wb") as file:
        file.write(decoded)
        print(f"Finished writing to {output_file}")


if __name__ == "__main__":
    _main()
