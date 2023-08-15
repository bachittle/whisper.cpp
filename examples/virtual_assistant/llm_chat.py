import openai

with open("build/bin/query.txt", "r") as fp:
    text = fp.read()

print(f"text in python: {text}")

OPENAI_MODEL = "gpt-3.5-turbo"

response = openai.ChatCompletion.create(
    model=OPENAI_MODEL,
    messages=[
        {'role': 'user', 'content': text}
    ]
)

print(f'response: {response}')