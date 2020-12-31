#!/usr/bin/python3
import argparse
import glob
import os
import subprocess
import sys


parser = argparse.ArgumentParser()
parser.add_argument("branch", default="gh-pages", nargs="?")
args = parser.parse_args()

version = subprocess.getoutput("git describe --always")

fd = os.fdopen(sys.stdout.fileno(), 'wb')

fd.write(b"commit refs/heads/" + args.branch.encode('utf-8') + b"\n")
fd.write(b"committer Doc Man <noreply@example.com> now" + b"\n")
fd.write(b"data <<EOF" + b"\n")
fd.write(b"Docs built at " + version.encode('utf-8') + b"\n")
fd.write(b"EOF" + b"\n")

files = glob.glob("doc/*")
for fn in files:
    with open(fn, 'rb') as f: contents = f.read()
    fd.write(b"M 644 inline " + os.path.basename(fn).encode('utf-8') + b"\n")
    fd.write(b"data " + str(len(contents)).encode("utf-8") + b"\n")
    fd.write(contents)
fd.write(b"done\n")

