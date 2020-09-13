import os
import heapq

class SortFiles:
    def __init__(self):
        self._dir = "Z:/Games/ZxGames/GBA_Games/ROMS/Fire-Emblem/FEUniverse/FEUniverse/Battle Animations/7. Spells"
        self._heap = []

    def execute(self):
        self._heap = []
        with os.scandir(self._dir) as iter:
            for entry in iter:
                if entry.is_dir():
                    count = self._count_png_in_dir(entry)
                    heapq.heappush(self._heap, (count, entry.name))

        self._iterate_heap()

    def _count_png_in_dir(self, entry: os.DirEntry):
        count = 0
        with os.scandir(entry) as iter2:
            for entry2 in iter2:
                if entry2.is_file() and entry2.name.endswith(".png"):
                    count += 1
        return count
     
    def _iterate_heap(self):
        while self._heap:
            val = heapq.heappop(self._heap)
            print("{}: {}".format(val[0], val[1]))


if __name__ == "__main__":
    sort_files = SortFiles()
    sort_files.execute()
