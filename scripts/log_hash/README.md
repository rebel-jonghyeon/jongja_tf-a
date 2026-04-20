## Log Hash Encoding Process
1. Directory Copy

   The original directory rebel_cds_collab_hw is copied to rebel_cds_collab_hw_hash.
2. .c File Encoding

   Log formats, such as ERR("result:%s",res), are parsed in the .c files within the copied directory and encoded into hash values.
3. Build Execution

   The build process starts after the encoding is complete.
4. Image Location

   The built images are generated in the rebel_cds_collab_hw_hash/binaries directory.
5. Hash Map Generation

   The hashmap.csv file, containing the mapping between log hash values and original log strings, is generated at rebel_cds_collab_hw_hash/scripts/log_hash.

## 5 files in script/loghash
1. **macros_to_hash.txt** (User Added. self-write file)

   : add log macro here to encode
3. **dirs_to_exclude.txt** (User Added. self-write file)

   : add directory here to keep from encoding
5. **log_hash_encoder.py**

   : The script that encodes log macros in .c files into hash values.
7. **log_hash_decoder.py**

   : The script that decodes log hash values back into the original log strings. (It performs decoding by importing log_hash_directory_decoder.py)


## How to use with build option
- Basic Encoding Build : `./build.sh --loghash`
- Build with Release Messages : `./build.sh --loghash --rel_msg "1124_buildtest"`

record build information "1124_buildtest" in hashmap.csv as header

## How to decode

**Independence of the Log Hash Directory** : Copy and Use this log_hash directory at any location

Essential files : hashmap.csv log_hash_decoder.py log_hash_dir_deocder.py

Decode a Single Text File (Anywhere) : `python3 log_hash_decoder.py <hashmap.csv path> <textfile path to decode>`

Decode a Whole Directory (In the Log Hash Scripts Folder) : `python3 log_hash_decoder.py`