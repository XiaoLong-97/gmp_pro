from PyQt5 import QtGui, QtWidgets
from PyQt5.QtCore import *
import os
import json
import datetime
import re

from GMPWidget import QBoxWidget, QGroupWidget
from dataManager import *


class GMP_HG_mainWindow(QtWidgets.QMainWindow):
    def __init__(self):
        # super init
        super().__init__()
        self.setWindowIcon(QtGui.QIcon('../resource/icon.png'))
        self.setWindowTitle('GMP Header Generator')

        with open('../config.json', 'r') as f:
            self.__cfgData = json.load(f)

        self.dataMgr = dataManager(self)

        # setup window
        self.frameMain = None
        self.__menuBar = None

        self.setupMainWindow()
        self.setupMenuBar()
        self.setupMgr()
        self.setupMsgBox()
        self.setupUi()

        # show window
        self.show()

    def setupMainWindow(self):
        self.setObjectName('MainWindow')
        self.resize(1500, 1000)

        self.setCentralWidget(QtWidgets.QWidget())
        self.frameMain = self.centralWidget()
        self.frameMain.setGeometry(0, 0, self.size().width() - 20, self.size().height() - 20)

        self.layoutMain = QtWidgets.QVBoxLayout()
        self.frameMain.setLayout(self.layoutMain)

        self.editArea = QtWidgets.QTabWidget()
        self.editArea.show()
        self.editArea.setTabsClosable(True)
        self.editArea.tabCloseRequested.connect(self.eventTabClose)
        self.layoutMain.addWidget(self.editArea)

        self.statusBar().showMessage('Ready')

    def setupMenuBar(self):
        self.__menuBar = self.menuBar()

        # ----- file menu -----
        # create file menu
        menuFile = self.__menuBar.addMenu('&File')
        # new action
        actNew = QtWidgets.QAction('&New', self)
        actNew.setShortcut('Ctrl+N')
        actNew.setStatusTip('New configration file.')
        actNew.triggered.connect(self.eventNew)
        menuFile.addAction(actNew)
        # open action
        actOpen = QtWidgets.QAction('&Open', self)
        actOpen.setShortcut('Ctrl+O')
        actOpen.setStatusTip('Open configration file.')
        actOpen.triggered.connect(self.eventOpen)
        menuFile.addAction(actOpen)
        # save action
        actSave = QtWidgets.QAction('&Save', self)
        actSave.setShortcut('Ctrl+S')
        actSave.setStatusTip('Save configration file.')
        actSave.triggered.connect(self.eventSave)
        menuFile.addAction(actSave)
        # save as action
        actSaveAs = QtWidgets.QAction('S&ave as', self)
        actSaveAs.setShortcut('Shift+Ctrl+S')
        actSaveAs.setStatusTip('Save configration file as ...')
        actSaveAs.triggered.connect(self.eventSaveAs)
        menuFile.addAction(actSaveAs)
        # exit action
        actExit = QtWidgets.QAction('&Exit', self)
        actExit.setShortcut('Ctrl+E')
        actExit.setStatusTip('Exit.')
        actExit.triggered.connect(self.eventExit)
        menuFile.addAction(actExit)

        # ----- template menu -----
        # create template menu
        menuTemplate = self.__menuBar.addMenu('&Template')
        # new template action
        actNewTemplate = QtWidgets.QAction('&New template', self)
        actNewTemplate.setShortcut('Shift+Ctrl+N')
        actNewTemplate.setStatusTip('New template file.')
        actNewTemplate.triggered.connect(self.eventNewTemplate)
        menuTemplate.addAction(actNewTemplate)
        # import template action
        actImportTemplate = QtWidgets.QAction('&Import template to Library', self)
        actImportTemplate.setShortcut('Ctrl+I')
        actImportTemplate.setStatusTip('Import existing template file to template library.')
        actImportTemplate.triggered.connect(self.eventImportTemplate)
        menuTemplate.addAction(actImportTemplate)
        # set template path action
        actSetTemplatePath = QtWidgets.QAction('&Set template Path', self)
        actSetTemplatePath.setShortcut('Alt+S')
        actSetTemplatePath.setStatusTip('Set template path.')
        actSetTemplatePath.triggered.connect(self.eventSetTemplatePath)
        menuTemplate.addAction(actSetTemplatePath)
        # use absolute path check action
        actUseRelativePath = QtWidgets.QAction('&Use Relative Path', self)
        actUseRelativePath.setStatusTip('Whether use relative path or not.')
        actUseRelativePath.setCheckable(True)
        actUseRelativePath.setChecked(bool(self.__cfgData['flag_use_relative_path']))
        actUseRelativePath.triggered.connect(self.eventUseRelativePath)
        menuTemplate.addAction(actUseRelativePath)

        # ----- template menu -----
        # create template menu
        menuGenerate = self.__menuBar.addMenu('&Generate')
        # generate action
        actGenerate = QtWidgets.QAction('&Generate', self)
        actGenerate.setShortcut('Ctrl+G')
        actGenerate.setStatusTip('Generate header file.')
        actGenerate.triggered.connect(self.eventGenerate)
        menuGenerate.addAction(actGenerate)

    def setupMgr(self):
        self.dockProjMgr = QtWidgets.QDockWidget('template Library', self)
        self.addDockWidget(Qt.LeftDockWidgetArea, self.dockProjMgr)
        self.tree = QtWidgets.QTreeView(self.frameMain)
        self.modelFile = QtWidgets.QFileSystemModel()
        self.modelFile.setRootPath(QDir.currentPath())
        # self.modelFile.setRootPath(self.path)
        self.tree.setModel(self.modelFile)
        self.tree.setRootIndex(self.modelFile.index(self.__cfgData['template_path']))
        self.dockProjMgr.setWidget(self.tree)

        self.tree.doubleClicked.connect(self.eventTreeDoubleClicked)

        self.tree.setColumnHidden(1, True)
        self.tree.setColumnHidden(2, True)
        self.tree.setColumnHidden(3, True)

    def setupMsgBox(self):
        initMsgLog = 'Welcome to GMP Header Generator!\r\n' + \
                     '\r\n' + \
                     '................................................\r\n' + \
                     '................................................\r\n' + \
                     '.....MMMMMMMM.........MM.....,MMM....=MMWWDMN,..\r\n' + \
                     '...8MM.......M.......MMMM....N8MM ....:MM...MM8.\r\n' + \
                     '...MMM............. MM..MM?.?N.8M=....:MM..:MM..\r\n' + \
                     '..=MMD.............=M,..DMM.N..8M=....:MMMMZ,...\r\n' + \
                     '...MMM.....MMM.....=M,...MMMN..8M=....:MM.......\r\n' + \
                     '...=MM......M......=M,....MM...8M=....:MM.......\r\n' + \
                     '.....$M$$$$MMM.....===..........===..=NNMM+.....\r\n' + \
                     '................................................\r\n' + \
                     '................................................\r\n' + \
                     '....Generic..........Motor...........Platform...\r\n' + \
                     '.........for all Motor & all Platform...........\r\n' + \
                     '................................................\r\n' + \
                     '................................................\r\n' + \
                     '\r\n'

        self.msgBox = QtWidgets.QTextEdit()
        self.msgBox.setReadOnly(True)
        dock1 = QtWidgets.QDockWidget('Message Box', self)
        self.addDockWidget(Qt.BottomDockWidgetArea, dock1)
        dock1.setWidget(self.msgBox)

        self.addMsgLog(initMsgLog)
        self.addMsgLog('Current template path is : ' + self.__cfgData['template_path'] + '\r\n')

    def setupUi(self):
        # self.tabMain = QtWidgets.QTabWidget(self.frameMain)
        #
        # self.tabMain.setGeometry(10, 10, 100, 100)
        #
        # tab1 = QtWidgets.QWidget()
        # btn1 = QtWidgets.QPushButton('Button1', tab1)
        # self.tabMain.addTab(tab1, 'Tab1')
        #
        # tab2 = QtWidgets.QWidget()
        # btn2 = QtWidgets.QPushButton('Button2', tab2)
        # self.tabMain.addTab(tab2, 'Tab2')

        # self.dockProjMgr.setGeometry()

        # btn = QtWidgets.QPushButton('Button', self.frameMain)
        pass

    def writeConfig(self):
        with open('../config.json', 'w') as f:
            json.dump(self.__cfgData, f, indent=4)

    def addMsgLog(self, msg, msgType='Info'):
        log = self.msgBox.toPlainText()
        if msgType not in {'Info', 'Warning', 'Error'}:
            msgType = 'Info'
        self.msgBox.setPlainText(
            log + '[' + datetime.datetime.now().strftime('%Y-%m-%d %H:%M:%S') + '][' + msgType + '] ' + msg)
        self.msgBox.moveCursor(self.msgBox.textCursor().End)

    def plotTemplate(self, templateData):
        tab = QtWidgets.QSplitter(Qt.Horizontal)

        editTab = QtWidgets.QScrollArea()  # one editTab, which is a QScrollArea instance
        editTabContent = QBoxWidget('V', self.frameMain)
        tab.addWidget(editTab)

        previewBox = QtWidgets.QTextEdit()
        previewBox.setReadOnly(True)
        tab.addWidget(previewBox)

        tab.setStretchFactor(0, 1)
        tab.setStretchFactor(1, 2)

        # print(tab.widget(1))

        # general information plot function
        def plotGeneralInfo(_name, _container, _editType='line', _enable=False):
            width = 350
            height = 100

            _HWidget = QBoxWidget('H')

            _label = QtWidgets.QLabel(_name.replace('_', ' ').title() + ' :  ')
            if _editType == 'line':
                _editBox = QtWidgets.QLineEdit()
                _editBox.setMinimumWidth(width)
                _editBox.setText(templateData[_name])
                _editBox.setEnabled(_enable)
            elif _editType == 'box':
                _editBox = QtWidgets.QTextEdit()
                _editBox.setMinimumWidth(width)
                _editBox.setFixedHeight(height)
                _editBox.setPlainText(templateData[_name])
                _editBox.setEnabled(_enable)
            else:
                _editBox = None
                return
            _HWidget.addWidget(_label)
            _HWidget.addWidget(_editBox)

            _container.addWidget(_HWidget)

        # general information
        groupGeneralInfo = QGroupWidget('V', 'General Information', editTabContent)
        plotGeneralInfo('file_name', groupGeneralInfo)  # info
        plotGeneralInfo('template_version', groupGeneralInfo)  # info
        plotGeneralInfo('file_type', groupGeneralInfo)  # info
        plotGeneralInfo('file_header', groupGeneralInfo)  # info
        plotGeneralInfo('comment', groupGeneralInfo, _editType='box')  # info
        editTabContent.addWidget(groupGeneralInfo)  # add to content layout

        # definitions plot function
        def plotDefinitions(_data, _containerLayout, _containerWidget=editTabContent):
            _widget = QtWidgets.QWidget()
            _layout = QtWidgets.QHBoxLayout()

            # comment
            _label = QtWidgets.QLabel('// ' + _data['comment'])
            _containerLayout.addWidget(_label)

            if _data['type'] == 'None':
                _item = QtWidgets.QCheckBox(_data['content'])
                _layout.addWidget(_item)
                _item.setChecked(True)
                _item.setEnabled(False)
            elif _data['type'] == 'type_in':
                _item = QtWidgets.QCheckBox(_data['content'])
                _layout.addWidget(_item)
                _input = QtWidgets.QLineEdit()  # input box (QLineEdit)
                _input.setText(_data['default'])
                _layout.addWidget(_input)
                _item.setChecked(True)
                _item.setEnabled(False)
                _input.setEnabled(bool(_data['enable']))
                # where to get data
                _data['get'] = _input
                # # edit event
                # _input.textChanged.connect(self.eventEdit)
            elif _data['type'] == 'check':
                _item = QtWidgets.QCheckBox(_data['content'])
                _layout.addWidget(_item)
                _item.setChecked(bool(_data['default']))
                _item.setEnabled(bool(_data['enable']))
                # where to get data
                _data['get'] = _item
                # # edit event
                # _item.stateChanged.connect(self.eventEdit)
            elif _data['type'] == 'radio':
                _groupBox = QtWidgets.QGroupBox(_data['content'], _containerWidget)
                _groupLayout = QtWidgets.QVBoxLayout(_groupBox)
                for _member in _data['members']:
                    _radioBtn = QtWidgets.QRadioButton(_member['content'] + '  // ' + _member['comment'])
                    _groupLayout.addWidget(_radioBtn)
                    # where to get data
                    _member['get'] = _radioBtn
                    # # edit event
                    # _radioBtn.toggled.connect(self.eventEdit)
                # set to default
                for _member in _data['members']:
                    if _member['content'] == _data['default']:
                        _member['get'].setChecked(True)
                        break
                _groupBox.setLayout(_groupLayout)
                _layout.addWidget(_groupBox)
            elif _data['type'] == 'drop_down':
                _item = QtWidgets.QCheckBox(_data['content'])
                _item.setChecked(True)
                _item.setEnabled(False)
                _item.setMaximumWidth(200)
                _layout.addWidget(_item)

                _select = QtWidgets.QComboBox()
                for _opt in _data['options']:
                    _select.addItem(_opt)
                # where to get data
                _data['get'] = _select
                # # edit event
                # _select.currentIndexChanged.connect(self.eventEdit)
                # set to default
                _idx = 0
                for _opt in _data['options']:
                    if _opt == _data['default']:
                        _data['get'].setCurrentIndex(_idx)
                        break
                    else:
                        _idx = _idx + 1
                _layout.addWidget(_select)
            elif _data['type'] == 'group':
                _groupBox = QtWidgets.QGroupBox(_data['content'], _containerWidget)
                _groupLayout = QtWidgets.QVBoxLayout(_groupBox)

                for _member in _data['members']:
                    plotDefinitions(_member, _groupLayout, _groupBox)

                _groupBox.setLayout(_groupLayout)
                _layout.addWidget(_groupBox)
            else:
                self.addMsgLog('Template Error!\r\n', 'Error')
                return

            _widget.setLayout(_layout)
            _containerLayout.addWidget(_widget)

        # plot definitions
        # general definition
        # TODO
        # use my class
        groupGeneralDef = QtWidgets.QGroupBox('General Definition', editTabContent)
        groupLayoutGeneralDef = QtWidgets.QVBoxLayout(groupGeneralDef)
        plotDefinitions(templateData['general_define'], groupLayoutGeneralDef)  # def
        groupGeneralDef.setLayout(groupLayoutGeneralDef)
        editTabContent.addWidget(groupGeneralDef)
        # definitions
        groupDef = QtWidgets.QGroupBox('Definitions', editTabContent)
        groupLayoutDef = QtWidgets.QVBoxLayout(groupDef)
        for data in templateData['defines']:
            plotDefinitions(data, groupLayoutDef, groupDef)
        groupDef.setLayout(groupLayoutDef)
        editTabContent.addWidget(groupDef)

        editTab.setWidget(editTabContent)
        idx = self.editArea.addTab(tab, templateData['file_name'])
        self.editArea.setCurrentIndex(idx)

    def showPreview(self, focus=None):
        idx = self.editArea.currentIndex()  # get active tab index
        if idx >= 0:
            # get template data (dict)
            dataToSave = self.dataMgr.getTemplateData(idx)
            # get result dict
            res, highLight = self.getResult(dataToSave['defines'], focus)
            print(highLight)

            # get file name
            currentName = self.editArea.tabText(idx)
            if currentName[0] == '*':
                currentName = currentName[1:]

            # calculate file header on preview box
            textHeader = ''
            # file header comment
            textHeader += '/* --- ' + dataToSave["file_header"] + ' --- */\r\n\r\n'
            # file information
            textHeader += '/**\r\n'
            textHeader += ' * File Name: ' + currentName + '.' + dataToSave["file_type"] + '\r\n'
            textHeader += ' * Template Name: ' + dataToSave["file_name"] + '\r\n'
            textHeader += ' * Template version: ' + dataToSave["template_version"] + '\r\n'
            textHeader += ' * Last Edition: ' + datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S") + '\r\n'
            textHeader += ' */\r\n\r\n'
            # file comment
            cmtList = re.split(r'[\r\n]+', dataToSave['comment'])
            textHeader += '/**\r\n'
            for cmt in cmtList:
                textHeader += ' * ' + cmt + '\r\n'
            textHeader += ' */\r\n\r\n'
            # general define start
            if bool(dataToSave['general_define']['redef_check']):
                textHeader += '#ifndef ' + dataToSave['general_define']['content'] + '\r\n'
            textHeader += '#define ' + dataToSave['general_define']['content'] + '\r\n\r\n'

            # calculate definitions on preview box
            def calcDef(defData, _res):
                text = ''
                for _def in defData:
                    # comment
                    if _def['comment'] != '':
                        _cmtList = re.split(r'[\r\n]+', _def['comment'])
                        for _cmt in _cmtList:
                            text += '// ' + _cmt + '\r\n'

                    # redefine check start
                    if bool(_def['redef_check']):
                        text += '#ifndef ' + _def['content'] + '\r\n'

                    if _def['type'] == 'None':
                        text += '#define ' + _def['content'] + '\r\n\r\n'
                    elif _def['type'] == 'type_in':
                        text += '#define ' + _def['content'] + ' ' + _res[_def['content']] + '\r\n\r\n'
                    elif _def['type'] == 'check':
                        if not bool(_res[_def['content']]):
                            text += '// '
                        text += '#define ' + _def['content'] + '\r\n\r\n'
                    elif _def['type'] == 'radio':
                        text += '#define ' + _def['content'] + '\r\n'
                        for _opt in _def['members']:
                            # comment
                            if _opt['comment'] != '':
                                _cmtList = re.split(r'[\r\n]+', _opt['comment'])
                                for _cmt in _cmtList:
                                    text += '// ' + _cmt + '\r\n'

                            # redefine check start
                            if bool(_def['redef_check']):
                                if _opt['content'] != _res[_def['content']]:
                                    text += '// '
                                text += '#ifndef ' + _def['content'] + '\r\n'

                            if _opt['content'] != _res[_def['content']]:
                                text += '// '
                            text += '#define ' + _opt['content'] + '\r\n'

                            # redefine check end
                            if bool(_def['redef_check']):
                                if _opt['content'] != _res[_def['content']]:
                                    text += '// '
                                text += '#endif\r\n'

                            text += '\r\n'
                    elif _def['type'] == 'drop_down':
                        text += '#define ' + _def['content'] + ' ' + _res[_def['content']] + '\r\n'
                    elif _def['type'] == 'group':
                        text += '#define ' + _def['content'] + '\r\n'
                        text += calcDef(_def['members'], _res[_def['content']])
                    else:
                        pass

                    # redefine check end
                    if bool(_def['redef_check']):
                        text += '#endif\r\n'

                    if _def['type'] != 'group':
                        text += '\r\n'
                return text

            textDef = calcDef(dataToSave['defines'], res)

            # general define end
            textEnd = ''
            if bool(dataToSave['general_define']['redef_check']):
                textEnd += '#endif\r\n'

            # set initial format
            cursor = QtGui.QTextCursor(self.editArea.widget(idx).widget(1).document())
            initFormat = QtGui.QTextCharFormat()
            initFont = QtGui.QFont('Monaco', 9)
            initFormat.setFont(initFont)
            cursor.mergeCharFormat(initFormat)
            self.editArea.widget(idx).widget(1).setTextCursor(cursor)
            # with QFile('../resource/codeStyle.css') as file:
            # file = QFile('../resource/codeStyle.css')
            # file.open(QFile.ReadOnly)
            # stream = QTextStream(file)
            # # file.close()
            # self.editArea.widget(idx).widget(1).document().setDefaultStyleSheet(stream.readAll())
            #
            # cursor = QtGui.QTextCursor(self.editArea.widget(idx).widget(1).document())
            # cursor.movePosition(QtGui.QTextCursor.End)
            # # cursor.insertHtml('<highlighted>')
            # self.editArea.widget(idx).widget(1).clear()
            # flag = True
            # for t in re.split(r'[\r\n]+', textHeader + textDef + textEnd):
            #     cursor.movePosition(QtGui.QTextCursor.End)
            #     t = t + '\r\n'
            #     if flag:
            #         cursor.insertHtml(f'<hl>{t}</hl>')
            #     else:
            #         cursor.insertHtml(f'<nhl>{t}</nhl>')
            #     flag = not flag
            #     self.editArea.widget(idx).widget(1).setTextCursor(cursor)
            # cursor.insertHtml('</highlighted>')

            # html = '<highlighted>\r\n'
            # for t in re.split(r'[\r\n]+?', textHeader + textDef + textEnd):
            #     html += f'<hh>{t}<br></hh>\r\n'
            # html += '</highlighted>\r\n'
            # self.editArea.widget(idx).widget(1).setHtml(html)

            # cursor = QtGui.QTextCursor(self.editArea.widget(idx).widget(1).document())
            # initFormat = QtGui.QTextCharFormat()
            # initFormat.setFont(QtGui.QFont('Monaco', 9))
            # cursor.movePosition(QtGui.QTextCursor.End)
            # flag = True
            # self.editArea.widget(idx).widget(1).clear()
            # for t in re.split(r'[\r\n]+', textHeader + textDef + textEnd):
            #     if flag:
            #         initFormat.setBackground(QtGui.QBrush(QtGui.QColor('#AED6F1')))
            #     else:
            #         initFormat.setBackground(QtGui.QBrush(QtGui.QColor('#ffffff')))
            #     flag = not flag
            #     cursor.mergeCharFormat(initFormat)
            #     self.editArea.widget(idx).widget(1).setTextCursor(cursor)
            #     self.editArea.widget(idx).widget(1).append(t)
            #     cursor.movePosition(QtGui.QTextCursor.End)

            # set preview
            # self.editArea.widget(idx).widget(1).setHtml(
            #     f'<pre class="highlighted">{textHeader + textDef + textEnd}</pre>')
            # self.editArea.widget(idx).widget(1).setHtml(
            #     f'<highlighted><hh>{textHeader + textDef + textEnd}</hh></highlighted>')
            self.editArea.widget(idx).widget(1).setPlainText(textHeader + textDef + textEnd)
            newText = self.editArea.widget(idx).widget(1).toPlainText()

            if highLight is not None:
                startIdx = newText.find(highLight)
                cursor = QtGui.QTextCursor(self.editArea.widget(idx).widget(1).document())
                cursor.setPosition(startIdx)
                cursor.movePosition(cursor.StartOfLine)
                cursor.movePosition(cursor.EndOfLine, mode=cursor.KeepAnchor)

                highlightFormat = QtGui.QTextCharFormat()
                highlightFormat.setFontWeight(QtGui.QFont.Bold)
                highlightFormat.setForeground(QtGui.QColor('red'))
                cursor.mergeCharFormat(highlightFormat)
                cursor.movePosition(cursor.EndOfLine)

                self.editArea.widget(idx).widget(1).setTextCursor(cursor)

    def getResult(self, defData, focus=None):
        result = dict()
        focusDef = None
        for _data in defData:
            if _data['type'] == 'type_in':
                # get result from a QLineEdit obj
                result[_data['content']] = _data['get'].text()
                # get focused definition
                if _data['get'] is focus:
                    focusDef = _data['content']
            elif _data['type'] == 'check':
                # get result from a QCheckBox obj
                result[_data['content']] = _data['get'].isChecked()
                # get focused definition
                if _data['get'] == focus:
                    focusDef = _data['content']
            elif _data['type'] == 'radio':
                # get result from a LIST of QRadioButton obj
                # loop implement
                for _member in _data['members']:
                    if _member['get'].isChecked():
                        result[_data['content']] = _member['content']
                        # get focused definition
                        if _member['get'] == focus:
                            focusDef = _member['content']
                        break
                else:
                    # raise error
                    self.addMsgLog('Please select one.\r\n', 'Error')
                    self.addMsgLog('Definition path: ' + _data['content'] + '\r\n', 'Error')
                    return
            elif _data['type'] == 'drop_down':
                # get result from a QComboBox obj
                result[_data['content']] = _data['get'].currentText()
                # get focused definition
                if _data['get'] == focus:
                    focusDef = _data['content']
            elif _data['type'] == 'group':
                # get result from a group
                # recursion implement
                res, fDef = self.getResult(_data['members'], focus)
                if res is not None:
                    result[_data['content']] = res
                    if fDef is not None:
                        focusDef = fDef
                else:
                    self.addMsgLog('Definition path: ' + _data['content'] + '\r\n', 'Error')
                    return
            else:
                pass
        return result, focusDef

    def setResult(self, defData, res):
        flags = dict()
        for key in res:
            if key != 'template_info':
                flags[key] = False

        state = 'ok'
        for _data in defData:
            if _data['content'] in res:
                content = _data['content']
                flags[content] = True
                if _data['type'] == 'group' or bool(_data['enable']):
                    if _data['type'] == 'type_in':
                        # set result to a QLineEdit obj
                        _data['get'].setText(res[content])
                    elif _data['type'] == 'check':
                        # get result from a QCheckBox obj
                        _data['get'].setChecked(bool(res[content]))
                    elif _data['type'] == 'radio':
                        # get result from a LIST of QRadioButton obj
                        # loop implement
                        for _member in _data['members']:
                            if _member['content'] == res[content]:
                                _member['get'].setChecked(True)
                                break
                        else:
                            state = 'warning'
                            self.addMsgLog('No matching options found, used default value.\r\n', 'Warning')
                            self.addMsgLog('Definition path: ' + _data['content'] + '\r\n', 'Warning')
                    elif _data['type'] == 'drop_down':
                        # get result from a QComboBox obj
                        _idx = 0
                        for _opt in _data['options']:
                            if _opt == res[content]:
                                _data['get'].setCurrentIndex(_idx)
                                break
                            else:
                                _idx = _idx + 1
                        else:
                            state = 'warning'
                            self.addMsgLog('No matching options found, use default value.\r\n', 'Warning')
                            self.addMsgLog('Definition path: ' + _data['content'] + '\r\n', 'Warning')
                    elif _data['type'] == 'group':
                        # get result from a group
                        # recursion implement
                        state = self.setResult(_data['members'], res[content])
                        if state != 'ok':
                            self.addMsgLog('Definition path: ' + _data['content'] + '\r\n', 'Warning')
                    else:
                        pass
                else:
                    # check if saved value same to the default for disabled difinition
                    if _data['type'] == 'check':
                        _default = bool(_data['default'])
                        _res = bool(res[content])
                    else:
                        _default = _data['default']
                        _res = res[content]
                    if _default != _res:
                        state = 'warning'
                        self.addMsgLog(
                            'Definition is disabled in template, the default value is different from it in opened file.\r\n',
                            'Warning')
                        self.addMsgLog('Definition path: ' + _data['content'] + '\r\n', 'Warning')
            elif _data['type'] != 'None':
                # definition in template but not in result
                state = 'warning'
                self.addMsgLog('New definition in template, use default value.\r\n', 'Warning')
                self.addMsgLog('Definition path: ' + _data['content'] + '\r\n', 'Warning')

        # check if there are definitions that in result but not in template
        for key in flags:
            if flags[key] is False:
                state = 'warning'
                self.addMsgLog('Definition not found in template, it will be ignored.\r\n', 'Warning')
                self.addMsgLog('Definition path: ' + key + '\r\n', 'Warning')

        return state

    # call it when:
    # 1. save a file as ...
    def getSaveFileName(self, title, initPath='last_save_path', fileType='JSON(*.json)'):
        if initPath == 'last_save_path':
            path = self.__cfgData['last_save_path']
        elif initPath == 'template_path':
            path = self.__cfgData['template_path']
        else:
            path = initPath
        filename, _ = QtWidgets.QFileDialog.getSaveFileName(self, title, path, fileType)
        return filename

    # call it when:
    # 1. open a template to new a file
    # 2. open an existing file
    def getOpenFileName(self, title, initPath='template_path', fileType='JSON(*.json)'):
        if initPath == 'last_save_path':
            path = self.__cfgData['last_save_path']
        elif initPath == 'template_path':
            path = self.__cfgData['template_path']
        else:
            path = initPath
        filename, _ = QtWidgets.QFileDialog.getOpenFileName(self, title, path, fileType)
        return filename

    def getTemplatePath(self):
        return self.__cfgData['template_path']

    def connectEventEdit(self, defDate):
        for _data in defDate:
            if _data['type'] == 'type_in':
                # edit event
                _data['get'].textChanged.connect(self.eventEdit)
            elif _data['type'] == 'check':
                # edit event
                _data['get'].stateChanged.connect(self.eventEdit)
            elif _data['type'] == 'radio':
                for _member in _data['members']:
                    # edit event
                    _member['get'].toggled.connect(self.eventEdit)
            elif _data['type'] == 'drop_down':
                # edit event
                _data['get'].currentIndexChanged.connect(self.eventEdit)
            elif _data['type'] == 'group':
                self.connectEventEdit(_data['members'])

    @pyqtSlot(int)
    def eventTabClose(self, index):
        closeName = self.editArea.tabText(index)
        if closeName[0] == '*':
            # this file not saved
            # ask for save reply
            msg = f'Do you want to save this file?\r\n    {closeName[1:]}'
            reply = QtWidgets.QMessageBox.question(self, 'save file?', msg,
                                                   QtWidgets.QMessageBox.Yes | QtWidgets.QMessageBox.No |
                                                   QtWidgets.QMessageBox.Cancel)
            if reply == QtWidgets.QMessageBox.Cancel:
                return
            if reply == QtWidgets.QMessageBox.Yes:
                # save file
                self.eventSave(index)
        self.editArea.removeTab(index)
        self.dataMgr.closeTab(index)

    @pyqtSlot()
    def eventEdit(self):
        # print(self.sender())
        if isinstance(self.sender(), QtWidgets.QRadioButton) and not self.sender().isChecked():
            return
        idx = self.editArea.currentIndex()
        if idx >= 0:
            self.showPreview(self.sender())
            currentName = self.editArea.tabText(idx)
            if currentName[0] != '*':
                self.editArea.setTabText(idx, '*' + currentName)

    @pyqtSlot()
    def eventNew(self):
        f = self.getOpenFileName('Select Template')
        if os.path.isfile(f):
            self.dataMgr.readTemplate(f)
            self.plotTemplate(self.dataMgr.getTemplateData())
            self.showPreview()
            self.connectEventEdit(self.dataMgr.getTemplateData()['defines'])

    @pyqtSlot()
    def eventOpen(self):
        f = self.getOpenFileName('Open File', 'last_save_path')
        if os.path.isfile(f):
            # plot template
            self.dataMgr.readFile(f)
            self.plotTemplate(self.dataMgr.getTemplateData())
            # fill result
            s = self.setResult(self.dataMgr.getTemplateData()['defines'], self.dataMgr.getResult())
            self.showPreview()
            self.connectEventEdit(self.dataMgr.getTemplateData()['defines'])
            # rename tab
            newName, _ = os.path.splitext(os.path.basename(f))
            self.editArea.setTabText(self.editArea.currentIndex(), newName)
            # display msg
            self.addMsgLog(f'File opened: {newName}\r\n')
            print(s)

    @pyqtSlot()
    def eventSave(self, idx=-1):
        if idx < 0:
            # event called by user save
            idx = self.editArea.currentIndex()  # get active tab index
        if idx >= 0:
            # get data (dict)
            dataToSave = self.dataMgr.getTemplateData(idx)
            # get result dict
            res, _ = self.getResult(dataToSave['defines'])
            path = self.dataMgr.save(idx, res)

            if path is not None:
                # rename tab
                newName, _ = os.path.splitext(os.path.basename(path))
                self.editArea.setTabText(idx, newName)
                # save last saving path
                self.__cfgData['last_save_path'] = os.path.dirname(path)
                self.writeConfig()
                # update preview
                self.showPreview()

    @pyqtSlot()
    def eventSaveAs(self):
        idx = self.editArea.currentIndex()
        if idx >= 0:
            # get data (dict)
            dataToSave = self.dataMgr.getTemplateData(idx)
            # get result dict
            res = self.getResult(dataToSave['defines'])
            path = self.dataMgr.saveAs(idx, res)
            self.__cfgData['last_save_path'] = path
            self.writeConfig()

            if path is not None:
                # rename tab
                newName, _ = os.path.splitext(os.path.basename(path))
                self.editArea.setTabText(idx, newName)
                # save last saving path
                self.__cfgData['last_save_path'] = os.path.dirname(path)
                self.writeConfig()
                # update preview
                self.showPreview()

    @pyqtSlot()
    def eventExit(self):
        print('Exit')
        self.close()

    @pyqtSlot()
    def eventNewTemplate(self):
        # TODO
        self.addMsgLog('To be updated...\r\n')
        print('New template')

    @pyqtSlot()
    def eventImportTemplate(self):
        # TODO
        self.addMsgLog('To be updated...\r\n')
        print('Import template')

    @pyqtSlot()
    def eventSetTemplatePath(self):
        newPath = QtWidgets.QFileDialog.getExistingDirectory(self, 'select path', self.__cfgData['template_path'])
        if newPath:
            if bool(self.__cfgData['flag_use_relative_path']):
                self.__cfgData['template_path'] = os.path.relpath(newPath, os.getcwd())
            else:
                self.__cfgData['template_path'] = newPath
            self.writeConfig()
            self.tree.setRootIndex(self.modelFile.index(newPath))
            self.addMsgLog('Set template path to : ' + self.__cfgData['template_path'] + '\r\n')
            print('Set template path to : ' + self.__cfgData['template_path'])
        else:
            self.addMsgLog('ERROR: Set template path to invalid path: ' + newPath + '\r\n')
            print('Set template path --- Invalid path')

    @pyqtSlot()
    def eventUseRelativePath(self):
        self.__cfgData['flag_use_relative_path'] = 1 - self.__cfgData['flag_use_relative_path']
        if bool(self.__cfgData['flag_use_relative_path']):
            self.__cfgData['template_path'] = os.path.relpath(self.__cfgData['template_path'], os.getcwd())
            self.addMsgLog('Set use relative path.\r\n')
        else:
            self.__cfgData['template_path'] = os.path.abspath(self.__cfgData['template_path'])
            self.addMsgLog('Do not use absolute path.\r\n')
        self.writeConfig()

    @pyqtSlot()
    def eventTreeDoubleClicked(self):
        index = self.tree.currentIndex()
        file_path = self.modelFile.filePath(index)
        print(file_path)
        if os.path.isfile(file_path):
            self.dataMgr.readTemplate(file_path)
            self.plotTemplate(self.dataMgr.getTemplateData())
            self.showPreview()
            self.connectEventEdit(self.dataMgr.getTemplateData()['defines'])

    @pyqtSlot()
    def eventGenerate(self):
        idx = self.editArea.currentIndex()
        if idx >= 0:
            # TODO
            print('generate')
