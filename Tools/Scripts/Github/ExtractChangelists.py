import re
import subprocess
import sys

# CONFIG: Change this to your repo + issues base URL
GITHUB_REPO = "https://github.com/ScottGarryFoster/SuperGameEngine"
ISSUES_URL = f"{GITHUB_REPO}/issues"
COMMIT_URL = f"{GITHUB_REPO}/commit"

# --- usage ---
# python changelog.py <from_commit> <to_commit>
# If only <to_commit> is provided, it will assume from_commit = empty tree (full history)
# Example: python changelog.py v1.0.0 HEAD

if len(sys.argv) < 2:
    print("Usage: python changelog.py <from_commit> <to_commit>")
    sys.exit(1)

from_commit = sys.argv[1] if len(sys.argv) > 2 else None
to_commit = sys.argv[2] if len(sys.argv) > 2 else sys.argv[1]

if from_commit:
    commit_range = f"{from_commit}..{to_commit}"
else:
    commit_range = to_commit

# Run git log to fetch hash + subject within the given range
logs = subprocess.check_output(
    ["git", "log", commit_range, "--pretty=format:%H %s"], text=True
).splitlines()

pattern = re.compile(r"\[#(\d+)\]\s+\*\*\s+(.*?)\s+\*\*")

markdown_lines = []

for log in logs:
    commit_hash, subject = log.split(" ", 1)
    match = pattern.search(subject)
    if match:
        ticket, desc = match.groups()
        md = f"- [[#{ticket}]({ISSUES_URL}/{ticket})] [ {desc} ]({COMMIT_URL}/{commit_hash})"
        markdown_lines.append(md)
        
pattern = re.compile(r"\s+\*\*\s+(.*?)\s+\*\*")

for log in logs:
    commit_hash, subject = log.split(" ", 1)
    match = pattern.search(subject)
    if match:
        desc = match.groups()
        md = f"- [ {desc} ]({COMMIT_URL}/{commit_hash})"
        markdown_lines.append(md)

print("\n".join(markdown_lines))