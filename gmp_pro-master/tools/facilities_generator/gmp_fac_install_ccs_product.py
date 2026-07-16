
import os
import shutil
import json

library_version = "1.00.00.05"

# suffix for source code template 
suffix = '.xdt'


# Get GMP installation path
gmp_pro_location = os.getenv('GMP_PRO_LOCATION')

# Check if GMP path has registered.
if gmp_pro_location is not None:
    print(f"Environment variable GMP_PRO_LOCATION is: {gmp_pro_location}")
else:
    print("Environment variable GMP_PRO_LOCATION unknown. Reinstall this software may solve this problem.")

# Container of facilities
facilities_json = os.path.join(gmp_pro_location, 'tools', 'facilities_generator', 'json','facilities.json')



# GMP path
gmp_installed_path = gmp_pro_location

# product config file
config_file_template = {
    "name": "gmp_pro",
    "displayName": "General Motor Platform",
    "version": library_version,
    "documentationPath": gmp_pro_location + "/manual",
    "includePaths": [
        gmp_pro_location,
        os.path.join(gmp_pro_location, 'csp/c28x_syscfg/')
    ],
    "devices": [
        "F28004x", "F2837xD", "F2837xS", "F2807x", "F2838x",
        "F28002x", "F28003x", "F28P65x", "F28P55x", "GMP_NULL_DEVICE"
    ],
    "minToolVersion": "1.21.0"
}

# tirex config file
tirex_package_template = [{
    "rootMacroName": "COM_GMP_PRO_SDK_INSTALL_DIR",
    "compilerIncludePath": [
        gmp_pro_location,
        os.path.join(gmp_pro_location, 'csp/c28x_syscfg/')
    ],
    "compilerSymbols": [],
    "linkerSearchPath": []
}]

# ccs package config file
tirex_config_template = [{
    "id": "GMP-PRO-SDK",
    "name": "General Motor Platform",
    "version": library_version,
    "type": "software",
    "image": gmp_pro_location + "/manual/icon/GMP_LOGO.png",
    "license": gmp_pro_location + "/LICENSE.txt",
    "description": "This is a part of GMP Pro software.",
    "tags": [ "GMP" ],

    "dependencies": [
        {
            "packageId": "C2000WARE",
            "version": "5.03.00.00",
            "require": "mandatory"
        },
        {
            "packageId": "sysconfig",
            "version": "1.21.0",
            "require": "mandatory"
        }
    ],
    "metadataVersion": "3.1.0"
}]



######################################################################
# Here is the implement function for GMP facilities

def gen_facilities_config_files(fac_data): 
    # init record
    records = [] 

    # target script file
    config_path = os.path.join(gmp_installed_path, fac_data['productDir'], '.metadata')

    config_file_template['displayName'] = fac_data['displayName']
    
    # ensure config path is exists
    if not os.path.exists(config_path):
        os.makedirs(config_path)

    # For all folder objects
    for folder_item in fac_data['sourceDir'] :
        # source folder
        src_dir = os.path.join(gmp_installed_path, folder_item, 'src')

        # target path
        dest_dir = os.path.join(gmp_installed_path, folder_item, '.meta')

         # ensure target dir is exists
        if not os.path.exists(dest_dir):
            os.makedirs(dest_dir)
        # For all file objects
        #for root, dirs, files in os.walk(src_dir):
        #    for file in files:
        #        # construct full file path
        #        src_file_path = os.path.join(root, file)
        #        dest_file_path = os.path.join(dest_dir, f"{os.path.splitext(file)[0]}{suffix}")
        #
        #        # copy
        #        shutil.copy2(src_file_path, dest_file_path)
        #        
        #        # record
        #        record = {
        #            "name": folder_item + f"{os.path.splitext(file)[0]}{suffix}" ,
        #            "outputPath": file,
        #            "alwaysRun": True
        #        }
        #        records.append(record)
        #
        #        print('\033[93m[INFO]\033[00m ' + dest_file_path + ' is generated.')

    # generate config files
    config_file_template["templates"] = records

    # generate config files
    with open(os.path.join(config_path, 'product.json'), 'w') as f:
        json.dump(config_file_template, f, indent=4)

    # tirex config files
    tirex_file_path = os.path.join(config_path, '.tirex')

    # ensure config path is exists
    if not os.path.exists(tirex_file_path):
        os.makedirs(tirex_file_path)

    # config tirex resource
    tirex_package_template[0]['rootMacroName'] = fac_data['rootMacroName']

    tirex_config_template[0]['id'] = fac_data['name']
    tirex_config_template[0]['name'] = fac_data['displayName']
    tirex_config_template[0]['description'] = fac_data['description']

    # generate tirex config files
    with open(os.path.join(tirex_file_path, 'package.ccs.json'), 'w') as f:
        json.dump(tirex_package_template, f, indent=4)

    with open(os.path.join(tirex_file_path, 'package.tirex.json'), 'w') as f:
        json.dump(tirex_config_template, f, indent=4)




######################################################################
# Start here
with open(facilities_json, 'r') as f:
    data = json.load(f)

for name in data["facilities"]:
    
    # Say something
    print("\r\n\r\n\033[93m[INFO]\033[00m facilities: " + data[name]['name'] + ' in ' + data[name]['productDir'] + 'is generating...')

    # generate config file for target 
    gen_facilities_config_files(data[name])


    #print("\033[93m[INFO]\033[00m " + src_dir)
    #print("\033[93m[INFO]\033[00m " + dest_dir)
    #print("\033[93m[INFO]\033[00m " + config_path)

    
