import psutil
import time
import sys


def close_process(processName: str, waitTime: float = 2.0) -> int:
    """
    Attempts to close a process by name, force-killing if needed.
    
    Args:
        processName (string): The name of the process to kill.
        waitTime (float): How long to wait in seconds before checking to see if the application is still alive.
    
    Returns:
        0 - Process was killed/terminated successfully or process wasn't running initially
        1 - Process is still running after all attempts
    """

    # Find processes with matching name
    processes = [
        p
        for p in psutil.process_iter(["pid", "name"])
        if p.info["name"] and processName.lower() == p.info["name"].lower()
    ]

    # Process is not running, nothing more we can do.
    if not processes:
        print(f"{processName} is not running.")
        return 0  

    # Attempt to terminate processes
    for proc in processes:
        try:
            print(f"Terminating: {proc.info['name']} (PID {proc.info['pid']})")
            proc.terminate()
        except Exception as e:
            print(f"Error terminating {proc}: {e}")

    # Wait for termination
    time.sleep(waitTime)

    # Check if still running
    stillRunning = [
        p
        for p in psutil.process_iter(["pid", "name"])
        if p.info["name"] and processName.lower() == p.info["name"].lower()
    ]

    # Really kill if not
    if stillRunning:
        print(f"{processName} did not terminate, forcing kill...")

        for proc in stillRunning:
            try:
                print(f"Killing: {proc.info['name']} (PID {proc.info['pid']})")
                proc.kill()
            except Exception as e:
                print(f"Error killing {proc}: {e}")

        time.sleep(1.0)

    # Final check
    finalRunning = any(
        p.info["name"].lower() == processName.lower()
        for p in psutil.process_iter(["name"])
    )

    if finalRunning:
        print(f"{processName} is still running after kill attempt.")
        return 1
    else:
        print(f"{processName} was terminated/killed successfully.")
        return 0


if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python close_process.py <processName.exe>")
        sys.exit(99)

    processName = sys.argv[1]
    exitCode = close_process(processName)
    sys.exit(exitCode)