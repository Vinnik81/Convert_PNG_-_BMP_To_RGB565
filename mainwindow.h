#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <vector>
#include <cstdint>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dropEvent(QDropEvent *event) override;

private slots:
    void on_selectFileButton_clicked();

    void on_convertButton_clicked();

    void on_saveButton_clicked();

    void on_clearButton_clicked();

    void updateProgressBar(int value);

private:
    Ui::MainWindow *ui;
    std::vector<uint16_t> data;
    QStringList fileList;

    uint16_t convertTo565(uint8_t r, uint8_t g, uint8_t b);
        void loadPNG(const char *filename, std::vector<uint16_t> &data, int &width, int &height);
        void loadBMP(const char *filename, std::vector<uint16_t> &data, int &width, int &height);
        void updateFileCount();
};
#endif // MAINWINDOW_H
