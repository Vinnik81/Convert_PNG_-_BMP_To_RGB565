#define STB_IMAGE_IMPLEMENTATION

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "stb_image.h"
#include <QFileDialog>
#include <QMessageBox>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <QFile>
#include <QTextStream>
#include <QDragEnterEvent>
#include <QMimeData>



#pragma pack(push, 1)

struct BMPHeader
{
    uint16_t bfType;
    uint32_t bfSyze;
    uint16_t bfReserved1;
    uint16_t bfReserved2;
    uint32_t bfOfBits;
    uint32_t biSize;
    int32_t biWidth;
    int32_t biHeight;
    uint16_t biPlanes;
    uint16_t biBitCount;
    uint32_t biCompression;
    uint32_t biSizeImage;
    int32_t biXPelsPerMeter;
    int32_t biYPelsPerMeter;
    uint32_t biClrUsed;
    uint32_t biClrImportant;
};

#pragma pack(pop)

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setAcceptDrops(true);
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowMaximizeButtonHint);

    connect(ui->selectFileButton, &QPushButton::clicked, this, &MainWindow::on_selectFileButton_clicked);
    connect(ui->convertButton, &QPushButton::clicked, this, &MainWindow::on_convertButton_clicked);
    connect(ui->saveButton, &QPushButton::clicked, this, &MainWindow::on_saveButton_clicked);
    connect(ui->clearButton, &QPushButton::clicked, this, &MainWindow::on_clearButton_clicked);

    updateFileCount();
}

MainWindow::~MainWindow()
{
    delete ui;
}

uint16_t MainWindow::convertTo565(uint8_t r, uint8_t g, uint8_t b)
{
    return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
}

void MainWindow::loadPNG(const char *filename, std::vector<uint16_t> &data, int &width, int &height)
{
    int channels;
    unsigned char* img = stbi_load(filename, &width, &height, &channels, 3);

    if (!img)
    {
        QMessageBox::critical(this, "Error", "Cannot load Image");
        return;
    }

    data.resize(width * height);

    for (int i = 0; i < width * height; ++i)
    {
        int index = i * 3;
        uint8_t r = img[index];
        uint8_t g = img[index + 1];
        uint8_t b = img[index + 2];
        data[i] = convertTo565(r, g, b);
    }

    stbi_image_free(img);
}

void MainWindow::loadBMP(const char *filename, std::vector<uint16_t> &data, int &width, int &height)
{
    std::ifstream file(filename, std::ios::binary);

    if (!file)
    {
        QMessageBox::critical(this, "Error", "Cannot open file");
        return;
    }

    BMPHeader header;
    file.read(reinterpret_cast<char*>(&header), sizeof(BMPHeader));

    if (header.bfType != 0x4D42)
    {
        QMessageBox::critical(this, "Error", "Not a BMP file");
        return;
    }

    if (header.biBitCount != 32)
    {
        QMessageBox::critical(this, "Error", "Only 32-bit BMP files are supported");
        return;
    }

    width = header.biWidth;
    height = header.biHeight;

    file.seekg(header.bfOfBits, std::ios::beg);
    data.resize(width * height);

    for (int y = height - 1; y >= 0; y--)
    {
        for (int x = 0; x < width; x++)
        {
            uint8_t b, g, r, a;
            file.read(reinterpret_cast<char*>(&b), 1);
            file.read(reinterpret_cast<char*>(&g), 1);
            file.read(reinterpret_cast<char*>(&r), 1);
            file.read(reinterpret_cast<char*>(&a), 1);
            data[y * width + x] = convertTo565(r, g, b);
        }
    }
    file.close();
}

void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasUrls())
    {
        event->acceptProposedAction();
    }
}

void MainWindow::dropEvent(QDropEvent *event)
{
    const QMimeData *mimeData = event->mimeData();

    if (mimeData->hasUrls())
    {
        foreach (const QUrl &url, mimeData->urls())
        {
            QString filename = url.toLocalFile();
            if (filename.endsWith(".png") || filename.endsWith(".bmp"))
            {
               fileList.append(filename);
               ui->fileListWidget->addItem(filename);
               updateFileCount();
            }
        }
    }
}

void MainWindow::on_selectFileButton_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, "Open Image File", "", "Image Files (*.png *.bmp)");

    if(!filename.isEmpty())
    {
        fileList.append(filename);
        ui->fileListWidget->addItem(filename);
        updateFileCount();
    }
}

void MainWindow::updateFileCount()
{
    ui->fileCountLabel->setText(QString("File added: %1").arg(fileList.size()));
}

