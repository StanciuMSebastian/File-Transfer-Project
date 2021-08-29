#include "MainWindow.h"
#include "LoginWindow.h"
#include "UploadDialog.h"
#include "changePasswordDialog.h"
#include"AllFiles.h"
MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    ui.listWidget->setSelectionMode(QAbstractItemView::MultiSelection);
}

void MainWindow::on_actionChange_Password_triggered()
{
    changePasswordDialog* p = new changePasswordDialog;
    p->exec();

    delete p;
}

void MainWindow::on_actionLog_out_triggered()
{
    LoginWindow* l = new LoginWindow;
    delete this->c;

    ui.listWidget->clear();

    AllFiles::Files.clear();

    this->close();
    l->show();
}

QString MainWindow::processFilename(QString filepath)
{
    QString filename = "";

    for (int i = 0; i < filepath.size(); i++)
    {
        if (filepath[i] == '/')
            filename = "";
        else
            filename += filepath[i];
    }

    return filename;
}

void MainWindow::on_uploadButton_clicked()
{
    QString filter = "All Files (*.*) ;; Text File (*.txt) ;; Image File(*.png)";
    QString filepath = QFileDialog::getOpenFileName(this, "Select a file", "C://", filter);
    QString filename = processFilename(filepath);
    QFile file(filepath);



    if (!file.open(QIODevice::ReadOnly)) //|QFile::Text, desi nu trebuie neaparat sa fie fisier de tip text
    {
        QMessageBox::warning(this, "Warning", "Cannot open file :" + file.errorString());
        return;
    }
    UploadDialog* u = new UploadDialog;
    file.close();

    if (!this->c->sendFile(filepath, filename, u))
    {
        QMessageBox::warning(this, "Warning", "Nu s-a putut trimite fisierul : " + file.errorString());
        file.close();
        return;
    }

    ui.listWidget->addItem(filename);

}

void MainWindow::on_downloadFromButton_clicked()
{
    QModelIndexList selectedList = ui.notificationsList->selectionModel()->selectedIndexes(); // take the list of selected indexes
    std::sort(selectedList.begin(), selectedList.end(), [](const QModelIndex& a, const QModelIndex& b)->bool {return a.row() > b.row(); }); // sort from bottom to top
    QString filter = "All Files (*.*) ;; Text File (*.txt) ;; Image File(*.png)";

    c->sendPacketType(P_Download);
    c->sendInt(c->getID());

    for (const QModelIndex& singleIndex : selectedList)
    {
        QString Qfilename = QVariant(ui.notificationsList->model()->data(ui.notificationsList->model()->index(singleIndex.row(), singleIndex.column()), Qt::DisplayRole)).toString();
        QString Qfilepath = QFileDialog::getSaveFileName(this, "Select a file", "E:\\DownloadFiles\\" + Qfilename, filter);
        std::string filename = Qfilename.toUtf8().constData();
        std::string filepath = Qfilepath.toUtf8().constData();

        c->sendString(filename);

        ofstream fileItself(filepath, std::ios::binary);
        int fileSize;
        c->getInt(fileSize);

        char* fileContents = new char[fileSize];

        c->getCharString(fileContents, fileSize);
        fileContents[fileSize] = '\0';

        fileItself.write(fileContents, fileSize);


        fileItself.close();
    }
    c->sendString("done");
}

void MainWindow::on_downloadButton_clicked()
{
    QModelIndexList selectedList = ui.listWidget->selectionModel()->selectedIndexes(); // take the list of selected indexes
    std::sort(selectedList.begin(), selectedList.end(), [](const QModelIndex& a, const QModelIndex& b)->bool {return a.row() > b.row(); }); // sort from bottom to top
    QString filter = "All Files (*.*) ;; Text File (*.txt) ;; Image File(*.png)";

    c->sendPacketType(P_Download);
    c->sendInt(c->getID());

    for (const QModelIndex& singleIndex : selectedList)
    {
        QString Qfilename = QVariant(ui.listWidget->model()->data(ui.listWidget->model()->index(singleIndex.row(), singleIndex.column()), Qt::DisplayRole)).toString();
        QString Qfilepath = QFileDialog::getSaveFileName(this, "Select a file", "E:\\DownloadFiles\\file.txt", filter);
        std::string filename = Qfilename.toUtf8().constData();
        std::string filepath = Qfilepath.toUtf8().constData();
        std::string filebuffer;

        c->sendString(filename);
        c->getString(filebuffer);

        ofstream fileItself(filepath, std::ios::binary);
        int fileSize;
        c->getInt(fileSize);
        char* fileContents = new char[fileSize];

        c->getCharString(fileContents, fileSize);

        fileItself.write(fileContents, fileSize);        

        fileItself.close();
    }
    c->sendString("done");

}

void MainWindow::on_removeButton_clicked()
{
    //remove button should delete from database
    //send all files in a string+ server should parse them and delete from database
    QModelIndexList selectedList = ui.listWidget->selectionModel()->selectedIndexes(); // take the list of selected indexes
    std::sort(selectedList.begin(), selectedList.end(), [](const QModelIndex& a, const QModelIndex& b)->bool {return a.row() > b.row(); }); // sort from bottom to top
    Client* c = c->getInstance();
    c->sendPacketType(P_Remove);
    c->sendInt(c->getID());

    for (const QModelIndex& singleIndex : selectedList)
    {
        QString nume= QVariant(ui.listWidget->model()->data(ui.listWidget->model()->index(singleIndex.row(), singleIndex.column()), Qt::DisplayRole)).toString();
        std::string filename = nume.toUtf8().constData();
        c->sendString(filename);
        std::cout << filename << endl;
        ui.listWidget->model()->removeRow(singleIndex.row());

        int index = singleIndex.row();
        AllFiles::Files.erase(AllFiles::Files.begin() + index);
    }

    c->sendString("end");
   
}

void MainWindow::setClient()
{
    this->c = c->getInstance();
    this->ui.rankLabel->setText(QString::fromUtf8(c->getRank()));


    for (int i = 0; i < AllFiles::Files.size(); i++)
    {
        QString names = QString::fromStdString(AllFiles::Files[i]);
        if (names != "end")
            ui.listWidget->addItem(names);
    }

    std::string filename;
    c->getString(filename);
    while (filename != "done")
    {
        ui.notificationsList->addItem(QString::fromUtf8(filename.c_str()));
        c->getString(filename);
    }
}
