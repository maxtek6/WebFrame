#!/usr/bin/env python3
"""
vcpkg Bootstrap Script

This script bootstraps vcpkg and sets up the environment for building WebFrame.
It supports cross-platform builds with configurable OS and triplet targets.

Usage:
    python setup.py --os <windows|linux|macos> --triplet <x64-linux|x64-windows|etc>
"""

import argparse
import os
import platform
import subprocess
import sys
from pathlib import Path


def get_vcpkg_root() -> Path:
    """Get the vcpkg root directory."""
    script_dir = Path(__file__).parent.resolve()
    project_root = script_dir.parent.parent
    vcpkg_root = project_root / "vcpkg"
    return vcpkg_root


def get_default_os() -> str:
    """Get the default OS based on the current platform."""
    system = platform.system()
    if system == "Windows":
        return "windows"
    elif system == "Darwin":
        return "macos"
    else:
        return "linux"


def get_default_triplet() -> str:
    """Get the default triplet based on the current platform and architecture."""
    machine = platform.machine()
    system = platform.system()
    
    # Map machine architectures
    arch = "x64" if machine in ("x86_64", "AMD64") else "x86"
    if machine in ("arm64", "aarch64"):
        arch = "arm64"
    
    # Map OS to triplet
    if system == "Windows":
        return f"{arch}-windows"
    elif system == "Darwin":
        return f"{arch}-osx"
    else:
        return f"{arch}-linux"


def bootstrap_vcpkg(vcpkg_root: Path) -> bool:
    """
    Bootstrap vcpkg if it hasn't been already.
    
    Args:
        vcpkg_root: Path to vcpkg directory
        
    Returns:
        True if bootstrap was successful or already bootstrapped, False otherwise
    """
    vcpkg_executable = vcpkg_root / ("vcpkg.exe" if sys.platform == "win32" else "vcpkg")
    
    if vcpkg_executable.exists():
        print(f"✓ vcpkg already bootstrapped at {vcpkg_root}")
        return True
    
    print(f"📦 Bootstrapping vcpkg...")
    
    # Clone vcpkg if not present
    if not vcpkg_root.exists():
        print(f"📥 Cloning vcpkg to {vcpkg_root}")
        try:
            subprocess.run(
                ["git", "clone", "https://github.com/Microsoft/vcpkg.git", str(vcpkg_root)],
                check=True,
                capture_output=True
            )
        except subprocess.CalledProcessError as e:
            print(f"✗ Failed to clone vcpkg: {e.stderr.decode()}")
            return False
    
    # Run bootstrap script
    try:
        if sys.platform == "win32":
            bootstrap_script = vcpkg_root / "bootstrap-vcpkg.bat"
            subprocess.run(
                [str(bootstrap_script)],
                cwd=vcpkg_root,
                check=True
            )
        else:
            bootstrap_script = vcpkg_root / "bootstrap-vcpkg.sh"
            subprocess.run(
                ["bash", str(bootstrap_script)],
                cwd=vcpkg_root,
                check=True
            )
        print("✓ vcpkg bootstrapped successfully")
        return True
    except subprocess.CalledProcessError as e:
        print(f"✗ Bootstrap failed: {e}")
        return False


def install_dependencies(vcpkg_root: Path, triplet: str, os_name: str) -> bool:
    """
    Install project dependencies using vcpkg.
    
    Args:
        vcpkg_root: Path to vcpkg directory
        triplet: Target triplet (e.g., x64-linux)
        os_name: Target OS (e.g., linux)
        
    Returns:
        True if installation was successful, False otherwise
    """
    vcpkg_executable = vcpkg_root / ("vcpkg.exe" if sys.platform == "win32" else "vcpkg")
    project_root = vcpkg_root.parent.parent
    
    print(f"📦 Installing dependencies for {triplet}...")
    
    try:
        subprocess.run(
            [
                str(vcpkg_executable),
                "install",
                f"--triplet={triplet}",
                f"--manifest-root={project_root}",
                "--clean-after-build"
            ],
            check=True
        )
        print(f"✓ Dependencies installed successfully")
        return True
    except subprocess.CalledProcessError as e:
        print(f"✗ Dependency installation failed: {e}")
        return False


def main():
    parser = argparse.ArgumentParser(
        description="Bootstrap vcpkg and install WebFrame dependencies",
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog="""
Examples:
  python setup.py                                    # Use system defaults
  python setup.py --os linux-latest --triplet x64-linux
  python setup.py --os windows-latest --triplet x64-windows
  python setup.py --triplet arm64-linux
        """
    )
    
    parser.add_argument(
        "--os",
        dest="os_name",
        choices=["windows-latest", "linux-latest", "macos-latest"],
        default=get_default_os(),
        help="Target operating system (default: %(default)s)"
    )
    
    parser.add_argument(
        "--triplet",
        dest="triplet",
        default=get_default_triplet(),
        help="vcpkg triplet (default: %(default)s)"
    )
    
    parser.add_argument(
        "--skip-bootstrap",
        action="store_true",
        help="Skip vcpkg bootstrap (assume already bootstrapped)"
    )
    
    args = parser.parse_args()
    
    print(f"🚀 WebFrame vcpkg Setup")
    print(f"   OS: {args.os_name}")
    print(f"   Triplet: {args.triplet}")
    print()
    
    vcpkg_root = get_vcpkg_root()
    
    # Bootstrap vcpkg
    if not args.skip_bootstrap:
        if not bootstrap_vcpkg(vcpkg_root):
            sys.exit(1)
    
    # Install dependencies
    if not install_dependencies(vcpkg_root, args.triplet, args.os_name):
        sys.exit(1)
    
    print()
    print("✓ Setup complete!")
    print(f"   vcpkg root: {vcpkg_root}")
    print(f"   Use CMAKE_TOOLCHAIN_FILE={vcpkg_root}/scripts/buildsystems/vcpkg.cmake")


if __name__ == "__main__":
    main()
