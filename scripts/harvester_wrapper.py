#!/usr/bin/env python3
"""
Wrapper script for theHarvester
Provides a simplified interface for OSINT data gathering
"""
import sys
import subprocess
import json

def run_harvester(domain, sources="google,bing"):
    """
    Run theHarvester on a target domain
    
    Args:
        domain: Target domain to investigate
        sources: Comma-separated list of sources (default: google,bing)
    """
    try:
        cmd = ["theHarvester", "-d", domain, "-b", sources]
        result = subprocess.run(cmd, capture_output=True, text=True, timeout=60)
        
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
        print("Usage: harvester_wrapper.py <domain> [sources]")
        sys.exit(1)
    
    domain = sys.argv[1]
    sources = sys.argv[2] if len(sys.argv) > 2 else "google,bing"
    
    print(run_harvester(domain, sources))
