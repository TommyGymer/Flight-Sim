#create copies of the md to modify
import os
import re
import time

def copy(src, dest):
    print(f"copy '{src}' '{dest}'")
    os.system(f"copy '{src}' '{dest}'")

def convert(src):
    print(f"pandoc -f markdown-yaml_metadata_block -t docx -o '{''.join(src.split('.')[:-1])}.docx' '{''.join(src.split('.')[:-1])}.md'")
    #os.system(f"pandoc -f markdown-yaml_metadata_block -t docx -o '{''.join(src.split('.')[:-1])}.docx' '{''.join(src.split('.')[:-1])}.md'")

files = [
    "Analysis.md",
    "Design.md",
    "Developing a Coded Solution.md"
]

cdiff = "mdtemp"

expr = re.compile("!\[\[.*\]\]")

for file in files:
    #copy(file, f"{cfolder}\\{file}")
    #time.sleep(1)

    f = open(f"{file}", 'r')
    text = f.read()
    f.close()

    i = expr.finditer(text)
    for m in i:
        #print(f"{m.start()}-{m.end()}: {m.group(0)}")
        text = text[:m.start()] + f"![]({m.group(0)[3:-2]})" + text[m.end():]

    f = open(f".\\{cdiff}_{file}", 'w+')
    f.write(text)
    f.close()

    convert(f"{cdiff}_{file}")