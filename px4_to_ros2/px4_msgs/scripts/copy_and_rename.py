import os
import sys

from shutil import copyfile

print("Number of arguments:", len(sys.argv), "arguments.")
print("Argument List:", str(sys.argv))

input_dir = sys.argv[1]
output_dir = sys.argv[2]

for filename in os.listdir(input_dir):
    if ".msg" in filename:
        input_file = input_dir + filename
        output_file = output_dir + filename.partition(".")[0].title().replace('_','') + ".msg"
        copyfile(input_file, output_file)
        print "Created " + output_file
