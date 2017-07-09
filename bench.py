#!/usr/bin/env python3

import os
import re
import subprocess
import sys
import time

iterations = 25
benchmarks = [
    {
        "name": "libjpeg-turbo",
        "version": "1.5.2",
        "dir": "libjpeg-turbo",
        "compile": "make",
        "bin": "libjpeg-turbo",
    },
    {
        "name": "stb_image",
        "version": "2.15",
        "dir": "stb_image",
        "compile": "make",
        "bin": "stb_image",
    },
    {
        "name": "jpeg-decoder",
        "version": "0.1.13",
        "dir": "jpeg-decoder",
        "compile": "cargo build --release",
        "bin": "target/release/jpeg-decoder",
    },
]

# time.perf_counter requires python 3.3
if sys.version_info < (3, 3):
    print("Python >= 3.3 is required")
    exit(1)

if len(sys.argv) < 2:
    print("Please specify an image to benchmark")
    exit(1)

image = sys.argv[1]

if not os.path.isfile(image):
    print("The specified image does not exist")
    exit(1)

try:
    output = subprocess.check_output(["go", "version"]).decode(encoding='UTF-8')
    version = re.findall("([0-9]+\.[0-9]+(\.[0-9]+)?)", output)[0][0]

    benchmarks.append({
        "name": "go",
        "version": version,
        "dir": "go",
        "compile": "go build main.go",
        "bin": "main",
    })
except:
    print("go not found, skipping go benchmark")
    print("")

print("Compiling...")
for bench in benchmarks:
    name = "{} ({})".format(bench["name"], bench["version"])

    with open(os.devnull, "w") as fnull:
        try:
            exit_code = subprocess.call(bench["compile"].split(), cwd=bench["dir"], stdout=fnull)

            if exit_code != 0:
                print("")
                print("{} failed to compile".format(name))
                continue
        except OSError as err:
            print("")
            print("{} failed to compile: {}".format(name, err))
            continue

print("Benchmarking...")
print("")
for bench in benchmarks:
    name = "{} ({})".format(bench["name"], bench["version"])

    start_time = time.perf_counter()
    exit_code = subprocess.call([os.path.join(bench["dir"], bench["bin"]), image, str(iterations)])
    time_elapsed = time.perf_counter() - start_time

    result = "{:.2f}ms".format((time_elapsed * 1000) / iterations) if exit_code == 0 else "failed"
    print("{:30} {}".format(name, result))
