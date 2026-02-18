#!/usr/bin/env python3

import argparse
import subprocess
import sys

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Setup vcpkg for the project")
    parser.add_argument("--vcpkg-root", type=str, default="vcpkg", help="Path to the vcpkg directory")
    args = parser.parse_args()

    
