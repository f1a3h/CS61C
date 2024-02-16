from pathlib import Path
import hashlib
import sys


lab_dir_path = Path(__file__).parent

starter_file_hashes = {
    "tests/ex1-test.circ": "77b5865ca1a2460ac0aff2e99bb60198",
    "tests/ex2-test.circ": "dbddd69dc361a4828841a222f1806948",
    "tests/ex4-test.circ": "aebcfa35c51bf11f8507ea1ee9c87c6a",
    "tests/ex5-test.circ": "812e9574bae104b826dc1b4082da0ad0",
    "tests/out/ex1-test.ref": "20b5b99b077dd26b8112737cc8d7fdae",
    "tests/out/ex2-test.ref": "41cc2149612f5e9a94dc4bf6dd7ccb41",
    "tests/out/ex4-test.ref": "6d327cf3e4e89717b3e915dc9b86ffb7",
    "tests/out/ex5-test.ref": "55f4da9c4ee26ab817be5a28440c12d6",
}


def check_hash(rel_path_str):
    if rel_path_str not in starter_file_hashes:
        return (True, f"Starter does not have hash for {rel_path_str}")
    path = lab_dir_path / rel_path_str
    with path.open("rb") as f:
        contents = f.read()
    contents = contents.replace(b"\r\n", b"\n")
    hashed_val = hashlib.md5(contents).hexdigest()
    if hashed_val != starter_file_hashes[rel_path_str]:
        return (False, f"{rel_path_str} was changed from starter")
    return (True, f"{rel_path_str} matches starter file")


def check_hashes():
    passed_all = True
    for rel_path_str in starter_file_hashes.keys():
        passed, reason = check_hash(rel_path_str)
        if not passed:
            passed_all = False
            print(f"Error: {reason}", file=sys.stderr)
    if not passed_all:
        sys.exit(1)
