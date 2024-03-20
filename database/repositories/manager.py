from pathlib import Path
from os import path, remove
from string import ascii_letters
from random import randrange, choice


this_file_path = Path(__file__).parent
worlds = path.join(this_file_path, "worlds.txt")
users = path.join(this_file_path, "users.txt")


def load_users_in_world(world_id=1, lat=10, long=10, user_count=4):
    with open(worlds, "w") as f:
        f.write(f"{world_id} {lat} {long}\n")

    with open(users, "w") as f:
        f.write("\n".join(
            f"{i + 1} {world_id} {randrange(lat)} {randrange(long)} {''.join(choice(ascii_letters) for _ in range(randrange(6, 10)))}"
            for i in range(user_count)))


def reset():
    remove(worlds)
    remove(users)
