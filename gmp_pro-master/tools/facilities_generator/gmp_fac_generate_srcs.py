import json
import sys
import os
import filecmp
import shutil
from pathlib import Path

def read_json_file(file_path):
    with open(file_path, 'r') as file:
        return json.load(file)

def copy_files(src_path, dest_path):
    src_path = Path(src_path)
    dest_path = Path(dest_path)
    if not dest_path.exists():
        dest_path.mkdir(parents=True)
    for item in src_path.rglob("*"):
        if item.is_file():
            if(os.path.exists(dest_path / item.relative_to(src_path))):
                if filecmp.cmp(src_path / item.relative_to(src_path), dest_path / item.relative_to(src_path), shallow=False):
                    print(f"[ SKIP ] Source File: '{src_path / item.relative_to(src_path)} '")
                else :
                    #print(f"Debug Info: source position'{src_path}'")
                    #print(f"Debug Info: target position'{dest_path}', '{item.relative_to(src_path)}'")
                    print(f"[UPDATE] Source File: '{src_path / item.relative_to(src_path)}'")
                    shutil.copy(item, dest_path / item.relative_to(src_path))
            else :
                print(f"[CREATE] Source File: '{src_path / item.relative_to(src_path)}'")
                shutil.copy(item, dest_path / item.relative_to(src_path))

def main():
    # Check parameter
    if len(sys.argv) < 3:
        print("Usage: python script.py <config_file.json> <destination_dir>")
        sys.exit(1)

    # Get Environment variables GMP_PRO_LOCATION
    gmp_location_dir = os.getenv('GMP_PRO_LOCATION')
    if not gmp_location_dir:
        print("Environment variable GMP_PRO_LOCATION is not set.")
        sys.exit(1)

    config_file_path = sys.argv[1]
    destination_dir = sys.argv[2]

    config_data = read_json_file(config_file_path)

    # gmp_source_dic_file = config_data.get("gmp_source_dic_file")
    gmp_source_dic_file = os.path.join(gmp_location_dir, 'tools', 'facilities_generator', 'json', config_data.get("gmp_source_dic_file"))

    if not gmp_source_dic_file:
        print("gmp_source_dic_file not found in the config file.")
        sys.exit(1)

    gmp_source_dic_data = read_json_file(gmp_source_dic_file)

    # Collect all source_path & include_path
    src_paths = set()
    for item in gmp_source_dic_data:
        if config_data.get(item["name"]):
            src_paths.update(item["source_path"])

    inc_paths = set()
    for item in gmp_source_dic_data:
        if config_data.get(item["name"]):
            inc_paths.update(item["include_path"])

    dest_dir = Path(destination_dir) / "gmp_src" 
    print(dest_dir)
    if not os.path.exists(dest_dir):
        os.makedirs(dest_dir)

    # Copy Source Files
    print('Related source files:')
    for path in src_paths:
        src_dir = Path(gmp_location_dir) / path / "src"
        print(src_dir)
        copy_files(src_dir, dest_dir)

    # Generate a list of include_path
    include_paths = ""
    print('\r\nRelated header files:')
    for itor in inc_paths:
        print(itor)
        if itor == '.':
            include_paths += gmp_location_dir;
        else:
            include_paths += os.path.join(gmp_location_dir, itor);
        include_paths += '\r\n'

    with open("include_paths.txt", "w") as f:
        f.write(include_paths)

if __name__ == "__main__":
    main()