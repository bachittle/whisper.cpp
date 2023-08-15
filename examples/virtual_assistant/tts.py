import subprocess

with open("build/bin/response.txt", "r") as fp:
    text = fp.read()

print(f"text in python: {text}")

PIPER_DIR = "/home/bachittle/Downloads/piper/"

command = [f"{PIPER_DIR}bin/piper", "--model", f"{PIPER_DIR}models/en_US-joe-medium.onnx", "--output_file", "build/bin/response.wav"]
#command = ["sleep", "5"]

process = subprocess.Popen(command, stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)

stdout, stderr = process.communicate(input=text.encode())

print(f"stdout: {stdout.decode()}")
print(f"stderr: {stderr.decode()}")