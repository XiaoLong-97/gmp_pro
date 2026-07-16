import os
import json

# get environment variable GMP_PRO_LOCATION
gmp_pro_location = os.getenv('GMP_PRO_LOCATION')

# path of gmp_source_dic.json
json_file_path = os.path.join(gmp_pro_location, 'tools', 'facilities_generator', 'json', 'gmp_source_dic.json')

# Check if file has existed
if not os.path.exists(json_file_path):
    raise FileNotFoundError(f"The file {json_file_path} does not exist.")

# Add config source file name
new_json_data = {}
new_json_data["gmp_source_dic_file"] = 'gmp_source_dic.json'

# parse gmp_source_dic.json
with open(json_file_path, 'r') as file:
    data = json.load(file)

# generate new JSON content

for item in data:
    # generate new section based on name, and set it to default value true
    new_json_data[item['name']] = True

# Last item is false
# new_json_data[data[-1]['name']] = False

# save facility_cfg.json
output_json_path = os.path.join(gmp_pro_location, 'tools', 'facilities_generator', 'json', 'facility_cfg.json')
with open(output_json_path, 'w') as outfile:
    json.dump(new_json_data, outfile, indent=4)

print(f"The file {output_json_path} has been generated successfully.")
