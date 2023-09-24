from tkinter import *
from tkinter import messagebox

class Cryptography(Frame):

    def __init__(self):

        Frame.__init__(self)
        self.master.title("Cryptography")
        self.pack()

        self.LblYear = Label(self, text = "Cryptography", font = ("Times New Roman", 25)) #Label widget
        self.LblYear.pack(pady = 20)

        # Variable to hold the user entry which is a datatype of integer
        self.yearEntry = Entry(self, font = ("Times New Roman", 15)) #Entry widget or textbox
        self.yearEntry.pack(pady = 20)

        self.YearVar1 = IntVar() # Variable to hold the user entry which is a datatype of integer
        self.yearEntry1 = Entry(self, font = ("Times New Roman", 15), textvariable = self.YearVar1) #Entry widget or textbox
        self.yearEntry1.pack(pady = 20)
        

        self.Btn = Button(self, text = " Encryption", font = ("Times New Roman", 18), command = self.encryption) #Button widget
        self.Btn.pack(pady = 20)

        self.Btn = Button(self, text = " Decryption", font = ("Times New Roman", 18), command = self.decryption) #Button widget
        self.Btn.pack(pady = 20)


    def encryption(self):
        try:
            text = self.yearEntry.get()
            num = int(self.YearVar1.get())
            code = ""
            for ch in text:
                ordVal = ord(ch) 
                cipherVal = ordVal - num
                if cipherVal > ord('z'):
                    cipherVal = ord('a') + num - \
                        (ord('z') - ordVal + 1)
                code += chr(cipherVal) 
            
            messagebox.showinfo("Your encrypted messaged is", f"the messaged is: {code}")

        except ValueError:
            messagebox.showerror("Error", "Please enter the message! / wrong format")


    def decryption(self):
        
        try:
            code = self.yearEntry.get()
            num = int(self.YearVar1.get())
            text = ""
            for ch in code:
                ordVal = ord(ch)
                cipherVal = ordVal + num
                if cipherVal < ord('0'):
                    cipherVal = ord('Z') - num - \
                        (ord('a') + ordVal - 1 )
                text += chr(cipherVal)
                print(text)
            messagebox.showinfo("Your decrypted messaged is", f"the messaged is: {text}")
        except ValueError:
            messagebox.showerror("Error", "Please enter the message! / wrong format")

def main():

    Cryptography().mainloop()
main()