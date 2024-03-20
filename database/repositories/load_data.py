from timeit import Timer
from sys import argv

import manager


def main():
    manager.load_users_in_world(
        world_id=int(argv[1]),
        lat=int(argv[2]), long=int(argv[3]),
        user_count=int(argv[4])
    )


if __name__ == "__main__":
    print(f"Db loaded in {Timer(main).timeit(number=1)} sec.")
