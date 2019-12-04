import tkinter as tk
from tkinter import filedialog
from objviewer import objView

class SlicerGUI:
    def __init__(self, master):
        self.master = master
        master.title("Slicer")

        self.label = tk.Label(master, text="Load a wavefront 3D object file.")
        self.label.pack()

        self.greet_button = tk.Button(master, text="Open .obj File", command=self.openFile)
        self.greet_button.pack()

        self.close_button = tk.Button(master, text="Close", command=master.quit)
        self.close_button.pack()

    def openFile(self):
        self.filename = tk.filedialog.askopenfilename(initialdir="/", title="Select file",
                                                      filetypes=(("Object files", "*.obj"), ("all files", "*.*")))
        objView(self.filename)


if __name__ == "__main__":
    root = tk.Tk()
    gui = SlicerGUI(root)
    root.mainloop()