void MainWindow::on_convertButton_clicked()
{
    QString outputDirectory = "C:/ConvertFileTo_C";

    if (!QDir(outputDirectory).exists())
    {
        QDir().mkpath(outputDirectory);
    }

     ui->outputTextEdit->clear();
     int totalFiles = fileList.size();
     int currentFileIndex = 0;

    for (const QString &filename : fileList)
        {
            int width, height;
           /* bool widthOk, heightOk;
            int width = ui->widthLineEdit->text().toInt(&widthOk);
            int height = ui->heightLineEdit->text().toInt(&heightOk);

            if (!widthOk || !heightOk || width <= 0 || height <= 0)
            {
                QMessageBox::warning(this, "Warning", "Please enter valid width and height.");
                return;
            } */

            std::vector<uint16_t>().swap(data);

            //data.clear();

            if (filename.endsWith(".png"))
            {
                loadPNG(filename.toStdString().c_str(), data, width, height);
            }
            else if (filename.endsWith(".bmp"))
            {
                loadBMP(filename.toStdString().c_str(), data, width, height);
            }

            if (!data.empty())
            {
                std::ostringstream oss;
                for (size_t i = 0; i < data.size(); ++i)
                {
                    oss << "0x" << std::hex << std::setw(4) << std::setfill('0') << data[i] << " ";
                    if ((i + 1) % 10 == 0) oss << "\n"; // Add line breaks every 10 values
                }

                ui->outputTextEdit->appendPlainText(QString::fromStdString(oss.str()));

                QString baseFileName = QFileInfo(filename).completeBaseName();
                QString extension = QFileInfo(filename).suffix();
                QString saveFileName = outputDirectory + "/" + baseFileName + "_" + extension + ".c";

                if (!saveFileName.isEmpty())
                {
                    QFile file(saveFileName);

                    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
                    {
                        QMessageBox::warning(this, "Warning", "Cannot save file");
                        return;
                    }

                    QTextStream out(&file);

                    out << "#include <stdint.h>\n\n";
                    out << "const uint16_t " << baseFileName << "_" << extension << "_image_data[] = {\n";

                    QStringList lines = QString::fromStdString(oss.str()).split('\n');

                    for (const QString &line : lines)
                    {
                        out << line << "\n";
                    }

                    out << "};\n";
                    file.close();
                }
            }
            currentFileIndex++;
            int progress = static_cast<int>((static_cast<float>(currentFileIndex) / totalFiles) * 100);
            updateProgressBar(progress);

            ui->outputTextEdit->clear();
        }
}


void MainWindow::on_saveButton_clicked()
{
    QString outputDirectory ="C:/ConvertFileTo_C";
    QString saveDirectory = QFileDialog::getExistingDirectory(this, "Select Directory", "", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    if (saveDirectory.isEmpty())
    {
        return;
    }

    QDir dir (outputDirectory);

    if (!dir.exists())
    {
        QMessageBox::warning(this, "Warning", "Output directory does not exist");
                return;
    }

    QStringList fileList = dir.entryList(QStringList() << "*.c", QDir::Files);

    if (fileList.isEmpty())
    {
        QMessageBox::information(this, "Information", "No files to move");
        return;
    }

    bool success = true;

    foreach (QString fileName, fileList)
    {
        QString sourceFilePath = outputDirectory + "/" + fileName;
        QString destinationFilePath = saveDirectory + "/" +fileName;

        if (QFile::exists(destinationFilePath))
        {
            if (!QFile::remove(destinationFilePath))
            {
                QMessageBox::warning(this, "warning", "Failed to remove existing file: " + destinationFilePath);
                success = false;
                break;
            }
        }

        if (!QFile::copy(sourceFilePath, destinationFilePath))
        {
            QMessageBox::warning(this, "Warning", "Failed to copy file: " + sourceFilePath + " to " + destinationFilePath);
            success = false;
            break;
        }

       if (!QFile::remove(sourceFilePath))
       {
           QMessageBox::warning(this, "Warning", "Failed to remove file: " + sourceFilePath);
           success = false;
           break;
       }
    }

    if (success)
    {
        QMessageBox::information(this, "Information", "Files moved successfully");
    }
    else
    {
        QMessageBox::warning(this, "Warning", "An error occurred while moving files");
    }

    //QString saveFileName = QFileDialog::getSaveFileName(this, "Save as", "", "C Files (*.c)");

       /* if (saveFileName.isEmpty())
        {
            return;
        } */

        //QFile file(saveFileName);

       /* if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QMessageBox::warning(this, "Warning", "Cannot save file");
            return;
        }

        QTextStream out(&file);

        out << "#include <stdint.h>\n\n";
        out << "const uint16_t image_data[] = {\n";


        QStringList lines = ui->outputTextEdit->toPlainText().split('\n');
        for (const QString &line : lines)
        {
            out << line << "\n";
        }

        out << "};\n";
        file.close(); */
}

void MainWindow::on_clearButton_clicked()
{
    fileList.clear();
    ui->fileListWidget->clear();
    ui->outputTextEdit->clear();
    ui->progressBar->setValue(0);
    updateFileCount();
}

void MainWindow::updateProgressBar(int value)
{
    ui->progressBar->setValue(value);
}

