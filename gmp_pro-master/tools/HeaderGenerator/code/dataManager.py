import json
import os


class dataManager:
    def __init__(self, parent):
        self.parent = parent

        self.__templateData = []  # list of template data (dicts)
        self.__result = []  # list of user inputs (dicts)
        self.__savePath = []  # list of saving path (strings)

    def readFile(self, pathFile):
        with open(pathFile, 'r') as f:
            data = json.load(f)

        # find template
        templateNameRef = data['template_info']['file_name']
        templateVersionRef = data['template_info']['template_version']
        templateTypeRef = data['template_info']['file_type']
        templateFoundData = None
        msgWarning = None
        for root, dirs, files in os.walk(self.parent.getTemplatePath()):
            for file in files:
                if file.endswith('.json'):
                    _fullPath = self.parent.getTemplatePath() + '\\' + file
                    with open(_fullPath, 'r') as _f:
                        _templateData = json.load(_f)
                    if _templateData['file_name'] == templateNameRef:
                        # name matched
                        if _templateData['template_version'] == templateVersionRef:
                            # version matched
                            templateFoundData = _templateData
                            if _templateData['file_type'] == templateTypeRef:
                                msgWarning = None
                                break
                            else:
                                msgWarning = 'Template with the same file type not found.\r\n'
                        else:
                            # version do not matched
                            if templateFoundData is None:
                                templateFoundData = _templateData
                            else:
                                # get higher version
                                if _templateData['template_version'] > templateFoundData['template_version']:
                                    templateFoundData = _templateData
                            msgWarning = 'Template with the same version not found.\r\n'
            else:
                # no exact matching template found
                if msgWarning is None:
                    # no matching file name
                    self.addMsgLog('No matching template found.\r\n', 'Error')
                else:
                    # same file name found, but no same version or file type
                    self.addMsgLog(msgWarning, 'Warning')

        self.__templateData.append(templateFoundData)
        self.__result.append(data)
        self.__savePath.append(pathFile)

    def readTemplate(self, path, savePath=''):
        with open(path, 'r') as f:
            self.__templateData.append(json.load(f))
            self.__result.append(dict())
            self.__savePath.append(savePath)
        print(len(self.__templateData))

    def closeTab(self, index):
        self.__templateData.pop(index)
        self.__result.pop(index)
        self.__savePath.pop(index)

    def __resultJsonWrite(self, index, path, res):
        dataToWrite = res.copy()
        dataToWrite['template_info'] = dict()
        dataToWrite['template_info']['template_version'] = self.__templateData[index].get('template_version')
        dataToWrite['template_info']['file_name'] = self.__templateData[index].get('file_name')
        dataToWrite['template_info']['file_type'] = self.__templateData[index].get('file_type')

        with open(path, 'w') as f:
            json.dump(dataToWrite, f, indent=4)

    def saveToNewFile(self, index, result):
        filename = self.parent.getSaveFileName('save file')
        if filename:
            try:
                self.__resultJsonWrite(index, filename, result)
            except IOError as e:
                self.addMsgLog(f'Cannot save file:\r\n{e}\r\n', 'Error')
            return filename
        else:
            return

    def save(self, index, res):
        if res is not None:
            self.__result[index] = res
            print(self.__result[index])

            # write file
            if self.__savePath[index] == "":
                # save to new file
                newPath = self.saveToNewFile(index, self.__result[index])
                if newPath is not None:
                    self.__savePath[index] = newPath
                else:
                    self.__savePath[index] = ""
                    self.addMsgLog('Error occurred while saving\r\n', 'Error')
                pathReturn = newPath
            else:
                # save to existing file
                self.__resultJsonWrite(index, self.__savePath[index], self.__result[index])
                pathReturn = self.__savePath[index]
            self.addMsgLog('Saved\r\n')
        else:
            self.addMsgLog('Error occurred while saving\r\n', 'Error')
            pathReturn = None

        return pathReturn

    def saveAs(self, index, res):
        if res is not None:
            self.__result[index] = res
            print(self.__result[index])

            newPath = self.saveToNewFile(index, self.__result[index])
            if newPath is not None:
                self.__savePath[index] = newPath
            else:
                self.__savePath[index] = ""
                self.addMsgLog('Error occurred while saving\r\n', 'Error')
        else:
            newPath = None

        return newPath

    def addMsgLog(self, msg, msgType='Info'):
        self.parent.addMsgLog(msg, msgType)

    def getTemplateData(self, index=-1):
        return self.__templateData[index]

    def getResult(self, index=-1):
        return self.__result[index]
