from os import system
from os import chdir
from os.path import dirname

from tkinter import *
from tkinter.scrolledtext import ScrolledText
from tkinter.font import BOLD
from tkinter.ttk import Separator


APP_TITLE: str = "Enigma GUI"
EXE_NAME: str = "enigma.exe"
INPUT_PATH: str = "GUI/input.txt"
OUTPUT_PATH: str = "GUI/output.txt"


def encrypt(input_box: Text, output: Text):
    inp = input_box.get("1.0", "end")
    inp = inp.removesuffix('\n').upper()

    input_file = open(INPUT_PATH, "w")
    input_file.write(inp)
    input_file.close()
    
    system(f".\\{EXE_NAME} -f {INPUT_PATH} > {OUTPUT_PATH}")
    
    output_file = open(OUTPUT_PATH, "r")
    text = output_file.read()
    output_file.close()
    
    if '\n' in inp:
        inp = inp.replace('\n', " \\n ")
        text = text.removesuffix('\n').replace('\n', "\n\t")
        text = f"~#~[\"{inp}\"]:\n\n\t{text}\n"
    else:
        text = f"~#~[\"{inp}\"]> {text}"

    input_box.delete("1.0", "end")
    
    output.config(state="normal")
    output.insert("end", text)
    output.config(state="disabled")

def clear(output: Text):
    output.config(state="normal")
    output.delete("1.0", "end")
    output.config(state="disabled")

def main():
    print(__file__)
    chdir(dirname(__file__))
    chdir("../")

    window = Tk()
    window.title(APP_TITLE)
    
    frame = Frame(window)
    frame.grid()

    Label(frame, text="Output:", font="BOLD").grid(row=0, column=0)
    
    output = ScrolledText(frame, width=80, height=12, font=BOLD, fg="green", bg="lightgray", border="10", state="disabled", relief="flat")
    output.grid(row=0, column=1)

    Separator(frame, orient="horizontal").grid(row=1, column=0, sticky='nswe')
    Separator(frame, orient="horizontal").grid(row=1, column=1, sticky='nswe')

    encrypt_button = Button(frame, text="-Encrpt-", command=lambda: encrypt(input_box, output), font="BOLD")
    encrypt_button.grid(row=2, column=0)

    input_box = ScrolledText(frame, width=80, height=6, font="BOLD")
    input_box.grid(row=2, column=1)

    Button(frame, text="-Clear-", command=lambda: clear(output), font="BOLD").grid(row=3, column=1)

    window.mainloop()


if __name__ == "__main__":
    main()
