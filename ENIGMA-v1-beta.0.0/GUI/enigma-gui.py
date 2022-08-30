from os import system
from os import chdir

from tkinter import *
from tkinter.font import BOLD
from tkinter.ttk import Separator

APP_TITLE: str = "Enigma GUI"
EXE_NAME: str = "enigma.exe"
INPUT_PATH: str = "GUI/input.txt"
OUTPUT_PATH: str = "GUI/output.txt"

def encrypt(text: str, output: Label):
    text = text.removesuffix('\n')

    input_file = open(INPUT_PATH, "w")
    input_file.write(text)
    input_file.close()
    
    system(f".\\{EXE_NAME} -f {INPUT_PATH} > {OUTPUT_PATH}")
    
    output_file = open(OUTPUT_PATH, "r")
    text = output_file.read()
    output_file.close()

    output.config(text=text)

def main():
    chdir("../")
    window = Tk()
    window.title(APP_TITLE)
    
    frame = Frame(window)
    frame.grid()

    Label(frame, text="output:\n\n\n").grid(row=0, column=0)
    
    output = Label(frame, font=BOLD, fg="green", justify="left")
    output.grid(row=0, column=1)

    Separator(frame, orient="horizontal").grid(row=1, column=0, sticky='nswe')
    Separator(frame, orient="horizontal").grid(row=1, column=1, sticky='nswe')

    input_box = Text(frame, width=50, height=2)
    input_box.grid(row=2, column=1)
    
    encrypt_button = Button(frame, text="-Encrpt-", command=lambda: encrypt(input_box.get("1.0", "end"), output))
    encrypt_button.grid(row=3, column=1)

    window.mainloop()


if __name__ == "__main__":
    main()
