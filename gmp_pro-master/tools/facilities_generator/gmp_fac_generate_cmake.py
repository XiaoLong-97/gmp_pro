import os
import sys
import json

def read_paths(file_name):
    with open(file_name, 'r') as file:
        return [line.strip() for line in file if line.strip()]

def read_json_file(file_path):
    with open(file_path, 'r') as file:
        return json.load(file)

def generate_cmakeLists(include_paths, source_paths, gmp_pro_location):
    cmake_content = f"""
cmake_minimum_required(VERSION 3.10)

# Use Env Variable GMP_PRO_LOCATION
set(GMP_PRO_LOCATION $ENV{{GMP_PRO_LOCATION}})

# fix file path bug
string(REPLACE "\\\\" "/" GMP_PRO_LOCATION "${{GMP_PRO_LOCATION}}")

# Add include path
"""

    for path in include_paths:
        if path == '.':
            cmake_content += "\tinclude_directories(\"" + '${GMP_PRO_LOCATION}/' + "\")\n"
        else :
            cmake_content += "\tinclude_directories(\"" + '${GMP_PRO_LOCATION}/' + f"{path}\")\n"

    cmake_content += """
# Add Source path
"""

    # Collect all source files
    source_files = []
    for path in source_paths:
        for root, dirs, files in os.walk(os.path.join(gmp_pro_location, path, 'src')):
            for file in files:
                if file.endswith(('.c', '.cpp')):
                    source_files.append(os.path.join(root, file).replace(gmp_pro_location, '').replace('\\','/'))

    # Add all sources
    cmake_content += "set(GMP_SOURCE_FILES\n"
    for file in source_files:
        cmake_content += '\t\"' + '${GMP_PRO_LOCATION}' + f"{file}\"\n"
    cmake_content += ")\n"

    # replace all \ to /
    #cmake_content.replace('\\', '/')

    # Add execute
    #cmake_content += "add_executable(MyExecutable ${SOURCE_FILES})\n"

    return cmake_content


######################################################################
# Start Here
# Read Environment Path GMP_PRO_LOCATION
gmp_pro_location = os.getenv('GMP_PRO_LOCATION')
if not gmp_pro_location:
    raise ValueError("The environment variable GMP_PRO_LOCATION is not set.")

# Check parameter
if len(sys.argv) < 2:
    print("Usage: python gmp_fac_generate_srcs.py <config_file.json> <destination_dir>")
    sys.exit(1)

config_file_path = sys.argv[1]
#destination_dir = sys.argv[2]

config_data = read_json_file(config_file_path)

gmp_source_dic_file = config_data.get("gmp_source_dic_file")
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

# generate CMakeLists.txt content
cmake_content = generate_cmakeLists(inc_paths, src_paths, gmp_pro_location)

# write gmp_make_tool.cmake
with open('gmp_make_tool.cmake', 'w') as cmake_file:
    cmake_file.write(cmake_content)

print("Generated gmp_make_tool.cmake")
