import sys
from PyQt5.QtWidgets import QApplication, QMainWindow
from Ui_MainWindow import Ui_MainWindow


class MainWindow:
    def __init__(self):
        self.main_win = QMainWindow()
        self.ui = Ui_MainWindow()
        self.ui.setupUi(self.main_win)
        self.ui.reconnect_slider.valueChanged.connect(self.reconnect_changed)
        self.ui.timeout_slider_fast.valueChanged.connect(self.timeout_fast_changed)
        self.ui.timeout_slider_slow.valueChanged.connect(self.timeout_slow_changed)

    def show(self):
        self.main_win.show()

    def reconnect_changed(self):
        new_reconnect = str(self.ui.reconnect_slider.value())
        self.ui.recconect.setText(new_reconnect)

    def timeout_fast_changed(self):
        new_timeout_fast = str(self.ui.timeout_slider_fast.value())
        self.ui.timeout_fast.setText(new_timeout_fast)

    def timeout_slow_changed(self):
        new_timeout_slow = str(self.ui.timeout_slider_slow.value())
        self.ui.timeout_slow.setText(new_timeout_slow)


if __name__ == '__main__':
    app = QApplication(sys.argv)
    main_win = MainWindow()
    main_win.show()
    sys.exit(app.exec_())
