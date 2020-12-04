import json
import os
import random


class RandomIcons:
    def __init__(self):
        self._icon_dir = self._read_json()
        self._file_list = []

    def execute(self):
        self._set_file_list()
        self._output()

    def _output(self):
        user_input = "y"
        while user_input.lower() == "y":
            print("Your icon directory is...")
            print(random.choice(self._file_list))
            print("Randomize again? (Y/n): ")
            user_input = input(">>> ")
        print("Thanks for using this program.")

    def _set_file_list(self):
        self._file_list = []
        for file in os.listdir(self._icon_dir):
            self._file_list.append(file)

        ###########################################################################
        # PRIVATE FUNCTIONS
        ###########################################################################

    def _read_json(self):
        with open("config.json", "r") as file:
            data = json.load(file)
        return data["iconsDirectory"]


if __name__ == "__main__":
    random_icons = RandomIcons()
    random_icons.execute()
