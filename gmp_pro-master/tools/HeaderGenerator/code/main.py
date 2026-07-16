import os.path
import sys
from PyQt5.QtWidgets import QApplication, QMainWindow
from PyQt5 import QtCore

import mainWindow

if __name__ == '__main__':
    print("hello!")

    app = QApplication(sys.argv)
    ui = mainWindow.GMP_HG_mainWindow()
    sys.exit(app.exec_())
