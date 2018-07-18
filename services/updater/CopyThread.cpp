#include "CopyThread.h"

CopyThread::CopyThread()
{

}

void CopyThread::setPath(QString _sourceDir, QString _destinationDir, bool _overWriteDirectory)
{
    sourceDir = _sourceDir;
    destinationDir = _destinationDir;
    overWriteDirectory = _overWriteDirectory;
}

bool CopyThread::copyPath(QString sourceDir, QString destinationDir, bool overWriteDirectory, bool counting)
{
    QDir originDirectory(sourceDir);

    if (!originDirectory.exists())
    {
        return false;
    }

    QDir destinationDirectory(destinationDir);

    if(destinationDirectory.exists() && !overWriteDirectory)
    {
        return false;
    }
    else if(destinationDirectory.exists() && overWriteDirectory)
    {
        destinationDirectory.removeRecursively();
    }

    originDirectory.mkpath(destinationDir);

    foreach (QString directoryName, originDirectory.entryList(QDir::Dirs | \
                                                              QDir::NoDotAndDotDot))
    {
        QString destinationPath = destinationDir + "/" + directoryName;
        originDirectory.mkpath(destinationPath);
        copyPath(sourceDir + "/" + directoryName, destinationPath, overWriteDirectory, counting);
    }

   // int fileNums = originDirectory.entryList(QDir::Files).size();

    foreach (QString fileName, originDirectory.entryList(QDir::Files))
    {
        auto fileSource = sourceDir + "/" + fileName;
        auto fileDist = destinationDir + "/" + fileName;
        qDebug()<<"........ fileSource "<<fileSource;
        qDebug()<<"........ fileDist "<<fileDist;

        if(counting)
        {
            filesCount++;

        }
        else
        {
            QFile::copy(fileSource, fileDist);
            emit copyFile();
        }
    }

    /*! Possible race-condition mitigation? */
    QDir finalDestination(destinationDir);
    finalDestination.refresh();

    if(finalDestination.exists())
    {
        return true;
    }

    return false;
}

void CopyThread::doWork()
{
    filesCount = 0;

    copyPath(sourceDir, destinationDir, overWriteDirectory, true);
    emit filesCounted(filesCount);

    bool status =copyPath(sourceDir, destinationDir, overWriteDirectory, false);
    emit copyProcessComplete(status);
}
