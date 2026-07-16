import typing
from PyQt5 import QtWidgets, QtCore, Qt


class QBoxWidget(QtWidgets.QWidget):
    def __init__(self, direction,
                 parent: typing.Optional['QtWidgets.QWidget'] = None):
        super().__init__(parent)

        if direction == 'H':
            self.layout = QtWidgets.QHBoxLayout()  # init HBoxLayout
        elif direction == 'V':
            self.layout = QtWidgets.QVBoxLayout()  # init VBoxLayout

        super().setLayout(self.layout)  # set layout

    def addWidget(self, w):
        self.layout.addWidget(w)


class QGroupWidget(QtWidgets.QGroupBox):
    def __init__(self, direction,
                 title: typing.Optional[str] = "",
                 parent: typing.Optional[QtWidgets.QWidget] = None):
        super().__init__(title, parent)

        if direction == 'H':
            self.layout = QtWidgets.QHBoxLayout()  # init HBoxLayout
        elif direction == 'V':
            self.layout = QtWidgets.QVBoxLayout()  # init VBoxLayout

        super().setLayout(self.layout)  # set layout

    def addWidget(self, w):
        self.layout.addWidget(w)
