import sys
import os
import re

from cmake_project_version import extract_version_from_cmakelists
from determine_dev_release import determine_dev_release

REPOSITORY_NAME = os.environ.get("REPOSITORY")
REF = os.environ.get("REF")

# Determine the branch that triggered the workflow
match = re.match(r"refs/heads/(.*)", REF)
if not match:
    sys.exit(1)

branch_name = match.group(1)
print(f"Determined branch name: {branch_name}")

version = extract_version_from_cmakelists()

is_dev_branch = branch_name != "main"
dev_release = None
if is_dev_branch:
    last_dev_release = determine_dev_release(version, REPOSITORY_NAME)
    dev_release = str(last_dev_release + 1)
    version += f"-dev.{dev_release}"

# Ensure GITHUB_OUTPUT is set correctly
github_output = os.getenv("GITHUB_OUTPUT")
if not github_output:
    print("Error: GITHUB_OUTPUT is not set!", file=sys.stderr)
    sys.exit(1)

with open(os.environ["GITHUB_OUTPUT"], "a", encoding="utf-8") as fh:
    print(f"version={version}", file=fh)
    print(f"dev_release={dev_release}", file=fh)
