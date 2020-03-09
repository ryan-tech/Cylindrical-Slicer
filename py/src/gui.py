import tkinter as tk
from tkinter import *
from tkinter import filedialog
from objviewer import objView
import os

class SlicerGUI:
    def __init__(self, master):
        self.master = master
        master.title("Slicer")

        self.initMenu()
        #print('asdf')
        self.embedPyGame()
        #print('asdf')
        self.master.config(menu=self.menubar)
        #print('asdf')
        self.label = tk.Label(master, text="Open a wavefront 3D object file.")
        self.label.pack()


        """self.greet_button = tk.Button(master, text="Open .obj File", command=self.openFile)
        self.greet_button.pack()

        self.close_button = tk.Button(master, text="Close", command=master.quit)
        self.close_button.pack()"""

    def embedPyGame(self):
        embed = tk.Frame(self.master, width=500, height=500)  # creates embed frame for pygame window
        embed.grid(columnspan=600, rowspan=500)  # Adds grid
        embed.pack(side=BOTTOM)  # packs window to the left
        os.environ['SDL_WINDOWID'] = str(embed.winfo_id())
        os.environ['SDL_VIDEODRIVER'] = 'windib'

    def donothing(self):
        x = 0

    def openFile(self):
        self.filename = tk.filedialog.askopenfilename(initialdir="/", title="Select file",
                                                      filetypes=(("Object files", "*.obj"), ("all files", "*.*")))
        if self.filename is not None:
            if self.filename.lower().endswith('.obj'):  #makes sure it's a .obj file
                objView(self.filename)
            else:
                print('error: Unsupported or missing file')

    def initMenu(self):
        self.menubar = Menu(self.master)
        filemenu = Menu(self.menubar, tearoff=0)
        filemenu.add_command(label="Open", command=self.openFile)
        filemenu.add_command(label="Save", command=self.donothing)
        filemenu.add_separator()
        filemenu.add_command(label="Exit", command=self.master.quit)
        self.menubar.add_cascade(label='File', menu=filemenu)

        helpmenu = Menu(self.menubar, tearoff=0)
        helpmenu.add_command(label="Help Index", command=self.donothing)
        helpmenu.add_command(label="About...", command=self.donothing)
        self.menubar.add_cascade(label="Help", menu=helpmenu)



if __name__ == "__main__":
    root = tk.Tk()

    gui = SlicerGUI(root)

    root.mainloop()