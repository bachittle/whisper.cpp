import openai
import json

with open("build/bin/query.txt", "r") as fp:
    text = fp.read()

print(f"text in python: {text}")

#OPENAI_MODEL = "gpt-3.5-turbo"
OPENAI_MODEL = "gpt-4"

SYS_MSG = """
You are Ivan, an intelligent virtual assistant.
People talk to you by speech, similar to other home assistants like Alexa or Siri.
You respond to requests and try to help people.
"""

messages = [
    {'role': 'system', 'content': SYS_MSG}
]
try:
    with open("build/bin/messages.json", "r") as fp:
        messages = json.load(fp)
except FileNotFoundError:
    pass

messages.append({'role': 'user', 'content': text})

response = openai.ChatCompletion.create(
    model=OPENAI_MODEL,
    messages=messages
)

msg = response['choices'][0]['message']
messages.append(msg)
msg_content = msg['content']
print(f'response: {msg_content}')

MSG_LIMIT = 10
if len(messages) > MSG_LIMIT:
    messages = messages[1:-3]
with open("build/bin/messages.json", "w") as fp:
    json.dump(messages, fp)

with open("build/bin/response.txt", "w") as fp:
    fp.write(msg_content)