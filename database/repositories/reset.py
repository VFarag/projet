from timeit import Timer

import manager


def main():
    manager.reset()


if __name__ == "__main__":
    print(f"Db reset in {Timer(main).timeit(number=1)} sec.")
