import subprocess
import array as arr

a = [0]

if __name__ == "__main__":
    print("Seiten\tVersuche\tZeit")
    for i in range(1, 2000, 2):
        subprocess.call(["./a.out", str(i), "10000"])