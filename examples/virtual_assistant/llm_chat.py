import openai
import json
import sys

SAVE_CONVOS = True 

def llm_chat(query):
    #OPENAI_MODEL = "gpt-3.5-turbo"
    OPENAI_MODEL = "gpt-4"

    SYS_MSG = """
    Behave like Ivan, an intelligent virtual assistant.
    Do not behave like ChatGPT or any other chatbot. Behave like Ivan.
    People talk to Ivan by speech, similar to other home assistants like Alexa or Siri.
    Ivan responds to requests and try to help people.
    Ivan is also British. Have a preference towards giving British responses.
    For example, if the user asks for dinner recipes, Ivan should give British recipes.
    Also speak in a British accent. 
    Give short responses, 3-5 sentences max.
    """

    messages = [
        {'role': 'system', 'content': SYS_MSG}
    ]
    if SAVE_CONVOS:
        try:
            with open("build/bin/messages.json", "r") as fp:
                messages.extend(json.load(fp))
        except FileNotFoundError:
            pass

    messages.append({'role': 'user', 'content': query})

    print(messages)
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
    if SAVE_CONVOS:
        with open("build/bin/messages.json", "w") as fp:
            json.dump(messages, fp)

    return msg_content


def llm_chat_file(query_fname, resp_fname):
    # with open("build/bin/query.txt", "r") as fp:
    with open(query_fname, "r") as fp:
        text = fp.read()

    print(f"text in python: {text}")

    # hack to remove []
    try:
        ind = text.index(']')
        text = text[ind+1:]
    except ValueError:
        pass

    msg_content = llm_chat(text)

    # with open("build/bin/response.txt", "w") as fp:
    with open(resp_fname, "w") as fp:
        fp.write(msg_content)



if (len(sys.argv) < 3):
    print("no query given")
    sys.exit(1)

llm_chat_file(sys.argv[1], sys.argv[2])