#!/usr/bin/env python3
"""
Wrapper script for Sherlock
Provides a simplified interface for username enumeration
"""
import sys
import subprocess
import json

def run_sherlock(username):
    """
    Run Sherlock on a target username
    
    Args:
        username: Target username to search for
    """
    try:
        cmd = ["sherlock", username, "--print-found"]
        result = subprocess.run(cmd, capture_output=True, text=True, timeout=120)
        
        output = {
            "status": "success" if result.returncode == 0 else "error",
            "stdout": result.stdout,
            "stderr": result.stderr
        }
        
        return json.dumps(output, indent=2)
    except subprocess.TimeoutExpired:
        return json.dumps({"status": "error", "message": "Command timed out"})
    except Exception as e:
        return json.dumps({"status": "error", "message": str(e)})

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: sherlock_wrapper.py <username>")
        sys.exit(1)
    
    username = sys.argv[1]
    
    print(run_sherlock(username))
