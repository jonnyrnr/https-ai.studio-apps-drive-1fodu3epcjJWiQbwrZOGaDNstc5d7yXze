#!/usr/bin/env python3
"""
Wrapper script for theHarvester
Provides a simplified interface for OSINT data gathering
"""
import sys
import subprocess
import json
import re

def validate_domain(domain):
    """
    Validate domain name format
    
    Args:
        domain: Domain string to validate
        
    Returns:
        bool: True if valid, False otherwise
    """
    # Basic domain validation regex
    pattern = r'^(?:[a-zA-Z0-9](?:[a-zA-Z0-9\-]{0,61}[a-zA-Z0-9])?\.)+[a-zA-Z]{2,}$'
    return bool(re.match(pattern, domain))

def run_harvester(domain, sources="google,bing"):
    """
    Run theHarvester on a target domain
    
    Args:
        domain: Target domain to investigate
        sources: Comma-separated list of sources (default: google,bing)
    """
    # Validate domain input
    if not validate_domain(domain):
        return json.dumps({
            "status": "error",
            "message": "Invalid domain format. Please provide a valid domain name."
        })
    
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
